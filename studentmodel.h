#ifndef STUDENTMODEL_H
#define STUDENTMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QVector>
#include <QMap>

class StudentModel : public QObject {
    Q_OBJECT

public:

    explicit StudentModel(QObject *parent = nullptr);

    QVector<QMap<QString, QVariant> >getAllStudents();
    bool                             addStudent(const QMap<QString,
                                                           QVariant>& studentData);
    bool                             updateStudent(int                   id,
                                                   const QMap<QString,
                                                              QVariant>& studentData);
    bool                             deleteStudent(int id);

signals:

public slots:

private:
};

#endif // STUDENTMODEL_H
