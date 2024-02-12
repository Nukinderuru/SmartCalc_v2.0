#ifndef CPP3_SMARTCALC_V2_0_1_MODEL_BONUSMODEL_H_
#define CPP3_SMARTCALC_V2_0_1_MODEL_BONUSMODEL_H_

#include <math.h>

#include <QDate>
#include <QDebug>
#include <QVector>
#include <algorithm>
#include <array>
#include <stack>
#include <string>

namespace s21 {

typedef struct CreditResult {
  double sum;
  double overpayment;
  double total;
  double last_sum;
  int type;
} CreditResult;

typedef struct DepositResult {
  double accrued_interest;
  double tax_amount;
  double total_sum;
} DepositResult;
class BonusModel {
 public:
  BonusModel();

  CreditResult GetCreditResult(int credit, int months, int interest, int type);
  DepositResult GetDepositResult(
      int periodicity, QDate date_start, QDate date_end, long double sum,
      long double interest, bool replenishments, int replenishment,
      std::array<QDate, 100> input_replenishment_dates,
      std::array<long double, 100> input_replenishment_amounts,
      bool withdrawals, int withdrawal,
      std::array<QDate, 100> input_withdrawal_dates,
      std::array<long double, 100> input_withdrawal_amounts, double tax_rate);

 private:
  int CountDays(QDate current_date, int periodicity);
  long double CalculateTaxes(long double yearly_income, double tax_rate);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_MODEL_BONUSMODEL_H_
