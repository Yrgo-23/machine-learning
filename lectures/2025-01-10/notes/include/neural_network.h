/*******************************************************************************
 * @brief Neural network implementation.
 ******************************************************************************/
#pragma once

#include <iostream>
#include <vector>

#include "act_func.h"
#include "dense_layer.h"

namespace ml
{

/*******************************************************************************
 * @brief Class implementation of a neural network.
 * 
 *        This class is non-copyable and non-movable.
 ******************************************************************************/
class NeuralNetwork
{
public:

    /*******************************************************************************
     * @brief Creates a neural network.
     * 
     * @param inputCount    The number of inputs in the network.
     * @param hiddenCount   The number of hidden nodes in the network.
     * @param outputCount   The number of outputs in the network.
     * @param actFuncHidden Activation function of the hidden layer (default = ReLU).
     * @param actFuncOutput Activation function of the hidden layer (default = ReLU).
     ******************************************************************************/
    NeuralNetwork(const std::size_t inputCount,
                  const std::size_t hiddenCount,
                  const std::size_t outputCount,
                  const ActFunc actFuncHidden = ActFunc::Relu,
                  const ActFunc actFuncOutput = ActFunc::Relu);

    /*******************************************************************************
     * @brief Deletes neural network.
     ******************************************************************************/
    ~NeuralNetwork() = default;

    /*******************************************************************************
     * @brief Provides the number of input of the network.
     * 
     * @return The number of inputs of the network.
     ******************************************************************************/
    std::size_t inputCount() const;

    /*******************************************************************************
     * @brief Provides the number of outputs of the network.
     * 
     * @return The number of outputs of the network.
     ******************************************************************************/
    std::size_t outputCount() const;

    /*******************************************************************************
     * @brief Provides the number of stored training sets.
     * 
     * @return The number of stored training sets.
     ******************************************************************************/
    std::size_t trainingSetCount() const;

    /*******************************************************************************
     * @brief Trains the neural network with given parameters.
     * 
     * @param epochCount   The number of epochs for which to perform training.
     * @param learningRate The learning rate used for optimization (default = 1 %).
     * 
     * @return True if training was performed, otherwise false.
     ******************************************************************************/
    bool train(const std::size_t epochCount, const double learningRate = 0.01);

    /*******************************************************************************
     * @brief Performs prediction with given input.
     * 
     * @param input Reference to vector holding the input for which to predict.
     * 
     * @return Reference to vector holding the predicted output.
     ******************************************************************************/
    const std::vector<double>& predict(const std::vector<double>& input);

    /*******************************************************************************
     * @brief Adds training data.
     * 
     * @param input  Reference to vector holding the input sets.
     * @param output Reference to vector holding output sets.
     * 
     * @return True if at least one training set was added, otherwise false.
     ******************************************************************************/
    bool addTrainingData(const std::vector<std::vector<double>>& input,
                         const std::vector<std::vector<double>>& output);

    /*******************************************************************************
     * @brief Prints training result in the terminal.
     * 
     * @param printSource Reference to print source (default = terminal print).
     ******************************************************************************/
    void printResults(std::ostream& printSource = std::cout);

    NeuralNetwork()                                = delete; // No default constructor.
    NeuralNetwork(const NeuralNetwork&)            = delete; // No copy constructor.
    NeuralNetwork(NeuralNetwork&&)                 = delete; // No move constructor.
    NeuralNetwork& operator=(const NeuralNetwork&) = delete; // No copy assignment.
    NeuralNetwork& operator=(NeuralNetwork&&)      = delete; // No move assignment.

private:

    /*******************************************************************************
     * @brief Performs feedforward operation.
     * 
     * @param input Reference to the input used for the operation.
     ******************************************************************************/
    void feedforward(const std::vector<double>& input);

    /*******************************************************************************
     * @brief Performs backpropagation.
     * 
     * @param output Reference to the output containing reference values.
     ******************************************************************************/
    void backpropagate(const std::vector<double>& output);

    /*******************************************************************************
     * @brief Performs optimization.
     * 
     * @param input        Reference to the input used for the operation.
     * @param learningRate Learning rate to use for the optimization.
     ******************************************************************************/
    void optimize(const std::vector<double>& input, const double learningRate);

     DenseLayer myHiddenLayer;                          // The network's single hidden layer.
     DenseLayer myOutputLayer;                          // Output layer of the network.
     std::vector<std::vector<double>> myTrainingInput;  // Training input sets.
     std::vector<std::vector<double>> myTrainingOutput; // Training output sets.
};

} // namespace ml