#include "model/studentmodel.h"

StudentController::StudentController(QObject *parent) : QObject(parent)
{
    m_model = new StudentModel(this);
}

QVector<QMap<QString, QVariant> >StudentController::getAllStudents()
{
    return m_model->getAllStudents();
}

bool StudentController::addStudent(const QMap<QString, QVariant>& studentData)
{
    return m_model->addStudent(studentData);
}

bool StudentController::updateStudent(int id,
                                      const QMap<QString, QVariant>& studentData)
{
    return m_model->updateStudent(id, studentData);
}

bool StudentController::deleteStudent(int id)
{
    return m_model->deleteStudent(id);
}
