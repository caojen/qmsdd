#pragma once

#include <iostream>

class Complex {
public:
  int real;
  int imag;

  char vch; // virtual char, if this complex value is a symbol

  Complex(int real = 0, int imag = 0);
  Complex(char vch);
  bool isvirtual() const;
  bool operator==(const Complex& other) const;
  bool operator<(const Complex& other) const;
  bool operator>(const Complex& other) const;

  friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};
