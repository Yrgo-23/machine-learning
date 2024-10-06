/*******************************************************************************
 * @brief Implementation of dense layer for neural networks. 
 * 
 *        This file defines a dense layer structure that provides the core 
 *        functionality for dense layers, including feedforward, 
 *        backpropagation, and optimization operations.
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
struct dense_layer; /* Dense layer structure for neural networks. */

/*******************************************************************************
 * @brief Creates new dense layer.
 * 
 * @param node_count   The number of nodes in the dense layer.
 * @param weight_count The number of weights per node in the dense layer.
 * @param act_func     The activation function to use for the layer.
 * 
 * @return Pointer to the new dense layer if created, NULL if the dense
 *         layer couldn't be created due to lack of memory.
 ******************************************************************************/
struct dense_layer* dense_layer_new(const size_t node_count, const size_t weight_count,
                                    const enum act_func act_func);

/*******************************************************************************
 * @brief Deletes dense layer by freeing allocated resources.
 * 
 * @param self Double pointer to the dense layer to delete.
 ******************************************************************************/
void dense_layer_delete(struct dense_layer** self);

/*******************************************************************************
 * @brief Provides the outputs of the dense layer.
 * 
 * @param self Pointer to the dense layer.
 * 
 * @return Pointer to field holding the dense layer's output.
 ******************************************************************************/
const double* dense_layer_output(const struct dense_layer* self);

/*******************************************************************************
 * @brief Provides the error values of the dense layer.
 * 
 * @param self Pointer to the dense layer.
 * 
 * @return Pointer to field holding the dense layer's error values.
 ******************************************************************************/
const double* dense_layer_error(const struct dense_layer* self);

/*******************************************************************************
 * @brief Provides the bias of each node in the dense layer.
 * 
 * @param self Pointer to the dense layer.
 * 
 * @return Pointer to field holding the bias of each node in the dense layer.
 ******************************************************************************/
const double* dense_layer_bias(const struct dense_layer* self);

/*******************************************************************************
 * @brief Provides the weights of the dense layer.
 * 
 * @param self Pointer to the dense layer.
 * 
 * @return Pointer to field holding the weights of each node in the dense layer.
 ******************************************************************************/
const double** dense_layer_weights(const struct dense_layer* self);

/*******************************************************************************
 * @brief Provides the activation function used for the dense layer.
 * 
 * @param self Pointer to the dense layer.
 * 
 * @return The activation function used for the dense layer as an enumerator
 *         of enum act_func.
 ******************************************************************************/
enum act_func dense_layer_act_func(const struct dense_layer* self);

/*******************************************************************************
 * @brief Provides the number of nodes in the dense layer.
 * 
 * @param self Pointer to the dense layer.
 * 
 * @return The number of nodes in the dense layer as an integer.
 ******************************************************************************/
size_t dense_layer_node_count(const struct dense_layer* self);

/*******************************************************************************
 * @brief Provides the number of weights per node in the dense layer.
 * 
 * @param self Pointer to the dense layer.
 * 
 * @return The number of weights per node in the dense layer as an integer.
 ******************************************************************************/
size_t dense_layer_weight_count(const struct dense_layer* self);

/*******************************************************************************
 * @brief Performs feedforward with given input.
 * 
 * @param self        Pointer to the dense layer.
 * @param input       Pointer to field holding input values.
 * @param input_count The number of input values.
 * 
 * @return True if feedforward was performed, false upon dimension mismatch
 *         between the input values and the weight count of the dense layer.
 ******************************************************************************/
bool dense_layer_feedforward(struct dense_layer* self, const double* input, 
                             const size_t input_count);

/*******************************************************************************
 * @brief Performs backpropagation for output layer with given reference values.
 * 
 * @param self            Pointer to the dense layer.
 * @param reference       Pointer to field holding reference values.
 * @param reference_count The number of reference values.
 * 
 * @return True if backpropagation was performed, false upon dimension mismatch
 *         between the reference values and the node count of the dense layer.
 * 
 * @note This function is intended to be used by output layers only!
 ******************************************************************************/
bool dense_layer_backpropagate_output(struct dense_layer* self, const double* reference,
                                      const size_t reference_count);

/*******************************************************************************
 * @brief Performs backpropagation for hidden layer with next connected layer.
 * 
 * @param self       Pointer to the dense layer.
 * @param next_layer Reference to the next connected layer 
 * 
 * @return True if backpropagation was performed, false upon dimension mismatch
 *         between the node count in this layer and the weight count in the
 *         next layer.
 * 
 * @note This function is intended to be used by output layers only!
 ******************************************************************************/
bool dense_layer_backpropagate_hidden(struct dense_layer* self,
                                      const struct dense_layer* next_layer);

/*******************************************************************************
 * @brief Performs optimization for dense layer.
 * 
 * @param self          Pointer to the dense layer.
 * @param input         Pointer to field holding input values.
 * @param input_count   The number of input values.
 * @param learning_rate The rate with which to optimize the parameters.
 * 
 * @return True if optimization was performed, false upon dimension mismatch
 *         between the input values and the weight count of the dense layer
 *         of if the learning rate is less or equal to 0.
 ******************************************************************************/
bool dense_layer_optimize(struct dense_layer* self, const double* input,
                          const size_t input_count, const double learning_rate);

/*******************************************************************************
 * @brief Prints dense layer parameters.
 * 
 * @param self    Pointer to the dense layer.
 * @param ostream Pointer to output stream to use (default = terminal print).
 ******************************************************************************/
void dense_layer_print(const struct dense_layer* self, FILE* ostream);

#ifdef __cplusplus__
}
#endif

#endif /* DENSE_LAYER_INCLUDED */