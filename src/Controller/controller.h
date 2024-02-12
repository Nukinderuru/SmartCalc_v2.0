#ifndef CPP3_SMARTCALC_V2_0_1_CONTROLLER_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_1_CONTROLLER_CONTROLLER_H_

#include <QDebug>
#include <array>
#include <iostream>
#include <string>

#include "Model/bonusmodel.h"
#include "Model/model.h"

namespace s21 {

class Controller {
 public:
  Controller();
  ~Controller();

  int CheckInput(std::string str);
  double Calculate(std::string str, long double x);
  std::pair<std::vector<double>, std::vector<double>> DrawGraphic(
      std::string const &str, double x_begin, double x_end);
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
  s21::Model model_;
  s21::BonusModel bonusModel_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_CONTROLLER_CONTROLLER_H_
