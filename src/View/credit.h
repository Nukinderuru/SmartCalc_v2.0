#ifndef CPP3_SMARTCALC_V2_0_1_VIEW_CREDIT_H_
#define CPP3_SMARTCALC_V2_0_1_VIEW_CREDIT_H_

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

namespace s21 {
class Credit : public QWidget {
  Q_OBJECT

 public:
  Credit();

 private slots:
  void ButtonClicked();
  void AnnCreditClicked();
  void DiffCreditClicked();

 private:
  Button *CreateButton(const QString &text, const char *member);
  void Calculate(int credit, int months, int interest);

  QLineEdit *m_display_sum_;
  QLineEdit *m_display_term_;
  QLineEdit *m_display_interest_;

  QLabel *m_sum_;
  QLabel *m_term_;
  QLabel *m_interest_;

  QLabel *m_calculate_;

  QLabel *m_monthly_payment_;
  QLabel *m_overpayment_;
  QLabel *m_total_payment_;

  QLabel *m_monthly_payment_response_;
  QLabel *m_overpayment_response_;
  QLabel *m_total_payment_response_;

  QRadioButton *m_ann_;
  QRadioButton *m_diff_;

  int type_ = 1;
  CreditResult result_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_VIEW_CREDIT_H_
