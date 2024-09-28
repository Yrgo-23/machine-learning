/********************************************************************************
 * @brief Implementation of one- and two-dimensional double vectors.
 * 
 *        This file provides functionality to create, delete and print vectors.
 *******************************************************************************/
#ifndef DOUBLE_VECTOR_INCLUDED
#define DOUBLE_VECTOR_INCLUDED

#ifdef __cplusplus__
extern "C" {
#endif

#include <stdio.h>

/********************************************************************************
 * @brief Dynamically allocates a one-dimensional vector of doubles.
 * 
 * @param size The number of elements the vector can hold.
 * 
 * @return Pointer to the newly allocated vector upon success, 
 *         or NULL if memory allocation fails.
 *******************************************************************************/
double* double_vector_new(const size_t size);

/********************************************************************************
 * @brief Deletes one-dimensional vector and frees all allocated memory.
 * 
 * @param self Double pointer to the vector to be deleted.
 *******************************************************************************/
void double_vector_delete(double** self);

/********************************************************************************
 * @brief Dynamically allocates a two-dimensional vector of doubles with 
 *        the specified number of rows and columns.
 * 
 * @param row_count    The number of rows to allocate.
 * @param column_count The number of columns for each row.
 * 
 * @return Pointer to the newly allocated 2D vector of doubles upon success, 
 *         or NULL if memory allocation fails.
 *******************************************************************************/
double** double_vector_2d_new(const size_t row_count, const size_t column_count);

/********************************************************************************
 * @brief Deletes two-dimensional vector and frees all allocated memory.
 * 
 * @param self Triple pointer to the two-dimensional vector to be deleted.
 * 
 * @note All referenced one-dimensional vectors will be deleted before the
 *       deletion of the two-dimensional vector.
 *******************************************************************************/
void double_vector_2d_delete(double*** self, const size_t row_count);

/*******************************************************************************
 * @brief Prints content held by one-dimensional vector.
 * 
 * @param self    Pointer to the vector.
 * @param size    Size of the vector in terms of values it holds.
 * @param ostream Pointer to the output stream to use (default = terminal print).
 * @param end     Ending characters (default = new line).
 ******************************************************************************/
void double_vector_print(const double* data, const size_t size, FILE* ostream, const char* end);

/********************************************************************************
 * @brief Prints the content of a two-dimensional double vector, row by row.
 * 
 * @param data         Pointer to the two-dimensional vector.
 * @param row_count    The number of rows in the vector.
 * @param column_count The number of columns in each row of the vector.
 * @param ostream      Pointer to output stream to use (default = terminal print).
 * @param end          Ending characters (default = new line).
 *******************************************************************************/
void double_vector_2d_print(double** data, const size_t row_count,
                            const size_t column_count, FILE* ostream, const char* end);

#ifdef __cplusplus__
}
#endif

#endif /* DOUBLE_VECTOR_INCLUDED */