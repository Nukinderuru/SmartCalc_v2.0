#include "model.h"

namespace s21 {
Model::Model() {}
Model::~Model() {}

int Model::CheckInput(std::string str) {
  InputStatus status = kOk;
  int opBraces = 0, cl_braces = 0;
  for (int i = 0; i < static_cast<int>(str.length()); i++) {
    if (str[i] == '(') opBraces++;
    if (str[i] == ')') {
      cl_braces++;
      if (str[i - 1] == '(') status = kWrongExpression;
    }
    if ((str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' ||
         str[i] == '^' || str[i] == 'd' || str[i] == '(' || str[i] == 'e') &&
        str[i + 1] == '\0')
      status = kWrongExpression;
    if ((str[i] == '/' || str[i] == '*' || str[i] == '^' || str[i] == 'm' ||
         str[i] == 'e' || str[i] == ')') &&
        i == 0)
      status = kWrongExpression;
    if (status) break;
  }
  if (opBraces != cl_braces) {
    status = kWrongExpression;
  }
  return status;
}

double Model::GetResult(std::string const &str, double x) {
  std::stack<Lexeme> parsed_input = ParseInput(str);
  std::stack<Lexeme> rpn = ReversePolishNotation(parsed_input);
  return Calculate(rpn, x);
}

std::pair<std::vector<double>, std::vector<double>> Model::DrawGraphic(
    const std::string &str, double x_begin, double x_end) {
  std::stack<Lexeme> parsed_input = ParseInput(str);
  std::stack<Lexeme> rpn = ReversePolishNotation(parsed_input);
  std::vector<double> x_vec;
  std::vector<double> y_vec;
  for (double x_val = x_begin; x_val < x_end; x_val += 0.01) {
    double y_val = Calculate(rpn, x_val);
    if (!isnan(y_val) && y_val != INFINITY) {
      x_vec.push_back(x_val);
      y_vec.push_back(y_val);
    }
  }
  std::pair<std::vector<double>, std::vector<double>> result(x_vec, y_vec);
  return result;
}

std::stack<Lexeme> Model::ParseInput(std::string input) {
  setlocale(LC_ALL, "en_US.UTF-8");
  std::stack<Lexeme> result;
  for (int i = 0; i < static_cast<int>(input.length()); i++) {
    if (input[i] >= '0' && input[i] <= '9') {
      long double val = ParceNumber(input, &i);
      result.push({val, 1, kNum});
      if (input[i] == 'x') {
        result.push({0.0, 3, kMult});
      }
    }
    if (input[i] == 'x') {
      result.push({0.0, 1, kX});
    }
    if (input[i] == '+') {
      result.push({0.0, 2, kPlus});
    }
    if (input[i] == '-') {
      if (result.empty() ||
          (input[i - 1] < '0' && input[i - 1] > '9' && input[i - 1] != ')') ||
          input[i - 1] == '(') {
        result.push({0.0, 1, kNum});
      }
      result.push({0.0, 2, kMinus});
    }
    if (input[i] == '*') {
      result.push({0.0, 3, kMult});
    }
    if (input[i] == '/') {
      result.push({0.0, 3, kDiv});
    }
    if (input[i] == 'm' && input[i + 1] == 'o' && input[i + 2] == 'd') {
      result.push({0.0, 3, kMod});
    }
    if (input[i] == '^') {
      result.push({0.0, 4, kExp});
    }
    if (input[i] == 'c' && input[i + 1] == 'o' && input[i + 2] == 's') {
      result.push({0.0, 5, kCos});
      i += 2;
    }
    if (input[i] == 's' && input[i + 1] == 'i' && input[i + 2] == 'n') {
      result.push({0.0, 5, kSin});
      i += 2;
    }
    if (input[i] == 't' && input[i + 1] == 'a' && input[i + 2] == 'n') {
      result.push({0.0, 5, kTan});
      i += 2;
    }
    if (input[i] == 'a' && input[i + 1] == 'c' && input[i + 2] == 'o' &&
        input[i + 3] == 's') {
      result.push({0.0, 5, kAcos});
      i += 3;
    }
    if (input[i] == 'a' && input[i + 1] == 's' && input[i + 2] == 'i' &&
        input[i + 3] == 'n') {
      result.push({0.0, 5, kAsin});
      i += 3;
    }
    if (input[i] == 'a' && input[i + 1] == 't' && input[i + 2] == 'a' &&
        input[i + 3] == 'n') {
      result.push({0.0, 5, kAtan});
      i += 3;
    }
    if (input[i] == 's' && input[i + 1] == 'q' && input[i + 2] == 'r' &&
        input[i + 3] == 't') {
      result.push({0.0, 5, kSqrt});
      i += 3;
    }
    if (input[i] == 'l' && input[i + 1] == 'n') {
      result.push({0.0, 5, kLn});
      i++;
    }
    if (input[i] == 'l' && input[i + 1] == 'o' && input[i + 2] == 'g') {
      result.push({0.0, 5, kLog});
      i += 2;
    }
    if (input[i] == '(') {
      result.push({0.0, -1, kOpB});
    }
    if (input[i] == ')') {
      result.push({0.0, -1, kClB});
    }
  }
  std::stack<Lexeme> reversed = ReverseStack(result);
  return reversed;
}

long double Model::ParceNumber(std::string input, int *i) {
  int ind = *i;
  int y = 0;
  long double result = 0.0;
  bool exp_is_present = false;
  char number_char[256] = "";
  char power_char[256] = "";
  while ((input[ind] >= '0' && input[ind] <= '9') || (input[ind] == '.') ||
         (input[ind] == 'e')) {
    if (input[ind] == 'e') {
      exp_is_present = true;
      ++ind;
      break;
    }
    if (!exp_is_present) {
      number_char[y] = input[ind];
      ++ind;
      ++y;
    }
  }
  if (exp_is_present) {
    y = 0;
    while (input[ind] >= '0' && input[ind] <= '9') {
      power_char[y] = input[ind];
      ++ind;
      ++y;
    }
  }
  *i = ind;
  char *end = NULL;
  if (exp_is_present) {
    long double number = strtold(number_char, &end);
    int power = atoi(power_char);
    power = pow(10, power);
    result = number * power;
  } else {
    result = strtold(number_char, &end);
  }
  return result;
}

std::stack<Lexeme> Model::ReverseStack(std::stack<Lexeme> &input) {
  std::stack<Lexeme> result;
  while (!input.empty()) {
    result.push({input.top().value, input.top().priority, input.top().type});
    input.pop();
  }
  return result;
}

std::stack<Lexeme> Model::ReversePolishNotation(
    std::stack<Lexeme> const &input) {
  std::stack<Lexeme> output;
  std::stack<Lexeme> support;
  std::stack<Lexeme> i = input;
  while (!i.empty()) {
    if (i.top().priority == 1) {
      output.push({i.top().value, i.top().priority, i.top().type});
    } else if (i.top().type == kOpB) {
      support.push({i.top().value, i.top().priority, i.top().type});
    } else if (i.top().type == kClB) {
      int op_br = 0;
      while (!op_br) {
        Lexeme temp = {support.top().value, support.top().priority,
                       support.top().type};
        if (temp.type == kOpB)
          op_br = 1;
        else
          output.push({temp.value, temp.priority, temp.type});
        support.pop();
      }
    } else if (i.top().priority > 1) {
      if (support.empty() || support.top().priority < i.top().priority) {
        support.push({i.top().value, i.top().priority, i.top().type});
      } else {
        DealWithOperator(i, support, output);
      }
    }
    i.pop();
  }

  while (!support.empty()) {
    output.push(
        {support.top().value, support.top().priority, support.top().type});
    support.pop();
  }
  std::stack<Lexeme> reversed = ReverseStack(output);
  return reversed;
}

void Model::DealWithOperator(std::stack<Lexeme> &i, std::stack<Lexeme> &support,
                             std::stack<Lexeme> &output) {
  output.push(
      {support.top().value, support.top().priority, support.top().type});
  support.pop();
  if (support.empty() || (support.top().priority < i.top().priority)) {
    support.push({i.top().value, i.top().priority, i.top().type});
  } else {
    DealWithOperator(i, support, output);
  }
}

double Model::Calculate(std::stack<Lexeme> const &rpn, double x) {
  long double res = 0.0;
  Lexeme current_operand;
  std::stack<Lexeme> operands;
  std::stack<Lexeme> input = rpn;
  while (!input.empty()) {  // Если в стеке число или x
    if (input.top().priority == 1) {
      if (input.top().type == 1) input.top().value = x;
      operands.push({input.top().value, 1, kNum});
    } else {  // В противном случае это оператор или функция
      switch (input.top().type) {
        case kPlus:
          current_operand = {operands.top().value, operands.top().priority,
                             operands.top().type};
          operands.pop();
          res = operands.top().value + current_operand.value;
          operands.top().value = res;
          break;
        case kMinus:
          current_operand = {operands.top().value, operands.top().priority,
                             operands.top().type};
          operands.pop();
          res = operands.top().value - current_operand.value;
          operands.top().value = res;
          break;
        case kMult:
          current_operand = {operands.top().value, operands.top().priority,
                             operands.top().type};
          operands.pop();
          res = operands.top().value * current_operand.value;
          operands.top().value = res;
          break;
        case kDiv:
          current_operand = {operands.top().value, operands.top().priority,
                             operands.top().type};
          operands.pop();
          res = operands.top().value / current_operand.value;
          operands.top().value = res;
          break;
        case kMod:
          current_operand = {operands.top().value, operands.top().priority,
                             operands.top().type};
          operands.pop();
          res = fmodl(operands.top().value, current_operand.value);
          operands.top().value = res;
          break;
        case kExp:
          current_operand = {operands.top().value, operands.top().priority,
                             operands.top().type};
          operands.pop();
          res = powl(operands.top().value, current_operand.value);
          operands.top().value = res;
          break;
        case kCos:
          res = cosl(operands.top().value);
          operands.top().value = res;
          break;
        case kSin:
          res = sinl(operands.top().value);
          operands.top().value = res;
          break;
        case kTan:
          res = tanl(operands.top().value);
          operands.top().value = res;
          break;
        case kAcos:
          res = acosl(operands.top().value);
          operands.top().value = res;
          break;
        case kAsin:
          res = asinl(operands.top().value);
          operands.top().value = res;
          break;
        case kAtan:
          res = atanl(operands.top().value);
          operands.top().value = res;
          break;
        case kSqrt:
          res = sqrtl(operands.top().value);
          operands.top().value = res;
          break;
        case kLn:
          res = logl(operands.top().value);
          operands.top().value = res;
          ;
          break;
        case kLog:
          res = log10l(operands.top().value);
          operands.top().value = res;
          break;

        default:
          break;
      }
    }
    input.pop();
  }
  return res;
}

}  // namespace s21
