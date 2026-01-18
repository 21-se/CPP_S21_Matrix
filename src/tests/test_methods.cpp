#include <gtest/gtest.h>
#include "../s21_matrix_oop.h"

TEST(EqMatrixTest, Equal) {
  S21Matrix A;
  A(1, 2) = 4.9;
  A(2, 2) = 0.000001;

  S21Matrix B;
  B(1, 2) = 4.9;
  B(2, 2) = 0.000001;

  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(EqMatrixTest, DifferentRows) {
  S21Matrix A(5, 3);
  S21Matrix B(3, 3);

  EXPECT_FALSE(A.EqMatrix(B));
}

TEST(EqMatrixTest, DifferentCols) {
  S21Matrix A(3, 2);
  S21Matrix B(3, 3);

  EXPECT_FALSE(A.EqMatrix(B));
}

TEST(EqMatrixTest, DifferentValues) {
  S21Matrix A;
  A(1, 2) = 4.9;
  A(2, 2) = 0.000002;

  S21Matrix B;
  B(1, 2) = 4.9;
  B(2, 2) = 0.000001;

  EXPECT_FALSE(A.EqMatrix(B));
}

TEST(SumMatrixTest, Basic) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  
  A(0, 0) = 1.0; A(0, 1) = 2.0;
  A(1, 0) = 3.0; A(1, 1) = 4.0;
  
  B(0, 0) = 5.0; B(0, 1) = 6.0;
  B(1, 0) = 7.0; B(1, 1) = 8.0;
  
  A.SumMatrix(B);
  
  EXPECT_DOUBLE_EQ(A(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 12.0);
}

TEST(SumMatrixTest, ExpectionThrow) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 4);

  EXPECT_THROW(A.SumMatrix(B), std::logic_error);
}

TEST(SubMatrixTest, Basic) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  
  A(0, 0) = 1.0; A(0, 1) = 9.0;
  A(1, 0) = 3.0; A(1, 1) = 8.0;
  
  B(0, 0) = 5.0; B(0, 1) = 6.0;
  B(1, 0) = 1.0; B(1, 1) = 8.0;
  
  A.SubMatrix(B);

  EXPECT_DOUBLE_EQ(A(0, 0), -4.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 0.0);
}

TEST(SubMatrixTest, ExpectionThrow) {
  S21Matrix A(3, 3);
  S21Matrix B(4, 4);

  EXPECT_THROW(A.SubMatrix(B), std::logic_error);
}

TEST(MulNumberTest, Basic) {
  S21Matrix A(2, 2);
  double num = 3.0;
  
  A(0, 0) = 1.0; A(0, 1) = 9.0;
  A(1, 0) = 3.0; A(1, 1) = 8.0;
  
  A.MulNumber(num);

  EXPECT_DOUBLE_EQ(A(0, 0), 3.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 27.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 9.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 24.0);
}

TEST(MulMatrixTest, Basic) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  
  A(0, 0) = 1.0; A(0, 1) = 9.0;
  A(1, 0) = 3.0; A(1, 1) = 8.0;
  A(2, 0) = 2.0; A(2, 1) = 5.0;
  
  B(0, 0) = 5.0; B(0, 1) = 6.0; B(0, 2) = 4.0;
  B(1, 0) = 1.0; B(1, 1) = 8.0; B(1, 2) = 7.0;

  double expected[3][3] = {
    {14.0, 78.0, 67.0},
    {23.0, 82.0, 68.0},
    {15.0, 52.0, 43.0}
  };
  
  A.MulMatrix(B);

  EXPECT_EQ(A.GetRows(), A.GetCols());

  for (int i = 0; i < A.GetRows(); ++i) {
    for (int j = 0; j < A.GetCols(); ++j) {
      EXPECT_DOUBLE_EQ(A(i, j), expected[i][j]);
    }
  }
}

TEST(MulMatrixTest, ExpectionThrow) {
  S21Matrix A(3, 3);
  S21Matrix B(4, 3);

  EXPECT_THROW(A.MulMatrix(B), std::logic_error);
}

TEST(TransponseTest, basic) {
  S21Matrix A(3, 2);
  A(0, 0) = 1; A(0, 1) = 2;
  A(1, 0) = 3; A(1, 1) = 4;
  A(2, 0) = 5; A(2, 1) = 6;

  S21Matrix B = A.Transpose();

  EXPECT_EQ(B.GetRows(), 2);
  EXPECT_EQ(B.GetCols(), 3);
  EXPECT_DOUBLE_EQ(B(0, 0), 1);
  EXPECT_DOUBLE_EQ(B(0, 2), 5);
  EXPECT_DOUBLE_EQ(B(1, 1), 4);

  // Проверка, что исходная матрица не изменилась
  EXPECT_EQ(A.GetRows(), 3);
}

TEST(DeterminantTest, Matrix1x1) {
  S21Matrix A(1, 1);
  A(0, 0) = 5.5;
  double det = A.Determinant();
  EXPECT_NEAR(det, 5.5, 1e-7);
}

TEST(DeterminantTest, Matrix2x2) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0; A(0, 1) = 2.0;
  A(1, 0) = 3.0; A(1, 1) = 4.0;
  
  double det = A.Determinant();
  EXPECT_NEAR(det, -2.0, 1e-7);
}

TEST(DeterminantTest, Matrix3x3_NonZero) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0; A(0, 1) = 2.0; A(0, 2) = 3.0;
  A(1, 0) = 4.0; A(1, 1) = 5.0; A(1, 2) = 6.0;
  A(2, 0) = 7.0; A(2, 1) = 8.0; A(2, 2) = 10.0;
  
  double det = A.Determinant();
  EXPECT_NEAR(det, -3.0, 1e-7);
}

TEST(DeterminantTest, Matrix3x3_Zero) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0; A(0, 1) = 2.0; A(0, 2) = 3.0;
  A(1, 0) = 4.0; A(1, 1) = 5.0; A(1, 2) = 6.0;
  A(2, 0) = 7.0; A(2, 1) = 8.0; A(2, 2) = 9.0;
  
  double det = A.Determinant();
  EXPECT_NEAR(det, 0.0, 1e-7);
}

TEST(DeterminantTest, Matrix4x4) {
  S21Matrix A(4, 4);
  A(0, 0) = 1; A(0, 1) = 0; A(0, 2) = 2; A(0, 3) = -1;
  A(1, 0) = 0; A(1, 1) = 1; A(1, 2) = 0; A(1, 3) = 2;
  A(2, 0) = 2; A(2, 1) = 0; A(2, 2) = 1; A(2, 3) = 0;
  A(3, 0) = 0; A(3, 1) = 2; A(3, 2) = 0; A(3, 3) = 1;
  
  double det = A.Determinant();
  EXPECT_NEAR(det, 9.0, 1e-7);
}

TEST(DeterminantTest, NonSquareMatrix) {
  S21Matrix A(2, 3);
  EXPECT_THROW(A.Determinant(), std::logic_error);
}

TEST(CalcComplementsTest, Matrix1x1) {
    S21Matrix M(1, 1);
    M(0, 0) = 5.0;

    S21Matrix res = M.CalcComplements();
    
    EXPECT_EQ(res.GetRows(), 1);
    EXPECT_EQ(res.GetCols(), 1);
    EXPECT_DOUBLE_EQ(res(0, 0), 1.0); 
}

TEST(CalcComplementsTest, Matrix3x3_Normal) {
  S21Matrix M(3, 3);
  M(0, 0) = 1; M(0, 1) = 2; M(0, 2) = 3;
  M(1, 0) = 0; M(1, 1) = 4; M(1, 2) = 2;
  M(2, 0) = 5; M(2, 1) = 2; M(2, 2) = 1;

  S21Matrix res = M.CalcComplements();

  EXPECT_DOUBLE_EQ(res(0, 0), 0);
  EXPECT_DOUBLE_EQ(res(0, 1), 10);
  EXPECT_DOUBLE_EQ(res(0, 2), -20);
  EXPECT_DOUBLE_EQ(res(1, 0), 4);
  EXPECT_DOUBLE_EQ(res(1, 1), -14);
  EXPECT_DOUBLE_EQ(res(1, 2), 8);
  EXPECT_DOUBLE_EQ(res(2, 0), -8);
  EXPECT_DOUBLE_EQ(res(2, 1), -2);
  EXPECT_DOUBLE_EQ(res(2, 2), 4);
}

TEST(CalcComplementsTest, NonSquareMatrix) {
  S21Matrix m(2, 3);
  EXPECT_THROW(m.CalcComplements(), std::logic_error);
}

TEST(CalcComplementsTest, Immutability) {
  S21Matrix M(2, 2);
  M(0, 0) = 1; M(0, 1) = 2;
  M(1, 0) = 3; M(1, 1) = 4;
  
  M.CalcComplements();
  
  EXPECT_DOUBLE_EQ(M(0, 0), 1);
  EXPECT_DOUBLE_EQ(M(1, 1), 4);
}

TEST(InverseMatrixTest, Matrix1x1) {
  S21Matrix M(1, 1);
  M(0, 0) = 5.0;
  S21Matrix res = M.InverseMatrix();
  
  EXPECT_NEAR(res(0, 0), 0.2, 1e-7);
}

TEST(InverseMatrixTest, ZeroDeterminant) {
  S21Matrix M(3, 3);
  
  M(0, 0) = 1; M(0, 1) = 2; M(0, 2) = 3;
  M(1, 0) = 2; M(1, 1) = 4; M(1, 2) = 6;
  M(2, 0) = 7; M(2, 1) = 8; M(2, 2) = 9;
  
  EXPECT_THROW(M.InverseMatrix(), std::logic_error);
}

TEST(InverseMatrixTest, NonSquare) {
  S21Matrix M(3, 2);
  EXPECT_THROW(M.InverseMatrix(), std::logic_error);
}

TEST(InverseMatrixTest, SmallDeterminant) {
  S21Matrix M(2, 2);
  M(0, 0) = 0.0001; M(0, 1) = 0.0;
  M(1, 0) = 0.0;    M(1, 1) = 0.0001;
  
  EXPECT_NO_THROW(M.InverseMatrix());
  
  S21Matrix res = M.InverseMatrix();
  EXPECT_NEAR(res(0, 0), 10000.0, 1e-7);
}

TEST(InverseMatrixTest, Matrix3x3_IdentityCheck) {
  S21Matrix M(3, 3);
  M(0, 0) = 2; M(0, 1) = 5; M(0, 2) = 7;
  M(1, 0) = 6; M(1, 1) = 3; M(1, 2) = 4;
  M(2, 0) = 5; M(2, 1) = -2; M(2, 2) = -3;

  S21Matrix inv = M.InverseMatrix();
  S21Matrix identity = M * inv;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (i == j)
        EXPECT_NEAR(identity(i, j), 1.0, 1e-7);
      else
        EXPECT_NEAR(identity(i, j), 0.0, 1e-7);
    }
  }
}