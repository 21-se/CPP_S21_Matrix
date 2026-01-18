#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(ConstructorsTest, Default) {
  S21Matrix M;

  EXPECT_EQ(M.GetRows(), 3);
  EXPECT_EQ(M.GetCols(), 3);
}

TEST(ConstructorsTest, Parameters) {
  S21Matrix M(5, 5);

  EXPECT_EQ(M.GetRows(), 5);
  EXPECT_EQ(M.GetCols(), 5);

  for (int i = 0; i < M.GetRows(); ++i) {
    for (int j = 0; j < M.GetCols(); ++j) {
      EXPECT_DOUBLE_EQ(M(i, j), 0.0);
    }
  }
}

TEST(ConstructorsTest, NegativeRowParameter) {
  EXPECT_THROW(S21Matrix M(-1, 5), std::invalid_argument);
}

TEST(ConstructorsTest, ZeroColumnParameter) {
  EXPECT_THROW(S21Matrix M(3, 0), std::invalid_argument);
}

TEST(ConstructorsTest, CopyConstructor) {
  S21Matrix M(2, 2);
  M(0, 0) = 5.5;
  M(1, 1) = 3.3;

  S21Matrix C(M);

  EXPECT_EQ(C.GetRows(), M.GetRows());
  EXPECT_EQ(C.GetRows(), M.GetCols());

  for (int i = 0; i < C.GetRows(); ++i) {
    for (int j = 0; j < C.GetCols(); ++j) {
      EXPECT_DOUBLE_EQ(C(i, j), M(i, j));
    }
  }
  // Проверка на то что изменение копии не изменяет оригинал
  C(0, 1) = 1.1;
  C(1, 0) = 4.4;

  EXPECT_NE(C(0, 1), M(0, 1));
  EXPECT_NE(C(1, 0), M(1, 0));
}

TEST(ConstructorsTest, CopyConstructorNullPtrMatrix) {
  S21Matrix M;
  S21Matrix N(std::move(M));  // Матрица M стала пустой (matrix_ == nullptr)

  S21Matrix C(M);

  EXPECT_EQ(C.GetRows(), 0);
  EXPECT_EQ(C.GetRows(), 0);
}

TEST(ConstructorsTest, TransferConstructor) {
  S21Matrix M(2, 2);
  M(0, 0) = 5.5;
  M(1, 1) = 3.3;

  S21Matrix N(
      std::move(M));  // std::move принудительно делает M rvalue - выражением
  // std::move: Не копирует данные, а "разрешает" забрать их.
  // Без него вызовется конструктор копирования.

  EXPECT_EQ(N.GetRows(), 2);
  EXPECT_EQ(N.GetCols(), 2);
  EXPECT_DOUBLE_EQ(N(0, 0), 5.5);
  EXPECT_DOUBLE_EQ(N(1, 1), 3.3);

  EXPECT_EQ(M.GetRows(), 0);
  EXPECT_EQ(M.GetCols(), 0);
}