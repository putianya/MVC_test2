#ifndef FINANCIALMODEL_H
#define FINANCIALMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QVector>
#include <QMap>
#include <QDate>

class FinancialModel : public QObject {
    Q_OBJECT

public:

    explicit FinancialModel(QObject *parent = nullptr);

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
};

#endif // FINANCIALMODEL_H
