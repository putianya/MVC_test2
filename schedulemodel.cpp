#include "model/databasemanager.h"
ScheduleModel::ScheduleModel(QObject *parent) : QObject(parent)
{}

QVector<QVector<QString> >ScheduleModel::getSchedule(int year, int week)
{
    QVector<QVector<QString> > courses(7, QVector<QString>(6, ""));
    QPair<QDate, QDate> weekRange = getWeekRange(year, week);
    QDate startDate = weekRange.first;
    QDate endDate = weekRange.second;

    QSqlQuery query;

    query.prepare(
        "SELECT date, time, course_name FROM schedule WHERE date BETWEEN ? AND ?");
    query.addBindValue(startDate.toString("yyyy-MM-dd"));
    query.addBindValue(endDate.toString("yyyy-MM-dd"));

    if (query.exec()) {
        while (query.next()) {
            QDate date = QDate::fromString(query.value(0).toString(),
                                           "yyyy-MM-dd");
            QString time = query.value(1).toString();
            int     dayIndex = startDate.daysTo(date);
            int     timeIndex = times.indexOf(time);

            if ((dayIndex >= 0) && (dayIndex < 7) && (timeIndex != -1)) {
                courses[dayIndex][timeIndex] = query.value(2).toString();
            }
        }
    }
    return courses;
}

bool ScheduleModel::addCourse(const QDate  & date,
                              const QString& time,
                              const QString& courseName)
{
    QSqlQuery query;

    query.prepare(
        "INSERT INTO schedule (date, time, course_name) VALUES (?, ?, ?)");
    query.addBindValue(date.toString("yyyy-MM-dd"));
    query.addBindValue(time);
    query.addBindValue(courseName);
    return query.exec();
}

bool ScheduleModel::deleteCourse(const QDate& date, const QString& time)
{
    QSqlQuery query;

    query.prepare("DELETE FROM schedule WHERE date = ? AND time = ?");
    query.addBindValue(date.toString("yyyy-MM-dd"));
    query.addBindValue(time);
    return query.exec();
}
