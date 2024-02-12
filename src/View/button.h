#ifndef CPP3_SMARTCALC_V2_0_1_VIEW_BUTTON_H_
#define CPP3_SMARTCALC_V2_0_1_VIEW_BUTTON_H_

#include <QToolButton>

class Button : public QToolButton {
  Q_OBJECT
 public:
  explicit Button(const QString &text, QWidget *parent = nullptr);

  QSize sizeHint() const override;
};

#endif  // CPP3_SMARTCALC_V2_0_1_VIEW_BUTTON_H_
