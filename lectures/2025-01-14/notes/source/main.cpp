/*******************************************************************************
 * @brief Demonstration of a dense layer network.
 ******************************************************************************/
#include <iostream>
#include <vector>

#include "neural_network.h"

using namespace ml;

/*******************************************************************************
 * @brief Creates and initializes neural network consisting of two inputs, 
 *        three hidden nodes and one output. The network is trained to detect 
 *        a 2-bit XOR pattern. 
 *  
 *        The neural network consists of:
 * 
 *        - A hidden layer with three nodes, using the hyperbolic tangent (tanh) 
 *         as activation function.
 * 
 *        - An output layer with one node, using the ReLU (Rectified Linear Unit) 
 *          as activation function.
 *  
 *        The network is trained during 1000 epochs with a 1 % learning rate.
 *        The results post training are printed in the terminal.      
 * 
 * @return Success code 0 upon termination of the program.
 ******************************************************************************/
int main()
{
    // Define network parameters and training sets.
    constexpr std::size_t epochCount{1000U};
    constexpr double learningRate{0.1};
    const std::vector<std::vector<double>> inputSets{{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    const std::vector<std::vector<double>> referenceSets{{0}, {1}, {1}, {0}};

    // Create a 2-3-1 neural network, use tanh as activation for the hidden layer.
    NeuralNetwork network{2U, 3U, 1U, ActFunc::Tanh};

    // Add the training data.
    network.addTrainingData(inputSets, referenceSets);

    // If the training went well, print the result in the terminal.
    if (network.train(epochCount, learningRate))
    {
        network.printResults();
    }
    // Else print an error message.
    else
    {
        std::cout << "Failed to train the network!\n";
    }


    return 0;
}
