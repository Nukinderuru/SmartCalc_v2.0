#ifndef CPP3_SMARTCALC_V2_0_1_VIEW_REPLENISHMENTS_H_
#define CPP3_SMARTCALC_V2_0_1_VIEW_REPLENISHMENTS_H_

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

class Replenishments : public QWidget {
  Q_OBJECT

 public:
  Replenishments();

  int replenishment = 0;
  std::array<QDate, 100> input_replenishment_dates;
  std::array<long double, 100> input_replenishment_amounts;

 private slots:
  void AddButtonClicked();
  void OkButtonClicked();

 private:
  Button *CreateButton(const QString &text, const char *member);

  QGridLayout *main_layout_;

  QLabel *m_replenishment_date_;
  QLabel *m_replenishment_amount_;
  Button *add_replenishment_button_;
  Button *ok_button_;

  int replenishments_line_ = 1;

  QLineEdit *m_replenishment_dates_[100];
  QLineEdit *m_replenishment_amounts_[100];
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_0_1_VIEW_REPLENISHMENTS_H_
