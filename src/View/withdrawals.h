#ifndef CPP3_SMARTCALC_V2_0_1_VIEW_WITHDRAWALS_H_
#define CPP3_SMARTCALC_V2_0_1_VIEW_WITHDRAWALS_H_

#include <QDate>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <array>

#include "button.h"

namespace s21 {

class Withdrawals : public QWidget {
  Q_OBJECT
 public:
  Withdrawals();

  int withdrawal = 0;
  std::array<QDate, 100> input_withdrawal_dates;
  std::array<long double, 100> input_withdrawal_amounts;

 private slots:
  void AddButtonClicked();
  void OkButtonClicked();

 private:
  Button *CreateButton(const QString &text, const char *member);

  QGridLayout *main_layout_;

  QLabel *m_withdrawal_date_;
  QLabel *m_withdrawal_amount_;
  Button *add_withdrawal_button_;
  Button *ok_button_;

  QLineEdit *m_withdrawal_dates_[100];
  QLineEdit *m_withdrawal_amounts_[100];

  int withdrawals_line_ = 1;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_VIEW_WITHDRAWALS_H_
