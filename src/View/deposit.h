#ifndef CPP3_SMARTCALC_V2_0_1_VIEW_DEPOSIT_H_
#define CPP3_SMARTCALC_V2_0_1_VIEW_DEPOSIT_H_

#include <QComboBox>
#include <QDate>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QToolButton>
#include <QWidget>
#include <QtMath>

#include "Controller/controller.h"
#include "button.h"
#include "replenishments.h"
#include "withdrawals.h"

namespace s21 {

class Deposit : public QWidget {
  Q_OBJECT

 public:
  Deposit();

 private slots:
  void ButtonClicked();
  void CapitalizationYesClicked();
  void CapitalizationNoClicked();
  void AddReplenishmantClicked();
  void AddWithdrawalClicked();

 private:
  Button *CreateButton(const QString &text, const char *member);
  void Calculate();

  QGridLayout *main_layout_;

  QLineEdit *m_display_sum_;
  QLineEdit *m_display_date_;
  QLineEdit *m_display_term_;
  QComboBox *m_display_term_in_;
  QLineEdit *m_display_interest_;
  QLineEdit *m_display_tax_rate_;
  QComboBox *m_display_periodicity_;

  QLabel *m_sum_;
  QLabel *m_start_date_;
  QLabel *m_term_;
  QLabel *m_interest_;
  QLabel *m_tax_rate_;
  QLabel *m_periodicity_;
  QLabel *m_capitalization_;

  QLabel *m_replenishments_;
  QLabel *m_replenishment_date_;
  QLabel *m_replenishment_amount_;
  Button *add_replenishment_button_;
  QLabel *m_withdrawals_;
  QLabel *m_withdrawal_date_;
  QLabel *m_withdrawal_amount_;
  Button *add_withdrawal_button_;

  QLabel *m_calculate_;
  Button *calc_button_;

  QLabel *m_accrued_interest_;
  QLabel *m_tax_amount_;
  QLabel *m_total_payment_;

  QLabel *m_accrued_interest_response_;
  QLabel *m_tax_amount_response_;
  QLabel *m_total_payment_response_;

  QRadioButton *m_capitalization_yes_;
  QRadioButton *m_capitalization_no_;

  QLineEdit *m_withdrawal_dates_[100];
  QLineEdit *m_withdrawal_amounts_[100];

  bool capitalization_ = 1;
  bool replenishments_ = 0;
  bool withdrawals_ = 0;
  DepositResult result_;

  s21::Replenishments *r_;
  QDate input_replenishment_dates_[100];
  long double input_replenishment_amounts_[100];

  s21::Withdrawals *w_;
  QDate input_withdrawal_dates_[100];
  long double input_withdrawal_amounts_[100];
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_VIEW_DEPOSIT_H_
