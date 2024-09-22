/********************************************************************************
 * @brief Implementation of a simple neural network in C.
 * 
 * @note Virtual tables have been used as a design pattern to achieve 
 *       polymorphism and encapsulation, which adds flexibility but also 
 *       complexity to the code structure.
 *******************************************************************************/
#include <stdio.h>

#include "neural_network.h"
#include "vector.h"
#include "vector_2d.h"

#define SET_COUNT          4U /* The number of training sets. */
#define INPUT_COUNT        2U /* The number of inputs in the neural network. */
#define HIDDEN_NODES_COUNT 3U /* The number of hidden nodes in the neural network. */
#define OUTPUT_COUNT       1U /* The number of outputs in the neural network. */

/*******************************************************************************
 * @brief Creates vector holding input sets for training of the neural network.
 * 
 * @param data Reference to two-dimensional array holding input sets.
 * 
 * @return Pointer to two-dimensional vector holding the input sets.
 ******************************************************************************/
static struct vector_2d* create_train_input_vector(const double data[SET_COUNT][INPUT_COUNT])
{
    struct vector_2d* self = vector_2d_new(0, SET_COUNT);
    if (!self) { return NULL; }
    struct vector** sets  = (self->vptr->data(self));

    for (size_t i = 0U; i < SET_COUNT; ++i)
    {
        sets[i] = vector_new(VECTOR_TYPE_DOUBLE, data[i], INPUT_COUNT);
    }
    return self;
}

/*******************************************************************************
 * @brief Creates vector holding output sets for training of the neural network.
 * 
 * @param data Reference to two-dimensional array holding output sets.
 * 
 * @return Pointer to two-dimensional vector holding the output sets.
 ******************************************************************************/
static struct vector_2d* create_train_output_vector(const double data[SET_COUNT][OUTPUT_COUNT])
{
    struct vector_2d* self = vector_2d_new(0, SET_COUNT);
    if (!self) { return NULL; }
    struct vector** sets  = (self->vptr->data(self));

    for (size_t i = 0U; i < SET_COUNT; ++i)
    {
        sets[i] = vector_new(VECTOR_TYPE_DOUBLE, data[i], OUTPUT_COUNT);
    }
    return self;
}

/*******************************************************************************
 * @brief Creates and initializes a small neural network, which is trained to 
 *        detect a 2-bit XOR pattern. 
 *  
 *        The network consists of:
 * 
 *        - An input layer with two nodes.
 * 
 *        - A hidden layer with three nodes, using the hyperbolic tangent (tanh) 
 *         as activation function.
 * 
 *         - An output layer with one node, using the ReLU (Rectified Linear Unit) 
 *           as activation function.
 *   
 *         Training is performed until the network's accuracy exceeds 99,99 %.
 *   
 *         The results post training are printed in the terminal upon completion.
 * 
 * @return Success code 0 upon termination of the program.
 ******************************************************************************/
int main(void)
{
    const double input_data[SET_COUNT][INPUT_COUNT]   = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    const double output_data[SET_COUNT][OUTPUT_COUNT] = {{0}, {1}, {1}, {0}};

    struct vector_2d* inputs       = create_train_input_vector(input_data);
    struct vector_2d* outputs      = create_train_output_vector(output_data);
    struct neural_network* network = neural_network_new(2, 3, 1, ACT_FUNC_TANH, ACT_FUNC_RELU);

    if (!inputs || !outputs || !network || 
        !network->vptr->add_training_sets(network, &inputs, &outputs)) 
    { 
        fprintf(stderr, "Failed to create neural network and/or training sets!\n"); 
        vector_2d_delete(&inputs);
        vector_2d_delete(&outputs);
        neural_network_delete(&network);
        return 1;
    }

    while (network->vptr->train(network, 1000U, 0.1) < 0.9999);
    network->vptr->print_results(network, 0);
    neural_network_delete(&network);
    return 0;
}