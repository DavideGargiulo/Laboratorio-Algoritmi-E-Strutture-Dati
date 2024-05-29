#include "zlasdtest/test.hpp"
#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>
#include "vector/vector.hpp"
#include <string>

/* ************************************************************************** */

int main() {
  std::string text = "1) LasdTest";
  std::string text2 = "2) MyTest";
  std::string text3 = "3) Goodbye";
  int scelta = 0;

  lasd::Vector<int> startColor1(3);
  lasd::Vector<int> endColor1(3);
  lasd::Vector<int> startColor2(3);
  lasd::Vector<int> endColor2(3);
  lasd::Vector<int> startColor3(3);
  lasd::Vector<int> endColor3(3);

  startColor1[0] = 255; startColor1[1] = 100; startColor1[2] = 100;
  endColor1[0] = 100; endColor1[1] = 100; endColor1[2] = 255;

  startColor2[0] = 100; startColor2[1] = 255; startColor2[2] = 100;
  endColor2[0] = 255; endColor2[1] = 255; endColor2[2] = 100;

  startColor3[0] = 100; startColor3[1] = 255; startColor3[2] = 255;
  endColor3[0] = 255; endColor3[1] = 100; endColor3[2] = 255;

  auto printGradientText = [](const std::string& text, lasd::Vector<int>& startColor, lasd::Vector<int>& endColor) {
    int length = text.length();
    for (int i = 0; i < length; ++i) {
      float ratio = static_cast<float>(i) / (length - 1);

      int r = static_cast<int>(startColor[0] * (1 - ratio) + endColor[0] * ratio);
      int g = static_cast<int>(startColor[1] * (1 - ratio) + endColor[1] * ratio);
      int b = static_cast<int>(startColor[2] * (1 - ratio) + endColor[2] * ratio);

      std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m" << text[i];
    }
    std::cout << "\033[0m" << std::endl;
  };

  do {
    printGradientText(text, startColor1, endColor1);
    printGradientText(text2, startColor2, endColor2);
    printGradientText(text3, startColor3, endColor3);
    std::cin >> scelta;

    switch (scelta) {
    case 1:
      lasdtest();
      break;
    case 2:
      mytest();
      break;
    case 3:
      return 0;
    default:
      break;
    }
  } while (scelta != 3);

  return 0;
}
