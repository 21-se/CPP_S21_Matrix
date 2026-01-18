#include "s21_matrix_oop.h"

double Module(double number) { return number > 0 ? number : -number; }

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool status = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    status = false;
  } else {
    for (int i = 0; i < rows_ && status; ++i) {
      for (int j = 0; j < cols_ && status; ++j) {
        if (Module(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) status = false;
      }
    }
  }

  return status;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Matrix dimensions must be equal for summation");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Matrix dimensions must be equal for summation");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error("Cols must be equal rows other matrix");
  }

  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k)
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
    }
  }

  FreeMatrix();
  rows_ = result.rows_;
  cols_ = result.cols_;
  matrix_ = result.matrix_;

  result.matrix_ = nullptr;
  result.rows_ = 0;
  result.cols_ = 0;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);

  for (int i = 0; i < cols_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }

  return result;
}

S21Matrix S21Matrix::GetMinorMatrix(int row, int col) const {
  if (rows_ <= 1 || cols_ <= 1) {
    throw std::logic_error("Cannot get minor from matrix smaller than 2x2");
  }

  S21Matrix result(rows_ - 1, cols_ - 1);
  int r = 0;
  for (int i = 0; i < rows_; ++i) {
    if (i != row) {
      int c = 0;
      for (int j = 0; j < cols_; j++) {
        if (j != col) {
          result.matrix_[r][c] = matrix_[i][j];
          ++c;
        }
      }
      ++r;
    }
  }

  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::logic_error(
        "The matrix must be square to calculate the determinant");
  }
  double result = 0;
  if (rows_ == 1)
    result = matrix_[0][0];
  else if (rows_ == 2)
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  else {
    result = 0;
    for (int j = 0; j < rows_; ++j) {
      S21Matrix minor_matrix = GetMinorMatrix(0, j);
      double minor = minor_matrix.Determinant();
      result += (j % 2 == 0 ? 1 : -1) * matrix_[0][j] * minor;
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::logic_error(
        "The matrix must be square to calculate CalcComplements");
  }

  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1.0;
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        S21Matrix minor_matrix = GetMinorMatrix(i, j);
        double minor = minor_matrix.Determinant();
        result.matrix_[i][j] = ((i + j) % 2 == 0 ? 1.0 : -1.0) * minor;
      }
    }
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0.0) {
    throw std::logic_error("The determinant of the matrix is 0.");
  }

  if (rows_ == 1) {
    S21Matrix result(1, 1);
    result.matrix_[0][0] = 1 / matrix_[0][0];
    return result;
  }
  S21Matrix complements = CalcComplements();
  S21Matrix result = complements.Transpose();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] /= det;
    }
  }

  return result;
}