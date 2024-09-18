/*******************************************************************************
 * @brief Implementation of neural networks.
 * 
 *        This file defines a neural network structure, which includes
 *        methods for adding training data, predicting outputs, training the 
 *        network, and calculating accuracy. 
 * 
 * @note Virtual tables are used as a design pattern to achieve polymorphism,
 *       allowing support of different networks types. This design facilitates
 *       easy integration of new neural network types in the future.
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
struct dense_layer;           /* Struct implementation of dense (fully-connected) layers. */
struct neural_network_impl;   /* Implementation details of struct neural_network. */
struct neural_network_vtable; /* Virtual table for struct neural network. */
struct vector;                /* Polymorphic one-dimensional vector. */ 
struct vector_2d;             /* Polymorphic two-dimensional vector. */

/*******************************************************************************
 * @brief Struct implementation of neural networks.
 ******************************************************************************/
struct neural_network
{
    const struct neural_network_vtable* vptr; /* Pointer to virtual table. */
    struct neural_network_impl* impl;         /* Pointer to implementation details. */
};

/********************************************************************************
 * @brief Virtual table containing function pointers for struct neural network.
 *******************************************************************************/
struct neural_network_vtable
{
    /*******************************************************************************
     * @brief Provides the number of inputs in the neural network.
     *  
     * @param self Pointer to the neural network.
     * 
     * @return The number of inputs as an integer.
     ******************************************************************************/
    size_t (*input_count)(const struct neural_network* self);

    /*******************************************************************************
     * @brief Provides the number of nodes in the network's hidden layer.
     *
     * @param self Pointer to the neural network.
     * 
     * @return The number of hidden nodes as an integer.
     ******************************************************************************/
    size_t (*hidden_nodes_count)(const struct neural_network* self);

    /*******************************************************************************
     * @brief Provides the number of outputs in the neural network.
     * 
     * @param self Pointer to the neural network.
     * 
     * @return The number of outputs as an integer.
     ******************************************************************************/
    size_t (*output_count)(const struct neural_network* self);

    /*******************************************************************************
     * @brief Provides the output of the neural network.
     * 
     * @param self Pointer to the neural network.
     * 
     * @return Pointer to vector holding the output of the network.
     ******************************************************************************/
    const struct vector* (*output)(const struct neural_network* self);

    /*******************************************************************************
     * @brief Provides the number of stored training sets.
     * 
     * @param self Pointer to the neural network.
     * 
     * @return The number of training sets as an integer.
     ******************************************************************************/
    size_t (*training_set_count)(const struct neural_network* self);
    
    /*******************************************************************************
     * @brief Performs prediction based on given input.
     * 
     * @param self  Pointer to the neural network.
     * @param input Pointer to vector holding the input on which to predict.
     * 
     * @return Pointer to vector holding the predicted output, or NULL if an
     *         error occurred (e.g., if the input dimensions do not match).
     ******************************************************************************/
    const struct vector* (*predict)(struct neural_network* self, 
                                    const struct vector* input);
    
    /*******************************************************************************
     * @brief Adds sets of training data to neural network.
     *
     * @param self            Pointer to the neural network.
     * @param training_input  Pointer to two-dimensional vector holding values of
     *                        the input sets.
     * @param training_output Pointer to two-dimensional vector holding values of 
     *                        the output sets.
     * 
     * @return True if the training sets were successfully added, else false.
     * 
     * @note The neural network takes ownership of the training data vectors.
     *       Consequently, the data will be deleted upon deletion of the neural
     *       network.
     ******************************************************************************/
    bool (*add_training_sets)(struct neural_network* self,
                              struct vector_2d** training_input,
                              struct vector_2d** training_output);

    /*******************************************************************************
     * @brief Trains the neural network.
     * 
     * @param self          Pointer to the neural network.
     * @param epoch_count   The number of epochs to perform training.
     * @param learning_rate The rate with witch to optimize the network parameters.
     *
     * @return The accuracy post training as a double in the range 0 - 1, which
     *         corresponds to 0 - 100 %, or -1 if an error occurred (e.g., if there 
     *          are no training sets available, or either the epoch count is 0 or 
     *          the learning rate is zero or below).
     ******************************************************************************/
    double (*train)(struct neural_network* self, const size_t epoch_count,
                    const double learning_rate);

    /*******************************************************************************
     * @brief Provides the accuracy of the network by using stored training data.
     * 
     * @param self Pointer to the neural network.
     * 
     * @return The accuracy as a double in the range 0 - 1, which corresponds 
     *          to 0 - 100 %.
     ******************************************************************************/
    double (*accuracy)(struct neural_network* self);

    /*******************************************************************************
     * @brief Prints training results.
     * 
     * @param self    Pointer to the neural network.
     * @param ostream Pointer to output stream (default = terminal print).
     * 
     * @note An error message will be printed if training data is missing!
     ******************************************************************************/
    void (*print_results)(const struct neural_network* self, FILE* ostream);
};

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
                                          const size_t hidden_nodes_count,
                                          const size_t output_count,
                                          const enum act_func act_func_hidden,
                                          const enum act_func act_func_output);

/*******************************************************************************
 * @brief Deletes neural network and frees all allocated memory.
 *
 * @param self Double pointer to the neural network to be deleted.
 ******************************************************************************/
void neural_network_delete(struct neural_network** self);

#ifdef __cplusplus__
}
#endif

#endif /* NEURAL_NETWORK_INCLUDED */