#include "graphic.h"

namespace s21 {

Graphic::Graphic() {
  resize(700, 700);
  QGridLayout *main_layout = new QGridLayout();
  plot = new QCustomPlot();
  m_from = new QLabel("From:");
  m_to = new QLabel("To:");
  m_display_from = new QLineEdit();
  m_display_to = new QLineEdit();
  QFont font = m_display_from->font();
  font.setPointSize(font.pointSize() + 5);
  m_display_from->setFont(font);
  m_display_to->setFont(font);
  m_from->setFont(font);
  m_to->setFont(font);
  m_display_from->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_display_to->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_from->setStyleSheet("QLabel {color: #ACFF83;}");
  m_to->setStyleSheet("QLabel {color: #ACFF83;}");
  QToolButton *button = new QToolButton();
  button->setText("Print");
  button->setFont(font);
  button->setStyleSheet("QToolButton {color: #ACFF83; background: #232522;}");
  button->setFixedSize(100, 35);
  connect(button, SIGNAL(clicked()), this, SLOT(PrintClicked()));
  main_layout->addWidget(plot, 0, 0, 7, 7);
  main_layout->addWidget(m_from, 8, 0, 1, 1);
  main_layout->addWidget(m_display_from, 8, 1, 1, 1);
  main_layout->addWidget(m_to, 8, 3, 1, 1);
  main_layout->addWidget(m_display_to, 8, 4, 1, 1);
  main_layout->addWidget(button, 8, 6, 1, 1);
  setLayout(main_layout);
  setWindowTitle("Graphic");
}

void Graphic::PrintClicked() {
  x_begin_ = m_display_from->text().toDouble();
  x_end_ = m_display_to->text().toDouble();
  if (x_begin_ < -1000000 || x_begin_ > 1000000)
    m_display_from->setStyleSheet(
        "QLineEdit {color: #CD730D; background: #232522;}");
  else if (x_end_ < -1000000 || x_end_ > 1000000)
    m_display_to->setStyleSheet(
        "QLineEdit {color: #CD730D; background: #232522;}");
  else {
    m_display_from->setStyleSheet(
        "QLineEdit {color: #ACFF83; background: #232522;}");
    m_display_to->setStyleSheet(
        "QLineEdit {color: #ACFF83; background: #232522;}");
    std::string str = expression.toStdString();
    s21::Controller controller;
    std::pair<std::vector<double>, std::vector<double>> all_values =
        controller.DrawGraphic(str, x_begin_, x_end_);
    double y_min =
        *(std::min_element(all_values.second.begin(), all_values.second.end()));
    double y_max =
        *(std::max_element(all_values.second.begin(), all_values.second.end()));
    plot->xAxis->setRange(x_begin_, x_end_);
    plot->yAxis->setRange(y_min, y_max);
    plot->addGraph();
    // QVector<double> x;
    for (auto it = all_values.first.begin(); it != all_values.first.end();
         ++it) {
      x_g_.push_back(*it);
    }
    // QVector<double> y;
    for (auto it = all_values.second.begin(); it != all_values.second.end();
         ++it) {
      y_g_.push_back(*it);
    }
    plot->graph(0)->addData(x_g_, y_g_);
    plot->replot();
  }
}

}  // namespace s21
