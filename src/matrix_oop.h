#ifndef _SRC_MATRIX_OOP_H_
#define _SRC_MATRIX_OOP_H_

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <exception>
#include <iostream>
#include <iterator>
#include <limits>
class Matrix {
 public:
  Matrix();
  explicit Matrix(const int &rows, const int &cols);
  Matrix(const Matrix &other_matrix);
  Matrix(Matrix &&other_matrix) noexcept;
  ~Matrix();

  int rows() const;
  int cols() const;
  void set_rows(const int &);
  void set_cols(const int &);

  Matrix &operator=(const Matrix &other_matrix);
  Matrix &operator=(Matrix &&other_matrix) noexcept;
  Matrix operator+(const Matrix &other_matrix) const;
  Matrix operator-(const Matrix &other_matrix) const;
  bool operator==(const Matrix &other_matrix) const;
  double &operator()(const int &index_i, const int &index_j) const;
  Matrix operator*(const Matrix &other_matrix) const;
  friend Matrix operator*(const Matrix &other_matrix, double const &number);
  friend Matrix operator*(const double &number, const Matrix &other_matrix);
  Matrix &operator+=(const Matrix &other_matrix);
  Matrix &operator-=(const Matrix &other_matrix);
  Matrix &operator*=(const Matrix &other_matrix);
  Matrix &operator*=(const double &number);

  bool EqMatrix(const Matrix &other_matrix) const;
  Matrix Transpose();
  Matrix CalcComplements();
  void SumMatrix(const Matrix &other_matrix);
  void SubMatrix(const Matrix &other_matrix);
  void MulNumber(const double &num);
  void MulMatrix(const Matrix &other_matrix);
  double Determinant();
  Matrix InverseMatrix();
  Matrix MinorMatrix(const int &rows, const int &cols);

 protected:
  [[nodiscard]] inline bool IsCorrectIndex(const int &rows,
                                           const int &cols) const;
  [[nodiscard]] inline bool IsDimension(const Matrix &other_matrix) const;
  [[nodiscard]] inline bool IsSquareMatrix(const int &rows,
                                           const int &cols) const;
  double CountingDet();
  Matrix &CopyMatrix(const Matrix &other_matrix);
  void MemoryAllocating();
  void NullifyObj();
  void DeleteMatrix();

 private:
  int rows_;
  int cols_;
  double **matrix_;
};

#endif  // _SRC_MATRIX_OOP_H_