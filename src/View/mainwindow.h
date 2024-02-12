#ifndef CPP3_SMARTCALC_V2_0_1_VIEW_MAINWINDOW_H_
#define CPP3_SMARTCALC_V2_0_1_VIEW_MAINWINDOW_H_

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>

#include "Controller/controller.h"
#include "button.h"
#include "credit.h"
#include "deposit.h"
#include "graphic.h"

class MainWindow : public QWidget {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void ExpClicked();
  void NumberClicked();
  void XClicked();
  void OperandClicked();
  void FunctionClicked();
  void EqualClicked();
  void PointClicked();
  void BackspaceClicked();
  void ClearClicked();
  void ClearAllClicked();
  void PrintClicked();
  void CreditClicked();
  void DepositClicked();

 private:
  Button *CreateButton(const QString &text, const char *member);
  bool CheckAndCalculate(QString input, long double);
  void AbortOperation();

  QLineEdit *m_display_up_;
  QLineEdit *m_display_down_;
  QLabel *m_sign_;

  QString m_square_root_sign_ = QChar(0x221A);
  QString m_power_sign_ = 'x' + QChar(0x000002b8);
  QString m_backspace_sign_ = QChar(0x2190);
  QString m_division_sign_ = QChar(0x000000F7);
  QString m_times_sign_ = QChar(0x000000D7);
  QString m_plus_sign_ = "+";
  QString m_minus_sign_ = "-";

  static const int kNumButtons_ = 10;
  Button *m_number_buttons_[10];

  int x_is_present_ = 0;
  int answer_is_shown_ = 0;
  double temp_result_ = 0.0;

  s21::Graphic *g_;
  s21::Credit *c_;
  s21::Deposit *d_;
};
#endif  // CPP3_SMARTCALC_V2_0_1_VIEW_MAINWINDOW_H_
