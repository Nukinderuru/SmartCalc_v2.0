#include "deposit.h"

namespace s21 {
Deposit::Deposit() {
  main_layout_ = new QGridLayout();

  m_sum_ = new QLabel();
  m_sum_->setText("The whole sum:");
  m_start_date_ = new QLabel();
  m_start_date_->setText("The starting date:");
  m_term_ = new QLabel();
  m_term_->setText("Term:");
  m_interest_ = new QLabel();
  m_interest_->setText("Interest rate (%):");
  m_tax_rate_ = new QLabel();
  m_tax_rate_->setText("Tax rate:");
  m_periodicity_ = new QLabel();
  m_periodicity_->setText("Periodicity:");
  m_capitalization_ = new QLabel();
  m_capitalization_->setText("Capitalization:");

  m_display_sum_ = new QLineEdit();
  m_display_date_ = new QLineEdit();
  m_display_term_ = new QLineEdit();
  m_display_term_in_ = new QComboBox();
  m_display_term_in_->addItem("days");
  m_display_term_in_->addItem("months");
  m_display_term_in_->addItem("years");
  m_display_interest_ = new QLineEdit();
  m_display_tax_rate_ = new QLineEdit();
  m_display_periodicity_ = new QComboBox();
  m_display_periodicity_->addItem("Every day");
  m_display_periodicity_->addItem("Every week");
  m_display_periodicity_->addItem("Every month");
  m_display_periodicity_->addItem("Every quarter");
  m_display_periodicity_->addItem("Twice a year");
  m_display_periodicity_->addItem("Once a year");
  m_display_periodicity_->addItem("At the end of the term");

  m_replenishments_ = new QLabel();
  m_replenishments_->setText("Replenishments:");
  add_replenishment_button_ =
      CreateButton("Add +", SLOT(AddReplenishmantClicked()));
  m_withdrawals_ = new QLabel();
  m_withdrawals_->setText("Withdrawals:");
  add_withdrawal_button_ = CreateButton("Add +", SLOT(AddWithdrawalClicked()));

  m_accrued_interest_ = new QLabel();
  m_accrued_interest_->setText("Accrued interest:");
  m_tax_amount_ = new QLabel();
  m_tax_amount_->setText("Tax amount:");
  m_total_payment_ = new QLabel();
  m_total_payment_->setText("Total payment:");

  m_accrued_interest_response_ = new QLabel();
  m_tax_amount_response_ = new QLabel();
  m_total_payment_response_ = new QLabel();

  m_capitalization_yes_ = new QRadioButton("Yes");
  connect(m_capitalization_yes_, &QRadioButton::clicked,
          [=]() { this->CapitalizationYesClicked(); });
  m_capitalization_no_ = new QRadioButton("No");
  connect(m_capitalization_no_, &QRadioButton::clicked,
          [=]() { this->CapitalizationNoClicked(); });

  m_calculate_ = new QLabel();

  main_layout_->setSizeConstraint(QLayout::SetFixedSize);

  m_display_sum_->setAlignment(Qt::AlignRight);
  m_display_date_->setAlignment(Qt::AlignRight);
  m_display_term_->setAlignment(Qt::AlignRight);
  m_display_interest_->setAlignment(Qt::AlignRight);
  m_display_tax_rate_->setAlignment(Qt::AlignRight);

  m_accrued_interest_response_->setAlignment(Qt::AlignRight);
  m_total_payment_response_->setAlignment(Qt::AlignRight);
  m_tax_amount_response_->setAlignment(Qt::AlignRight);

  QFont font = m_display_sum_->font();
  font.setPointSize(font.pointSize() + 5);
  m_display_sum_->setFont(font);
  m_display_date_->setFont(font);
  m_display_term_->setFont(font);
  m_display_term_in_->setFont(font);
  m_display_interest_->setFont(font);
  m_display_tax_rate_->setFont(font);
  m_display_periodicity_->setFont(font);
  m_sum_->setFont(font);
  m_start_date_->setFont(font);
  m_term_->setFont(font);
  m_interest_->setFont(font);
  m_tax_rate_->setFont(font);
  m_periodicity_->setFont(font);
  m_capitalization_->setFont(font);
  m_replenishments_->setFont(font);
  m_withdrawals_->setFont(font);
  m_accrued_interest_->setFont(font);
  m_accrued_interest_response_->setFont(font);
  m_tax_amount_->setFont(font);
  m_tax_amount_response_->setFont(font);
  m_total_payment_->setFont(font);
  m_total_payment_response_->setFont(font);
  m_capitalization_yes_->setFont(font);
  m_capitalization_no_->setFont(font);

  m_display_sum_->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_display_date_->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_display_term_->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_display_term_in_->setStyleSheet(
      "QComboBox {color: #ACFF83; background: #232522;}");
  m_display_interest_->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_display_tax_rate_->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_display_periodicity_->setStyleSheet(
      "QComboBox {color: #ACFF83; background: #232522;}");

  m_sum_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_start_date_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_term_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_interest_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_tax_rate_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_periodicity_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_capitalization_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_replenishments_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_withdrawals_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_replenishments_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_withdrawals_->setStyleSheet("QLabel {color: #ACFF83;}");
  add_replenishment_button_->setStyleSheet(
      "QToolButton {color: #FF8800; background: #232522;}");
  add_withdrawal_button_->setStyleSheet(
      "QToolButton {color: #FF8800; background: #232522;}");
  m_accrued_interest_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_tax_amount_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_total_payment_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_capitalization_yes_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_capitalization_no_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_accrued_interest_response_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_tax_amount_response_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_total_payment_response_->setStyleSheet("QLabel {color: #ACFF83;}");

  m_capitalization_yes_->setStyleSheet("QRadioButton {color: #ACFF83;}");
  m_capitalization_yes_->setChecked(true);
  m_capitalization_no_->setStyleSheet("QRadioButton {color: #ACFF83;}");

  calc_button_ = CreateButton("Calculate!", SLOT(ButtonClicked()));
  calc_button_->setStyleSheet(
      "QToolButton {color: #FF8800; background: #232522;}");

  main_layout_->addWidget(m_sum_, 0, 0, 1, 5);
  main_layout_->addWidget(m_display_sum_, 0, 10, 1, 5);
  main_layout_->addWidget(m_start_date_, 1, 0, 1, 5);
  main_layout_->addWidget(m_display_date_, 1, 10, 1, 5);
  main_layout_->addWidget(m_term_, 2, 0, 1, 5);
  main_layout_->addWidget(m_display_term_, 2, 5, 1, 5);
  main_layout_->addWidget(m_display_term_in_, 2, 10, 1, 5);
  main_layout_->addWidget(m_interest_, 3, 0, 1, 5);
  main_layout_->addWidget(m_display_interest_, 3, 10, 1, 5);
  main_layout_->addWidget(m_tax_rate_, 4, 0, 1, 5);
  main_layout_->addWidget(m_display_tax_rate_, 4, 10, 1, 5);
  main_layout_->addWidget(m_periodicity_, 5, 0, 1, 5);
  main_layout_->addWidget(m_display_periodicity_, 5, 10, 1, 5);
  main_layout_->addWidget(m_capitalization_, 6, 0, 1, 5);
  main_layout_->addWidget(m_capitalization_yes_, 6, 5, 1, 2);
  main_layout_->addWidget(m_capitalization_no_, 6, 10, 1, 2);
  main_layout_->addWidget(m_replenishments_, 7, 0, 1, 6);
  main_layout_->addWidget(add_replenishment_button_, 7, 10, 1, 5);
  main_layout_->addWidget(m_withdrawals_, 8, 0, 1, 5);
  main_layout_->addWidget(add_withdrawal_button_, 8, 10, 1, 5);

  main_layout_->addWidget(calc_button_, 9, 3, 1, 10);

  main_layout_->addWidget(m_accrued_interest_, 10, 0, 1, 4);
  main_layout_->addWidget(m_accrued_interest_response_, 10, 10, 1, 5);
  main_layout_->addWidget(m_tax_amount_, 11, 0, 1, 4);
  main_layout_->addWidget(m_tax_amount_response_, 11, 10, 1, 5);
  main_layout_->addWidget(m_total_payment_, 12, 0, 1, 4);
  main_layout_->addWidget(m_total_payment_response_, 12, 10, 1, 5);

  setLayout(main_layout_);
  setWindowTitle("Deposit");
}

void Deposit::ButtonClicked() {
  Calculate();
  m_accrued_interest_response_->setText(
      QString::number(result_.accrued_interest, 'f', 2));
  m_total_payment_response_->setText(
      QString::number(result_.total_sum, 'f', 2));
  m_tax_amount_response_->setText(QString::number(result_.tax_amount, 'f', 2));
}

void Deposit::CapitalizationYesClicked() { capitalization_ = 1; }

void Deposit::CapitalizationNoClicked() {
  capitalization_ = 0;
  m_display_periodicity_->setCurrentIndex(6);
}

void Deposit::AddReplenishmantClicked() {
  r_ = new s21::Replenishments();
  r_->setStyleSheet("background-color:black;");
  r_->show();
  replenishments_ = 1;
}

void Deposit::AddWithdrawalClicked() {
  w_ = new s21::Withdrawals();
  w_->setStyleSheet("background-color:black;");
  w_->show();
  withdrawals_ = 1;
}

Button *Deposit::CreateButton(const QString &text, const char *member) {
  Button *btn = new Button(text);
  connect(btn, SIGNAL(clicked()), this, member);
  return btn;
}

void Deposit::Calculate() {
  long double sum = (long double)m_display_sum_->text().toDouble();
  long double interest =
      (long double)m_display_interest_->text().toDouble() / 100;
  QDate dateStart = QDate::fromString(m_display_date_->text(), "dd.MM.yyyy");
  int term = m_display_term_->text().toInt();
  QDate date_end;
  if (m_display_term_in_->currentIndex() == 0)
    date_end = dateStart.addDays(term);
  else if (m_display_term_in_->currentIndex() == 1)
    date_end = dateStart.addMonths(term);
  else if (m_display_term_in_->currentIndex() == 2)
    date_end = dateStart.addYears(term);

  int periodicity = m_display_periodicity_->currentIndex();
  double taxRate = m_display_tax_rate_->text().toDouble();

  s21::Controller controller;
  int replenishment;
  int withdrawal;
  std::array<QDate, 100> input_replenishment_dates;
  std::array<long double, 100> input_replenishment_amounts;
  std::array<QDate, 100> input_withdrawal_dates;
  std::array<long double, 100> input_withdrawal_amounts;
  if (replenishments_) {
    replenishment = r_->replenishment;
    input_replenishment_dates = r_->input_replenishment_dates;
    input_replenishment_amounts = r_->input_replenishment_amounts;
  }
  if (withdrawals_) {
    withdrawal = w_->withdrawal;
    input_withdrawal_dates = w_->input_withdrawal_dates;
    input_withdrawal_amounts = w_->input_withdrawal_amounts;
  }
  result_ = controller.GetDepositResult(
      periodicity, dateStart, date_end, sum, interest, replenishments_,
      replenishment, input_replenishment_dates, input_replenishment_amounts,
      withdrawals_, withdrawal, input_withdrawal_dates,
      input_withdrawal_amounts, taxRate);
}

}  // namespace s21
