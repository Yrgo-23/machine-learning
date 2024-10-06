/*******************************************************************************
 * @brief Demonstration of a simple neural network using the factory design
 *        pattern.
 ******************************************************************************/
#include <memory>
#include <vector>

#include "factory.h"

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
int main()
{
    const std::vector<std::vector<double>> trainingInput{{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    const std::vector<std::vector<double>> trainingOutput{{0}, {1}, {1}, {0}};
    auto network{ml::factory::neuralNetwork(2, 3, 1, ml::ActFunc::Relu)};
    (*network).addTrainingSets(trainingInput, trainingOutput);
    while ((*network).train(1000) <= 0.9999);
    (*network).printResults();
    return 0;
}