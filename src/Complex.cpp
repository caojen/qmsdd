#include "Complex.hpp"

Complex::Complex(int real, int imag) {
  this->real = real;
  this->imag = imag;
  this->vch = 0;
}

Complex::Complex(char vch) {
  this->real = 0;
  this->imag = 0;
  this->vch = vch;
}

bool Complex::isvirtual() const {
  return this->vch == 0;
}

bool Complex::operator==(const Complex& other) const {
  return this->real == other.real &&
    this->imag == other.imag &&
    this->vch == other.vch;
}

bool Complex::operator<(const Complex& other) const {
  return this->real < other.real ||
   this->real == other.real && this->imag < other.imag;
}

bool Complex::operator>(const Complex& other) const {
  return !(*this == other) && !(*this < other);
}
