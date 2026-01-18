#include <gtest/gtest.h>
#include "../s21_matrix_oop.h"

TEST(Accessors, GetRowsCols) {
  S21Matrix A;
  EXPECT_EQ(A.GetRows(), 3);
  EXPECT_EQ(A.GetCols(), 3);
}

TEST(Accessors, SetRows) {
  S21Matrix A;
  A.SetRows(7);
  
  EXPECT_EQ(A.GetRows(), 7);
  EXPECT_EQ(A.GetCols(), 3);
}

TEST(Accessors, SetCols) {
  S21Matrix A;
  A.SetCols(5);

  EXPECT_EQ(A.GetRows(), 3);
  EXPECT_EQ(A.GetCols(), 5);
}

TEST(Accessors, SetRowsCols) {
  S21Matrix A;
  A.SetRows(1);
  A.SetCols(1);
  
  EXPECT_EQ(A.GetRows(), 1);
  EXPECT_EQ(A.GetCols(), 1);
}

TEST(Accessors, SetNegativeRows) {
  S21Matrix A;

  EXPECT_THROW(A.SetRows(-1), std::invalid_argument);
}

TEST(Accessors, SetZeroCols) {
  S21Matrix A;

  EXPECT_THROW(A.SetCols(0), std::invalid_argument);
}

TEST(Accessors, SetNegativeRowsCols) {
  S21Matrix A;

  EXPECT_THROW(A.SetRows(-3), std::invalid_argument);
  EXPECT_THROW(A.SetCols(-3), std::invalid_argument);
}

TEST(Accessors, SetTheSameRowsCols) {
  S21Matrix A;
  A.SetRows(3);
  A.SetCols(3);

  EXPECT_EQ(A.GetRows(), 3);
  EXPECT_EQ(A.GetCols(), 3);
}