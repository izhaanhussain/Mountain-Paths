#include "color.hpp"

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed...
  const int kMaxColorValue = 255;
  if (r >= 0 && r <= kMaxColorValue) {
    red_ = r;
  } else {
    throw std::invalid_argument("Number not in RGB range!");
  }
  if (g >= 0 && g <= kMaxColorValue) {
    green_ = g;
  } else {
    throw std::invalid_argument("Number not in RGB range!");
  }
  if (b >= 0 && b <= kMaxColorValue) {
    blue_ = b;
  } else {
    throw std::invalid_argument("Number not in RGB range!");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}