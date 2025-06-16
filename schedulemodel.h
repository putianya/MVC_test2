#ifndef SCHEDULEMODEL_H
#define SCHEDULEMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QVector>
#include <QMap>
#include <QDate>

class ScheduleModel : public QObject {
    Q_OBJECT

public:

    explicit ScheduleModel(QObject *parent = nullptr);

    QVector<QVector<QString> >getSchedule(int year,
                                          int week);
    bool                      addCourse(const QDate  & date,
                                        const QString& time,
                                        const QString& courseName);
    bool                      deleteCourse(const QDate  & date,
                                           const QString& time);

signals:

public slots:

private:
};

#endif // SCHEDULEMODEL_H
