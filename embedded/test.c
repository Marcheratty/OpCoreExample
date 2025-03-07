#include <stdio.h>
#include <stdlib.h>
#include "include/Matrix.h"
#include "include/Vector.h"

// TEST VECTOR LIB
void testVector(){
    Vector* test_vect = (Vector*)malloc(sizeof(Vector));
    initVector(test_vect, 9);
    pushBack(test_vect, 1.0);
    pushBack(test_vect, 1.0);
    pushBack(test_vect, 2.0);
    pushBack(test_vect, 3.0);
    pushBack(test_vect, 5.0);
    pushBack(test_vect, 8.0);
    printVector(test_vect);

    Vector* test_vect2 = (Vector*)malloc(sizeof(Vector));
    initVector(test_vect2, 9);
    pushBack(test_vect2, 2.0);
    pushBack(test_vect2, 4.0);
    pushBack(test_vect2, 6.0);
    pushBack(test_vect2, 8.0);
    pushBack(test_vect2, 10.0);
    pushBack(test_vect2, 12.0);
    printVector(test_vect2);

    // Add and subtract
    addVectors(test_vect, test_vect2);
    subtractVectors(test_vect, test_vect2);

    Vector* test_vect3 = (Vector*)malloc(sizeof(Vector));
    Vector* test_vect4 = (Vector*)malloc(sizeof(Vector));
    initVector(test_vect3, 3);
    initVector(test_vect4, 3);
    // Push back to vector 3
    pushBack(test_vect3, 9.0);
    pushBack(test_vect3, 10.0);
    pushBack(test_vect3, 11.0);
    // Push back to vector 4
    pushBack(test_vect4, 2.0);
    pushBack(test_vect4, 3.0);
    pushBack(test_vect4, 4.0);
    // Cross product 
    crossProduct(test_vect3, test_vect4);
    // Dot product 
    dotProduct(test_vect3, test_vect4);
}

void testMatrix(){
    printf("\n");
    Vector* test_vect = (Vector*)malloc(sizeof(Vector));
    initVector(test_vect, 9);
    pushBack(test_vect, 1.0);
    pushBack(test_vect, 0.5);
    pushBack(test_vect, 4.2);
    pushBack(test_vect, 20.4);
    pushBack(test_vect, 6.1);
    pushBack(test_vect, 9.2);
    pushBack(test_vect, 11.7);
    pushBack(test_vect, 10.9);
    pushBack(test_vect, 3.2);

    Matrix* test_mat1 = (Matrix*)malloc(sizeof(Matrix));
    createMatrix(test_mat1, test_vect, 3, 3);
    printf("Matrix 1\n");
    printMatrix(test_mat1);

    // Matrix 2
    printf("\n");
    Vector* test_vect2 = (Vector*)malloc(sizeof(Vector));
    initVector(test_vect2, 9);
    pushBack(test_vect2, 1.1);
    pushBack(test_vect2, 2.5);
    pushBack(test_vect2, 9.9);
    pushBack(test_vect2, 44.0);
    pushBack(test_vect2, 25.1);
    pushBack(test_vect2, 35.21);
    pushBack(test_vect2, 4.12);
    pushBack(test_vect2, 3.1416);
    pushBack(test_vect2, 2.78);

    Matrix* test_mat2 = (Matrix*)malloc(sizeof(Matrix));
    createMatrix(test_mat2, test_vect2, 3, 3);
    printf("Matrix 2\n");
    printMatrix(test_mat2);

    // Matrix addition
    addMatrices(test_mat1, test_mat2);
    // Subtraction
    subtractMatrices(test_mat1, test_mat2);
    // Transpose 
    transposeMatrix(test_mat1);
    // Eye matrix
    eye(4);
    // Zero matrix 
    zeros(4, 5);
}

int main(){
    //testVector();
    testMatrix();
    return 0;
}