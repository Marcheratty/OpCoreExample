#include "Vector.h"
#include <stdlib.h>
#include <stdio.h>


// Allocate memory for a new vector of capacity n 
void initVector(Vector* vect, size_t initial_capacity){
    if(vect == NULL){
        fprintf(stderr, "Cannot initialize vector: NULL pointer, allocate memory first\n");
        return;
    }
    vect->capacity = initial_capacity;
    vect->data = (double*)malloc(vect->capacity * sizeof(double));
    vect->size = 0;
}

// Push back items
void pushBack(Vector* vect, double new_data){
    if(vect == NULL){
        fprintf(stderr, "Error in push back: Vector is NULL\n");
        return;
    }
    // If space runs out, duplicate it
    if(vect->size >= vect->capacity){
        vect->capacity *= 2;
    }
    vect->data = (double*)realloc(vect->data, vect->capacity * sizeof(double));
    *(vect->data + vect->size) = new_data;
    ++vect->size;
}

// Pop back
void popBack(Vector* vect){
    if(vect == NULL){
        fprintf(stderr, "Error in pop back: Vector is NULL\n");
        return;
    }
    if(vect->size == 0){
        fprintf(stderr, "Cannot pop back, vector is already empty\n");
        return;
    }
    --vect->size;
}

// Free space
void freeVector(Vector *vect){
    free(vect->data);
    vect->data = NULL;
    vect->size = 0;
    vect->capacity = 0;
}

// Print a vector
void printVector(const Vector* vect){
    if(vect == NULL){
        fprintf(stderr, "Error in print: Vector is NULL\n");
        return;
    }
    for(size_t i=0; i < vect->size; ++i){
        printf("%f ", *(vect->data + i));
    }
    printf("\n");
}

// Vector addition
Vector* addVectors(Vector* vect1, Vector* vect2){
    if(vect1 == NULL || vect2 == NULL){
        fprintf(stderr, "Error adding vectors: NULL vectors present\n");
        return NULL;
    }
    if(vect1->size != vect2->size){
        fprintf(stderr, "Vectors must be the same size for vector addition\n");
        return NULL;
    }
    Vector* result = (Vector*)malloc(sizeof(Vector));
    if(result == NULL){
        fprintf(stderr, "Vector memory could not be allocated\n");
        return NULL;
    }
    initVector(result, vect1->size);
    
    for(size_t i=0; i < vect1->size; ++i){
        pushBack(result, *(vect1->data + i) + *(vect2->data + i));
    }
    printf("Result vector addition: ");
    printVector(result);
    return result;
}

// Vector subtraction
Vector* subtractVectors(Vector* vect1, Vector* vect2){
    if(vect1 == NULL || vect2 == NULL){
        fprintf(stderr, "Error subtracting vectors: NULL vectors present\n");
        return NULL;
    }
    if(vect1->size != vect2->size){
        fprintf(stderr, "Vectors must be the same size for vector addition\n");
        return NULL;
    }
    Vector* result = (Vector*)malloc(sizeof(Vector));
    if(result == NULL){
        fprintf(stderr, "Vector memory could not be allocated\n");
        return NULL;
    }
    initVector(result, vect1->size);
    
    for(size_t i=0; i < vect1->size; ++i){
        pushBack(result, *(vect1->data + i) - *(vect2->data + i));
    }
    printf("Result vector subtraction: ");
    printVector(result);
    return result;
}

// Cross product 
Vector* crossProduct(Vector* vect1, Vector* vect2){
    if(vect1 == NULL || vect2 == NULL){
        fprintf(stderr, "Error in cross product: NULL vectors present\n");
        return NULL;
    }
    if(vect1->size != 3 || vect2->size != 3){
        fprintf(stderr, "Vector dimensionalities must be 3 for cross product\n");
        return NULL;
    }
    Vector* result = (Vector*)malloc(sizeof(Vector));
    if(result == NULL){
        fprintf(stderr, "Vector memory could not be allocated\n");
        return NULL;
    }
    // Three dimensional vector
    initVector(result, 3);
    // Perform cross product operations 
    pushBack(result, (*(vect1->data + 1)) * (*(vect2->data + 2)) - (*(vect1->data + 2)) * (*(vect2->data + 1)));
    pushBack(result, (*(vect1->data + 2)) * (*(vect2->data + 0)) - (*(vect1->data + 0)) * (*(vect2->data + 2)));
    pushBack(result, (*(vect1->data + 0)) * (*(vect2->data + 1)) - (*(vect1->data + 1)) * (*(vect2->data + 0)));
    printf("Result vector cross product: ");
    printVector(result);
    return result;
}

// Dot product 
long* dotProduct(Vector* vect1, Vector* vect2){
    if(vect1 == NULL || vect2 == NULL){
        fprintf(stderr, "Error in dot product: NULL vectors present\n");
        return NULL;
    }
    if(vect1->size != vect2->size){
        fprintf(stderr, "Vectors must be the same dimension\n");
        return NULL;
    }
    // Perform dot product 
    long* dot_result = (long*)malloc(sizeof(long));
    *dot_result = 0;
    for(size_t i=0; i < vect1->size; ++i){
        *dot_result += ((*(vect1->data + i)) * (*(vect2->data + i)));
    }
    printf("Dot product: %ld\n", *dot_result);
    return dot_result;
}

// Compare if 2 vectors are equal. Returns 0 if they are different, 1 if equal 
uint8_t compareVectors(const Vector* vect1, const Vector* vect2){
    if(vect1 == NULL || vect2 == NULL){
        fprintf(stderr, "Error comparing vectors: NULL vectors provided'n");
        return 0;
    }
    if(vect1->size != vect2->size){
        return 0;
    }
    for(size_t i=0; i < vect1->size; ++i){
        if(*(vect1->data + i) != *(vect2->data + i)){
            return 0;
        }
    }
    // If everything to this point went good they are equal
    return 1;
}