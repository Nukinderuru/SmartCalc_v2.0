#include "button.h"

Button::Button(const QString &text, QWidget *parent) : QToolButton(parent) {
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  setText(text);
  setStyleSheet("QToolButton {color: #ACFF83; background: #232522;}");
}

QSize Button::sizeHint() const {
  QSize size = QToolButton::sizeHint();
  size.rheight() += 30;
  size.rwidth() = qMax(size.width(), size.height());
  return size;
}
