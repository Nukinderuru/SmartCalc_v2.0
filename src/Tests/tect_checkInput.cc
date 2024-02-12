#include "test.h"

// Correct input
TEST(Check, Check_Correct_Input1) {
  std::string input = "18+11*24/2^2";
  s21::Model model;
  int status = model.CheckInput(input);
  EXPECT_EQ(status, 0);
}

TEST(Check, Check_Correct_Input2) {
  std::string input = "(123mod12)*(-2)-3";
  s21::Model model;
  int status = model.CheckInput(input);
  EXPECT_EQ(status, 0);
}

TEST(Check, Check_Correct_Input3) {
  std::string input = "-sin(2x)/(-cos(x))";
  s21::Model model;
  int status = model.CheckInput(input);
  EXPECT_EQ(status, 0);
}

TEST(Check, Check_Correct_Input4) {
  std::string input = "(sqrt(144)*8mod3)+ln(3x)/log(25x)-(atan(3x)^3*tan(x)/(asin(x)-acos(x)))";
  s21::Model model;
  int status = model.CheckInput(input);
  EXPECT_EQ(status, 0);
}

TEST(Check, Check_Correct_Input5) {
  std::string input = "(sqrt(14.4)*8mod3,0)+ln(3x)/log(2.5x)-(atan(3x)^3*tan(x)/"
      "(asin(x)-acos(x)))";
  s21::Model model;
  int status = model.CheckInput(input);
  EXPECT_EQ(status, 0);
}

// Incorrect input
TEST(Check, Check_Inorrect_Input1) {
  std::string input = "*sqrt(8+1)*8mod3,0)+ln(sin(3x))/log(2.5x)-(atan(mod8)^3*tan(x)/"
      "(asin(x)-acos(x)))";
  s21::Model model;
  int status = model.CheckInput(input);
  EXPECT_EQ(status, 1);
}

TEST(Check, Check_Inorrect_Input2) {
  std::string input = "(123mod12*(-2)";
  s21::Model model;
  int status = model.CheckInput(input);
  EXPECT_EQ(status, 1);
}

TEST(Check, Check_Inorrect_Input3) {
  std::string input = "(sqrt(144)*8mod3)+ln()/log(25x)-(atan(3x)^3*tan(x)/(asin(x)-acos(x)))";
  s21::Model model;
  int status = model.CheckInput(input);
  EXPECT_EQ(status, 1);
}

TEST(Check, Check_Inorrect_Input4) {
  std::string input = "(sqrt(14.4*8mod3,0)+ln(3x)/lg(2.5x)-(atan(3x)^3*tan(x)/"
      "(asin(x)-acos(x)))";
  s21::Model model;
  int status = model.CheckInput(input);
  EXPECT_EQ(status, 1);
}

TEST(Check, Check_Inorrect_Input5) {
  std::string input = "asin(x+cos(x))mod4/";
  s21::Model model;
  int status = model.CheckInput(input);
  EXPECT_EQ(status, 1);
}