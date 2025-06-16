#ifndef SCHEDULECONTROLLER_H
#define SCHEDULECONTROLLER_H

#include <QObject>
#include "schedulemodel.h"

class ScheduleController : public QObject {
    Q_OBJECT

public:

    explicit ScheduleController(QObject *parent = nullptr);

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

    ScheduleModel *m_model;
};

#endif // SCHEDULECONTROLLER_H
