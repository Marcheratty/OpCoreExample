#include "Matrix.h"
#include "stdio.h"
#include <stdlib.h>

// Initialize a new matrix from vector and dimensions 
void createMatrix(Matrix* mat, Vector* vect, size_t rows, size_t cols){
    if(mat == NULL){
        fprintf(stderr, "Cannot initialize matrix: Matrix NULL pointer, allocate memory first\n");
        return;
    }
    if(vect == NULL){
        fprintf(stderr, "Cannot initialize matrix: Value vector NULL pointer, allocate memory first\n");
        return;
    }
    // Handles rows or cols = 0
    if(vect->size != rows * cols){
        fprintf(stderr, "Value vector content should fill matrix dimensions");
        return;
    }
    mat->rows = rows;
    mat->cols = cols;
    mat->data = vect;
}

// Free allocated memory (destroy)
void freeMatrix(Matrix* mat){
    free(mat->data);
    mat->rows = 0;
    mat->cols = 0;
    mat->data = NULL;
}

// Print matrix
void printMatrix(const Matrix* mat){
    for(size_t row=0; row < mat->rows; ++row){
        printf("| ");
        for(size_t col=0; col < mat->cols; ++col){
            printf("%f ", *(mat->data->data + (row * mat->cols) + col));
        }
        printf("|\n");
    }
    printf("\n");
}

// Matrix addition
Matrix* addMatrices(const Matrix* mat1, const Matrix* mat2){
    if(mat1 == NULL || mat2 == NULL){
        fprintf(stderr, "Error adding matrices: NULL matrices present\n");
        return NULL;
    }
    if(mat1->rows != mat2->rows || mat1->cols != mat2->cols){
        fprintf(stderr, "Matrices must be the same size for matrix addition\n");
        return NULL;
    }
    Matrix* result = (Matrix*)malloc(sizeof(Matrix));
    if(result == NULL){
        fprintf(stderr, "Matrix memory could not be allocated\n");
        return NULL;
    }
    Vector* result_vect = (Vector*)malloc(sizeof(Vector));
    if(result == NULL){
        fprintf(stderr, "Result vector failed to allocate\n");
        return NULL;
    }
    initVector(result_vect, mat1->rows * mat1->cols);
    for(size_t i=0; i < mat1->data->size; ++i){
        pushBack(result_vect, (*(mat1->data->data + i)) + (*(mat2->data->data + i)));
    }
    createMatrix(result, result_vect, mat1->rows, mat1->cols);
    printf("The result of matrix addition:\n");
    printMatrix(result);
    return result;
}

// Matrix subtraction
Matrix* subtractMatrices(const Matrix* mat1, const Matrix* mat2){
    if(mat1 == NULL || mat2 == NULL){
        fprintf(stderr, "Error subtracting matrices: NULL matrices present\n");
        return NULL;
    }
    if(mat1->rows != mat2->rows || mat1->cols != mat2->cols){
        fprintf(stderr, "Matrices must be the same size for matrix subtraction\n");
        return NULL;
    }
    Matrix* result = (Matrix*)malloc(sizeof(Matrix));
    if(result == NULL){
        fprintf(stderr, "Matrix memory could not be allocated\n");
        return NULL;
    }
    Vector* result_vect = (Vector*)malloc(sizeof(Vector));
    if(result == NULL){
        fprintf(stderr, "Result vector failed to allocate\n");
        return NULL;
    }
    initVector(result_vect, mat1->rows * mat1->cols);
    for(size_t i=0; i < mat1->data->size; ++i){
        pushBack(result_vect, (*(mat1->data->data + i)) - (*(mat2->data->data + i)));
    }
    createMatrix(result, result_vect, mat1->rows, mat1->cols);
    printf("The result of matrix subtraction:\n");
    printMatrix(result);
    return result;
}

// Transpose a matrix
Matrix* transposeMatrix(const Matrix* mat){
    if(mat == NULL){
        fprintf(stderr, "Error transposing: Matrix is NULL\n");
        return NULL;
    }
    Matrix* result = (Matrix*)malloc(sizeof(Matrix));
    createMatrix(result, mat->data, mat->cols, mat->rows);
    for(size_t i=0; i < mat->rows; ++i){
        for(size_t j=0; j < mat->cols; ++j){
            *(result->data->data + (i * mat->cols + j)) = *(mat->data->data + (j * mat->cols) + i);
        }
    }
    printf("\nThe result of matrix transpose:\n");
    printMatrix(result);
    return result;
}

// Compare if 2 matrices are equal
uint8_t compareMatrices(const Matrix* mat1, const Matrix* mat2){
    return compareVectors(mat1->data, mat2->data);
}

// Create special matrices 
Matrix* eye(size_t rows){
    Matrix* eyed_matrix = (Matrix*)malloc(sizeof(Matrix));
    if(eyed_matrix == NULL){
        fprintf(stderr, "Eye: Failed to allocate matrix\n");
        return NULL;
    }
    Vector* eyed_vect = (Vector*)malloc(sizeof(Vector));
    if(eyed_vect == NULL){
        fprintf(stderr, "Eye: Failed to allocate vector\n");
        return NULL;
    }
    initVector(eyed_vect, 2);
    size_t aux = 0;
    for(size_t i=0; i < rows*rows; ++i){
        if(i == aux){
            pushBack(eyed_vect, 1.0);
            aux += (rows + 1);
            continue;
        }
            pushBack(eyed_vect, 0.0);
    }
    createMatrix(eyed_matrix, eyed_vect, rows, rows);  // Square matrix
    printf("The result of eye matrix 4x4:\n");
    printMatrix(eyed_matrix);
    return eyed_matrix;
}

Matrix* zeros(size_t rows, size_t cols){
    Matrix* zero_matrix = (Matrix*)malloc(sizeof(Matrix));
    if(zero_matrix == NULL){
        fprintf(stderr, "Zeros: Failed to allocate matrix\n");
        return NULL;
    }
    Vector* zero_vect = (Vector*)malloc(sizeof(Vector));
    if(zero_vect == NULL){
        fprintf(stderr, "Zeros: Failed to allocate vector\n");
        return NULL;
    }
    initVector(zero_vect, 2);
    for(size_t i=0; i < rows * cols; ++i){
        pushBack(zero_vect, 0.0);
    }
    createMatrix(zero_matrix, zero_vect, rows, cols);
    printf("Result of zero matrix:\n");
    printMatrix(zero_matrix);
    return zero_matrix;
}