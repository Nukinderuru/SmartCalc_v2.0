#ifndef CPP3_SMARTCALC_V2_0_1_MODEL_MODEL_H_
#define CPP3_SMARTCALC_V2_0_1_MODEL_MODEL_H_

#include <math.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

namespace s21 {

typedef enum { kOk, kWrongExpression } InputStatus;

typedef enum {
  kNum,
  kX,
  kPlus,
  kMinus,
  kMult,
  kDiv,
  kMod,
  kExp,
  kCos,
  kSin,
  kTan,
  kAcos,
  kAsin,
  kAtan,
  kSqrt,
  kLn,
  kLog,
  kOpB,
  kClB
} LexemeType;

typedef struct Lexeme {
  long double value;
  int priority;
  LexemeType type;
} Lexeme;

class Model {
 public:
  Model();
  ~Model();

  int CheckInput(std::string str);
  double GetResult(std::string const &str, double x);
  std::pair<std::vector<double>, std::vector<double>> DrawGraphic(
      std::string const &str, double x_begin, double x_end);

 private:
  InputStatus CheckChar(std::string str, int *i, int *op_braces);
  std::stack<Lexeme> ParseInput(std::string input);
  long double ParceNumber(std::string input, int *i);
  std::stack<Lexeme> ReverseStack(std::stack<Lexeme> &input);
  std::stack<Lexeme> ReversePolishNotation(const std::stack<Lexeme> &input);
  void DealWithOperator(std::stack<Lexeme> &i, std::stack<Lexeme> &support,
                        std::stack<Lexeme> &output);
  double Calculate(std::stack<Lexeme> const &rpn, double x);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_MODEL_MODEL_H_
