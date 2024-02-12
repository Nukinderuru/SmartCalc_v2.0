#include "test.h"

TEST(Check, Test1) {
  std::string input = "18+11*24/2^2";
  s21::Model model;
  double result = model.GetResult(input, 0);
  EXPECT_DOUBLE_EQ(result, 84);
}

TEST(Check, Test2) {
  std::string input = "(123mod12)*(-2)-3";
  s21::Model model;
  double result = model.GetResult(input, 0);
  EXPECT_DOUBLE_EQ(result, -9);
}

TEST(Check, Test3) {
  std::string input = "-sin(2x)/(-cos(x))";
  s21::Model model;
  double result = model.GetResult(input, 2.0);
  double real_result = -sinl(2*2.0)/(-cosl(2.0));
  EXPECT_FLOAT_EQ(result, real_result);
}

TEST(Check, Test4) {
  std::string input = "sqrt(144)*(8mod3)";
  s21::Model model;
  double result = model.GetResult(input, 0);
  EXPECT_DOUBLE_EQ(result, 24);
}

TEST(Check, Test5) {
  std::string input = "ln(3x)/log(25x)";
  s21::Model model;
  double result = model.GetResult(input, 0.5);
  double real_result = logl(3*0.5)/log10l(25*0.5);
  EXPECT_FLOAT_EQ(result, real_result);
}

TEST(Check, Test6) {
  std::string input = "tan(3x)^3*tan(x)/(sin(x)-cos(x))";
  s21::Model model;
  double result = model.GetResult(input, 4.0);
  double real_result = powl(tanl(3*4), 3)*tanl(4)/(sinl(4)-cosl(4));
  EXPECT_FLOAT_EQ(result, real_result);
}

TEST(Check, Test7) {
  std::string input = "sqrt((9^3-sqrt(81)-2^2*5)/7+3*7)+0.111";
  s21::Model model;
  double result = model.GetResult(input, 0.0);
  EXPECT_DOUBLE_EQ(result, 11.111);
}

TEST(Check, Test8) {
  std::string input = "18.8-8.3";
  s21::Model model;
  double result = model.GetResult(input, 0.0);
  EXPECT_DOUBLE_EQ(result, 10.5);
}

TEST(Check, Test9) {
  std::string input = "88/1.1";
  s21::Model model;
  double result = model.GetResult(input, 0.0);
  EXPECT_DOUBLE_EQ(result, 80);
}

TEST(Check, Test10) {
  std::string input = "12mod5";
  s21::Model model;
  double result = model.GetResult(input, 0.0);
  EXPECT_DOUBLE_EQ(result, 2);
}

TEST(Check, Test11) {
  std::string input = "acos(cos(11.0)) + asin(cos(11.0))";
  s21::Model model;
  double result = model.GetResult(input, 0.0);
  double real_result = acosl(cosl(11.0)) + asinl(cosl(11.0));
  EXPECT_DOUBLE_EQ(result, real_result);
}

TEST(Check, Test12) {
  std::string input = "atan(cos(11.0)) + sqrt(cos(11.0))";
  s21::Model model;
  double result = model.GetResult(input, 0.0);
  double real_result = atanl(cosl(11.0)) + sqrtl(cosl(11.0));
  EXPECT_DOUBLE_EQ(result, real_result);
}

TEST(Check, Test13) {
  std::string input = "1.23e4+3";
  s21::Model model;
  double result = model.GetResult(input, 0.0);
  EXPECT_DOUBLE_EQ(result, 12303);
}
