#include "s21_matrix_oop.h"
// #include <algorithm> для std::copy

void S21Matrix::CreateMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::FreeMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Matrix dimensions must be non-negative");
  }
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(nullptr) {
  // Обработка на пустую матрицу
  if (other.matrix_ != nullptr) {
    CreateMatrix();
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
    /* В современной разработке используют std::copy
    for (int i = 0; i < rows_; ++i) {
      std::copy(other.matrix_[i], other.matrix_[i] + cols_, matrix_[i]);
    }
      */
  } else {
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  // спецификатор noexcept указывается для обеспечения эффективности
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;

  /* Забираем ресурсы другого объекта (другая реализация)
  S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(0), cols_(0), matrix_(nullptr) { // Сначала делаем текущий объект
  пустым std::swap(rows_, other.rows_); std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
    Если вдруг добавить в класс какой-то сложный объект, swap гарантирует,
    что старый объект получит «чистое» состояние текущего.
  }
  */
}

S21Matrix::~S21Matrix() { FreeMatrix(); }