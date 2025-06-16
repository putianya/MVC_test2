#include "model/databasemanager.h"
StudentModel::StudentModel(QObject *parent) : QObject(parent)
{}

QVector<QMap<QString, QVariant> >StudentModel::getAllStudents()
{
    QVector<QMap<QString, QVariant> > students;
    QSqlQuery query("SELECT * FROM studentInfo");

    while (query.next()) {
        QMap<QString, QVariant> student;

        for (int i = 0; i < query.record().count(); ++i) {
            student[query.record().fieldName(i)] = query.value(i);
        }
        students.append(student);
    }
    return students;
}

bool StudentModel::addStudent(const QMap<QString, QVariant>& studentData)
{
    QSqlQuery query;
    QString   fields;
    QString   values;
    QList<QVariant> bindValues;

    for (auto it = studentData.begin(); it != studentData.end(); ++it) {
        if (!fields.isEmpty()) {
            fields += ", ";
            values += ", ";
        }
        fields += it.key();
        values += "?";
        bindValues.append(it.value());
    }
    QString queryStr = QString("INSERT INTO studentInfo (%1) VALUES (%2)").arg(
        fields).arg(values);
    query.prepare(queryStr);

    for (const auto& value : bindValues) {
        query.addBindValue(value);
    }
    return query.exec();
}

bool StudentModel::updateStudent(int id,
                                 const QMap<QString, QVariant>& studentData)
{
    QSqlQuery query;
    QString   setClause;
    QList<QVariant> bindValues;

    for (auto it = studentData.begin(); it != studentData.end(); ++it) {
        if (!setClause.isEmpty()) {
            setClause += ", ";
        }
        setClause += QString("%1 = ?").arg(it.key());
        bindValues.append(it.value());
    }
    QString queryStr = QString("UPDATE studentInfo SET %1 WHERE id = ?").arg(
        setClause);
    query.prepare(queryStr);

    for (const auto& value : bindValues) {
        query.addBindValue(value);
    }
    query.addBindValue(id);
    return query.exec();
}

bool StudentModel::deleteStudent(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM studentInfo WHERE id = ?");
    query.addBindValue(id);
    return query.exec();
}
