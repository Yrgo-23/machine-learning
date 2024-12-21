/*******************************************************************************
 * @brief Test script for a simple neural network implementation.
 ******************************************************************************/
#include <iostream>
#include <vector>

#include "neural_network.h"
#include "utils.h"

using namespace ml;

/*******************************************************************************
 * @brief Creates and initializes a neural network, which is trained to 
 *        detect a 2-bit XOR pattern. 
 *  
 *        The dense layer network consists of:
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
    // Defines network parameters and training sets.
    constexpr std::size_t epochCount{1000U};
    constexpr double learningRate{0.1};
    const std::vector<std::vector<double>> inputSets{{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    const std::vector<std::vector<double>> referenceSets{{0}, {1}, {1}, {0}};

    // Creates the neural network and adds training data.
    NeuralNetwork neuralNetwork{3U, 2U, 1U, ActFunc::Tanh};
    neuralNetwork.addTrainingData(inputSets, referenceSets);

    // Trains the neural network.
    neuralNetwork.train(epochCount, learningRate);

    // Prints the results in the terminal.
    for (const auto& input : inputSets)
    {
        std::cout << "Input: ";
        utils::vector::print(input, std::cout, ", ");
        std::cout << "output: ";
        utils::vector::print(neuralNetwork.predict(input));
    }
    return 0;
}