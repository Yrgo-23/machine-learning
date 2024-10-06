/*******************************************************************************
 * @brief Definition of interface for dense layers in neural networks.
 ******************************************************************************/
#pragma once

#include <vector>

namespace ml
{

/*******************************************************************************
 * @brief Interface for dense layers in neural networks.
 ******************************************************************************/
class DenseLayerInterface
{
public:

    /*******************************************************************************
     * @brief Deletes dense layer.
     ******************************************************************************/
    virtual ~DenseLayerInterface() = default;

    /*******************************************************************************
     * @brief Provides the output of the dense layer.
     *
     * @return Reference to vector holding the output of the dense layer.
     ******************************************************************************/
    virtual const std::vector<double>& output() const = 0;

    /*******************************************************************************
     * @brief Provides the error of the dense layer.
     *
     * @return Reference to vector holding the error of the dense layer.
     ******************************************************************************/
    virtual const std::vector<double>& error() const = 0;

    /*******************************************************************************
     * @brief Provides the bias of the dense layer.
     *
     * @return Reference to vector holding the bias of the dense layer.
     ******************************************************************************/
    virtual const std::vector<double>& bias() const = 0;

    /*******************************************************************************
     * @brief Provides the weights of the dense layer.
     *
     * @return Reference to two-dimensional vector holding the weights of 
     *         the dense layer.
     ******************************************************************************/
    virtual const std::vector<std::vector<double>>& weights() const = 0;

    /*******************************************************************************
     * @brief Provides the number of nodes in the dense layer.
     * 
     * @return The number of nodes as an unsigned integer.
     ******************************************************************************/
    virtual std::size_t nodeCount() const = 0;

    /*******************************************************************************
     * @brief Provides the number of weights per node in the dense layer.
     * 
     * @return The number of weights per node as an unsigned integer.
     ******************************************************************************/
    virtual std::size_t weightCount() const = 0;
    
    /*******************************************************************************
     * @brief Performs feedforward for dense layer.
     * 
     * @param input Reference to vector holding the input of the dense layer.
     ******************************************************************************/
    virtual void feedforward(const std::vector<double>& input) = 0;

    /*******************************************************************************
     * @brief Performs backpropagation for output layer.
     * 
     * @param reference Reference to vector holding reference values.
     * 
     * @note This method is implemented for output layers only.
     ******************************************************************************/
    virtual void backpropagate(const std::vector<double>& reference) = 0;

    /*******************************************************************************
     * @brief Performs backpropagation for hidden layer.
     * 
     * @param nextLayer Reference to the next layer in the neural network.
     * 
     * @note This method is implemented for hidden layers only.
     ******************************************************************************/
    virtual void backpropagate(const DenseLayerInterface& nextLayer) = 0;

    /*******************************************************************************
     * @brief Performs optimization for dense layer.
     * 
     * @param input        Reference to vector holding the input of the layer.
     * @param learningRate The rate with which to optimize the parameters.
     ******************************************************************************/
    virtual void optimize(const std::vector<double>& input, const double learningRate = 0.01) = 0;
};

} // namespace ml