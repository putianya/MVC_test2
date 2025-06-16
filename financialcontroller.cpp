#include "model/financialmodel.h"

FinancialController::FinancialController(QObject *parent) : QObject(parent)
{
    m_model = new FinancialModel(this);
}

QVector<QMap<QString, QVariant> >FinancialController::getFinancialRecords(
    const QString& studentId,
    const QDate  & startDate,
    const QDate  & endDate)
{
    return m_model->getFinancialRecords(studentId, startDate, endDate);
}

bool FinancialController::addRecord(const QString& studentId,
                                    const QDate  & paymentDate,
                                    double         amount,
                                    const QString& paymentType,
                                    const QString& notes)
{
    return m_model->addRecord(studentId, paymentDate, amount, paymentType, notes);
}

bool FinancialController::updateRecord(int            id,
                                       const QString& studentId,
                                       const QDate  & paymentDate,
                                       double         amount,
                                       const QString& paymentType,
                                       const QString& notes)
{
    return m_model->updateRecord(id,
                                 studentId,
                                 paymentDate,
                                 amount,
                                 paymentType,
                                 notes);
}

bool FinancialController::deleteRecord(int id)
{
    return m_model->deleteRecord(id);
}
