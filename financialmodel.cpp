#include "model/databasemanager.h"
FinancialModel::FinancialModel(QObject *parent) : QObject(parent)
{}

QVector<QMap<QString, QVariant> >FinancialModel::getFinancialRecords(
    const QString& studentId,
    const QDate  & startDate,
    const QDate  & endDate)
{
    QVector<QMap<QString, QVariant> > records;
    QString queryStr = QString(
        "SELECT fr.id, s.name, fr.payment_date, fr.amount, fr.payment_type, fr.notes "
        "FROM financialRecords fr "
        "JOIN studentInfo s ON fr.student_id = s.id "
        "WHERE fr.payment_date BETWEEN '%1' AND '%2' %3"
        ).arg(startDate.toString("yyyy-MM-dd"),
              endDate.toString("yyyy-MM-dd"),
              (studentId !=
               "-1") ? QString("AND fr.student_id = '%1'").arg(studentId) : "");

    QSqlQuery query(queryStr);

    while (query.next()) {
        QMap<QString, QVariant> record;

        for (int i = 0; i < query.record().count(); ++i) {
            record[query.record().fieldName(i)] = query.value(i);
        }
        records.append(record);
    }
    return records;
}

bool FinancialModel::addRecord(const QString& studentId,
                               const QDate  & paymentDate,
                               double         amount,
                               const QString& paymentType,
                               const QString& notes)
{
    QSqlQuery query;

    query.prepare(
        "INSERT INTO financialRecords (student_id, payment_date, amount, payment_type, notes) VALUES (:student_id, :payment_date, :amount, :payment_type, :notes)");
    query.bindValue(":student_id",   studentId);
    query.bindValue(":payment_date", paymentDate.toString("yyyy-MM-dd"));
    query.bindValue(":amount",       amount);
    query.bindValue(":payment_type", paymentType);
    query.bindValue(":notes",        notes);
    return query.exec();
}

bool FinancialModel::updateRecord(int            id,
                                  const QString& studentId,
                                  const QDate  & paymentDate,
                                  double         amount,
                                  const QString& paymentType,
                                  const QString& notes)
{
    QSqlQuery query;

    query.prepare(
        "UPDATE financialRecords SET student_id = ?, payment_date = ?, amount = ?, payment_type = ?, notes = ? WHERE id = ?");
    query.addBindValue(studentId);
    query.addBindValue(paymentDate.toString("yyyy-MM-dd"));
    query.addBindValue(amount);
    query.addBindValue(paymentType);
    query.addBindValue(notes);
    query.addBindValue(id);
    return query.exec();
}

bool FinancialModel::deleteRecord(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM financialRecords WHERE id = ?");
    query.addBindValue(id);
    return query.exec();
}
