/*******************************************************************************
 * @brief Implementation of neural networks.
 ******************************************************************************/
#pragma once

#include <iostream>
#include <vector>

#include "dense_layer.h"

namespace ml
{

/*******************************************************************************
 * @brief Class implementation of neural networks with a single hidden layer.
 * 
 *        This class is non-copyable and non-movable.
 ******************************************************************************/
class NeuralNetwork
{
public:

    /*******************************************************************************
     * @brief Creates new neural network.
     * 
     * @param inputCount       The number of inputs in the neural network.
     * @param hiddenNodesCount The number of nodes in in the network's single 
     *                         hidden layer.
     * @param outputCount      The number of output in the neural network.
     * @param actFuncHidden    Activation function of the hidden layer 
     *                         (default = ReLU).
     * @param actFuncOutput    Activation function of the output layer 
     *                         (default = ReLU).
     ******************************************************************************/
    NeuralNetwork(const std::size_t inputCount, 
                  const std::size_t hiddenNodesCount,
                  const std::size_t outputCount, 
                  const ActFunc actFuncHidden = ActFunc::Relu, 
                  const ActFunc actFuncOutput = ActFunc::Relu);

    /*******************************************************************************
     * @brief Deletes neural network.
     ******************************************************************************/
    ~NeuralNetwork() = default;

    /*******************************************************************************
     * @brief Provides the number of inputs in the neural network.
     *  
     * @return The number of inputs as an integer.
     ******************************************************************************/
    std::size_t inputCount() const;

    /*******************************************************************************
     * @brief Provides the number of nodes in the network's hidden layer.
     *
     * @return The number of hidden nodes as an integer.
     ******************************************************************************/
    std::size_t hiddenNodesCount() const;

    /*******************************************************************************
     * @brief Provides the number of outputs in the neural network.
     * 
     * @return The number of outputs as an integer.
     ******************************************************************************/
    std::size_t outputCount() const;

    /*******************************************************************************
     * @brief Provides the output of the neural network.
     * 
     * @return Reference to vector holding the output of the network.
     ******************************************************************************/
    const std::vector<double>& output() const;

    /*******************************************************************************
     * @brief Provides the number of stored training sets.
     * 
     * @return The number of training sets as an integer.
     ******************************************************************************/
    std::size_t trainingSetCount() const;

    /*******************************************************************************
     * @brief Performs prediction based on given input.
     * 
     * @param input Reference to vector holding the input on which to predict.
     * 
     * @return Reference to vector holding the predicted output.
     ******************************************************************************/
    const std::vector<double>& predict(const std::vector<double>& input);

    /*******************************************************************************
     * @brief Adds sets of training data. 
     *
     * @param trainingInput  Reference to vector holding values of the input sets.
     * @param trainingOutput Reference to vector holding values of the output sets.
     ******************************************************************************/
    void addTrainingSets(const std::vector<std::vector<double>>& trainingInput,
                         const std::vector<std::vector<double>>& trainingOutput);

    /*******************************************************************************
     * @brief Trains the neural network.
     *
     * @param epochCount   The number of epochs to perform training.
     * @param learningRate The rate with witch to optimize the network parameters 
     *                     (default = 0.01).
     *
     * @return The accuracy post training as a double in the range 0 - 1, which
     *         corresponds to 0 - 100 %.
     ******************************************************************************/
    double train(const std::size_t epochCount, const double learningRate = 0.01);

    /*******************************************************************************
     * @brief Provides the accuracy of the network by using stored training data.
     * 
     * @return The accuracy as a double in the range 0 - 1, which corresponds 
     *          to 0 - 100 %.
     ******************************************************************************/
    double accuracy();

    /*******************************************************************************
     * @brief Prints training results.
     * 
     * @param ostream      Reference to output stream (default = terminal print).
     * @param decimalCount The number of decimals for which to print floats
     *                     (default = 1).
     ******************************************************************************/
    void printResults(std::ostream& ostream = std::cout, const std::size_t decimalCount = 1U);

    NeuralNetwork()                                = delete; // No default constructor.
    NeuralNetwork(const NeuralNetwork&)            = delete; // No copy constructor.
    NeuralNetwork(NeuralNetwork&&)                 = delete; // No move constructor.
    NeuralNetwork& operator=(const NeuralNetwork&) = delete; // No copy assignment.
    NeuralNetwork& operator=(NeuralNetwork&&)      = delete; // No move assignment.

private:

    /*******************************************************************************
     * @brief Initializes the training order after adding training sets.
     ******************************************************************************/
    void initTrainingOrder();

    /*******************************************************************************
     * @brief Randomizes the order of the training sets for next epoch.
     ******************************************************************************/
    void randomizeTrainingOrder();

    /*******************************************************************************
     * @brief Performs feedforward to calculate new output for each node.
     *   
     * @param input Reference to vector holding the network's current input.
     ******************************************************************************/
    void feedforward(const std::vector<double>& input);

    /*******************************************************************************
     * @brief Performs backpropagation to calculate new error for each node.
     * 
     * @param reference Reference to vector holding the network's current 
     *                  reference values.
     ******************************************************************************/
    void backpropagate(const std::vector<double>& reference);

    /*******************************************************************************
     * @brief Performs optimization by adjusting the network's parameters.
        
     * @param input        Reference to vector holding the network's current input.
     * @param learningRate The rate to adjust the network's parameters.
     ******************************************************************************/
    void optimize(const std::vector<double>& input, const double learningRate);

    /*******************************************************************************
     * @brief Calculates the average error for given training set.
     *
     * @param input     Reference to vector holding training set input.
     * @param reference Reference to vector holding training set output.
     * 
     * @return The average error of given training set as a double.
     ******************************************************************************/
    double averageError(const std::vector<double>& input, const std::vector<double>& reference);

    DenseLayer myHiddenLayer;                          // Hidden layer of the neural network.
    DenseLayer myOutputLayer;                          // Output layer of the neural network.
    std::vector<std::vector<double>> myTrainingInput;  // Training input values.
    std::vector<std::vector<double>> myTrainingOutput; // Training output values.
    std::vector<std::size_t> myTrainingOrder;          // Training order via set index.
};

} // namespace ml