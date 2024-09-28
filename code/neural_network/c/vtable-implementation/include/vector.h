/********************************************************************************
 * @brief Implementation of polymorphic one-dimensional vectors.
 * 
 *         This file defines a vector structure that can hold either integers, 
 *         doubles, or strings, supporting various operations like resizing, 
 *         adding elements, and changing the vector type at runtime. 
 * 
 * @note Virtual tables are used as a design pattern to achieve polymorphic 
 *       behavior, allowing support of different types of vectors. This design
 *       facilitates easy integration of new vector types in the future.
 *******************************************************************************/
#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

#ifdef __cplusplus__
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>

/********************************************************************************
 * @brief Enum representing the different types of vectors available.
 * 
 *        This enum defines the possible types of one-dimensional vectors that
 *        can be implemented, allowing for type-specific operations and behaviors.
 *******************************************************************************/
enum vector_type
{
    VECTOR_TYPE_INT,     /* Int vector. */
    VECTOR_TYPE_DOUBLE,  /* Double vector. */
    VECTOR_TYPE_STRING,  /* String vector. */
    VECTOR_TYPE_COUNT    /* The number of available enumerators. */
};

/*******************************************************************************
 * @brief Forward declarations.
 ******************************************************************************/
struct vector_vtable;
struct vector_impl;

/********************************************************************************
 * @brief Struct implementation of polymorphic one-dimensional vectors.
 *******************************************************************************/
struct vector
{
    const struct vector_vtable* vptr; /* Pointer to virtual table. */
    struct vector_impl* impl;         /* Pointer to implementation details. */
};

/********************************************************************************
 * @brief Virtual table containing function pointers for the vector struct.
 *******************************************************************************/
struct vector_vtable
{
    /********************************************************************************
     * @brief Provides the data held by vector.
     * 
     * @param self Pointer to the vector.
     * 
     * @return Pointer to the data held by the vector.
     *******************************************************************************/
    void* (*data)(const struct vector* self);

    /********************************************************************************
     * @brief Provides the size of vector.
     * 
     * @param self Pointer to the vector.
     * 
     * @return The size of the vector as an unsigned integer.
     *******************************************************************************/
    size_t (*size)(const struct vector* self);

    /********************************************************************************
     * @brief Provides the type of vector.
     * 
     * @param self Pointer to the vector.
     * 
     * @return The type of the vector as an enumerator of enum vector_type.
     *******************************************************************************/
    enum vector_type (*type)(const struct vector* self);

    /********************************************************************************
     * @brief Indicates if vector is of arithmetic type.
     * 
     * @param self Pointer to the vector.
     * 
     * @return True if the vector is of arithmetic type, else false.
     *******************************************************************************/
    bool (*is_arithmetic)(const struct vector* self);

    /********************************************************************************
     * @brief Provides the start of the vector.
     * 
     * @param self Pointer to the vector.
     * 
     * @return Pointer to the start address of the vector.
     *******************************************************************************/
    void* (*begin)(const struct vector* self);

    /********************************************************************************
     * @brief Provides the end of the vector.
     * 
     * @param self Pointer to the vector.
     * 
     * @return Pointer to the end address of the vector.
     *******************************************************************************/
    void* (*end)(const struct vector* self);

    /********************************************************************************
     * @brief Clears vector.
     * 
     * @param self Pointer to the vector.
     *******************************************************************************/
    void (*clear)(struct vector* self);

    /********************************************************************************
     * @brief Resizes vector.
     * 
     * @param self     Pointer to the vector.
     * @param new_size The new size of the vector.
     * 
     * @return True if the vector was resized, else false.
     *******************************************************************************/
    bool (*resize)(struct vector* self, const size_t new_size);

    /********************************************************************************
     * @brief Pushes value to the back of vector.
     * 
     * @param self  Pointer to the vector.
     * @param value Pointer to the value to add.
     * 
     * @return True if the value was added, else false (if memory allocation fails).
     *******************************************************************************/
    bool (*push_back)(struct vector* self, const void* value);

    /********************************************************************************
     * @brief Pushes multiple values to the back of vector.
     * 
     * @param self Pointer to the vector.
     * @param data Pointer to field containing the data to add.
     * @param size The size of the field containing data.
     * 
     * @return True if all values were added, else false.
     *******************************************************************************/
    bool (*push_back_multiple)(struct vector* self, const void* data, const size_t size);

    /********************************************************************************
     * @brief Sets new type of vector.
     * 
     * @param self     Pointer to the vector.
     * @param new_type New type of the vector.
     * 
     * @return True if the vector type was changed, else false.
     * 
     * @note Previous vector content is cleared when the vector type is changed,
     *       which may lead to data loss if not managed properly.
     *******************************************************************************/
    bool (*set_type)(struct vector* self, const enum vector_type new_type);

    /*******************************************************************************
     * @brief Prints vector content.
     * 
     * @param self    Pointer to the vector.
     * @param ostream Pointer to output stream (default = terminal print).
     * @param end     Ending characters (default = new line).
     ******************************************************************************/
    void (*print)(const struct vector* self, FILE* ostream, const char* end);
};

/********************************************************************************
 * @brief Creates new vector.
 * 
 * @param type The vector type as an enumerator of enum vector_type.
 * @param data Pointer to data used to initialize the vector (if any). If NULL, 
 *             an empty vector of the specified type is created.
 * @param size The size of the data field (or the initial size of the
 *             vector if no field is specified).
 * 
 * @return Pointer to the new vector upon successful creation, otherwise NULL.
 *******************************************************************************/
struct vector* vector_new(const enum vector_type type, const void* data, 
                          const size_t size);

/********************************************************************************
 * @brief Deletes vector and frees all allocated memory.
 * 
 * @param self Double pointer to the vector to be deleted.
 *******************************************************************************/
void vector_delete(struct vector** self);

#ifdef __cplusplus__
}
#endif

#endif /* VECTOR_INCLUDED */