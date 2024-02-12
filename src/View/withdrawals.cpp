#include "withdrawals.h"

namespace s21 {
Withdrawals::Withdrawals() {
  main_layout_ = new QGridLayout();

  m_withdrawal_date_ = new QLabel();
  m_withdrawal_date_->setText("Date:");
  m_withdrawal_amount_ = new QLabel;
  m_withdrawal_amount_->setText("Amount:");

  add_withdrawal_button_ = CreateButton("Add +", SLOT(AddButtonClicked()));
  ok_button_ = CreateButton("OK", SLOT(OkButtonClicked()));

  m_withdrawal_dates_[withdrawal] = new QLineEdit();
  m_withdrawal_amounts_[withdrawal] = new QLineEdit();

  main_layout_->setSizeConstraint(QLayout::SetFixedSize);

  QFont font = m_withdrawal_date_->font();
  font.setPointSize(font.pointSize() + 5);
  m_withdrawal_date_->setFont(font);
  m_withdrawal_amount_->setFont(font);
  m_withdrawal_dates_[withdrawal]->setFont(font);
  m_withdrawal_amounts_[withdrawal]->setFont(font);

  m_withdrawal_date_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_withdrawal_amount_->setStyleSheet("QLabel {color: #ACFF83;}");
  add_withdrawal_button_->setStyleSheet(
      "QToolButton {color: #FF8800; background: #232522;}");
  ok_button_->setStyleSheet(
      "QToolButton {color: #FF8800; background: #232522;}");
  m_withdrawal_dates_[withdrawal]->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_withdrawal_amounts_[withdrawal]->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");

  main_layout_->addWidget(m_withdrawal_date_, 0, 0, 1, 5);
  main_layout_->addWidget(m_withdrawal_amount_, 0, 6, 1, 5);
  main_layout_->addWidget(m_withdrawal_dates_[withdrawal], 1, 0, 1, 5);
  main_layout_->addWidget(m_withdrawal_amounts_[withdrawal], 1, 6, 1, 5);
  main_layout_->addWidget(add_withdrawal_button_, 2, 0, 1, 5);
  main_layout_->addWidget(ok_button_, 2, 5, 1, 5);

  setLayout(main_layout_);
  setWindowTitle("Withdrawals");
}

void Withdrawals::AddButtonClicked() {
  withdrawals_line_++;
  withdrawal++;
  m_withdrawal_dates_[withdrawal] = new QLineEdit();
  m_withdrawal_amounts_[withdrawal] = new QLineEdit();
  m_withdrawal_dates_[withdrawal]->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_withdrawal_amounts_[withdrawal]->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  QFont font = m_withdrawal_date_->font();
  m_withdrawal_dates_[withdrawal]->setFont(font);
  m_withdrawal_amounts_[withdrawal]->setFont(font);
  main_layout_->addWidget(m_withdrawal_dates_[withdrawal], withdrawals_line_, 0,
                          1, 5);
  main_layout_->addWidget(m_withdrawal_amounts_[withdrawal], withdrawals_line_,
                          6, 1, 5);
  main_layout_->addWidget(add_withdrawal_button_, withdrawals_line_ + 1, 0, 1,
                          5);
  main_layout_->addWidget(ok_button_, withdrawals_line_ + 1, 5, 1, 5);
}

void Withdrawals::OkButtonClicked() {
  for (int i = 0; i <= withdrawal; i++) {
    input_withdrawal_dates[i] =
        QDate::fromString(m_withdrawal_dates_[i]->text(), "dd.MM.yyyy");
  }
  for (int i = 0; i <= withdrawal; i++) {
    input_withdrawal_amounts[i] = m_withdrawal_amounts_[i]->text().toDouble();
  }
}

Button *Withdrawals::CreateButton(const QString &text, const char *member) {
  Button *btn = new Button(text);
  connect(btn, SIGNAL(clicked()), this, member);
  return btn;
}
}  // namespace s21
