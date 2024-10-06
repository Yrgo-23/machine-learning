/*******************************************************************************
 * @brief Implementation of neural networks.
 * 
 *        This file defines a neural network structure, which includes
 *        methods for adding training data, predicting outputs, training the 
 *        network, and calculating accuracy. 
 ******************************************************************************/
#ifndef NEURAL_NETWORK_INCLUDED
#define NEURAL_NETWORK_INCLUDED

#ifdef __cplusplus__
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>

#include "act_func.h"

/*******************************************************************************
 * @brief Forward declarations.
 ******************************************************************************/
struct dense_layer;    /* Dense layer structure for neural networks. */
struct neural_network; /* Neural network structure. */

/*******************************************************************************
 * @brief Creates new neural network.
 * 
 * @param input_count        The number of inputs in the neural network.
 * @param hidden_nodes_count The number of nodes in in the network's single 
 *                           hidden layer.
 * @param output_count       The number of output in the neural network.
 * @param act_func_hidden    Activation function of the hidden layer 
 *                           (default = ReLU).
 * @param act_func_output    Activation function of the output layer 
 *                           (default = ReLU).
 * 
 * @return Pointer to the new neural network upon successful creation, 
 *         otherwise NULL.
 ******************************************************************************/
struct neural_network* neural_network_new(const size_t input_count, 
                                          const size_t hidden_count,
                                          const size_t output_count, 
                                          const enum act_func act_func_hidden,
                                          const enum act_func act_func_output);

/*******************************************************************************
 * @brief Deletes neural network and frees all allocated memory.
 *
 * @param self Double pointer to the neural network to be deleted.
 ******************************************************************************/
void neural_network_delete(struct neural_network** self);

/*******************************************************************************
 * @brief Provides the number of inputs in the neural network.
 *  
 * @param self Pointer to the neural network.
 * 
 * @return The number of inputs as an integer.
 ******************************************************************************/
size_t neural_network_input_count(const struct neural_network* self);

/*******************************************************************************
 * @brief Provides the number of nodes in the network's hidden layer.
 *
 * @param self Pointer to the neural network.
 * 
 * @return The number of hidden nodes as an integer.
 ******************************************************************************/
size_t neural_network_hidden_nodes_count(const struct neural_network* self);

/*******************************************************************************
 * @brief Provides the number of outputs in the neural network.
 * 
 * @param self Pointer to the neural network.
 * 
 * @return The number of outputs as an integer.
 ******************************************************************************/
size_t neural_network_output_count(const struct neural_network* self);

/*******************************************************************************
 * @brief Provides the output of the neural network.
 * 
 * @param self Pointer to the neural network.
 * 
 * @return Pointer to field holding the output of the network.
 ******************************************************************************/
const double* neural_network_output(const struct neural_network* self);

/*******************************************************************************
 * @brief Provides the number of stored training sets.
 * 
 * @param self Pointer to the neural network.
 * 
 * @return The number of training sets as an integer.
 ******************************************************************************/
size_t neural_network_training_set_count(const struct neural_network* self);

/*******************************************************************************
 * @brief Performs prediction based on given input.
 * 
 * @param self        Pointer to the neural network.
 * @param input       Pointer to field holding the input on which to predict.
 * @param input_count The number of input values.
 * 
 * @return Pointer to field holding the predicted output, or NULL if an
 *         error occurred (e.g., if the input dimensions do not match).
 ******************************************************************************/
const double* neural_network_predict(struct neural_network* self, const double* input,
                                     const size_t input_count);

/*******************************************************************************
 * @brief Adds sets of training data to neural network.
 *
 * @param self      Pointer to the neural network.
 * @param input     Pointer to two-dimensional field holding values 
 *                  of the input sets.
 * @param output    Pointer to two-dimensional field holding values 
 *                  of the output sets.
 * @param set_count The number of training sets.
 * 
 * @return True if the training sets were successfully added, else false.
 * 
 * @note The neural network takes ownership of the training data vectors.
 *       Consequently, the data will be deleted upon deletion of the neural
 *       network.
 ******************************************************************************/
bool neural_network_add_training_sets(struct neural_network* self, double** input,
                                      double** output, const size_t set_count);

/*******************************************************************************
 * @brief Trains the neural network.
 * 
 * @param self          Pointer to the neural network.
 * @param epoch_count   The number of epochs to perform training.
 * @param learning_rate The rate with witch to optimize the network parameters.
 *
 * @return The accuracy post training as a double in the range 0 - 1, which
 *         corresponds to 0 - 100 %, or -1 if an error occurred (e.g., if there 
 *         are no training sets available, or either the epoch count is 0 or 
 *         the learning rate is zero or below).
 ******************************************************************************/
double neural_network_train(struct neural_network* self, const size_t epoch_count,
                            const double learning_rate);

/*******************************************************************************
 * @brief Provides the accuracy of the network by using stored training data.
 * 
 * @param self Pointer to the neural network.
 * 
 * @return The accuracy as a double in the range 0 - 1, which corresponds 
 *          to 0 - 100 %.
 ******************************************************************************/
double neural_network_accuracy(struct neural_network* self);

/*******************************************************************************
 * @brief Prints training results.
 * 
 * @param self    Pointer to the neural network.
 * @param ostream Pointer to output stream (default = terminal print).
 * 
 * @note An error message will be printed if training data is missing!
 ******************************************************************************/
void neural_network_print_results(struct neural_network* self, FILE* ostream);

#ifdef __cplusplus
}
#endif

#endif /* NEURAL_NETWORK_INCLUDED */