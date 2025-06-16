#ifndef STUDENTCONTROLLER_H
#define STUDENTCONTROLLER_H

#include <QObject>
#include "studentmodel.h"

class StudentController : public QObject {
    Q_OBJECT

public:

    explicit StudentController(QObject *parent = nullptr);

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

    StudentModel *m_model;
};

#endif // STUDENTCONTROLLER_H
