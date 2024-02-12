#include "controller.h"

namespace s21 {
Controller::Controller() {}

Controller::~Controller() {}

int Controller::CheckInput(std::string str) {
  return this->model_.CheckInput(str);
}

double Controller::Calculate(std::string str, long double x) {
  return this->model_.GetResult(str, x);
}

std::pair<std::vector<double>, std::vector<double> > Controller::DrawGraphic(
    const std::string &str, double x_begin, double x_end) {
  return this->model_.DrawGraphic(str, x_begin, x_end);
}

CreditResult Controller::GetCreditResult(int credit, int months, int interest,
                                         int type) {
  return this->bonusModel_.GetCreditResult(credit, months, interest, type);
}

DepositResult Controller::GetDepositResult(
    int periodicity, QDate date_start, QDate date_end, long double sum,
    long double interest, bool replenishments, int replenishment,
    std::array<QDate, 100> input_replenishment_dates,
    std::array<long double, 100> input_replenishment_amounts, bool withdrawals,
    int withdrawal, std::array<QDate, 100> input_withdrawal_dates,
    std::array<long double, 100> input_withdrawal_amounts, double tax_rate) {
  return this->bonusModel_.GetDepositResult(
      periodicity, date_start, date_end, sum, interest, replenishments,
      replenishment, input_replenishment_dates, input_replenishment_amounts,
      withdrawals, withdrawal, input_withdrawal_dates, input_withdrawal_amounts,
      tax_rate);
}
}  // namespace s21
