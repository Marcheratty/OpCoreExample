#ifndef VECTOR_H
#define VECTOR_H

#include <array>
#include <initializer_list>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <cstddef>
#include <cmath> 

namespace OpCore {

template<typename T, std::size_t N>
class Vector {
public:
    std::array<T, N> data;

    // Default constructor initializes all elements to T{}
    Vector();

    // Initializer list constructor: the list must have exactly N elements.
    Vector(const std::initializer_list<T>& list);

    // Element access.
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    // Vector addition and subtraction.
    Vector<T, N> operator+(const Vector<T, N>& other) const;
    Vector<T, N> operator-(const Vector<T, N>& other) const;

    // Scalar multiplication.
    Vector<T, N> operator*(const T scalar) const;

    // Dot product.
    T dot(const Vector<T, N>& other) const;

    // Vector transposition (no-op, since vectors are 1D).
    Vector<T, N> transpose() const;

    // Check if any element in the vector is NaN.
    bool isnan() const;

    // Debug: print the vector.
    void print() const;

    // Concatenation functions
    template<std::size_t M>
    Vector<T, N + M> hconcat(const Vector<T, M>& other) const;

    template<std::size_t M>
    Vector<T, N + M> vconcat(const Vector<T, M>& other) const;

    template<typename U, std::size_t M>
    friend bool operator==(const Vector<U, M>& lhs, const Vector<U, M>& rhs);

    template<typename U, std::size_t M>
    friend bool operator!=(const Vector<U, M>& lhs, const Vector<U, M>& rhs);


};

} // end namespace OpCore

#include "Vector.tpp"
#endif // VECTOR_H
