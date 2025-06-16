#include "model/schedulemodel.h"

ScheduleController::ScheduleController(QObject *parent) : QObject(parent)
{
    m_model = new ScheduleModel(this);
}

QVector<QVector<QString> >ScheduleController::getSchedule(int year, int week)
{
    return m_model->getSchedule(year, week);
}

bool ScheduleController::addCourse(const QDate  & date,
                                   const QString& time,
                                   const QString& courseName)
{
    return m_model->addCourse(date, time, courseName);
}

bool ScheduleController::deleteCourse(const QDate& date, const QString& time)
{
    return m_model->deleteCourse(date, time);
}
