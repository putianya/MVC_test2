#include "controller/studentcontroller.h"
#include <QTableWidgetItem>

void StudentInfoWidget::refreshTable()
{
    ui->tableWidget->blockSignals(true);
    ui->tableWidget->setRowCount(0);

    StudentController controller;
    QVector<QMap<QString, QVariant> > students = controller.getAllStudents();

    for (const auto& student : students) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);

            if (col == ui->tableWidget->columnCount() - 1) {
                QByteArray photoData = student["photo"].toByteArray();

                if (!photoData.isEmpty()) {
                    QPixmap photo;
                    photo.loadFromData(photoData);
                    item->setData(Qt::DecorationRole,
                                                photo.scaled(100, 100,
                                               Qt::KeepAspectRatio));
                    item->setData(Qt::UserRole, photoData);
                }
            } else {
                item->setText(student[ui->tableWidget->horizontalHeaderItem(col)->
                                      text()].toString());
            }

            ui->tableWidget->setItem(row, col, item);
        }
    }

    ui->tableWidget->blockSignals(false);
}
