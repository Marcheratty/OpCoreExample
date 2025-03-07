#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    double* data;
    size_t size;
    size_t capacity;
} Vector;

// Create a new vector from an existing array 
void initVector(Vector* vect, size_t initial_capacity);

// Push back 
void pushBack(Vector* vect, double new_data);

// Pop back
void popBack(Vector* vect);

// Print vector 
void printVector(const Vector* vect);

// Free allocated memory
void freeVector(Vector* vect);

// OPERATIONS
Vector* addVectors(Vector* vect1, Vector* vect2);

Vector* subtractVectors(Vector* vect1, Vector* vect2);

Vector* crossProduct(Vector* vect1, Vector* vect2);

long* dotProduct(Vector* vect1, Vector* vect2);

uint8_t compareVectors(const Vector* vect1, const Vector* vect2);

#endif /* VECTOR_H */