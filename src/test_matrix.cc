#include <gtest/gtest.h>

#include "matrix_oop.h"

TEST(test_create, t1) { ASSERT_ANY_THROW(Matrix matrix(-1, -1)); }

TEST(test_create, t3) {
  Matrix matrix(10, 10);
  for (int i = 0; i < matrix.rows(); i++) {
    for (int j = 0; j < matrix.cols(); j++) {
      ASSERT_DOUBLE_EQ(matrix(i, j), 0.0);
    }
  }
}

TEST(test_create, t4) {
  Matrix matrix1(10, 10);
  for (int i = 0; i < matrix1.rows(); i++) {
    matrix1(i, 0) = 15.0;
  }
  Matrix matrix2(matrix1);
  for (int i = 0; i < matrix1.rows(); i++) {
    for (int j = 0; j < matrix1.cols(); j++) {
      ASSERT_DOUBLE_EQ(matrix1(i, j), matrix2(i, j));
    }
  }
}

TEST(test_create, t5) {
  Matrix matrix1(10, 10);
  matrix1(0, 0) = 15.0;
  Matrix matrix2 = std::move(matrix1);
  ASSERT_EQ(matrix1.rows(), 0);
  ASSERT_EQ(matrix1.cols(), 0);
  ASSERT_DOUBLE_EQ(matrix2(0, 0), 15.0);
}

TEST(test_accessor, t1) {
  Matrix matrix1(1, 1);
  ASSERT_EQ(matrix1.rows(), 1);
  ASSERT_EQ(matrix1.cols(), 1);
}

TEST(test_mutators, t1) {
  Matrix matrix1(1, 1);
  matrix1.set_cols(15);
  matrix1.set_rows(15);
  ASSERT_EQ(matrix1.rows(), 15);
  ASSERT_EQ(matrix1.cols(), 15);
}

TEST(test_mutators, t2) {
  Matrix matrix1(1, 1);
  ASSERT_ANY_THROW(matrix1.set_cols(-1));
  ASSERT_ANY_THROW(matrix1.set_rows(-1));
}

TEST(test_equal, t1) {
  Matrix matrix1(5, 5);
  matrix1(0, 0) = 5.0;
  Matrix matrix2(5, 5);
  matrix2(0, 0) = 5.0;
  ASSERT_TRUE(matrix1.EqMatrix(matrix2));
  ASSERT_TRUE(matrix1 == matrix2);
}

TEST(test_equal, t2) {
  Matrix matrix1(5, 6);
  matrix1(0, 0) = 5.0;
  Matrix matrix2(5, 5);
  matrix2(0, 0) = 5.0;
  ASSERT_FALSE(matrix1.EqMatrix(matrix2));
  ASSERT_FALSE(matrix1 == matrix2);
}

TEST(test_equal, t3) {
  Matrix matrix1(5, 5);
  matrix1(0, 0) = 0.12345677;
  Matrix matrix2(5, 5);
  matrix2(0, 0) = 0.12345670;
  ASSERT_FALSE(matrix1.EqMatrix(matrix2));
  ASSERT_FALSE(matrix1 == matrix2);
}

TEST(test_sum, t1) {
  Matrix matrix1(1, 1);
  Matrix matrix2(1, 2);
  ASSERT_ANY_THROW(matrix1 + matrix2);
  ASSERT_ANY_THROW(matrix1.SumMatrix(matrix2));
  ASSERT_ANY_THROW(matrix1 += matrix2);
}

TEST(test_sum, t2) {
  Matrix matrix1(1, 2);
  matrix1(0, 0) = 15.0;
  matrix1(0, 1) = 1.0;
  Matrix matrix2(1, 2);
  matrix2(0, 0) = 19.0;
  matrix2(0, 1) = 0.0;
  Matrix result = matrix1 + matrix2;
  ASSERT_DOUBLE_EQ(result(0, 0), 34.0);
  ASSERT_DOUBLE_EQ(result(0, 1), 1.0);
  matrix1.SumMatrix(matrix2);
  ASSERT_DOUBLE_EQ(matrix1(0, 0), 34.0);
  ASSERT_DOUBLE_EQ(matrix1(0, 1), 1.0);
  matrix1 += matrix1;
  ASSERT_DOUBLE_EQ(matrix1(0, 0), 68.0);
  ASSERT_DOUBLE_EQ(matrix1(0, 1), 2.0);
}

TEST(test_sub, t1) {
  Matrix matrix1(1, 1);
  Matrix matrix2(1, 2);
  ASSERT_ANY_THROW(matrix1 - matrix2);
  ASSERT_ANY_THROW(matrix1.SubMatrix(matrix2));
  ASSERT_ANY_THROW(matrix1 -= matrix2);
}

TEST(test_sub, t2) {
  Matrix matrix1(1, 2);
  matrix1(0, 0) = 15.0;
  matrix1(0, 1) = 1.0;
  Matrix matrix2(1, 2);
  matrix2(0, 0) = 19.0;
  matrix2(0, 1) = 0.0;
  Matrix result = matrix1 - matrix2;
  ASSERT_DOUBLE_EQ(result(0, 0), -4.0);
  ASSERT_DOUBLE_EQ(result(0, 1), 1.0);
  matrix1.SubMatrix(matrix2);
  ASSERT_DOUBLE_EQ(matrix1(0, 0), -4.0);
  ASSERT_DOUBLE_EQ(matrix1(0, 1), 1.0);
  matrix1 -= matrix1;
  ASSERT_DOUBLE_EQ(matrix1(0, 0), 0.0);
  ASSERT_DOUBLE_EQ(matrix1(0, 1), 0.0);
}

TEST(test_mul_num, t1) {
  Matrix matrix(1, 2);
  matrix(0, 0) = 15.0;
  matrix(0, 1) = 1.0;
  Matrix result1 = matrix * 5.0;
  ASSERT_DOUBLE_EQ(result1(0, 0), 75.0);
  ASSERT_DOUBLE_EQ(result1(0, 1), 5.0);
  matrix.MulNumber(5.0);
  ASSERT_DOUBLE_EQ(matrix(0, 0), 75.0);
  ASSERT_DOUBLE_EQ(matrix(0, 1), 5.0);
  matrix *= 2;
  ASSERT_DOUBLE_EQ(matrix(0, 0), 150.0);
  ASSERT_DOUBLE_EQ(matrix(0, 1), 10.0);
}

TEST(test_mul_matr, t1) {
  Matrix matrix1(5, 3);
  Matrix matrix2(19, 2);
  ASSERT_ANY_THROW(matrix1.MulMatrix(matrix2));
  ASSERT_ANY_THROW(matrix1 * matrix2);
  ASSERT_ANY_THROW(matrix1 *= matrix2);
}

TEST(test_mul_matr, t2) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 0.0;
  matrix1(0, 1) = 1.0;
  matrix1(1, 0) = 1.0;
  matrix1(1, 1) = 30.0;
  Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 30.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 30.0;
  Matrix answer(2, 2);
  answer(0, 0) = 30.0;
  answer(0, 1) = 901.0;
  answer(1, 0) = 30.0;
  answer(1, 1) = 901.0;
  Matrix result = matrix2 * matrix1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ASSERT_DOUBLE_EQ(result(i, j), answer(i, j));
    }
  }
  matrix2.MulMatrix(matrix1);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ASSERT_DOUBLE_EQ(matrix2(i, j), answer(i, j));
    }
  }
}

TEST(test_mul_matr, t3) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 0.0;
  matrix1(0, 1) = 1.0;
  matrix1(1, 0) = 1.0;
  matrix1(1, 1) = 30.0;
  Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 30.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 30.0;
  Matrix answer(2, 2);
  answer(0, 0) = 30.0;
  answer(0, 1) = 901.0;
  answer(1, 0) = 30.0;
  answer(1, 1) = 901.0;
  matrix2 *= matrix1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ASSERT_DOUBLE_EQ(matrix2(i, j), answer(i, j));
    }
  }
}

TEST(test_transpose, t1) {
  Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 30.0;
  matrix(1, 0) = 1.0;
  matrix(1, 1) = 30.0;
  matrix = matrix.Transpose();
  Matrix answer(2, 2);
  answer(0, 0) = 1.0;
  answer(0, 1) = 1.0;
  answer(1, 0) = 30.0;
  answer(1, 1) = 30.0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ASSERT_DOUBLE_EQ(matrix(i, j), answer(i, j));
    }
  }
  ASSERT_EQ(matrix.cols(), 2);
  ASSERT_EQ(matrix.rows(), 2);
}

TEST(test_complements, t1) {
  Matrix matrix(2, 3);
  ASSERT_ANY_THROW(matrix.CalcComplements());
}

TEST(test_complements, t2) {
  Matrix matrix(1, 1);
  matrix = matrix.CalcComplements();
  ASSERT_DOUBLE_EQ(matrix(0, 0), 1.0);
}

TEST(test_complements, t3) {
  Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 4;
  matrix(0, 2) = 5;
  matrix(1, 0) = 2;
  matrix(1, 1) = 3;
  matrix(1, 2) = 6;
  matrix(2, 0) = 9;
  matrix(2, 1) = 8;
  matrix(2, 2) = 7;
  Matrix answer(3, 3);
  answer(0, 0) = -27;
  answer(0, 1) = 40;
  answer(0, 2) = -11;
  answer(1, 0) = 12;
  answer(1, 1) = -38;
  answer(1, 2) = 28;
  answer(2, 0) = 9;
  answer(2, 1) = 4;
  answer(2, 2) = -5;
  matrix = matrix.CalcComplements();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(matrix(i, j), answer(i, j));
    }
  }
}

TEST(test_determinant, t1) {
  Matrix matrix(2, 3);
  ASSERT_ANY_THROW(matrix.Determinant());
}

TEST(test_determinant, t2) {
  Matrix matrix(1, 1);
  matrix(0, 0) = 5;
  ASSERT_DOUBLE_EQ(matrix.Determinant(), 5.0);
}

TEST(test_determinant, t3) {
  Matrix matrix(2, 2);
  matrix(0, 0) = 5;
  matrix(1, 1) = 5;
  ASSERT_DOUBLE_EQ(matrix.Determinant(), 25.0);
}

TEST(test_determinant, t4) {
  Matrix matrix(5, 5);
  matrix(0, 0) = 0;
  matrix(0, 1) = 12;
  matrix(0, 2) = -12;
  matrix(0, 3) = 12;
  matrix(0, 4) = 6;
  matrix(1, 0) = -3;
  matrix(1, 1) = -9;
  matrix(1, 2) = 9;
  matrix(1, 3) = 9;
  matrix(1, 4) = -6;
  matrix(2, 0) = 0;
  matrix(2, 1) = 0;
  matrix(2, 2) = -2;
  matrix(2, 3) = 4;
  matrix(2, 4) = -2;
  matrix(3, 0) = -3;
  matrix(3, 1) = -17;
  matrix(3, 2) = 13;
  matrix(3, 3) = 3;
  matrix(3, 4) = -8;
  matrix(4, 0) = 0;
  matrix(4, 1) = 0;
  matrix(4, 2) = 4;
  matrix(4, 3) = -8;
  matrix(4, 4) = 0;
  ASSERT_DOUBLE_EQ(matrix.Determinant(), -1728);
}

TEST(test_inverse, t1) {
  Matrix matrix(1, 5);
  ASSERT_ANY_THROW(matrix.InverseMatrix());
}

TEST(test_inverse, t2) {
  Matrix matrix(2, 2);
  ASSERT_ANY_THROW(matrix.InverseMatrix());
}

TEST(test_inverse, t3) {
  Matrix matrix(1, 1);
  matrix(0, 0) = 0.2;
  matrix = matrix.InverseMatrix();
  ASSERT_DOUBLE_EQ(matrix(0, 0), 5);
}

TEST(test_inverse, t4) {
  Matrix matrix(3, 3);
  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;
  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;
  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;
  Matrix answer(3, 3);
  answer(0, 0) = 1;
  answer(0, 1) = -1;
  answer(0, 2) = 1;
  answer(1, 0) = -38;
  answer(1, 1) = 41;
  answer(1, 2) = -34;
  answer(2, 0) = 27;
  answer(2, 1) = -29;
  answer(2, 2) = 24;
  matrix = matrix.InverseMatrix();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(answer(i, j), matrix(i, j));
    }
  }
}

TEST(test_operator, t1) {
  Matrix matrix(5, 5);
  ASSERT_ANY_THROW(matrix(-2, 2));
  ASSERT_ANY_THROW(matrix(2, 20));
  ASSERT_ANY_THROW(matrix(5, 5));
}

TEST(test_operator, t2) {
  Matrix matrix(5, 5);
  Matrix result(3, 3);
  matrix = result;
  ASSERT_EQ(matrix.rows(), result.rows());
}

TEST(accessor, test_1) {
  Matrix mat_1(9, 4);
  ASSERT_EQ(mat_1.rows(), 9);
  ASSERT_EQ(mat_1.cols(), 4);
}

TEST(mutator, test_1) {
  Matrix mat_1(9, 4);
  mat_1.set_rows(6);
  mat_1.set_cols(6);
  ASSERT_EQ(mat_1.rows(), 6);
  ASSERT_EQ(mat_1.cols(), 6);
}

TEST(equal, test_1) {
  Matrix mat_1(9, 4);
  Matrix mat_2(5, 4);
  ASSERT_FALSE(mat_1.EqMatrix(mat_2));
  mat_1.set_rows(4);
  mat_2.set_rows(4);
  ASSERT_TRUE(mat_1.EqMatrix(mat_2));
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      mat_1(i, j) = (double)(i + j) * 4.322 / M_PI;
      mat_2(i, j) = (double)(i + j) * 4.322 / M_PI;
    }
  }
  ASSERT_TRUE(mat_1.EqMatrix(mat_2));
}

TEST(equal, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  mat_1(0, 0) = 987654321.1234567;
  mat_1(0, 1) = 1111111111111.111111;
  mat_1(0, 2) = 2.0000005;
  mat_1(1, 0) = 3.0000001;
  mat_1(1, 1) = 4.1111111;
  mat_1(1, 2) = 5123454321.5123454;
  mat_1(2, 0) = 666666666666.0;
  mat_1(2, 1) = 7.0;
  mat_1(2, 2) = 987654321.9123456;

  mat_2(0, 0) = 987654321.1234567;
  mat_2(0, 1) = 1111111111111.111111;
  mat_2(0, 2) = 2.0000005;
  mat_2(1, 0) = 3.0000001;
  mat_2(1, 1) = 4.1111111;
  mat_2(1, 2) = 5123454321.5123454;
  mat_2(2, 0) = 666666666666.0;
  mat_2(2, 1) = 7.0;
  mat_2(2, 2) = 987654321.9123456;

  ASSERT_TRUE(mat_1.EqMatrix(mat_2));

  mat_1(2, 2) = 4.1;
  ASSERT_FALSE(mat_1.EqMatrix(mat_2));
}

TEST(sum, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mat_1(i, j) = i * j * 1.34;
      mat_2(i, j) = i * j * 2.54;
      mat_3(i, j) = i * j * (1.34 + 2.54);
    }
  }
  mat_1.SumMatrix(mat_2);
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(sum, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mat_1(i, j) = M_PI - i * j * 1.34;
      mat_2(i, j) = M_PI - i * j * 2.54;
      mat_3(i, j) = 2 * M_PI - i * j * (1.34 + 2.54);
    }
  }
  mat_1.SumMatrix(mat_2);
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(sum, test_4) {
  Matrix mat_1(2, 2);
  Matrix mat_2(2, 2);
  Matrix mat_3(2, 2);
  mat_1(0, 0) = 2.987654;
  mat_1(0, 1) = -5.3456;
  mat_1(1, 0) = 6.23;
  mat_1(1, 1) = -3.9292;
  mat_2(0, 0) = 4.838;
  mat_2(0, 1) = 8.0987;
  mat_2(1, 0) = -8;
  mat_2(1, 1) = -0.921;
  mat_3(0, 0) = 7.825654;
  mat_3(0, 1) = 2.7531;
  mat_3(1, 0) = -1.77;
  mat_3(1, 1) = -4.8502;
  mat_1.SumMatrix(mat_2);
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(sub, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mat_1(i, j) = i * j * 1.34;
      mat_2(i, j) = i * j * 2.54;
      mat_3(i, j) = i * j * (1.34 - 2.54);
    }
  }
  mat_1.SubMatrix(mat_2);
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(sub, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mat_1(i, j) = M_PI - i * j * 1.34;
      mat_2(i, j) = M_PI - i * j * 2.54;
      mat_3(i, j) = -i * j * (1.34 - 2.54);
    }
  }
  mat_1.SubMatrix(mat_2);
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(sub, test_4) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  mat_1(0, 0) = 0.1;
  mat_1(0, 1) = 0.2;
  mat_1(0, 2) = 0.3;
  mat_1(1, 0) = 0.4;
  mat_1(1, 1) = 0.5;
  mat_1(1, 2) = 0.6;
  mat_1(2, 0) = 0.7;
  mat_1(2, 1) = 0.8;
  mat_1(2, 2) = 0.9;
  mat_2(0, 0) = 1.0;
  mat_2(0, 1) = 2.0;
  mat_2(0, 2) = 3.0;
  mat_2(1, 0) = 4.0;
  mat_2(1, 1) = 5.0;
  mat_2(1, 2) = 6.0;
  mat_2(2, 0) = 7.0;
  mat_2(2, 1) = 8.0;
  mat_2(2, 2) = 9.0;
  mat_3(0, 0) = -0.9;
  mat_3(0, 1) = -1.8;
  mat_3(0, 2) = -2.7;
  mat_3(1, 0) = -3.6;
  mat_3(1, 1) = -4.5;
  mat_3(1, 2) = -5.4;
  mat_3(2, 0) = -6.3;
  mat_3(2, 1) = -7.2;
  mat_3(2, 2) = -8.1;
  mat_1.SubMatrix(mat_2);
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(MulNumber, test_1) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 9; ++j) {
      mat_1(i, j) = 53.32423;
      mat_2(i, j) = 53.32423 * 1.2342;
    }
  }
  mat_1.MulNumber(1.2342);
  ASSERT_TRUE(mat_1.EqMatrix(mat_2));
}

TEST(MulNumber, test_2) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 9; ++j) {
      mat_1(i, j) = 53.32423;
      mat_2(i, j) = -53.32423 * 1.13;
    }
  }
  mat_1.MulNumber(-1.13);
  ASSERT_TRUE(mat_1.EqMatrix(mat_2));
}

TEST(MulMatrix, test_2) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(0, 0) = 2;
  mat_1(0, 1) = 5;
  mat_1(0, 2) = 7;
  mat_1(0, 3) = -4;
  mat_1(1, 0) = 6;
  mat_1(1, 1) = 3;
  mat_1(1, 2) = 4;
  mat_1(1, 3) = 14;
  mat_1(2, 0) = 5;
  mat_1(2, 1) = -2;
  mat_1(2, 2) = -3;
  mat_1(2, 3) = -1;
  mat_1(3, 0) = 10;
  mat_1(3, 1) = 3;
  mat_1(3, 2) = 9;
  mat_1(3, 3) = -3;
  mat_1(4, 0) = -3;
  mat_1(4, 1) = 3;
  mat_1(4, 2) = 1;
  mat_1(4, 3) = 5;

  mat_2(0, 0) = 8;
  mat_2(0, 1) = 8;
  mat_2(0, 2) = 3;
  mat_2(0, 3) = 5;
  mat_2(1, 0) = -7;
  mat_2(1, 1) = 7;
  mat_2(1, 2) = 1;
  mat_2(1, 3) = 1;
  mat_2(2, 0) = 7;
  mat_2(2, 1) = 3;
  mat_2(2, 2) = 4;
  mat_2(2, 3) = -4;
  mat_2(3, 0) = 10;
  mat_2(3, 1) = 3;
  mat_2(3, 2) = 9;
  mat_2(3, 3) = -3;

  mat_3(0, 0) = -10;
  mat_3(0, 1) = 60;
  mat_3(0, 2) = 3;
  mat_3(0, 3) = -1;
  mat_3(1, 0) = 195;
  mat_3(1, 1) = 123;
  mat_3(1, 2) = 163;
  mat_3(1, 3) = -25;
  mat_3(2, 0) = 23;
  mat_3(2, 1) = 14;
  mat_3(2, 2) = -8;
  mat_3(2, 3) = 38;
  mat_3(3, 0) = 92;
  mat_3(3, 1) = 119;
  mat_3(3, 2) = 42;
  mat_3(3, 3) = 26;
  mat_3(4, 0) = 12;
  mat_3(4, 1) = 15;
  mat_3(4, 2) = 43;
  mat_3(4, 3) = -31;
  mat_1.MulMatrix(mat_2);
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(MulMatrix, test_3) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(0, 0) = 2.987654;
  mat_1(0, 1) = -5.3456;
  mat_1(1, 0) = 6.23;
  mat_1(1, 1) = -3.9292;
  mat_2(0, 0) = 4.838;
  mat_2(0, 1) = 8.0987;
  mat_2(0, 2) = 8.09;
  mat_2(0, 3) = -987;
  mat_2(1, 0) = -8;
  mat_2(1, 1) = -0.921;
  mat_2(1, 2) = -0.91;
  mat_2(1, 3) = 21;
  mat_3(0, 0) = 57.219070052;
  mat_3(0, 1) = 29.1194110498;
  mat_3(0, 2) = 29.03461686;
  mat_3(0, 3) = -3061.072098;
  mat_3(1, 0) = 61.57434;
  mat_3(1, 1) = 54.0736942;
  mat_3(1, 2) = 53.976272;
  mat_3(1, 3) = -6231.5232;
  mat_1.MulMatrix(mat_2);
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(MulMatrix, test_4) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      mat_2(i, j) = i + j;
    }
  }
  mat_1.MulMatrix(mat_2);
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(MulMatrix, test_5) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(1, 1) = 0;
  mat_1(1, 2) = 9;
  mat_1(1, 3) = 1;
  mat_1(2, 1) = 1;
  mat_1(2, 2) = 3;
  mat_1(2, 3) = 7;
  mat_1(3, 1) = 2;
  mat_1(3, 2) = 7;
  mat_1(3, 3) = 0;
  mat_2(1, 1) = 0;
  mat_2(1, 2) = 9;
  mat_2(1, 3) = 8;
  mat_2(2, 1) = 0;
  mat_2(2, 2) = 9;
  mat_2(2, 3) = 9;
  mat_2(3, 1) = 1;
  mat_2(3, 2) = 9;
  mat_2(3, 3) = 6;
  mat_3(1, 1) = 1;
  mat_3(1, 2) = 90;
  mat_3(1, 3) = 87;
  mat_3(2, 1) = 7;
  mat_3(2, 2) = 99;
  mat_3(2, 3) = 77;
  mat_3(3, 1) = 0;
  mat_3(3, 2) = 81;
  mat_3(3, 3) = 79;
  mat_1.MulMatrix(mat_2);
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(Transpose, test_1) {
  Matrix mat_1(5, 4);
  Matrix mat_2(mat_1.Transpose());
  Matrix mat_3(4, 5);
  ASSERT_TRUE(mat_2.EqMatrix(mat_3));
}

TEST(Transpose, test_2) {
  Matrix mat_1(1, 4);
  mat_1(0, 0) = 5.0;
  mat_1(0, 1) = 3.5;
  mat_1(0, 2) = 9.1;
  mat_1(0, 3) = 1.9;
  Matrix mat_2(mat_1.Transpose());
  Matrix mat_3(4, 1);
  mat_3(0, 0) = 5.0;
  mat_3(1, 0) = 3.5;
  mat_3(2, 0) = 9.1;
  mat_3(3, 0) = 1.9;
  ASSERT_TRUE(mat_2.EqMatrix(mat_3));
}

TEST(Determinant, test_1) {
  Matrix mat_1(3, 3);
  mat_1(0, 0) = 1;
  mat_1(0, 1) = 2;
  mat_1(0, 2) = 3;
  mat_1(1, 0) = 5;
  mat_1(1, 1) = 3;
  mat_1(1, 2) = 2;
  mat_1(2, 0) = -5;
  mat_1(2, 1) = 3;
  mat_1(2, 2) = 3;
  ASSERT_NEAR(mat_1.Determinant(), 43, 1e-7);
}

TEST(Determinant, test_2) {
  Matrix mat_1(1, 1);
  mat_1(0, 0) = 1.5;
  ASSERT_NEAR(mat_1.Determinant(), 1.5, 1e-7);
}

TEST(Determinant, test_3) {
  Matrix mat_1(2, 2);
  mat_1(0, 0) = 55.5;
  mat_1(0, 1) = 14.4;
  mat_1(1, 0) = -0.752;
  mat_1(1, 1) = 156.2;
  ASSERT_NEAR(mat_1.Determinant(), 8679.9288, 1e-7);
}

TEST(Determinant, test_4) {
  Matrix mat_1(4, 4);
  mat_1(0, 0) = 11.1;
  mat_1(0, 1) = 2.2;
  mat_1(0, 2) = 3.3;
  mat_1(0, 3) = 4.4;
  mat_1(1, 0) = 8.8;
  mat_1(1, 1) = -9.9;
  mat_1(1, 2) = 10.1;
  mat_1(1, 3) = 11.11;
  mat_1(2, 0) = 15.15;
  mat_1(2, 1) = 16.16;
  mat_1(2, 2) = 17.17;
  mat_1(2, 3) = 18.18;
  mat_1(3, 0) = -22.22;
  mat_1(3, 1) = 23.23;
  mat_1(3, 2) = 24.24;
  mat_1(3, 3) = 25.25;
  ASSERT_NEAR(mat_1.Determinant(), -11770.2443124, 1e-7);
}

TEST(Determinant, test_5) {
  Matrix mat_1(4, 4);
  ASSERT_NEAR(mat_1.Determinant(), 0.0, 1e-7);
}

TEST(complements, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  mat_1(0, 0) = 1;
  mat_1(0, 1) = 2;
  mat_1(0, 2) = 3;
  mat_1(1, 0) = 0;
  mat_1(1, 1) = 4;
  mat_1(1, 2) = 2;
  mat_1(2, 0) = 5;
  mat_1(2, 1) = 2;
  mat_1(2, 2) = 1;
  mat_2(0, 0) = 0;
  mat_2(0, 1) = 10;
  mat_2(0, 2) = -20;
  mat_2(1, 0) = 4;
  mat_2(1, 1) = -14;
  mat_2(1, 2) = 8;
  mat_2(2, 0) = -8;
  mat_2(2, 1) = -2;
  mat_2(2, 2) = 4;
  Matrix mat_3(std::move(mat_1.CalcComplements()));
  ASSERT_TRUE(mat_3.EqMatrix(mat_2));
}

TEST(complements, test_2) {
  Matrix mat_1(2, 2);
  Matrix mat_2(2, 2);
  mat_1(0, 0) = 2;
  mat_1(0, 1) = 4;
  mat_1(1, 0) = 6;
  mat_1(1, 1) = 3;
  mat_2(0, 0) = 3;
  mat_2(0, 1) = -6;
  mat_2(1, 0) = -4;
  mat_2(1, 1) = 2;
  Matrix mat_3(std::move(mat_1.CalcComplements()));
  ASSERT_TRUE(mat_3.EqMatrix(mat_2));
}

TEST(InverseMatrix, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  mat_1(0, 0) = 2;
  mat_1(0, 1) = 5;
  mat_1(0, 2) = 7;
  mat_1(1, 0) = 6;
  mat_1(1, 1) = 3;
  mat_1(1, 2) = 4;
  mat_1(2, 0) = 5;
  mat_1(2, 1) = -2;
  mat_1(2, 2) = -3;
  mat_2(0, 0) = 1;
  mat_2(0, 1) = -1;
  mat_2(0, 2) = 1;
  mat_2(1, 0) = -38;
  mat_2(1, 1) = 41;
  mat_2(1, 2) = -34;
  mat_2(2, 0) = 27;
  mat_2(2, 1) = -29;
  mat_2(2, 2) = 24;
  Matrix mat_3(mat_1.InverseMatrix());
  ASSERT_TRUE(mat_3.EqMatrix(mat_2));
}

TEST(InverseMatrix, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  mat_1(0, 0) = 2;
  mat_1(0, 1) = 1.3;
  mat_1(0, 2) = 0.7;
  mat_1(1, 0) = -1;
  mat_1(1, 1) = 0;
  mat_1(1, 2) = 3;
  mat_1(2, 0) = 0.3;
  mat_1(2, 1) = -0.3;
  mat_1(2, 2) = 2;
  mat_2(0, 0) = 45.0 / 289.0;
  mat_2(0, 1) = -281.0 / 578.0;
  mat_2(0, 2) = 195.0 / 289.0;
  mat_2(1, 0) = 145.0 / 289.0;
  mat_2(1, 1) = 379.0 / 578.0;
  mat_2(1, 2) = -335.0 / 289.0;
  mat_2(2, 0) = 15.0 / 289.0;
  mat_2(2, 1) = 99.0 / 578.0;
  mat_2(2, 2) = 65.0 / 289.0;
  Matrix mat_3(mat_1.InverseMatrix());
  ASSERT_TRUE(mat_3.EqMatrix(mat_2));
}

TEST(InverseMatrix, test_3) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  mat_1(0, 0) = 2.8;
  mat_1(0, 1) = 1.3;
  mat_1(0, 2) = 7.01;
  mat_1(1, 0) = -1.03;
  mat_1(1, 1) = -2.3;
  mat_1(1, 2) = 3.01;
  mat_1(2, 0) = 0;
  mat_1(2, 1) = -3;
  mat_1(2, 2) = 2;
  mat_2(0, 0) = 44300.0 / 367429.0;
  mat_2(0, 1) = -236300.0 / 367429.0;
  mat_2(0, 2) = 200360.0 / 367429.0;
  mat_2(1, 0) = 20600.0 / 367429.0;
  mat_2(1, 1) = 56000.0 / 367429.0;
  mat_2(1, 2) = -156483.0 / 367429.0;
  mat_2(2, 0) = 30900.0 / 367429.0;
  mat_2(2, 1) = 84000.0 / 367429.0;
  mat_2(2, 2) = -51010.0 / 367429.0;
  Matrix mat_3(mat_1.InverseMatrix());
  ASSERT_TRUE(mat_3.EqMatrix(mat_2));
}

TEST(InverseMatrix, test_4) {
  Matrix mat_1(1, 1);
  Matrix mat_2(1, 1);
  mat_1(0, 0) = 777.0;
  mat_2(0, 0) = 1.0 / 777.0;
  Matrix mat_3(mat_1.InverseMatrix());
  ASSERT_TRUE(mat_3.EqMatrix(mat_2));
}

TEST(operator_sum, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mat_1(i, j) = i * j * 1.34;
      mat_2(i, j) = i * j * 2.54;
      mat_3(i, j) = i * j * (1.34 + 2.54);
    }
  }
  Matrix mat_4 = mat_1 + mat_2;
  ASSERT_TRUE(mat_4.EqMatrix(mat_3));
}

TEST(operator_sum, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mat_1(i, j) = M_PI - i * j * 1.34;
      mat_2(i, j) = M_PI - i * j * 2.54;
      mat_3(i, j) = 2 * M_PI - i * j * (1.34 + 2.54);
    }
  }
  Matrix mat_4 = mat_1 + mat_2;
  ASSERT_TRUE(mat_4.EqMatrix(mat_3));
}

TEST(operator_sum, test_4) {
  Matrix mat_1(2, 2);
  Matrix mat_2(2, 2);
  Matrix mat_3(2, 2);
  mat_1(0, 0) = 2.987654;
  mat_1(0, 1) = -5.3456;
  mat_1(1, 0) = 6.23;
  mat_1(1, 1) = -3.9292;
  mat_2(0, 0) = 4.838;
  mat_2(0, 1) = 8.0987;
  mat_2(1, 0) = -8;
  mat_2(1, 1) = -0.921;
  mat_3(0, 0) = 7.825654;
  mat_3(0, 1) = 2.7531;
  mat_3(1, 0) = -1.77;
  mat_3(1, 1) = -4.8502;
  Matrix mat_4 = mat_1 + mat_2;
  ASSERT_TRUE(mat_4.EqMatrix(mat_3));
}

TEST(operator_sub, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mat_1(i, j) = i * j * 1.34;
      mat_2(i, j) = i * j * 2.54;
      mat_3(i, j) = i * j * (1.34 - 2.54);
    }
  }
  Matrix mat_4 = mat_1 - mat_2;
  ASSERT_TRUE(mat_4.EqMatrix(mat_3));
}

TEST(operator_sub, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mat_1(i, j) = M_PI - i * j * 1.34;
      mat_2(i, j) = M_PI - i * j * 2.54;
      mat_3(i, j) = -i * j * (1.34 - 2.54);
    }
  }
  Matrix mat_4 = mat_1 - mat_2;
  ASSERT_TRUE(mat_4.EqMatrix(mat_3));
}

TEST(operator_sub, test_4) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  mat_1(0, 0) = 0.1;
  mat_1(0, 1) = 0.2;
  mat_1(0, 2) = 0.3;
  mat_1(1, 0) = 0.4;
  mat_1(1, 1) = 0.5;
  mat_1(1, 2) = 0.6;
  mat_1(2, 0) = 0.7;
  mat_1(2, 1) = 0.8;
  mat_1(2, 2) = 0.9;
  mat_2(0, 0) = 1.0;
  mat_2(0, 1) = 2.0;
  mat_2(0, 2) = 3.0;
  mat_2(1, 0) = 4.0;
  mat_2(1, 1) = 5.0;
  mat_2(1, 2) = 6.0;
  mat_2(2, 0) = 7.0;
  mat_2(2, 1) = 8.0;
  mat_2(2, 2) = 9.0;
  mat_3(0, 0) = -0.9;
  mat_3(0, 1) = -1.8;
  mat_3(0, 2) = -2.7;
  mat_3(1, 0) = -3.6;
  mat_3(1, 1) = -4.5;
  mat_3(1, 2) = -5.4;
  mat_3(2, 0) = -6.3;
  mat_3(2, 1) = -7.2;
  mat_3(2, 2) = -8.1;
  Matrix mat_4 = mat_1 - mat_2;
  ASSERT_TRUE(mat_4.EqMatrix(mat_3));
}

TEST(operator_MulNumber, test_1) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 9; ++j) {
      mat_1(i, j) = 53.32423;
      mat_2(i, j) = 53.32423 * 1.2342;
    }
  }
  Matrix mat_3 = mat_1 * 1.2342;
  ASSERT_TRUE(mat_3.EqMatrix(mat_2));
}

TEST(operator_MulNumber, test_2) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 9; ++j) {
      mat_1(i, j) = 53.32423;
      mat_2(i, j) = -53.32423 * 1.13;
    }
  }
  Matrix mat_3 = mat_1 * -1.13;
  ASSERT_TRUE(mat_3.EqMatrix(mat_2));
}

TEST(operator_MulMatrix, test_2) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(0, 0) = 2;
  mat_1(0, 1) = 5;
  mat_1(0, 2) = 7;
  mat_1(0, 3) = -4;
  mat_1(1, 0) = 6;
  mat_1(1, 1) = 3;
  mat_1(1, 2) = 4;
  mat_1(1, 3) = 14;
  mat_1(2, 0) = 5;
  mat_1(2, 1) = -2;
  mat_1(2, 2) = -3;
  mat_1(2, 3) = -1;
  mat_1(3, 0) = 10;
  mat_1(3, 1) = 3;
  mat_1(3, 2) = 9;
  mat_1(3, 3) = -3;
  mat_1(4, 0) = -3;
  mat_1(4, 1) = 3;
  mat_1(4, 2) = 1;
  mat_1(4, 3) = 5;
  mat_2(0, 0) = 8;
  mat_2(0, 1) = 8;
  mat_2(0, 2) = 3;
  mat_2(0, 3) = 5;
  mat_2(1, 0) = -7;
  mat_2(1, 1) = 7;
  mat_2(1, 2) = 1;
  mat_2(1, 3) = 1;
  mat_2(2, 0) = 7;
  mat_2(2, 1) = 3;
  mat_2(2, 2) = 4;
  mat_2(2, 3) = -4;
  mat_2(3, 0) = 10;
  mat_2(3, 1) = 3;
  mat_2(3, 2) = 9;
  mat_2(3, 3) = -3;
  mat_3(0, 0) = -10;
  mat_3(0, 1) = 60;
  mat_3(0, 2) = 3;
  mat_3(0, 3) = -1;
  mat_3(1, 0) = 195;
  mat_3(1, 1) = 123;
  mat_3(1, 2) = 163;
  mat_3(1, 3) = -25;
  mat_3(2, 0) = 23;
  mat_3(2, 1) = 14;
  mat_3(2, 2) = -8;
  mat_3(2, 3) = 38;
  mat_3(3, 0) = 92;
  mat_3(3, 1) = 119;
  mat_3(3, 2) = 42;
  mat_3(3, 3) = 26;
  mat_3(4, 0) = 12;
  mat_3(4, 1) = 15;
  mat_3(4, 2) = 43;
  mat_3(4, 3) = -31;
  Matrix mat_4 = mat_1 * mat_2;
  ASSERT_TRUE(mat_4.EqMatrix(mat_3));
}

TEST(operator_MulMatrix, test_3) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(0, 0) = 2.987654;
  mat_1(0, 1) = -5.3456;
  mat_1(1, 0) = 6.23;
  mat_1(1, 1) = -3.9292;
  mat_2(0, 0) = 4.838;
  mat_2(0, 1) = 8.0987;
  mat_2(0, 2) = 8.09;
  mat_2(0, 3) = -987;
  mat_2(1, 0) = -8;
  mat_2(1, 1) = -0.921;
  mat_2(1, 2) = -0.91;
  mat_2(1, 3) = 21;
  mat_3(0, 0) = 57.219070052;
  mat_3(0, 1) = 29.1194110498;
  mat_3(0, 2) = 29.03461686;
  mat_3(0, 3) = -3061.072098;
  mat_3(1, 0) = 61.57434;
  mat_3(1, 1) = 54.0736942;
  mat_3(1, 2) = 53.976272;
  mat_3(1, 3) = -6231.5232;
  Matrix mat_4 = mat_1 * mat_2;
  ASSERT_TRUE(mat_4.EqMatrix(mat_3));
}

TEST(operator_MulMatrix, test_4) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      mat_2(i, j) = i + j;
    }
  }
  Matrix mat_4 = mat_1 * mat_2;
  ASSERT_TRUE(mat_4.EqMatrix(mat_3));
}

TEST(operator_MulMatrix, test_5) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(0, 0) = 0;
  mat_1(0, 1) = 9;
  mat_1(0, 2) = 1;
  mat_1(1, 0) = 1;
  mat_1(1, 1) = 3;
  mat_1(1, 2) = 7;
  mat_1(2, 0) = 2;
  mat_1(2, 1) = 7;
  mat_1(2, 2) = 0;
  mat_2(0, 0) = 0;
  mat_2(0, 1) = 9;
  mat_2(0, 2) = 8;
  mat_2(1, 0) = 0;
  mat_2(1, 1) = 9;
  mat_2(1, 2) = 9;
  mat_2(2, 0) = 1;
  mat_2(2, 1) = 9;
  mat_2(2, 2) = 6;
  mat_3(0, 0) = 1;
  mat_3(0, 1) = 90;
  mat_3(0, 2) = 87;
  mat_3(1, 0) = 7;
  mat_3(1, 1) = 99;
  mat_3(1, 2) = 77;
  mat_3(2, 0) = 0;
  mat_3(2, 1) = 81;
  mat_3(2, 2) = 79;
  Matrix mat_4 = mat_1 * mat_2;
  ASSERT_TRUE(mat_4.EqMatrix(mat_3));
}

TEST(operator_equal, test_1) {
  Matrix mat_1(9, 4);
  Matrix mat_2(5, 4);
  ASSERT_FALSE(mat_1.EqMatrix(mat_2));
  mat_1.set_rows(4);
  mat_2.set_rows(4);
  ASSERT_TRUE(mat_1.EqMatrix(mat_2));
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      mat_1(i, j) = mat_2(i, j) = (double)(i + j) * 4.322 / M_PI;
    }
  }
  ASSERT_TRUE(mat_1 == mat_2);
}

TEST(operator_equal, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  mat_1(0, 0) = 987654321.1234567;
  mat_1(0, 1) = 1111111111111.111111;
  mat_1(0, 2) = 2.0000005;
  mat_1(1, 0) = 3.0000001;
  mat_1(1, 1) = 4.1111111;
  mat_1(1, 2) = 5123454321.5123454;
  mat_1(2, 0) = 666666666666.0;
  mat_1(2, 1) = 7.0;
  mat_1(2, 2) = 987654321.9123456;

  mat_2(0, 0) = 987654321.1234567;
  mat_2(0, 1) = 1111111111111.111111;
  mat_2(0, 2) = 2.0000005;
  mat_2(1, 0) = 3.0000001;
  mat_2(1, 1) = 4.1111111;
  mat_2(1, 2) = 5123454321.5123454;
  mat_2(2, 0) = 666666666666.0;
  mat_2(2, 1) = 7.0;
  mat_2(2, 2) = 987654321.9123456;

  ASSERT_TRUE(mat_1 == mat_2);

  mat_1(2, 2) = 4.1;
  ASSERT_FALSE(mat_1 == mat_2);
}

TEST(operator_assignment, test_1) {
  Matrix mat_1(6, 3);
  Matrix mat_2(4, 9);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 9; ++j) {
      mat_2(i, j) = i + j + 1.5;
    }
  }
  mat_1 = mat_2;
  ASSERT_TRUE(mat_1.EqMatrix(mat_2));
}

TEST(operator_assignment, test_2) {
  Matrix mat_1(6, 3);
  Matrix mat_2(4, 9);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 9; ++j) {
      mat_2(i, j) = pow(i + j + 1.5, 2.0);
    }
  }
  mat_1 = mat_2;
  ASSERT_EQ(mat_1.rows(), 4);
  ASSERT_EQ(mat_1.cols(), 9);
  ASSERT_TRUE(mat_1.EqMatrix(mat_2));
}

TEST(operator_copy, test_1) {
  Matrix mat_1(6, 3);
  Matrix mat_2(4, 9);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 9; ++j) {
      mat_2(i, j) = pow(i + j + 1.5, 2.0);
    }
  }
  mat_1 = std::move(mat_2);
  ASSERT_EQ(mat_2.rows(), 0);
  ASSERT_EQ(mat_2.cols(), 0);
  ASSERT_FALSE(mat_1.EqMatrix(mat_2));
}

TEST(operator_sum_eq, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mat_1(i, j) = i * j * 1.34;
      mat_2(i, j) = i * j * 2.54;
      mat_3(i, j) = i * j * (1.34 + 2.54);
    }
  }
  mat_1 += mat_2;
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(operator_sum_eq, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mat_1(i, j) = M_PI - i * j * 1.34;
      mat_2(i, j) = M_PI - i * j * 2.54;
      mat_3(i, j) = 2 * M_PI - i * j * (1.34 + 2.54);
    }
  }
  mat_1 += mat_2;
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(operator_sum_eq, test_4) {
  Matrix mat_1(2, 2);
  Matrix mat_2(2, 2);
  Matrix mat_3(2, 2);
  mat_1(0, 0) = 2.987654;
  mat_1(0, 1) = -5.3456;
  mat_1(1, 0) = 6.23;
  mat_1(1, 1) = -3.9292;

  mat_2(0, 0) = 4.838;
  mat_2(0, 1) = 8.0987;
  mat_2(1, 0) = -8;
  mat_2(1, 1) = -0.921;

  mat_3(0, 0) = 7.825654;
  mat_3(0, 1) = 2.7531;
  mat_3(1, 0) = -1.77;
  mat_3(1, 1) = -4.8502;
  mat_1 += mat_2;
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(operator_sub_eq, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mat_1(i, j) = i * j * 1.34;
      mat_2(i, j) = i * j * 2.54;
      mat_3(i, j) = i * j * (1.34 - 2.54);
    }
  }
  mat_1 -= mat_2;
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(operator_sub_eq, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mat_1(i, j) = M_PI - i * j * 1.34;
      mat_2(i, j) = M_PI - i * j * 2.54;
      mat_3(i, j) = -i * j * (1.34 - 2.54);
    }
  }
  mat_1 -= mat_2;
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(operator_sub_eq, test_4) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  mat_1(0, 0) = 0.1;
  mat_1(0, 1) = 0.2;
  mat_1(0, 2) = 0.3;
  mat_1(1, 0) = 0.4;
  mat_1(1, 1) = 0.5;
  mat_1(1, 2) = 0.6;
  mat_1(2, 0) = 0.7;
  mat_1(2, 1) = 0.8;
  mat_1(2, 2) = 0.9;
  mat_2(0, 0) = 1.0;
  mat_2(0, 1) = 2.0;
  mat_2(0, 2) = 3.0;
  mat_2(1, 0) = 4.0;
  mat_2(1, 1) = 5.0;
  mat_2(1, 2) = 6.0;
  mat_2(2, 0) = 7.0;
  mat_2(2, 1) = 8.0;
  mat_2(2, 2) = 9.0;
  mat_3(0, 0) = -0.9;
  mat_3(0, 1) = -1.8;
  mat_3(0, 2) = -2.7;
  mat_3(1, 0) = -3.6;
  mat_3(1, 1) = -4.5;
  mat_3(1, 2) = -5.4;
  mat_3(2, 0) = -6.3;
  mat_3(2, 1) = -7.2;
  mat_3(2, 2) = -8.1;
  mat_1 -= mat_2;
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(operator_mul_number_eq, test_1) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 9; ++j) {
      mat_1(i, j) = 53.32423;
      mat_2(i, j) = 53.32423 * 1.2342;
    }
  }
  mat_1 *= 1.2342;
  ASSERT_TRUE(mat_1.EqMatrix(mat_2));
}

TEST(operator_mul_number_eq, test_2) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 9; ++j) {
      mat_1(i, j) = 53.32423;
      mat_2(i, j) = -53.32423 * 1.13;
    }
  }
  mat_1 *= -1.13;
  ASSERT_TRUE(mat_1.EqMatrix(mat_2));
}

TEST(operator_mul_number_eq, test_3) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 9; ++j) {
      mat_1(i, j) = 53.32423;
      mat_2(i, j) = -53.32423 * 1.13;
    }
  }
  mat_1 = -1.13 * mat_1;
  ASSERT_TRUE(mat_1.EqMatrix(mat_2));
}

TEST(operator_mul_mutrix_eq, test_2) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(0, 0) = 2;
  mat_1(0, 1) = 5;
  mat_1(0, 2) = 7;
  mat_1(0, 3) = -4;
  mat_1(1, 0) = 6;
  mat_1(1, 1) = 3;
  mat_1(1, 2) = 4;
  mat_1(1, 3) = 14;
  mat_1(2, 0) = 5;
  mat_1(2, 1) = -2;
  mat_1(2, 2) = -3;
  mat_1(2, 3) = -1;
  mat_1(3, 0) = 10;
  mat_1(3, 1) = 3;
  mat_1(3, 2) = 9;
  mat_1(3, 3) = -3;
  mat_1(4, 0) = -3;
  mat_1(4, 1) = 3;
  mat_1(4, 2) = 1;
  mat_1(4, 3) = 5;
  mat_2(0, 0) = 8;
  mat_2(0, 1) = 8;
  mat_2(0, 2) = 3;
  mat_2(0, 3) = 5;
  mat_2(1, 0) = -7;
  mat_2(1, 1) = 7;
  mat_2(1, 2) = 1;
  mat_2(1, 3) = 1;
  mat_2(2, 0) = 7;
  mat_2(2, 1) = 3;
  mat_2(2, 2) = 4;
  mat_2(2, 3) = -4;
  mat_2(3, 0) = 10;
  mat_2(3, 1) = 3;
  mat_2(3, 2) = 9;
  mat_2(3, 3) = -3;
  mat_3(0, 0) = -10;
  mat_3(0, 1) = 60;
  mat_3(0, 2) = 3;
  mat_3(0, 3) = -1;
  mat_3(1, 0) = 195;
  mat_3(1, 1) = 123;
  mat_3(1, 2) = 163;
  mat_3(1, 3) = -25;
  mat_3(2, 0) = 23;
  mat_3(2, 1) = 14;
  mat_3(2, 2) = -8;
  mat_3(2, 3) = 38;
  mat_3(3, 0) = 92;
  mat_3(3, 1) = 119;
  mat_3(3, 2) = 42;
  mat_3(3, 3) = 26;
  mat_3(4, 0) = 12;
  mat_3(4, 1) = 15;
  mat_3(4, 2) = 43;
  mat_3(4, 3) = -31;
  mat_1 *= mat_2;
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(operator_mul_mutrix_eq, test_3) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(0, 0) = 2.987654;
  mat_1(0, 1) = -5.3456;
  mat_1(1, 0) = 6.23;
  mat_1(1, 1) = -3.9292;
  mat_2(0, 0) = 4.838;
  mat_2(0, 1) = 8.0987;
  mat_2(0, 2) = 8.09;
  mat_2(0, 3) = -987;
  mat_2(1, 0) = -8;
  mat_2(1, 1) = -0.921;
  mat_2(1, 2) = -0.91;
  mat_2(1, 3) = 21;
  mat_3(0, 0) = 57.219070052;
  mat_3(0, 1) = 29.1194110498;
  mat_3(0, 2) = 29.03461686;
  mat_3(0, 3) = -3061.072098;
  mat_3(1, 0) = 61.57434;
  mat_3(1, 1) = 54.0736942;
  mat_3(1, 2) = 53.976272;
  mat_3(1, 3) = -6231.5232;
  mat_1 *= mat_2;
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(operator_mul_mutrix_eq, test_4) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      mat_2(i, j) = i + j;
    }
  }
  mat_1 *= mat_2;
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(operator_mul_mutrix_eq, test_5) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(0, 0) = 0;
  mat_1(0, 1) = 9;
  mat_1(0, 2) = 1;
  mat_1(1, 0) = 1;
  mat_1(1, 1) = 3;
  mat_1(1, 2) = 7;
  mat_1(2, 0) = 2;
  mat_1(2, 1) = 7;
  mat_1(2, 2) = 0;
  mat_2(0, 0) = 0;
  mat_2(0, 1) = 9;
  mat_2(0, 2) = 8;
  mat_2(1, 0) = 0;
  mat_2(1, 1) = 9;
  mat_2(1, 2) = 9;
  mat_2(2, 0) = 1;
  mat_2(2, 1) = 9;
  mat_2(2, 2) = 6;
  mat_3(0, 0) = 1;
  mat_3(0, 1) = 90;
  mat_3(0, 2) = 87;
  mat_3(1, 0) = 7;
  mat_3(1, 1) = 99;
  mat_3(1, 2) = 77;
  mat_3(2, 0) = 0;
  mat_3(2, 1) = 81;
  mat_3(2, 2) = 79;
  mat_1 *= mat_2;
  ASSERT_TRUE(mat_1.EqMatrix(mat_3));
}

TEST(indexing, test_1) {
  Matrix mat_1(4, 7);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 7; ++j) {
      mat_1(i, j) = (i + 1) + ((j + 1) * 3.42);
    }
  }
  ASSERT_NEAR(mat_1(2, 3), 16.68, 1E-7);
  ASSERT_NEAR(mat_1(1, 2), 12.26, 1E-7);
  ASSERT_NEAR(mat_1(3, 6), 27.94, 1E-7);
  ASSERT_NEAR(mat_1(0, 0), 4.42, 1E-7);
}

TEST(sum, test_3) {
  Matrix mat_1(3, 3);
  Matrix mat_2(5, 5);
  EXPECT_THROW({ mat_1.SumMatrix(mat_2); }, std::runtime_error);
}

TEST(operator_sub_eq, test_3) {
  Matrix mat_1(3, 3);
  Matrix mat_2(5, 5);
  EXPECT_THROW({ mat_1 -= mat_2; }, std::runtime_error);
}

TEST(operator_sum_eq, test_3) {
  Matrix mat_1(3, 3);
  Matrix mat_2(5, 5);
  EXPECT_THROW({ mat_1 += mat_2; }, std::runtime_error);
}

TEST(operator_MulMatrix, test_1) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  EXPECT_THROW({ mat_1 *mat_2; }, std::runtime_error);
}

TEST(operator_sub, test_3) {
  Matrix mat_1(3, 3);
  Matrix mat_2(5, 5);
  EXPECT_THROW({ mat_1 - mat_2; }, std::runtime_error);
}

TEST(InverseMatrix, test_5) {
  Matrix mat_1(3, 3);
  EXPECT_THROW({ mat_1.InverseMatrix(); }, std::runtime_error);
}

TEST(complements, test_3) {
  Matrix mat_1(2, 3);
  EXPECT_THROW({ mat_1.CalcComplements(); }, std::runtime_error);
}

TEST(Determinant, test_6) {
  Matrix mat_1(5, 4);
  EXPECT_THROW({ mat_1.Determinant(); }, std::runtime_error);
}

TEST(MulMatrix, test_1) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  EXPECT_THROW({ mat_1.MulMatrix(mat_2); }, std::runtime_error);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
