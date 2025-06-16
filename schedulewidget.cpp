#include "controller/schedulecontroller.h"
#include "schedulecontroller.h"
#include <QTableWidgetItem>

void ScheduleWidget::loadSchedule()
{
    tableWidget->blockSignals(true);
    tableWidget->clearContents();

    int year = yearComboBox->currentData().toInt();
    int week = weekComboBox->currentData().toInt();

    ScheduleController controller;
    QVector<QVector<QString> > courses = controller.getSchedule(year, week);

    QPair<QDate, QDate> weekRange = getWeekRange(year, week);
    QDate startDate = weekRange.first;
    QDate endDate = weekRange.second;

    dateRangeLabel->setText(startDate.toString(
                                "yyyy-MM-dd") + "到" +
                            endDate.toString("yyyy-MM-dd"));

    for (int day = 0; day < 7; ++day) {
        for (int time = 0; time < times.count(); ++time) {
            QTableWidgetItem *item = new QTableWidgetItem(courses[day][time]);
            item->setTextAlignment(Qt::AlignCenter);
            tableWidget->setItem(day, time, item);
        }
    }

    tableWidget->blockSignals(false);
}

void ScheduleWidget::addCourse()
{
    int dayIndex = tableWidget->currentRow();
    int timeIndex = tableWidget->currentColumn();

    if ((dayIndex == -1) || (timeIndex == -1)) {
        QMessageBox::warning(this, "错误", "请先选择一个时间段！");
        return;
    }

    if (!tableWidget->item(dayIndex, timeIndex)->text().isEmpty()) {
        QMessageBox::warning(this, "错误", "该时间段已被占用！");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("添加课程");
    QFormLayout layout(&dialog);

    QComboBox nameCombo;
    QSqlQuery nameQuery("SELECT name FROM studentInfo");

    while (nameQuery.next()) nameCombo.addItem(nameQuery.value(0).toString());

    QMap<int, QTime> timePresets = {
        { 0, QTime(9,  0)            },  { 1, QTime(11, 0) }, { 2, QTime(14, 0) },
        { 3, QTime(16, 0)            },  { 4, QTime(19, 0) }, { 5, QTime(21, 0) }
    };

    QTimeEdit timeEdit;
    timeEdit.setDisplayFormat("HH:mm");
    timeEdit.setTime(timePresets.value(timeIndex));

    layout.addRow("学生姓名:", &nameCombo);
    layout.addRow("课程时间:", &timeEdit);

    QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttons.button(QDialogButtonBox::Ok)->setText("确定");
    buttons.button(QDialogButtonBox::Cancel)->setText("取消");
    layout.addRow(&buttons);

    connect(&buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted) return;

    QString courseName = QString("%1,%2").arg(nameCombo.currentText()).arg(
        timeEdit.time().toString("HH:mm"));

    int year = yearComboBox->currentData().toInt();
    int week = weekComboBox->currentData().toInt();
    QPair<QDate, QDate> weekRange = getWeekRange(year, week);

    QDate   currentDate = weekRange.first.addDays(dayIndex);
    QString timeSlot = times[timeIndex];

    ScheduleController controller;

    if (controller.addCourse(currentDate, timeSlot, courseName)) {
        loadSchedule();
    } else {
        QMessageBox::critical(this, "错误", "添加失败");
    }
}
