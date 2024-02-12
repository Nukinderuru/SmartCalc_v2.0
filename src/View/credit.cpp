#include "credit.h"

namespace s21 {
Credit::Credit() {
  QGridLayout *mainLayout = new QGridLayout();

  m_sum_ = new QLabel();
  m_sum_->setText("The whole sum:");
  m_term_ = new QLabel();
  m_term_->setText("Amount of months:");
  m_interest_ = new QLabel();
  m_interest_->setText("Interest rate (%):");

  m_display_sum_ = new QLineEdit();
  m_display_term_ = new QLineEdit();
  m_display_interest_ = new QLineEdit();

  m_monthly_payment_ = new QLabel();
  m_monthly_payment_->setText("Monthly payment:");
  m_overpayment_ = new QLabel();
  m_overpayment_->setText("Overpayment:");
  m_total_payment_ = new QLabel();
  m_total_payment_->setText("Total payment:");

  m_monthly_payment_response_ = new QLabel();
  m_overpayment_response_ = new QLabel();
  m_total_payment_response_ = new QLabel();

  m_ann_ = new QRadioButton("Annuity");
  connect(m_ann_, &QRadioButton::clicked, [=]() { this->AnnCreditClicked(); });
  m_diff_ = new QRadioButton("Differentiated");
  connect(m_diff_, &QRadioButton::clicked,
          [=]() { this->DiffCreditClicked(); });

  m_calculate_ = new QLabel();

  mainLayout->setSizeConstraint(QLayout::SetFixedSize);

  m_display_sum_->setAlignment(Qt::AlignRight);
  m_display_term_->setAlignment(Qt::AlignRight);
  m_display_interest_->setAlignment(Qt::AlignRight);

  m_monthly_payment_response_->setAlignment(Qt::AlignRight);
  m_total_payment_response_->setAlignment(Qt::AlignRight);
  m_overpayment_response_->setAlignment(Qt::AlignRight);

  QFont font = m_display_sum_->font();
  font.setPointSize(font.pointSize() + 5);
  m_display_sum_->setFont(font);
  m_display_term_->setFont(font);
  m_display_interest_->setFont(font);
  m_sum_->setFont(font);
  m_term_->setFont(font);
  m_interest_->setFont(font);
  m_monthly_payment_->setFont(font);
  m_monthly_payment_response_->setFont(font);
  m_overpayment_->setFont(font);
  m_overpayment_response_->setFont(font);
  m_total_payment_->setFont(font);
  m_total_payment_response_->setFont(font);
  m_ann_->setFont(font);
  m_diff_->setFont(font);

  m_display_sum_->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_display_term_->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_display_interest_->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");

  m_sum_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_term_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_interest_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_monthly_payment_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_overpayment_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_total_payment_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_monthly_payment_response_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_overpayment_response_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_total_payment_response_->setStyleSheet("QLabel {color: #ACFF83;}");

  m_ann_->setStyleSheet("QRadioButton {color: #ACFF83;}");
  m_ann_->setChecked(true);
  m_diff_->setStyleSheet("QRadioButton {color: #ACFF83;}");

  Button *calc_button = CreateButton("Calculate!", SLOT(ButtonClicked()));
  calc_button->setStyleSheet(
      "QToolButton {color: #FF8800; background: #232522;}");

  mainLayout->addWidget(m_sum_, 0, 0, 1, 4);
  mainLayout->addWidget(m_display_sum_, 0, 5, 1, 5);
  mainLayout->addWidget(m_term_, 1, 0, 1, 4);
  mainLayout->addWidget(m_display_term_, 1, 5, 1, 5);
  mainLayout->addWidget(m_interest_, 2, 0, 1, 4);
  mainLayout->addWidget(m_display_interest_, 2, 5, 1, 5);

  mainLayout->addWidget(m_ann_, 3, 0, 1, 2);
  mainLayout->addWidget(m_diff_, 3, 5, 1, 2);

  mainLayout->addWidget(calc_button, 4, 0, 1, 10);

  mainLayout->addWidget(m_monthly_payment_, 5, 0, 1, 4);
  mainLayout->addWidget(m_monthly_payment_response_, 5, 5, 1, 5);
  mainLayout->addWidget(m_overpayment_, 6, 0, 1, 4);
  mainLayout->addWidget(m_overpayment_response_, 6, 5, 1, 5);
  mainLayout->addWidget(m_total_payment_, 7, 0, 1, 4);
  mainLayout->addWidget(m_total_payment_response_, 7, 5, 1, 5);

  setLayout(mainLayout);
  setWindowTitle("Credit");
}

void Credit::ButtonClicked() {
  int credit = m_display_sum_->text().toInt();
  int months = m_display_term_->text().toInt();
  int interest = m_display_interest_->text().toInt();
  if (credit && months && interest) {
    Calculate(credit, months, interest);
  }

  if (type_ == 1)
    m_monthly_payment_response_->setText(QString::number(result_.sum, 'f', 2));
  else if (type_ == 2)
    m_monthly_payment_response_->setText(
        QString::number(result_.sum, 'f', 2) + " ... " +
        QString::number(result_.last_sum, 'f', 2));
  m_total_payment_response_->setText(QString::number(result_.total, 'f', 2));
  m_overpayment_response_->setText(
      QString::number(result_.overpayment, 'f', 2));
}

void Credit::AnnCreditClicked() { type_ = 1; }

void Credit::DiffCreditClicked() { type_ = 2; }

Button *Credit::CreateButton(const QString &text, const char *member) {
  Button *btn = new Button(text);
  connect(btn, SIGNAL(clicked()), this, member);
  return btn;
}

void Credit::Calculate(int credit, int months, int interest) {
  s21::Controller controller;
  result_ = controller.GetCreditResult(credit, months, interest, type_);
}
}  // namespace s21
