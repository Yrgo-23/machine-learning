#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * @brief Implementation of vectors for holding integers.
 ******************************************************************************/
struct int_vector
{
    int* data;   /** Pointer to dynamically allocated field. */
    size_t size; /** The size of the vector. */
};

/*******************************************************************************
 * @brief Pushes value to the back of vector.
 * 
 * @param self  Pointer to the vector.
 * @param value The value to add.
 * 
 * @return True if the operation succeeded, else false.
 ******************************************************************************/
bool int_vector_push_back(struct int_vector* self, const int value);

/*******************************************************************************
 * @brief Clears vector.
 * 
 * @param self Pointer to the vector.
 ******************************************************************************/
void int_vector_clear(struct int_vector* self);

/*******************************************************************************
 * @brief Prints content held by vector in a bracket.
 * 
 * @param self    Pointer to the vector.
 * @param ostream Pointer to output file stream (default = terminal print).
 ******************************************************************************/
void int_vector_print(const struct int_vector* self, FILE* ostream);

#endif /* VECTOR_INCLUDED */
