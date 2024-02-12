#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  QGridLayout *main_layout = new QGridLayout();
  QMenuBar *main_menu = new QMenuBar;
  QMenu *graph_menu = new QMenu("&Graphic");
  QMenu *credit_menu = new QMenu("&Credit");
  QMenu *deposit_menu = new QMenu("&Deposit");
  main_menu->setStyleSheet("QMenuBar {color: #CD730D; background: #232522;}");
  graph_menu->addAction("&Plot a graphic", this, SLOT(PrintClicked()));
  credit_menu->addAction("&New credit calculator", this, SLOT(CreditClicked()));
  deposit_menu->addAction("&New deposit calculator", this,
                          SLOT(DepositClicked()));
  main_menu->addMenu(graph_menu);
  main_menu->addMenu(credit_menu);
  main_menu->addMenu(deposit_menu);
  main_layout->setMenuBar(main_menu);
  m_display_up_ = new QLineEdit();
  m_display_down_ = new QLineEdit();
  m_sign_ = new QLabel();

  m_display_up_->setReadOnly(true);
  m_display_down_->setReadOnly(true);
  m_display_up_->setMaxLength(255);
  m_display_down_->setMaxLength(255);
  m_display_down_->setText("0");

  m_display_up_->setAlignment(Qt::AlignRight);
  m_sign_->setAlignment(Qt::AlignRight);
  m_display_down_->setAlignment(Qt::AlignRight);

  QFont fontMenu = m_display_up_->font();
  fontMenu.setPointSize(fontMenu.pointSize() + 2);
  main_menu->setFont(fontMenu);
  QFont font = m_display_up_->font();
  font.setPointSize(font.pointSize() + 5);
  m_display_up_->setFont(font);
  m_display_down_->setFont(font);
  m_sign_->setFont(font);

  m_display_up_->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_display_down_->setStyleSheet(
      "QLineEdit {color: #ACFF83; background: #232522;}");
  m_sign_->setStyleSheet("QLabel {color: #ACFF83;}");

  for (int i = 0; i < kNumButtons_; ++i)
    m_number_buttons_[i] =
        CreateButton(QString::number(i), SLOT(NumberClicked()));

  Button *exp_button = CreateButton("e", SLOT(ExpClicked()));
  Button *clear_button = CreateButton("Clear", SLOT(ClearClicked()));
  Button *clear_all_button = CreateButton("AC", SLOT(ClearAllClicked()));

  Button *point_button = CreateButton(".", SLOT(PointClicked()));
  Button *backspace_button =
      CreateButton(m_backspace_sign_, SLOT(BackspaceClicked()));
  Button *equal_button = CreateButton("=", SLOT(EqualClicked()));
  Button *opening_bracket_button = CreateButton("(", SLOT(OperandClicked()));
  Button *closing_bracket_button = CreateButton(")", SLOT(OperandClicked()));

  Button *plus_button = CreateButton(m_plus_sign_, SLOT(OperandClicked()));
  Button *minus_button = CreateButton(m_minus_sign_, SLOT(OperandClicked()));
  Button *times_button = CreateButton(m_times_sign_, SLOT(OperandClicked()));
  Button *division_button =
      CreateButton(m_division_sign_, SLOT(OperandClicked()));
  Button *mod_button = CreateButton("%", SLOT(OperandClicked()));

  Button *square_root_button =
      CreateButton(m_square_root_sign_, SLOT(OperandClicked()));
  Button *power_button = CreateButton(m_power_sign_, SLOT(OperandClicked()));

  plus_button->setStyleSheet(
      "QToolButton {color: #FF8800; background: #232522;}");
  minus_button->setStyleSheet(
      "QToolButton {color: #FF8800; background: #232522;}");
  times_button->setStyleSheet(
      "QToolButton {color: #FF8800; background: #232522;}");
  division_button->setStyleSheet(
      "QToolButton {color: #FF8800; background: #232522;}");
  mod_button->setStyleSheet(
      "QToolButton {color: #FF8800; background: #232522;}");
  square_root_button->setStyleSheet(
      "QToolButton {color: #FF8800; background: #232522;}");
  power_button->setStyleSheet(
      "QToolButton {color: #FF8800; background: #232522;}");
  equal_button->setStyleSheet(
      "QToolButton {color: #FFFFFF; background: #CD730D; border-radius: "
      "28px;}");

  Button *log_button = CreateButton("log", SLOT(FunctionClicked()));
  Button *ln_button = CreateButton("ln", SLOT(FunctionClicked()));
  Button *cos_button = CreateButton("cos", SLOT(FunctionClicked()));
  Button *acos_button = CreateButton("acos", SLOT(FunctionClicked()));
  Button *sin_button = CreateButton("sin", SLOT(FunctionClicked()));
  Button *asin_button = CreateButton("asin", SLOT(FunctionClicked()));
  Button *tan_button = CreateButton("tan", SLOT(FunctionClicked()));
  Button *atan_button = CreateButton("atan", SLOT(FunctionClicked()));

  Button *x_button = CreateButton("x", SLOT(XClicked()));

  main_layout->addWidget(m_display_up_, 0, 0, 1, 6);
  main_layout->addWidget(m_sign_, 1, 5, 1, 1);
  main_layout->addWidget(m_display_down_, 2, 0, 1, 6);

  main_layout->addWidget(exp_button, 3, 0, 1, 1);
  main_layout->addWidget(backspace_button, 3, 3, 1, 1);
  main_layout->addWidget(clear_button, 3, 4, 1, 1);
  main_layout->addWidget(clear_all_button, 3, 5, 1, 1);

  main_layout->addWidget(sin_button, 4, 0);
  main_layout->addWidget(asin_button, 4, 1);
  main_layout->addWidget(square_root_button, 4, 2);
  main_layout->addWidget(power_button, 4, 3);
  main_layout->addWidget(mod_button, 4, 4);
  main_layout->addWidget(division_button, 4, 5);

  main_layout->addWidget(cos_button, 5, 0, 1, 1);
  main_layout->addWidget(acos_button, 5, 1, 1, 1);
  main_layout->addWidget(m_number_buttons_[1], 5, 2, 1, 1);
  main_layout->addWidget(m_number_buttons_[2], 5, 3, 1, 1);
  main_layout->addWidget(m_number_buttons_[3], 5, 4, 1, 1);
  main_layout->addWidget(times_button, 5, 5, 1, 1);

  main_layout->addWidget(tan_button, 6, 0, 1, 1);
  main_layout->addWidget(atan_button, 6, 1, 1, 1);
  main_layout->addWidget(m_number_buttons_[4], 6, 2, 1, 1);
  main_layout->addWidget(m_number_buttons_[5], 6, 3, 1, 1);
  main_layout->addWidget(m_number_buttons_[6], 6, 4, 1, 1);
  main_layout->addWidget(minus_button, 6, 5, 1, 1);

  main_layout->addWidget(log_button, 7, 0, 1, 1);
  main_layout->addWidget(ln_button, 7, 1, 1, 1);
  main_layout->addWidget(m_number_buttons_[7], 7, 2, 1, 1);
  main_layout->addWidget(m_number_buttons_[8], 7, 3, 1, 1);
  main_layout->addWidget(m_number_buttons_[9], 7, 4, 1, 1);
  main_layout->addWidget(plus_button, 7, 5, 1, 1);

  main_layout->addWidget(opening_bracket_button, 8, 0, 1, 1);
  main_layout->addWidget(closing_bracket_button, 8, 1, 1, 1);
  main_layout->addWidget(point_button, 8, 2, 1, 1);
  main_layout->addWidget(m_number_buttons_[0], 8, 3, 1, 1);
  main_layout->addWidget(x_button, 8, 4, 1, 1);
  main_layout->addWidget(equal_button, 8, 5, 1, 1);

  setLayout(main_layout);

  setWindowTitle("Calculator");
}

MainWindow::~MainWindow() {}

void MainWindow::ExpClicked() {
  if (m_display_down_->text().endsWith('.') || m_display_down_->text() == "0") {
    AbortOperation();
    return;
  }
  m_display_down_->setText(m_display_down_->text() + "e");
}

void MainWindow::NumberClicked() {
  Button *btn = static_cast<Button *>(sender());
  int number = btn->text().toInt();

  if (answer_is_shown_) {
    m_display_up_->clear();
    m_display_down_->clear();
    answer_is_shown_ = 0;
  }

  if (x_is_present_ == 2) {
    m_display_down_->clear();
    m_display_down_->setText(QString::number(number));
    x_is_present_ = 3;
  } else if (x_is_present_ == 3) {
    m_display_down_->setText(m_display_down_->text() + QString::number(number));
  } else {
    if (m_display_down_->text() == "0") {
      m_display_down_->clear();
      m_display_up_->clear();
    }
    m_display_down_->setText(m_display_down_->text() + QString::number(number));
  }
}

void MainWindow::XClicked() {
  answer_is_shown_ = 0;
  x_is_present_ = 1;
  if (m_display_down_->text().endsWith('.')) {
    AbortOperation();
    return;
  }
  if (m_display_down_->text() == "0") {
    m_display_down_->clear();
    m_display_up_->clear();
  }
  m_display_down_->setText(m_display_down_->text() + "x");
}

void MainWindow::OperandClicked() {
  Button *btn = static_cast<Button *>(sender());
  QString operation = btn->text();

  if (m_display_down_->text().endsWith('.')) {
    AbortOperation();
    return;
  }

  if (answer_is_shown_) {
    if (!temp_result_ || operation == m_square_root_sign_) {
      m_display_up_->clear();
      m_display_down_->clear();
    } else {
      m_display_up_->setText(QString::number(temp_result_, 'f', 7));
      m_display_down_->clear();
    }
    answer_is_shown_ = 0;
  }

  if (operation == m_power_sign_) operation = "^";
  if (operation == m_times_sign_) operation = "*";
  if (operation == m_division_sign_) operation = "/";
  if (operation == m_square_root_sign_) operation = "sqrt(";
  if (operation == "%") operation = "mod";

  m_sign_->setText(operation);

  QString text = m_display_up_->text() + m_display_down_->text();
  if (m_display_down_->text() == "0") {
    text = operation;
  }
  if ((text.endsWith("+") || text.endsWith("-") || text.endsWith("*") ||
       text.endsWith("%") || text.endsWith("/") || text.endsWith("^")) &&
      (operation == "+" || operation == "-" || operation == "*" ||
       operation == "/" || operation == "^" || operation == "%" ||
       operation == "mod")) {
    text.chop(1);
    m_display_up_->setText(text);
  }
  if (text.endsWith("mod") &&
      (operation == "+" || operation == "-" || operation == "*" ||
       operation == "/" || operation == "^" || operation == "%" ||
       operation == "mod")) {
    text.chop(3);
    m_display_up_->setText(text);
  }
  if (text.endsWith('(') &&
      (operation == "+" || operation == "-" || operation == "*" ||
       operation == "/" || operation == "^" || operation == "%" ||
       operation == "mod")) {
    m_sign_->clear();
    operation = "";
    m_display_up_->setText(m_display_up_->text());
  }

  if (m_display_down_->text() == "0")
    m_display_up_->setText(operation);
  else
    m_display_up_->setText(m_display_up_->text() + m_display_down_->text() +
                           operation);

  if (operation == ')') m_sign_->clear();

  m_display_down_->clear();
}

void MainWindow::FunctionClicked() {
  temp_result_ = 0;
  Button *btn = static_cast<Button *>(sender());
  QString operation = btn->text() + '(';

  if (m_display_down_->text().endsWith('.')) {
    AbortOperation();
    return;
  }

  if (answer_is_shown_) {
    m_display_up_->clear();
    m_display_down_->clear();
    answer_is_shown_ = 0;
  }

  QString whole_expression =
      m_display_up_->text() + m_display_down_->text() + operation;
  if (whole_expression[0] == "0")
    m_display_up_->setText(operation);
  else
    m_display_up_->setText(m_display_up_->text() + m_display_down_->text() +
                           operation);
  m_display_down_->clear();
}

void MainWindow::EqualClicked() {
  setlocale(LC_NUMERIC, "C");
  QString input;
  double result = 0.0;
  int status = 0;
  if (x_is_present_ == 1) {
    m_display_up_->setText(m_display_up_->text() + m_display_down_->text());
    x_is_present_ = 2;
    m_sign_->clear();
    m_display_down_->setText("Now enter the value of x:");
    return;
  } else if (x_is_present_ == 3) {
    x_is_present_ = 0;
    long double x =
        static_cast<long double>(m_display_down_->text().toDouble());
    m_display_down_->clear();
    input = m_display_up_->text() + m_display_down_->text();
    s21::Controller controller;
    std::string str = input.toStdString();
    status = controller.CheckInput(str);
    if (status) {
      AbortOperation();
    } else {
      result = controller.Calculate(str, x);
    }
  } else {
    input = m_display_up_->text() + m_display_down_->text();
    m_display_up_->setText(input);
    m_display_down_->clear();
    s21::Controller controller;
    std::string str = input.toStdString();
    status = controller.CheckInput(str);
    if (status) {
      AbortOperation();
    } else {
      result = controller.Calculate(str, 0.0);
    }
  }
  m_sign_->setText("=");
  if (!isnan(result) && result != INFINITY && x_is_present_ != 2 && !status) {
    m_display_down_->setText(QString::number(result, 'f', 7));
    answer_is_shown_ = 1;
    temp_result_ = result;
  } else {
    AbortOperation();
  }
}

void MainWindow::PointClicked() {
  if (!m_display_down_->text().contains('.') &&
      !m_display_down_->text().endsWith('x') &&
      !m_display_down_->text().endsWith('e')) {
    m_display_down_->setText(m_display_down_->text() + '.');
  }
}

void MainWindow::BackspaceClicked() {
  QString text = m_display_down_->text();
  text.chop(1);

  if (text.isEmpty()) {
    text = "0";
    m_sign_->clear();
  }

  m_display_down_->setText(text);
}

void MainWindow::ClearClicked() { m_display_down_->setText("0"); }

void MainWindow::ClearAllClicked() {
  m_display_down_->setText("0");
  m_display_up_->clear();
  m_sign_->clear();
  x_is_present_ = 0;
  answer_is_shown_ = 1;
  temp_result_ = 0.0;
}

void MainWindow::PrintClicked() {
  m_sign_->clear();
  x_is_present_ = 0;
  QString input = "";
  if (answer_is_shown_)
    input = m_display_up_->text();
  else
    input = m_display_up_->text() + m_display_down_->text();
  m_display_up_->setText(input);
  m_display_down_->clear();

  s21::Controller controller;
  std::string str = input.toStdString();
  if (controller.CheckInput(str) == 1) {
    AbortOperation();
  } else {
    g_ = new s21::Graphic();
    g_->setStyleSheet("background-color:black;");
    g_->expression = input;
    g_->show();
  }
  answer_is_shown_ = 1;
}

void MainWindow::CreditClicked() {
  c_ = new s21::Credit();
  c_->setStyleSheet("background-color:black;");
  c_->show();
}

void MainWindow::DepositClicked() {
  d_ = new s21::Deposit();
  d_->setStyleSheet("background-color:black;");
  d_->show();
}

Button *MainWindow::CreateButton(const QString &text, const char *member) {
  Button *btn = new Button(text);
  connect(btn, SIGNAL(clicked()), this, member);
  return btn;
}

void MainWindow::AbortOperation() {
  m_display_down_->setText("Wrong input");
  x_is_present_ = 0;
  answer_is_shown_ = 1;
}
