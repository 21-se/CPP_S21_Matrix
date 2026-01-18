#include "s21_matrix_oop.h"

void S21Matrix::SetRows(int new_rows) {
  if (new_rows < 1) throw std::invalid_argument("Rows must be > 0");
  if (new_rows != rows_) {
    S21Matrix T(new_rows, cols_);
    int less_rows = new_rows < rows_ ? new_rows : rows_;
    for (int i = 0; i < less_rows; ++i) {
      for (int j = 0; j < cols_; ++j) {
        T.matrix_[i][j] = matrix_[i][j];
      }
    }
    FreeMatrix();

    this->rows_ = T.rows_;
    this->cols_ = T.cols_;
    this->matrix_ = T.matrix_;

    T.rows_ = 0;
    T.cols_ = 0;
    T.matrix_ = nullptr;
  }
}

void S21Matrix::SetCols(int new_cols) {
  if (new_cols < 1) throw std::invalid_argument("Cols must be > 0");
  if (new_cols != cols_) {
    S21Matrix T(rows_, new_cols);
    int less_cols = new_cols < cols_ ? new_cols : cols_;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < less_cols; ++j) {
        T.matrix_[i][j] = matrix_[i][j];
      }
    }
    FreeMatrix();

    this->rows_ = T.rows_;
    this->cols_ = T.cols_;
    this->matrix_ = T.matrix_;

    T.rows_ = 0;
    T.cols_ = 0;
    T.matrix_ = nullptr;
  }
}