#include "controller/financialcontroller.h"
#include "financialcontroller.h"
#include <QTableWidgetItem>

void FinancialWidget::loadFinancialRecords()
{
    tableWidget->setRowCount(0);

    QString studentId = studentComboBox->currentData().toString();
    QDate   startDate = startDateEdit->date();
    QDate   endDate = endDateEdit->date();

    FinancialController controller;
    QVector<QMap<QString, QVariant> > records = controller.getFinancialRecords(
        studentId,
        startDate,
        endDate);

    for (const auto& record : records) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        for (int col = 0; col < 6; ++col) {
            QTableWidgetItem *item =
                new QTableWidgetItem(record[tableWidget->horizontalHeaderItem(col)
                                            ->
                                            text()].toString());
            item->setTextAlignment(Qt::AlignCenter);
            tableWidget->setItem(row, col, item);
        }
    }

    tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    updateChart();
    updatePieChart();
}

void FinancialWidget::addRecord()
{
    QDialog dialog(this);

    dialog.setWindowTitle("添加缴费记录");
    QFormLayout form(&dialog);

    QComboBox *studentNameComboBox = new QComboBox(&dialog);
    QSqlQuery  query("SELECT id, name FROM studentInfo");

    while (query.next()) {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        studentNameComboBox->addItem(name, QVariant(id));
    }
    QDateEdit *paymentDateEdit = new QDateEdit(&dialog);
    paymentDateEdit->setDate(QDate::currentDate());
    paymentDateEdit->setCalendarPopup(true);

    QLineEdit *amountEdit = new QLineEdit(&dialog);
    QLineEdit *feeTypeEdit = new QLineEdit(&dialog);
    QLineEdit *remarkEdit = new QLineEdit(&dialog);

    form.addRow("学生名称:", studentNameComboBox);
    form.addRow("缴费日期:", paymentDateEdit);
    form.addRow(  "金额:", amountEdit);
    form.addRow("支付类型:", feeTypeEdit);
    form.addRow(  "备注:", remarkEdit);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal,
                               &dialog);
    buttonBox.button(QDialogButtonBox::Ok)->setText("确定");
    buttonBox.button(QDialogButtonBox::Cancel)->setText("取消");
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox,
                     &QDialogButtonBox::accepted,
                     &dialog,
                     &QDialog::accept);
    QObject::connect(&buttonBox,
                     &QDialogButtonBox::rejected,
                     &dialog,
                     &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString studentId = studentNameComboBox->currentData().toString();
        QDate   paymentDate = paymentDateEdit->date();
        double  amount = amountEdit->text().toDouble();
        QString feeType = feeTypeEdit->text();
        QString remark = remarkEdit->text();

        FinancialController controller;

        if (controller.addRecord(studentId, paymentDate, amount, feeType,
                                 remark)) {
            qDebug() << "记录添加成功！";
            loadFinancialRecords();
        } else {
            qDebug() << "添加记录失败";
        }
    }
}
