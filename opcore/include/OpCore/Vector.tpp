#include <OpCore/Vector.h>

namespace OpCore {

template<typename T, std::size_t N>
Vector<T, N>::Vector() {
    data.fill(T{});
}

template<typename T, std::size_t N>
Vector<T, N>::Vector(const std::initializer_list<T>& list) {
    assert(list.size() == N && "Initializer list size must match vector dimension.");
    std::copy(list.begin(), list.end(), data.begin());
}

template<typename T, std::size_t N>
T& Vector<T, N>::operator[](std::size_t index) {
    assert(index < N);
    return data[index];
}

template<typename T, std::size_t N>
const T& Vector<T, N>::operator[](std::size_t index) const {
    assert(index < N);
    return data[index];
}

template<typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator+(const Vector<T, N>& other) const {
    Vector<T, N> result;
    for (std::size_t i = 0; i < N; ++i)
        result.data[i] = data[i] + other.data[i];
    return result;
}

template<typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator-(const Vector<T, N>& other) const {
    Vector<T, N> result;
    for (std::size_t i = 0; i < N; ++i)
        result.data[i] = data[i] - other.data[i];
    return result;
}

template<typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator*(const T scalar) const {
    Vector<T, N> result;
    for (std::size_t i = 0; i < N; ++i)
        result.data[i] = data[i] * scalar;
    return result;
}

template<typename T, std::size_t N>
T Vector<T, N>::dot(const Vector<T, N>& other) const {
    T sum = T{};
    for (std::size_t i = 0; i < N; ++i)
        sum += data[i] * other.data[i];
    return sum;
}

template<typename T, std::size_t N>
void Vector<T, N>::print() const {
    for (std::size_t i = 0; i < N; ++i)
        std::cout << data[i] << " ";
    std::cout << "\n";
}

// Horizontal concatenation.
template<typename T, std::size_t N>
template<std::size_t M>
Vector<T, N + M> Vector<T, N>::hconcat(const Vector<T, M>& other) const {
    Vector<T, N + M> result;
    for (std::size_t i = 0; i < N; ++i) {
        result[i] = data[i];
    }
    for (std::size_t i = 0; i < M; ++i) {
        result[N + i] = other[i];
    }
    return result;
}

// Vertical concatenation (same as horizontal for vectors).
template<typename T, std::size_t N>
template<std::size_t M>
Vector<T, N + M> Vector<T, N>::vconcat(const Vector<T, M>& other) const {
    return hconcat(other);
}

// Vector transposition (no-op, since vectors are 1D)
template<typename T, std::size_t N>
Vector<T, N> Vector<T, N>::transpose() const {
    return *this;
}

// Equality operator for vector comparison.
template<typename T, std::size_t N>
bool operator==(const Vector<T, N>& lhs, const Vector<T, N>& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
        if (lhs.data[i] != rhs.data[i]) {
            return false;
        }
    }
    return true;
}

template<typename T, std::size_t N>
bool operator!=(const Vector<T, N>& lhs, const Vector<T, N>& rhs) {
    return !(lhs == rhs);
}

// Check if any element in the vector is NaN.
template<typename T, std::size_t N>
bool Vector<T, N>::isnan() const {
    for (std::size_t i = 0; i < N; ++i) {
        if (std::isnan(data[i])) {
            return true;
        }
    }
    return false;
}

} // end namespace OpCore