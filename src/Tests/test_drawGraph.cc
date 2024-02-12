#include "test.h"

TEST(Check, Draw_Graph) {
  std::string input = "x^2";
  s21::Model model;
  std::pair<std::vector<double>, std::vector<double>> result = model.DrawGraphic(input, -1, 1);
  std::vector<double> x;
  for (double i = -1.0; i < 1.0; i += 0.01) {
    x.push_back(i);
  }
  std::vector<double> y;
  for (double i = -1.0; i < 1.0; i += 0.01) {
    y.push_back(pow(i, 2));
  }
  std::pair<std::vector<double>, std::vector<double>> real_result = {x, y};
  for (double i = 0; i < result.first.size(); ++i) {
    EXPECT_FLOAT_EQ(result.first[i], real_result.first[i]);
    EXPECT_FLOAT_EQ(result.second[i], real_result.second[i]);
  }
}