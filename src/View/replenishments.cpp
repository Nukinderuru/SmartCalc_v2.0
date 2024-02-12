#include "replenishments.h"

namespace s21 {
Replenishments::Replenishments() {
  main_layout_ = new QGridLayout();

  m_replenishment_date_ = new QLabel();
  m_replenishment_date_->setText("Date:");
  m_replenishment_amount_ = new QLabel;
  m_replenishment_amount_->setText("Amount:");

  add_replenishment_button_ = CreateButton("Add +", SLOT(AddButtonClicked()));
  ok_button_ = CreateButton("OK", SLOT(OkButtonClicked()));

  m_replenishment_dates_[replenishment] = new QLineEdit();
  m_replenishment_amounts_[replenishment] = new QLineEdit();

  main_layout_->setSizeConstraint(QLayout::SetFixedSize);

  QFont font = m_replenishment_date_->font();
  font.setPointSize(font.pointSize() + 5);
  m_replenishment_date_->setFont(font);
  m_replenishment_amount_->setFont(font);
  m_replenishment_dates_[replenishment]->setFont(font);
  m_replenishment_amounts_[replenishment]->setFont(font);

  m_replenishment_date_->setStyleSheet("QLabel {color: #ACFF83;}");
  m_replenishment_amount_->setStyleSheet("QLabel {color: #ACFF83;}");
  add_replenishment_button_->setStyleSheet(
      "QToolButton {color: #FF8800; background: #232522;}");
  m_replenishment_dates_[replenishment]->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_replenishment_amounts_[replenishment]->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");

  main_layout_->addWidget(m_replenishment_date_, 0, 0, 1, 5);
  main_layout_->addWidget(m_replenishment_amount_, 0, 6, 1, 5);
  main_layout_->addWidget(m_replenishment_dates_[replenishment], 1, 0, 1, 5);
  main_layout_->addWidget(m_replenishment_amounts_[replenishment], 1, 6, 1, 5);
  main_layout_->addWidget(add_replenishment_button_, 2, 0, 1, 5);
  main_layout_->addWidget(ok_button_, 2, 5, 1, 5);

  setLayout(main_layout_);
  setWindowTitle("Replenishments");
}

void Replenishments::AddButtonClicked() {
  replenishments_line_++;
  replenishment++;
  m_replenishment_dates_[replenishment] = new QLineEdit();
  m_replenishment_amounts_[replenishment] = new QLineEdit();
  m_replenishment_dates_[replenishment]->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_replenishment_amounts_[replenishment]->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  QFont font = m_replenishment_date_->font();
  m_replenishment_dates_[replenishment]->setFont(font);
  m_replenishment_amounts_[replenishment]->setFont(font);
  main_layout_->addWidget(m_replenishment_dates_[replenishment],
                          replenishments_line_, 0, 1, 5);
  main_layout_->addWidget(m_replenishment_amounts_[replenishment],
                          replenishments_line_, 6, 1, 5);
  main_layout_->addWidget(add_replenishment_button_, replenishments_line_ + 1,
                          0, 1, 5);
  main_layout_->addWidget(ok_button_, replenishments_line_ + 1, 5, 1, 5);
}

void Replenishments::OkButtonClicked() {
  for (int i = 0; i <= replenishment; i++) {
    input_replenishment_dates[i] =
        QDate::fromString(m_replenishment_dates_[i]->text(), "dd.MM.yyyy");
  }
  for (int i = 0; i <= replenishment; i++) {
    input_replenishment_amounts[i] =
        m_replenishment_amounts_[i]->text().toDouble();
  }
}

Button *Replenishments::CreateButton(const QString &text, const char *member) {
  Button *btn = new Button(text);
  connect(btn, SIGNAL(clicked()), this, member);
  return btn;
}
}  // namespace s21
