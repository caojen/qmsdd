#pragma once

class Complex {
public:
  int real;
  int imag;

  char vch; // virtual char, if this complex value is a symbol

  Complex(int real, int imag = 0);
  Complex(char vch);
  inline bool isvirtual() const;
  bool operator==(const Complex& other) const;
  bool operator<(const Complex& other) const;
  bool operator>(const Complex& other) const;
};
