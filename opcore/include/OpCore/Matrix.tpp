#include <OpCore/Matrix.h>


namespace OpCore {

// Default constructor: initialize all elements to T{}.
template<typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols>::Matrix() {
    data.fill(T{});
}

// Initializer list constructor.
template<typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols>::Matrix(const std::initializer_list<T>& list) {
    assert(list.size() == Rows * Cols && "Initializer list size must match matrix dimensions.");
    std::copy(list.begin(), list.end(), data.begin());
}

// Non-const element access.
template<typename T, std::size_t Rows, std::size_t Cols>
T& Matrix<T, Rows, Cols>::operator()(std::size_t row, std::size_t col) {
    assert(row < Rows && col < Cols);
    return data[row * Cols + col];
}

// Const element access.
template<typename T, std::size_t Rows, std::size_t Cols>
const T& Matrix<T, Rows, Cols>::operator()(std::size_t row, std::size_t col) const {
    assert(row < Rows && col < Cols);
    return data[row * Cols + col];
}

// Matrix addition.
template<typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator+(const Matrix<T, Rows, Cols>& other) const {
    Matrix<T, Rows, Cols> result;
    for (std::size_t i = 0; i < Rows * Cols; ++i)
        result.data[i] = data[i] + other.data[i];
    return result;
}

// Matrix subtraction.
template<typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator-(const Matrix<T, Rows, Cols>& other) const {
    Matrix<T, Rows, Cols> result;
    for (std::size_t i = 0; i < Rows * Cols; ++i)
        result.data[i] = data[i] - other.data[i];
    return result;
}

// Print the matrix.
template<typename T, std::size_t Rows, std::size_t Cols>
void Matrix<T, Rows, Cols>::print() const {
    for (std::size_t i = 0; i < Rows; ++i) {
        for (std::size_t j = 0; j < Cols; ++j)
            std::cout << (*this)(i, j) << " ";
        std::cout << "\n";
    }
}

// Matrix multiplication (Matrix * Matrix).
template<typename T, std::size_t Rows, std::size_t Cols, std::size_t OtherCols>
Matrix<T, Rows, OtherCols> operator*(const Matrix<T, Rows, Cols>& lhs,
                                       const Matrix<T, Cols, OtherCols>& rhs) {
    Matrix<T, Rows, OtherCols> result;
    for (std::size_t i = 0; i < Rows; ++i) {
        for (std::size_t j = 0; j < OtherCols; ++j) {
            T sum = T{};
            for (std::size_t k = 0; k < Cols; ++k)
                sum += lhs(i, k) * rhs(k, j);
            result(i, j) = sum;
        }
    }
    return result;
}

// Matrix-Vector multiplication: Matrix (Rows x Cols) * Vector (size Cols) = Vector (size Rows).
template<typename T, std::size_t Rows, std::size_t Cols>
Vector<T, Rows> operator*(const Matrix<T, Rows, Cols>& m, const Vector<T, Cols>& v) {
    Vector<T, Rows> result;
    for (std::size_t i = 0; i < Rows; ++i) {
        T sum = T{};
        for (std::size_t j = 0; j < Cols; ++j)
            sum += m(i, j) * v[j];
        result[i] = sum;
    }
    return result;
}

// Generate a matrix filled with zeros.
template<typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::zeros() {
    return Matrix<T, Rows, Cols>();  // Default constructor already initializes to zero.
}

// Generate an identity matrix (eye()).
template<typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::eye() {
    static_assert(Rows == Cols, "Identity matrix must be square.");
    Matrix<T, Rows, Cols> result;
    for (std::size_t i = 0; i < Rows; ++i)
        result(i, i) = T{1};  // Set diagonal elements to 1
    return result;
}

// Vertical concatenation: Matrix (Rows x Cols) + Matrix (Rows2 x Cols) = Matrix (Rows + Rows2 x Cols).
template<typename T, std::size_t Rows, std::size_t Cols>
template<std::size_t Rows2>
Matrix<T, Rows + Rows2, Cols> Matrix<T, Rows, Cols>::vconcat(const Matrix<T, Rows2, Cols>& bottom) const {
    Matrix<T, Rows + Rows2, Cols> result;
    for (std::size_t i = 0; i < Rows; ++i)
        for (std::size_t j = 0; j < Cols; ++j)
            result(i, j) = (*this)(i, j);
    for (std::size_t i = 0; i < Rows2; ++i)
        for (std::size_t j = 0; j < Cols; ++j)
            result(i + Rows, j) = bottom(i, j);
    return result;
}

// Horizontal concatenation: Matrix (Rows x Cols) + Matrix (Rows x Cols2) = Matrix (Rows x (Cols + Cols2)).
template<typename T, std::size_t Rows, std::size_t Cols>
template<std::size_t Cols2>
Matrix<T, Rows, Cols + Cols2> Matrix<T, Rows, Cols>::hconcat(const Matrix<T, Rows, Cols2>& right) const {
    Matrix<T, Rows, Cols + Cols2> result;
    for (std::size_t i = 0; i < Rows; ++i) {
        for (std::size_t j = 0; j < Cols; ++j)
            result(i, j) = (*this)(i, j);
        for (std::size_t j = 0; j < Cols2; ++j)
            result(i, j + Cols) = right(i, j);
    }
    return result;
}

// Scalar multiplication
template<typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator*(T scalar) const {
    Matrix<T, Rows, Cols> result;
    for (std::size_t i = 0; i < Rows * Cols; ++i) {
        result.data[i] = data[i] * scalar;
    }
    return result;
}

// Matrix transposition.
template<typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Cols, Rows> Matrix<T, Rows, Cols>::transpose() const {
    Matrix<T, Cols, Rows> result;
    for (std::size_t i = 0; i < Rows; ++i) {
        for (std::size_t j = 0; j < Cols; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}

// Equality operator for matrix comparison.
template<typename T, std::size_t Rows, std::size_t Cols>
bool operator==(const Matrix<T, Rows, Cols>& lhs, const Matrix<T, Rows, Cols>& rhs) {
    for (std::size_t i = 0; i < Rows * Cols; ++i) {
        if (lhs.data[i] != rhs.data[i]) {
            return false;
        }
    }
    return true;
}

template<typename T, std::size_t Rows, std::size_t Cols>
bool operator!=(const Matrix<T, Rows, Cols>& lhs, const Matrix<T, Rows, Cols>& rhs) {
    return !(lhs == rhs);
}


// Matrix inversion (only for square matrices).
template<typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::inverse() const {
    static_assert(Rows == Cols, "Matrix inversion is only defined for square matrices.");
    Matrix<T, Rows, Cols> result = eye();
    Matrix<T, Rows, Cols> copy = *this;

    for (std::size_t i = 0; i < Rows; ++i) {
        // Find the pivot element
        T maxElement = std::abs(copy(i, i));
        std::size_t maxRow = i;
        for (std::size_t k = i + 1; k < Rows; ++k) {
            if (std::abs(copy(k, i)) > maxElement) {
                maxElement = std::abs(copy(k, i));
                maxRow = k;
            }
        }

        // Swap rows
        if (i != maxRow) {
            for (std::size_t j = 0; j < Cols; ++j) {
                std::swap(copy(i, j), copy(maxRow, j));
                std::swap(result(i, j), result(maxRow, j));
            }
        }

        // Make the diagonal element 1
        T diagElement = copy(i, i);
        if (diagElement == 0) {
            throw std::runtime_error("Matrix is singular and cannot be inverted.");
        }
        for (std::size_t j = 0; j < Cols; ++j) {
            copy(i, j) /= diagElement;
            result(i, j) /= diagElement;
        }

        // Eliminate other elements in the column
        for (std::size_t k = 0; k < Rows; ++k) {
            if (k != i) {
                T factor = copy(k, i);
                for (std::size_t j = 0; j < Cols; ++j) {
                    copy(k, j) -= factor * copy(i, j);
                    result(k, j) -= factor * result(i, j);
                }
            }
        }
    }
    return result;
}

// Check if any element in the matrix is NaN.
template<typename T, std::size_t Rows, std::size_t Cols>
bool Matrix<T, Rows, Cols>::isnan() const {
    for (std::size_t i = 0; i < Rows * Cols; ++i) {
        if (std::isnan(data[i])) {
            return true;
        }
    }
    return false;
}

// Extract a submatrix.
template<typename T, std::size_t Rows, std::size_t Cols>
template<std::size_t SubRows, std::size_t SubCols>
Matrix<T, SubRows, SubCols> Matrix<T, Rows, Cols>::submatrix(std::size_t startRow, std::size_t startCol) const {
    assert(startRow + SubRows <= Rows && startCol + SubCols <= Cols);
    Matrix<T, SubRows, SubCols> result;
    for (std::size_t i = 0; i < SubRows; ++i) {
        for (std::size_t j = 0; j < SubCols; ++j) {
            result(i, j) = (*this)(startRow + i, startCol + j);
        }
    }
    return result;
}

} // end namespace OpCore