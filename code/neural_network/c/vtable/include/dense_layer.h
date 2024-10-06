/*******************************************************************************
 * @brief Implementation of dense (fully connected) layers for neural networks.
 * 
 *        This file defines a dense layer structure that provides the core 
 *        functionality for dense layers, including feedforward, 
 *        backpropagation, and optimization operations.
 * 
 * @note Virtual tables are used as a design pattern to achieve polymorphism,
 *       allowing support of different layer types. This design facilitates
 *       easy integration of new layer types in the future.
 ******************************************************************************/

#ifndef DENSE_LAYER_INCLUDED
#define DENSE_LAYER_INCLUDED

#ifdef __cplusplus__
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>

#include "act_func.h"

/*******************************************************************************
 * @brief Forward declarations.
 ******************************************************************************/
struct dense_layer_impl;   /* Implementation details of struct dense layer. */
struct dense_layer_vtable; /* Virtual table for struct dense_layer. */
struct vector;             /* Polymorphic one-dimensional vector. */
struct vector_2d;          /* Polymorphic two-dimensional vector. */

/*******************************************************************************
 * @brief Struct implementation of dense layers.
 ******************************************************************************/
struct dense_layer
{
    const struct dense_layer_vtable* vptr; /* Pointer to virtual table. */
    struct dense_layer_impl* impl;         /* Pointer to implementation details. */   
};

/********************************************************************************
 * @brief Virtual table containing function pointers for struct dense_layer.
 *******************************************************************************/
struct dense_layer_vtable
{
    /*******************************************************************************
     * @brief Provides the output of the dense layer.
     * 
     * @param self Pointer to the dense layer.
     *
     * @return Pointer to vector holding the output of the dense layer.
     ******************************************************************************/
    const vector* (*output)(const struct dense_layer* self);

    /*******************************************************************************
     * @brief Provides the error of the dense layer.
     * 
     * @param self Pointer to the dense layer.
     *
     * @return Pointer to vector holding the error of the dense layer.
     ******************************************************************************/
    const vector* (*error)(const struct dense_layer* self);

    /*******************************************************************************
     * @brief Provides the bias of the dense layer.
     * 
     * @param self Pointer to the dense layer.
     *
     * @return Pointer to vector holding the bias of the dense layer.
     ******************************************************************************/
    const vector* (*bias)(const struct dense_layer* self);

    /*******************************************************************************
     * @brief Provides the weights of the dense layer.
     * 
     * @param self Pointer to the dense layer.
     *
     * @return Pointer to two-dimensional vector holding the weights of the 
     *         dense layer.
     ******************************************************************************/
    const vector_2d* (*weights)(const struct dense_layer* self);

    /*******************************************************************************
     * @brief Provides the activation function of the dense layer.
     * 
     * @param self Pointer to the dense layer.
     * 
     * @return The activation function as an enumerator of enum act_func.
     ******************************************************************************/
    enum act_func (*act_func)(const struct dense_layer* self);

    /*******************************************************************************
     * @brief Provides the number of nodes in the dense layer.
     * 
     * @param self Pointer to the dense layer.
     * 
     * @return The number of nodes as an unsigned integer.
     ******************************************************************************/
    size_t (*node_count)(const struct dense_layer* self);

    /*******************************************************************************
     * @brief Provides the number of weights per node in the dense layer.
     * 
     * @param self Pointer to the dense layer.
     * 
     * @return The number of weights per node as an unsigned integer.
     ******************************************************************************/
    size_t (*weight_count)(const struct dense_layer* self);
    
    /*******************************************************************************
     * @brief Performs feedforward for dense layer.
     * 
     * @param self  Pointer to the dense layer.
     * @param input Reference to vector holding the input of the dense layer.
     * 
     * @return True if feedforward was performed, else false.
     ******************************************************************************/
    bool (*feedforward)(struct dense_layer* self, const struct vector* input);

    /*******************************************************************************
     * @brief Performs backpropagation for output layer.
     * 
     * @param self      Pointer to the dense layer.
     * @param reference Reference to vector holding reference values.
     * 
     * @return True if backpropagation was performed, else false.
     ******************************************************************************/
    bool (*backpropagate_output)(struct dense_layer* self, const struct vector* reference);

    /*******************************************************************************
     * @brief Performs backpropagation for hidden layer.
     * 
     * @param self       Pointer to the dense layer.
     * @param next_layer Reference to the next layer in the neural network.
     * 
     * @return True if backpropagation was performed, else false.
     ******************************************************************************/
    bool (*backpropagate_hidden)(struct dense_layer* self, 
                                 const struct dense_layer* next_layer);

    /*******************************************************************************
     * @brief Performs optimization for dense layer.
     * 
     * @param self          Pointer to the dense layer.
     * @param input         Reference to vector holding the input of the layer.
     * @param learning_rate The rate with which to optimize the parameters.
     * 
     * @return True if optimization was performed, else false.
     ******************************************************************************/
    bool (*optimize)(struct dense_layer* self, const struct vector* input,
                     const double learning_rate);

    /*******************************************************************************
     * @brief Prints stored parameters.
     * 
     * @param self    Pointer to the dense layer.
     * @param ostream Pointer to output stream (default = terminal print).
     ******************************************************************************/
    void (*print)(const struct dense_layer* self, FILE* ostream);
};

/*******************************************************************************
 * @brief Creates new dense layer. All parameters are initialized to random
 *        values between 0 - 1.
 *
 * @param node_count   The number of nodes in the new layer.
 * @param weight_count The number of weights per node in the new layer.
 * @param act_func     The activation function of the layer.
 * 
 * @return Pointer to the new dense layer upon successful creation, 
 *         otherwise NULL.
 ******************************************************************************/
struct dense_layer* dense_layer_new(const size_t node_count, const size_t weight_count,
                                    const enum act_func act_func);

/*******************************************************************************
 * @brief Deletes dense layer and frees all allocated memory.
 *
 * @param self Double pointer to the dense layer to be deleted.
 ******************************************************************************/
void dense_layer_delete(struct dense_layer** self);

#ifdef __cplusplus__
}
#endif

#endif /* DENSE_LAYER_INCLUDED */