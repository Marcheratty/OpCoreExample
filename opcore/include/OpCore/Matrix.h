#ifndef MATRIX_H
#define MATRIX_H


#include <array>
#include <initializer_list>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <cstddef>
#include <OpCore/Vector.h> 
#include <cmath> // For std::isnan

namespace OpCore {

template<typename T, std::size_t Rows, std::size_t Cols>
class Matrix {
public:
    std::array<T, Rows * Cols> data;

    // Default constructor: initializes all elements to T{}.
    Matrix();

    // Initializer list constructor; list must contain exactly Rows*Cols elements.
    Matrix(const std::initializer_list<T>& list);

    // Element access.
    T& operator()(std::size_t row, std::size_t col);
    const T& operator()(std::size_t row, std::size_t col) const;

    // Matrix addition and subtraction.
    Matrix<T, Rows, Cols> operator+(const Matrix<T, Rows, Cols>& other) const;
    Matrix<T, Rows, Cols> operator-(const Matrix<T, Rows, Cols>& other) const;

    // Matrix transposition.
    Matrix<T, Cols, Rows> transpose() const;

    // Matrix inversion (only for square matrices).
    Matrix<T, Rows, Cols> inverse() const;

    // Check if any element in the matrix is NaN.
    bool isnan() const;

    // Extract a submatrix.
    template<std::size_t SubRows, std::size_t SubCols>
    Matrix<T, SubRows, SubCols> submatrix(std::size_t startRow, std::size_t startCol) const;

    // Debug: print the matrix.
    void print() const;

    // Static factory methods
    static Matrix<T, Rows, Cols> zeros();
    static Matrix<T, Rows, Cols> eye();  // Identity matrix

    // Block concatenation functions
    template<std::size_t Rows2>
    Matrix<T, Rows + Rows2, Cols> vconcat(const Matrix<T, Rows2, Cols>& bottom) const;

    template<std::size_t Cols2>
    Matrix<T, Rows, Cols + Cols2> hconcat(const Matrix<T, Rows, Cols2>& right) const;

    // Scalar multiplication
    Matrix<T, Rows, Cols> operator*(T scalar) const;

    // Equality operators
    template<typename U, std::size_t R, std::size_t C>
    friend bool operator==(const Matrix<U, R, C>& lhs, const Matrix<U, R, C>& rhs);

    template<typename U, std::size_t R, std::size_t C>
    friend bool operator!=(const Matrix<U, R, C>& lhs, const Matrix<U, R, C>& rhs);

};

// Matrix multiplication: Matrix * Matrix.
template<typename T, std::size_t Rows, std::size_t Cols, std::size_t OtherCols>
Matrix<T, Rows, OtherCols> operator*(const Matrix<T, Rows, Cols>& lhs,
                                       const Matrix<T, Cols, OtherCols>& rhs);

// Matrix-Vector multiplication: Matrix * Vector.
template<typename T, std::size_t Rows, std::size_t Cols>
Vector<T, Rows> operator*(const Matrix<T, Rows, Cols>& m, const Vector<T, Cols>& v);

} // end namespace OpCore


#include "Matrix.tpp"
#endif // MATRIX_H
