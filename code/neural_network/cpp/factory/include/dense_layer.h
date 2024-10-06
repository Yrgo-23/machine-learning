/*******************************************************************************
 * @brief Implementation of dense layers for neural networks.
 ******************************************************************************/
#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "act_func_calc.h"
#include "dense_layer_interface.h"

namespace ml
{

/*******************************************************************************
 * @brief Class implementation of dense layers.
 * 
 *        This class is non-copyable and non-movable.
 ******************************************************************************/
class DenseLayer : public DenseLayerInterface
{
public:

    /*******************************************************************************
     * @brief Creates new dense layer.
     *
     * @param nodeCount   The number of nodes in the new layer.
     * @param weightCount The number of weights per node in the new layer.
     * @param actFunc     The activation function of the layer (default = ReLU).
     ******************************************************************************/
    DenseLayer(const std::size_t nodeCount, const std::size_t weightCount, 
               const ActFunc actFunc = ActFunc::Relu);

    /*******************************************************************************
     * @brief Deletes dense layer.
     ******************************************************************************/
    ~DenseLayer() = default;

    /*******************************************************************************
     * @brief Provides the output of the dense layer.
     *
     * @return Reference to vector holding the output of the dense layer.
     ******************************************************************************/
    const std::vector<double>& output() const;

    /*******************************************************************************
     * @brief Provides the error of the dense layer.
     *
     * @return Reference to vector holding the error of the dense layer.
     ******************************************************************************/
    const std::vector<double>& error() const;

    /*******************************************************************************
     * @brief Provides the bias of the dense layer.
     *
     * @return Reference to vector holding the bias of the dense layer.
     ******************************************************************************/
    const std::vector<double>& bias() const;

    /*******************************************************************************
     * @brief Provides the weights of the dense layer.
     *
     * @return Reference to two-dimensional vector holding the weights of 
     *         the dense layer.
     ******************************************************************************/
    const std::vector<std::vector<double>>& weights() const;

    /*******************************************************************************
     * @brief Provides the activation function of the dense layer.
     * 
     * @return The activation function as an enumerator of enum ActFunc.
     ******************************************************************************/
    ActFunc actFunc() const;

    /*******************************************************************************
     * @brief Provides the number of nodes in the dense layer.
     * 
     * @return The number of nodes as an unsigned integer.
     ******************************************************************************/
    std::size_t nodeCount() const;

    /*******************************************************************************
     * @brief Provides the number of weights per node in the dense layer.
     * 
     * @return The number of weights per node as an unsigned integer.
     ******************************************************************************/
    std::size_t weightCount() const;
    
    /*******************************************************************************
     * @brief Performs feedforward for dense layer.
     * 
     * @param input Reference to vector holding the input of the dense layer.
     ******************************************************************************/
    void feedforward(const std::vector<double>& input);

    /*******************************************************************************
     * @brief Performs backpropagation for output layer.
     * 
     * @param reference Reference to vector holding reference values.
     * 
     * @note This method is implemented for output layers only.
     ******************************************************************************/
    void backpropagate(const std::vector<double>& reference);

    /*******************************************************************************
     * @brief Performs backpropagation for hidden layer.
     * 
     * @param nextLayer Reference to the next layer in the neural network.
     * 
     * @note This method is implemented for hidden layers only.
     ******************************************************************************/
    void backpropagate(const DenseLayerInterface& nextLayer);

    /*******************************************************************************
     * @brief Performs optimization for dense layer.
     * 
     * @param input        Reference to vector holding the input of the layer.
     * @param learningRate The rate with which to optimize the parameters.
     ******************************************************************************/
    void optimize(const std::vector<double>& input, const double learningRate = 0.01);

     /*******************************************************************************
     * @brief Prints stored parameters.
     * 
     * @param ostream      Reference to output stream (default = terminal print).
     * @param decimalCount The number of decimals for which to print floats
     *                     (default = 1).
     ******************************************************************************/
    void print(std::ostream& ostream = std::cout, 
               const std::size_t decimalCount = 1U) const;

    DenseLayer()                              = delete; // No default constructor.
    DenseLayer(const DenseLayer&)             = delete; // No copy constructor.
    DenseLayer(const DenseLayer&&)            = delete; // No move constructor.
    DenseLayer& operator=(const DenseLayer&)  = delete; // No copy assignment.
    DenseLayer& operator=(const DenseLayer&&) = delete; // No move assignment.

private:
    std::vector<double> myOutput;               // Output of each node.
    std::vector<double> myError;                // Calculated error of each node.
    std::vector<double> myBias;                 // Bias of each node.
    std::vector<std::vector<double>> myWeights; // Weights of each node.
    std::unique_ptr<ActFuncCalc> myActFuncCalc; // Activation function calculator.
};

} // namespace ml