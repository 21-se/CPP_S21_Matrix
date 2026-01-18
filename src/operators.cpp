#include "s21_matrix_oop.h"

double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || i < 0 || j >= cols_) {
    throw std::out_of_range("Index out of bounds");
  }
  return matrix_[i][j];
}

double S21Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= rows_ || i < 0 || j >= cols_) {
    throw std::out_of_range("Index out of bounds");
  }
  return matrix_[i][j];
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);

  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);

  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);

  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);

  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) return *this;

  FreeMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  S21Matrix T(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      T.matrix_[i][j] = other.matrix_[i][j];
    }
  }
  matrix_ = T.matrix_;

  T.matrix_ = nullptr;
  T.rows_ = 0;
  T.cols_ = 0;
  /* Альтернативный вариант
  S21Matrix temp(other); // Используем конструктор копирования
  Просто меняем местами содержимое текущего объекта и временного
  std::swap(rows_, temp.rows_);
  std::swap(cols_, temp.cols_);
  std::swap(matrix_, temp.matrix_);
  */

  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}