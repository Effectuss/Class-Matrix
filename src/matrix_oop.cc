#include "matrix_oop.h"

bool Matrix::IsCorrectIndex(const int &rows, const int &cols) const {
  return rows > 0 && cols > 0;
}

bool Matrix::IsSquareMatrix(const int &rows, const int &cols) const {
  return rows == cols;
}

bool Matrix::IsDimension(const Matrix &other_matrix) const {
  return (this->cols_ == other_matrix.cols_) &&
         (this->rows_ == other_matrix.rows_);
}

Matrix::Matrix() : rows_{0}, cols_{0}, matrix_{nullptr} {}

Matrix::Matrix(const int &rows, const int &cols) : rows_{rows}, cols_{cols} {
  if (!IsCorrectIndex(rows_, cols_)) {
    throw std::runtime_error("Inncorect argument for Matrix");
  } else {
    this->MemoryAllocating();
  }
}

Matrix::~Matrix() { this->DeleteMatrix(); }

Matrix::Matrix(const Matrix &other_matrix)
    : rows_{other_matrix.rows_}, cols_{other_matrix.cols_} {
  if (this == &other_matrix) {
    throw std::runtime_error("Address this equel address other_matrix");
  }
  this->MemoryAllocating();
  CopyMatrix(other_matrix);
}

Matrix::Matrix(Matrix &&other_matrix) noexcept {
  rows_ = other_matrix.rows_;
  cols_ = other_matrix.cols_;
  matrix_ = other_matrix.matrix_;
  other_matrix.NullifyObj();
}

Matrix &Matrix::operator=(const Matrix &other_matrix) {
  if (this == &other_matrix) {
    return *this;
  }
  this->DeleteMatrix();
  this->rows_ = other_matrix.rows_;
  this->cols_ = other_matrix.cols_;
  this->MemoryAllocating();
  CopyMatrix(other_matrix);
  return *this;
}

Matrix &Matrix::operator=(Matrix &&other_matrix) noexcept {
  if (this == &other_matrix) {
    return *this;
  }
  this->DeleteMatrix();
  this->matrix_ = other_matrix.matrix_;
  std::swap(this->rows_, other_matrix.rows_);
  std::swap(this->cols_, other_matrix.cols_);
  other_matrix.NullifyObj();
  return *this;
}

double &Matrix::operator()(const int &index_i, const int &index_j) const {
  if (index_i >= rows_ || index_j >= cols_ || index_i < 0 || index_j < 0) {
    throw std::runtime_error("Error");
  }
  return this->matrix_[index_i][index_j];
}

int Matrix::cols() const { return this->cols_; }

int Matrix::rows() const { return this->rows_; }

void Matrix::set_cols(const int &cols) {
  Matrix tmp_matrix(this->rows_, cols);
  tmp_matrix.CopyMatrix(*this);
  *this = tmp_matrix;
}

void Matrix::set_rows(const int &rows) {
  Matrix tmp_matrix(rows, this->cols_);
  tmp_matrix.CopyMatrix(*this);
  *this = tmp_matrix;
}

void Matrix::NullifyObj() {
  this->matrix_ = nullptr;
  this->cols_ = 0;
  this->rows_ = 0;
}

void Matrix::DeleteMatrix() {
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; ++i) {
      if (this->matrix_[i] != nullptr) {
        delete[] this->matrix_[i];
      }
    }
    delete[] this->matrix_;
    this->matrix_ = nullptr;
  }
  this->cols_ = 0;
  this->rows_ = 0;
}

Matrix &Matrix::CopyMatrix(const Matrix &other_matrix) {
  for (int i = 0; i < std::min(this->rows_, other_matrix.rows_); ++i) {
    for (int j = 0; j < std::min(this->cols_, other_matrix.cols_); ++j) {
      this->matrix_[i][j] = other_matrix.matrix_[i][j];
    }
  }
  return *this;
}

void Matrix::MemoryAllocating() {
  this->matrix_ = new double *[this->rows_];
  for (int i = 0; i < this->rows_; ++i) {
    this->matrix_[i] = new double[this->cols_]{};
  }
}

bool Matrix::EqMatrix(const Matrix &other_matrix) const {
  if (!IsDimension(other_matrix)) {
    return false;
  }
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      if (fabs(this->matrix_[i][j] - other_matrix.matrix_[i][j]) >= 1e-8)
        return false;
    }
  }
  return true;
}

void Matrix::SumMatrix(const Matrix &other_matrix) {
  if (!IsDimension(other_matrix)) {
    throw std::runtime_error("Different dimensions of the matrix");
  }
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      (*this)(i, j) += other_matrix(i, j);
    }
  }
}

void Matrix::SubMatrix(const Matrix &other_matrix) {
  if (!IsDimension(other_matrix)) {
    throw std::runtime_error("Different dimensions of the matrix");
  }
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      (*this)(i, j) -= other_matrix(i, j);
    }
  }
}

void Matrix::MulNumber(const double &num) {
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      (*this)(i, j) *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix &other_matrix) {
  if (this->cols_ != other_matrix.rows_) {
    throw std::runtime_error("cols != rows");
  }
  Matrix res_matrix(this->rows_, other_matrix.cols_);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < other_matrix.cols_; ++j) {
      for (int k = 0; k < other_matrix.rows_; ++k) {
        res_matrix.matrix_[i][j] +=
            this->matrix_[i][k] * other_matrix.matrix_[k][j];
      }
    }
  }
  *this = res_matrix;
}

Matrix Matrix::Transpose() {
  Matrix trans_matrix(this->cols_, this->rows_);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      trans_matrix(j, i) = (*this)(i, j);
    }
  }
  return trans_matrix;
}

Matrix Matrix::MinorMatrix(const int &rows, const int &cols) {
  Matrix minor(this->rows_ - 1, this->cols_ - 1);
  for (int i = 0, minor_i = 0; i < this->rows_; ++i) {
    if (i != rows) {
      for (int j = 0, minor_j = 0; j < this->cols_; ++j) {
        if (j != cols) {
          minor(minor_i, minor_j++) = (*this)(i, j);
        }
      }
      ++minor_i;
    }
  }
  return minor;
}

double Matrix::CountingDet() {
  if (this->cols_ == 1) {
    return this->matrix_[0][0];
  }
  if (this->cols_ == 2) {
    return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  }
  double determinant = 0.0;
  for (int j = 0; j < this->rows_; ++j) {
    Matrix minor = MinorMatrix(0, j);
    determinant += this->matrix_[0][j] * pow(-1, j) * minor.CountingDet();
  }
  return determinant;
}

double Matrix::Determinant() {
  if (!IsSquareMatrix(this->rows_, this->cols_)) {
    throw std::runtime_error(
        "To calculate the determinant, you need a square matrix");
  }
  double determinant = 0.0;
  determinant = this->CountingDet();
  return determinant;
}

Matrix Matrix::CalcComplements() {
  if (!IsSquareMatrix(this->rows_, this->cols_)) {
    throw std::runtime_error(
        "To calculate the complemenets, you need a square matrix");
  }
  Matrix comp_matrix(this->rows_, this->cols_);
  if (this->rows_ == 1.0) {
    comp_matrix(0, 0) = 1.0;
    return comp_matrix;
  }
  for (int i = 0; i < comp_matrix.rows(); ++i) {
    for (int j = 0; j < comp_matrix.cols(); ++j) {
      Matrix minor = MinorMatrix(i, j);
      comp_matrix(i, j) = minor.Determinant() * pow(-1, i + j);
    }
  }
  return comp_matrix;
}

Matrix Matrix::InverseMatrix() {
  double determinant = Determinant();
  if (fabs(determinant) < std::numeric_limits<double>::epsilon()) {
    throw std::runtime_error("For inverse matrix determinant zero");
  }
  return CalcComplements().Transpose() * (1.0 / determinant);
}

Matrix Matrix::operator+(const Matrix &other_matrix) const {
  Matrix result = *this;
  result.SumMatrix(other_matrix);
  return result;
}

Matrix Matrix::operator-(const Matrix &other_matrix) const {
  Matrix result = *this;
  result.SubMatrix(other_matrix);
  return result;
}

Matrix Matrix::operator*(const Matrix &other_matrix) const {
  Matrix result = *this;
  result.MulMatrix(other_matrix);
  return result;
}

Matrix operator*(const Matrix &other_matrix, const double &number) {
  Matrix result = other_matrix;
  result.MulNumber(number);
  return result;
}

Matrix operator*(const double &number, const Matrix &other_matrix) {
  Matrix result = other_matrix;
  result.MulNumber(number);
  return result;
}

Matrix &Matrix::operator+=(const Matrix &other_matrix) {
  SumMatrix(other_matrix);
  return *this;
}

Matrix &Matrix::operator-=(const Matrix &other_matrix) {
  SubMatrix(other_matrix);
  return *this;
}

Matrix &Matrix::operator*=(const Matrix &other_matrix) {
  MulMatrix(other_matrix);
  return *this;
}

Matrix &Matrix::operator*=(const double &number) {
  MulNumber(number);
  return *this;
}

bool Matrix::operator==(const Matrix &other_matrix) const {
  return (*this).EqMatrix(other_matrix);
}
