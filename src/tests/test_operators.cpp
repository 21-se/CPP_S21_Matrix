#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(OperatorParenthesesTest, GetSet) {
  S21Matrix M;
  M(1, 1) = 7.5;
  EXPECT_DOUBLE_EQ(M(1, 1), 7.5);
}

TEST(OperatorParenthesesTest, OutOfBounds) {
  S21Matrix M(4, 4);
  EXPECT_THROW(M(5, 5), std::out_of_range);
  EXPECT_THROW(M(-1, 0), std::out_of_range);
  EXPECT_THROW(M(-1, 3), std::out_of_range);
  EXPECT_THROW(M(3, 4), std::out_of_range);
}

TEST(OperatorParenthesesTest, ConstRead) {
  S21Matrix M(2, 2);
  M(1, 1) = 10.1;

  S21Matrix& M_const = M;
  double value = static_cast<const S21Matrix&>(M_const)(1, 1);

  EXPECT_DOUBLE_EQ(value, 10.1);
}

TEST(OperatorParenthesesTest, ConstReadOutOfBounds) {
  const S21Matrix M(4, 4);
  EXPECT_THROW(M(4, 4), std::out_of_range);
  EXPECT_THROW(M(-1, 0), std::out_of_range);
  EXPECT_THROW(M(-1, 3), std::out_of_range);
  EXPECT_THROW(M(3, 4), std::out_of_range);
}

TEST(OperatorAssignment, Basic) {
  S21Matrix A;
  S21Matrix B(2, 2);

  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 1.0;
  B(1, 1) = 8.0;

  A = B;

  EXPECT_EQ(A.GetRows(), B.GetRows());
  EXPECT_EQ(A.GetCols(), B.GetCols());
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(OperatorAssignment, Itself) {
  S21Matrix A(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 9.0;
  A(1, 0) = 3.0;
  A(1, 1) = 8.0;

  A = A;

  EXPECT_DOUBLE_EQ(A(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 9.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 8.0);
}

TEST(OperatorSum, Functional) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1.0;
  B(0, 0) = 2.0;

  S21Matrix C = A + B;

  EXPECT_DOUBLE_EQ(C(0, 0), 3.0);
  EXPECT_DOUBLE_EQ(A(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(B(0, 0), 2.0);
}

TEST(OperatorSum, DimensionMismatchException) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);

  EXPECT_THROW({ S21Matrix C = A + B; }, std::logic_error);
}

TEST(OperatorSum, DifferentRowsException) {
  S21Matrix A(5, 5);
  S21Matrix B(4, 5);

  EXPECT_THROW(A + B, std::logic_error);
}

TEST(OperatorSub, Basic) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1.0;
  B(0, 0) = 2.0;

  S21Matrix C = A - B;

  EXPECT_DOUBLE_EQ(C(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(A(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(B(0, 0), 2.0);
}

TEST(OperatorSub, DimensionMismatchException) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);

  EXPECT_THROW({ S21Matrix C = A - B; }, std::logic_error);
}

TEST(OperatorSub, DifferentRowsException) {
  S21Matrix A(5, 5);
  S21Matrix B(4, 5);

  EXPECT_THROW(A - B, std::logic_error);
}

TEST(OperatorMulNum, Basic) {
  S21Matrix M;
  M(0, 0) = 1;
  M(0, 1) = 2;
  M(0, 2) = 3;
  M(1, 0) = 2;
  M(1, 1) = 4;
  M(1, 2) = 6;
  M(2, 0) = 7;
  M(2, 1) = 8;
  M(2, 2) = 9;

  double num = 3;

  double expected[3][3] = {
      {3.0, 6.0, 9.0}, {6.0, 12.0, 18.0}, {21.0, 24.0, 27.0}};

  S21Matrix N = M * num;

  for (int i = 0; i < N.GetRows(); ++i) {
    for (int j = 0; j < N.GetCols(); ++j) {
      EXPECT_DOUBLE_EQ(N(i, j), expected[i][j]);
    }
  }
}

TEST(OperatorMulMatrix, DifferentDimensions) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);

  for (int i = 0; i < 3; ++i) A(i, 0) = 1.0, A(i, 1) = 2.0;
  for (int j = 0; j < 3; ++j) B(0, j) = 3.0, B(1, j) = 4.0;

  S21Matrix C = A * B;

  EXPECT_EQ(C.GetRows(), 3);
  EXPECT_EQ(C.GetCols(), 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_DOUBLE_EQ(C(i, j), 11.0);
    }
  }
}

TEST(OperatorMulMatrix, ExceptionMismatch) {
  S21Matrix A(3, 3);
  S21Matrix B(2, 2);

  EXPECT_THROW(A * B, std::logic_error);
}

TEST(OperatorMulMatrix, Matrix1x1) {
  S21Matrix A(3, 1);
  S21Matrix B(1, 1);

  A(0, 0) = 2.0;
  A(1, 0) = 3.0;
  A(2, 0) = 4.0;
  B(0, 0) = 10.0;

  S21Matrix C = A * B;

  EXPECT_EQ(C.GetRows(), 3);
  EXPECT_EQ(C.GetCols(), 1);
  EXPECT_DOUBLE_EQ(C(0, 0), 20.0);
  EXPECT_DOUBLE_EQ(C(1, 0), 30.0);
  EXPECT_DOUBLE_EQ(C(2, 0), 40.0);
}

TEST(OperatorMulMatrix, SelfMultiplication) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 1.0;
  A(1, 0) = 1.0;
  A(1, 1) = 1.0;

  // Матрица из единиц при умножении на себя 2x2 дает матрицу из двоек
  S21Matrix C = A * A;

  EXPECT_DOUBLE_EQ(C(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(C(1, 1), 2.0);
}

TEST(OperatorMulMatrix, ConstCheck) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 5.0;
  B(0, 0) = 2.0;

  S21Matrix C = A * B;

  EXPECT_DOUBLE_EQ(A(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(B(0, 0), 2.0);
}

TEST(OperatorEq, BasicEqual) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);

  A(0, 0) = 1.1;
  B(0, 0) = 1.1;

  EXPECT_TRUE(A.EqMatrix(B));
  EXPECT_TRUE(A == B);
}

TEST(OperatorEq, NotEqual) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1.0;
  B(0, 0) = 2.0;

  EXPECT_FALSE(A == B);
}

TEST(OperatorEq, DifferentDimensions) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 3);

  EXPECT_FALSE(A == B);
}

TEST(OperatorSumAssignment, Basic) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 1.1;
  A(0, 1) = 2.2;
  A(1, 0) = 3.3;
  A(1, 1) = 4.4;

  B(0, 0) = 1.0;
  B(0, 1) = 1.0;
  B(1, 0) = 1.0;
  B(1, 1) = 1.0;

  S21Matrix& ref = (A += B);

  EXPECT_DOUBLE_EQ(A(0, 0), 2.1);
  EXPECT_DOUBLE_EQ(A(0, 1), 3.2);
  EXPECT_DOUBLE_EQ(A(1, 0), 4.3);
  EXPECT_DOUBLE_EQ(A(1, 1), 5.4);

  EXPECT_EQ(&ref, &A);
}

TEST(OperatorSumAssignment, ExpectThrow) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 2);

  EXPECT_THROW(A += B, std::logic_error);
}

TEST(OperatorSumAssignment, Chain) {
  S21Matrix A(1, 1);
  S21Matrix B(1, 1);
  S21Matrix C(1, 1);

  A(0, 0) = 1.0;
  B(0, 0) = 2.0;
  C(0, 0) = 3.0;

  A += B += C;

  EXPECT_DOUBLE_EQ(A(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(B(0, 0), 5.0);
}

TEST(OperatorSubAssignment, Basic) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 10.5;
  A(0, 1) = 20.5;
  B(0, 0) = 5.0;
  B(0, 1) = 10.0;

  S21Matrix& ref = (A -= B);

  EXPECT_DOUBLE_EQ(A(0, 0), 5.5);
  EXPECT_DOUBLE_EQ(A(0, 1), 10.5);

  EXPECT_EQ(&ref, &A);
}

TEST(OperatorSubAssignment, ExpectThrow) {
  S21Matrix A(2, 2);
  S21Matrix B(1, 1);

  EXPECT_THROW(A -= B, std::logic_error);
}
TEST(OperatorMulNumberAssignment, Basic) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.1;
  m(0, 1) = 2.2;
  m(1, 0) = 3.3;
  m(1, 1) = 4.4;

  m *= 2.0;

  EXPECT_DOUBLE_EQ(m(0, 0), 2.2);
  EXPECT_DOUBLE_EQ(m(0, 1), 4.4);
  EXPECT_DOUBLE_EQ(m(1, 0), 6.6);
  EXPECT_DOUBLE_EQ(m(1, 1), 8.8);
}

TEST(OperatorMulMatrixAssignment, Basic) {
  S21Matrix m1(2, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;

  S21Matrix m2(3, 2);
  m2(0, 0) = 7;
  m2(0, 1) = 8;
  m2(1, 0) = 9;
  m2(1, 1) = 10;
  m2(2, 0) = 11;
  m2(2, 1) = 12;
  m1 *= m2;

  ASSERT_EQ(m1.GetRows(), 2);
  ASSERT_EQ(m1.GetCols(), 2);
  EXPECT_DOUBLE_EQ(m1(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 154.0);
}

TEST(OperatorMulMatrixAssignment, ExpectThrow) {
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 2);

  EXPECT_THROW(m1 *= m2, std::logic_error);
}

TEST(OperatorMulMatrixAssignment, Chain) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;

  S21Matrix m2(2, 2);
  m2(0, 0) = 2;
  m2(0, 1) = 2;
  m2(1, 0) = 2;
  m2(1, 1) = 2;

  (m *= m2) *= 10.0;

  EXPECT_DOUBLE_EQ(m(0, 0), 40.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 40.0);
}
