#ifndef CPP3_SMARTCALC_V2_0_1_VIEW_GRAPHIC_H_
#define CPP3_SMARTCALC_V2_0_1_VIEW_GRAPHIC_H_

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QVector>
#include <algorithm>

#include "Controller/controller.h"
#include "qcustomplot.h"

namespace s21 {
class Graphic : public QWidget {
  Q_OBJECT
 public:
  Graphic();
  QString expression;
  QCustomPlot *plot;
  QLabel *m_from;
  QLabel *m_to;
  QLineEdit *m_display_from;
  QLineEdit *m_display_to;

 private slots:
  void PrintClicked();

 private:
  double x_begin_, x_end_;
  QVector<double> x_g_, y_g_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_VIEW_GRAPHIC_H_
