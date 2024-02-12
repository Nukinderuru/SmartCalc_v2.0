#include "bonusmodel.h"

namespace s21 {
BonusModel::BonusModel() {}

CreditResult BonusModel::GetCreditResult(int credit, int months, int interest,
                                         int type) {
  CreditResult result = {0, 0, 0, 0, 0};
  double hundredth_interest = 0.0;
  hundredth_interest = (static_cast<double>(interest) / 12.0) / 100.0;
  if (type == 1) {
    result.sum =
        static_cast<double>(credit) *
        (hundredth_interest +
         (hundredth_interest / (pow((1 + hundredth_interest), months) - 1)));
    result.total = result.sum * static_cast<double>(months);
    result.overpayment = result.total - static_cast<double>(credit);
  } else if (type == 2) {
    result.overpayment = 0.0;
    double fixed = credit / static_cast<double>(months);
    double remain = static_cast<double>(credit);
    for (int i = 0; i < months; i++) {
      double month_interest = remain * hundredth_interest;
      result.overpayment += month_interest;
      remain -= fixed;
      if (i == 0) result.sum = fixed + month_interest;
      if (i == months - 1) result.last_sum = fixed + month_interest;
    }
    result.total = credit + result.overpayment;
  }
  return result;
}

DepositResult BonusModel::GetDepositResult(
    int periodicity, QDate date_start, QDate date_end, long double sum,
    long double interest, bool replenishments, int replenishment,
    std::array<QDate, 100> input_replenishment_dates,
    std::array<long double, 100> input_replenishment_amounts, bool withdrawals,
    int withdrawal, std::array<QDate, 100> input_withdrawal_dates,
    std::array<long double, 100> input_withdrawal_amounts, double tax_rate) {
  DepositResult result = {0, 0, 0};
  int days = 0;
  if (periodicity == 6)
    days = date_start.daysTo(date_end);
  else
    days = CountDays(date_start, periodicity);

  QDate payment_day = date_start;
  if (periodicity > 0) payment_day = payment_day.addDays(days);

  long double ai = 0.0;
  long double whole_income = 0.0;
  long double yearly_income = 0.0;
  long double yearly_ai = 0.0;
  long double subtract_ai = 0.0;
  long double taxes_sum = 0.0;
  long double index =
      (QDate::isLeapYear(date_start.year())) ? 1 / 366.0 : 1 / 365.0;
  for (QDate curr = date_start; curr < date_end; curr = curr.addDays(1)) {
    if (replenishments) {
      for (int i = 0; i <= replenishment; i++) {
        if (input_replenishment_dates[i] == curr) {
          sum += input_replenishment_amounts[i];
        }
      }
    }
    if (withdrawals) {
      for (int i = 0; i <= withdrawal; i++) {
        if (input_withdrawal_dates[i] == curr) {
          sum -= input_withdrawal_amounts[i];
        }
      }
    }
    if (curr.day() == 1 && curr.month() == 1) {
      index = (QDate::isLeapYear(curr.year())) ? 1 / 366.0 : 1 / 365.0;
      yearly_ai = 0.0;
    }
    if (periodicity == 0) ai += sum * interest * index;
    if (curr == payment_day) {
      sum += ai;
      result.accrued_interest += ai;
      yearly_ai += ai;
      if (periodicity > 1 && periodicity < 6)
        days = CountDays(curr, periodicity);
      payment_day = payment_day.addDays(days);
      ai = 0.0;
    }
    if (periodicity > 0) ai += sum * interest * index;

    if (curr.addDays(1) == date_end) {
      sum += ai;
      result.accrued_interest += ai;
      yearly_ai += ai;
      ai = 0.0;
    }

    if ((curr.day() == 31 && curr.month() == 12) ||
        curr.addDays(1) == date_end) {
      yearly_income = yearly_ai + ai - subtract_ai;
      subtract_ai = ai;
      long double tax = CalculateTaxes(yearly_income, tax_rate);
      taxes_sum += tax;
      whole_income += yearly_income;
    }
  }
  result.tax_amount = taxes_sum;
  result.total_sum = sum;
  return result;
}

int BonusModel::CountDays(QDate current_date, int periodicity) {
  int days = 0;
  QDate next_term;
  next_term.setDate(current_date.year(), current_date.month(),
                    current_date.day());
  switch (periodicity) {
    case 0:
      days = 1;
      break;
    case 1:
      days = 7;
      break;
    case 2:
      days = current_date.daysInMonth();
      break;
    case 3:
      next_term = next_term.addMonths(3);
      days = current_date.daysTo(next_term);
      break;
    case 4:
      next_term = next_term.addMonths(6);
      days = current_date.daysTo(next_term);
      break;
    case 5:
      next_term = next_term.addYears(1);
      days = current_date.daysTo(next_term);
      break;
  }
  return days;
}

long double BonusModel::CalculateTaxes(long double yearly_income,
                                       double tax_rate) {
  double not_obliged = 1000000 * (tax_rate / 100.0);
  long double tax = 0.0;
  if (yearly_income > not_obliged) {
    tax = (yearly_income - not_obliged) * 0.13;
  }
  return tax;
}

}  // namespace s21
