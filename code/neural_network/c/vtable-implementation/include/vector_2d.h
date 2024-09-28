/********************************************************************************
 * @brief Implementation of polymorphic two-dimensional vectors.
 * 
 *        This file defines a two-dimensional vector structure that holds 
 *        pointers to one-dimensional vectors of any type, supporting operations 
 *        such as resizing, adding elements, and managing ownership of contained 
 *        vectors.
 * 
 * @note Virtual tables are used as a design pattern to achieve polymorphic 
 *       behavior, allowing support of different types of vectors. This design
 *       facilitates easy integration of new vector types in the future.
 *******************************************************************************/
#ifndef VECTOR_2D_INCLUDED
#define VECTOR_2D_INCLUDED

#ifdef __cplusplus__
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>

#include "vector.h"

/*******************************************************************************
 * @brief Forward declarations.
 ******************************************************************************/
struct vector_2d_impl;   /* Implementation details of struct vector_2d. */
struct vector_2d_vtable; /* Virtual table for struct vector_2d. */

/********************************************************************************
 * @brief Struct implementation of polymorphic two-dimensional vectors.
 *
 * @note This implementation holds pointers to vectors of any type.
 *******************************************************************************/
struct vector_2d
{
    const struct vector_2d_vtable* vptr; /* Pointer to virtual table. */
    struct vector_2d_impl* impl;         /* Pointer to implementation details. */
};

/********************************************************************************
 * @brief Virtual table containing function pointers for struct vector_2d.
 *******************************************************************************/
struct vector_2d_vtable
{
    /********************************************************************************
     * @brief Provides the data held by two-dimensional vector.
     * 
     * @param self Pointer to the two-dimensional vector.
     * 
     * @return Pointer to the data held by the vector.
     *******************************************************************************/
    struct vector** (*data)(const struct vector_2d* self);

    /********************************************************************************
     * @brief Provides the size of two-dimensional vector.
     * 
     * @param self Pointer to the two-dimensional vector.
     * 
     * @return The size of the vector as an unsigned integer.
     *******************************************************************************/
    size_t (*size)(const struct vector_2d* self);

    /********************************************************************************
     * @brief Provides the start of two-dimensional vector.
     * 
     * @param self Pointer to the two-dimensional vector.
     * 
     * @return Pointer to the start address of the vector.
     *******************************************************************************/
    struct vector** (*begin)(const struct vector_2d* self);

    /********************************************************************************
     * @brief Provides the end of two-dimensional vector.
     * 
     * @param self Pointer to the two-dimensional vector.
     * 
     * @return Pointer to the end address of the vector.
     *******************************************************************************/
    struct vector** (*end)(const struct vector_2d* self);

    /********************************************************************************
     * @brief Clears two-dimensional vector.
     * 
     * @param self Pointer to the two-dimensional vector.
     *******************************************************************************/
    void (*clear)(struct vector_2d* self);

    /********************************************************************************
     * @brief Resizes two-dimensional vector.
     * 
     * @param self     Pointer to the two-dimensional vector.
     * @param new_size The new size of the vector.
     * 
     * @return True if the vector was resized, else false.
     *******************************************************************************/
    bool (*resize)(struct vector_2d* self, const size_t new_size);

    /********************************************************************************
     * @brief Pushes vector pointer to the back of two-dimensional vector.
     * 
     * @param self   Pointer to the two-dimensional vector.
     * @param vector Double pointer referring to the vector to add.
     * 
     * @return True if the vector pointer was added, else false.
     * 
     *  @note The two-dimensional vector takes ownership of referenced
     *        one-dimensional vector. Consequently, the data will be deleted upon 
     *        deletion of the two-dimensional vector.
     *******************************************************************************/
    bool (*push_back)(struct vector_2d* self, const struct vector** vector);

    /********************************************************************************
     * @brief Pushes multiple vector pointers to the back of vector.
     * 
     * @param self Pointer to the vector.
     * @param data Pointer to field containing the vector pointers to add.
     * @param size The size of the field containing vector pointers.
     * 
     * @return True if all pointers were added, else false.
     *******************************************************************************/
    bool (*push_back_multiple)(struct vector_2d* self, const vector** vectors, 
                               const size_t size);

    /*******************************************************************************
     * @brief Prints content held by two-dimensional vector.
     * 
     * @param self    Pointer to the two-dimensional vector.
     * @param ostream Pointer to output stream (default = terminal print).
     * @param end     Ending characters (default = new line).
     ******************************************************************************/
    void (*print)(const struct vector_2d* self, FILE* ostream, const char* end);
};

/********************************************************************************
 * @brief Creates new two-dimensional vector.
 * 
 * @param vectors Pointer to field holding vector pointers used to initialize 
 *                the vector (if any).
 * @param size    The size of the vector pointer field (or the initial size
 *                of the vector if no vector pointer filed is specified).
 * 
 * @return Pointer to the new two-dimensional vector upon successful creation, 
 *         otherwise NULL.
 *******************************************************************************/
struct vector_2d* vector_2d_new(const struct vector** vectors, const size_t size);

/********************************************************************************
 * @brief Deletes two-dimensional vector and frees all allocated memory.
 * 
 * @param self Double pointer to the two-dimensional vector to be deleted.
 * 
 * @note All referenced one-dimensional vectors will be deleted before the
 *       deletion of the two-dimensional vector.
 *******************************************************************************/
void vector_2d_delete(struct vector_2d** self);

#ifdef __cplusplus__
}
#endif

#endif /* VECTOR_2D_INCLUDED */