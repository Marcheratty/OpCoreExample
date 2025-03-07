#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"
#include <stdint.h>

typedef struct {
    size_t rows; 
    size_t cols; 
    Vector* data;
} Matrix;

// Emulated constructor
void createMatrix(Matrix* mat, Vector* vect, size_t rows, size_t cols);

// Destroy matrix 
void freeMatrix(Matrix* mat);

// Print matrix 
void printMatrix(const Matrix* mat);

// Addition
Matrix* addMatrices(const Matrix* mat1, const Matrix* mat2);

// Subtraction
Matrix* subtractMatrices(const Matrix* mat1, const Matrix* mat2);

// Multiplication
Matrix* multiplyMatrices(const Matrix* mat1, const Matrix* mat2);

// Transpose 
Matrix* transposeMatrix(const Matrix* mat);

// Inverse 
Matrix* invertMatrix(const Matrix* mat);

// Compare matrices 
uint8_t compareMatrices(const Matrix* mat1, const Matrix* mat2);

/// Auxiliary functions
Matrix* eye(size_t rows);
Matrix* zeros(size_t rows, size_t cols);

#endif /* MATRIX_H */ 