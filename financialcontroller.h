#ifndef FINANCIALCONTROLLER_H
#define FINANCIALCONTROLLER_H

#include <QObject>
#include "financialmodel.h"

class FinancialController : public QObject {
    Q_OBJECT

public:

    explicit FinancialController(QObject *parent = nullptr);

    QVector<QMap<QString, QVariant> >getFinancialRecords(const QString& studentId,
                                                         const QDate  & startDate,
                                                         const QDate  & endDate);
    bool                             addRecord(const QString& studentId,
                                               const QDate  & paymentDate,
                                               double         amount,
                                               const QString& paymentType,
                                               const QString& notes);
    bool updateRecord(int            id,
                      const QString& studentId,
                      const QDate  & paymentDate,
                      double         amount,
                      const QString& paymentType,
                      const QString& notes);
    bool deleteRecord(int id);

signals:

public slots:

private:

    FinancialModel *m_model;
};

#endif // FINANCIALCONTROLLER_H
