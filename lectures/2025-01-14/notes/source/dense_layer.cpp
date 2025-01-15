/*******************************************************************************
 * @brief Implementation details of the ml::DenseLayer class.
 ******************************************************************************/
#include "dense_layer.h"
#include "utils.h"

namespace ml
{

// -----------------------------------------------------------------------------
DenseLayer::DenseLayer(const std::size_t nodeCount, const std::size_t weightCount,
                       const ActFunc actFunc)
    : myOutput(nodeCount, 0.0)
    , myError(nodeCount, 0.0)
    , myBias{}
    , myWeights{}
    , myActFunc{actFunc}
{
    // Throw an exception if any parameter is invalid.
    if (nodeCount == 0U) 
    {
        throw std::invalid_argument("Cannot create dense layer without nodes!");
    }
    if (weightCount == 0U)
    {
        throw std::invalid_argument("Cannot create dense layer without weights!");
    }
    if (actFunc >= ActFunc::Count)
    {
        throw std::invalid_argument("Invalid activation function!");
    }

    // Initialize node biases and weights with random values between 0.0 - 1.0
    utils::vector::initRandom<double>(myBias, nodeCount, 0.0, 1.0);
    utils::vector::initRandom<double>(myWeights, nodeCount, weightCount, 0.0, 1.0);
}

// -----------------------------------------------------------------------------
const std::vector<double>& DenseLayer::output() const { return myOutput; }

// -----------------------------------------------------------------------------
const std::vector<double>& DenseLayer::error() const { return myError; }

// -----------------------------------------------------------------------------
const std::vector<double>& DenseLayer::bias() const { return myBias; }

// -----------------------------------------------------------------------------
const std::vector<std::vector<double>>& DenseLayer::weights() const { return myWeights; }

// -----------------------------------------------------------------------------
ActFunc DenseLayer::actFunc() const { return myActFunc; }

// -----------------------------------------------------------------------------
std::size_t DenseLayer::nodeCount() const { return myOutput.size(); }

// -----------------------------------------------------------------------------
std::size_t DenseLayer::weightCount() const 
{ 
    return myWeights.size() > 0U ? myWeights[0U].size() : 0U; 
}

// -----------------------------------------------------------------------------
void DenseLayer::feedforward(const std::vector<double>& input)
{
    // Throw an exception on mismatch between the input and the shape of the dense layer.
    if (input.size() != weightCount())
    {
        throw std::invalid_argument(
            "Feedforward input does not match the shape of the dense layer!");
    }

    // Calculate new output for each node.
    for (std::size_t i{}; i < nodeCount(); ++i)
    {
        auto sum{myBias[i]};

        // Accumulate the node bias value and the contribution from each input.
        for (std::size_t j{}; j < weightCount(); ++j)
        {
            sum += input[j] * myWeights[i][j];
        }

        // Pass accumulated value through the activation function filter.
        myOutput[i] = actFuncOutput(myActFunc, sum);
    }
}

// -----------------------------------------------------------------------------
void DenseLayer::backpropagate(const std::vector<double>& reference)
{
    // Throw an exception on mismatch between the reference and the shape of the dense layer.
    if (reference.size() != nodeCount())
    {
        throw std::invalid_argument(
            "Backpropagation reference does not match the shape of the dense layer!");
    }

    // Calculate the error for each node.
    for (std::size_t i{}; i < nodeCount(); ++i)
    {
        // Calculate the error by comparing the reference and predicted values.
        const auto error{reference[i] - myOutput[i]};

        // Pass calculated error value through the activation function filter.
        myError[i] = error * actFuncGradient(myActFunc, myOutput[i]);
    }
}

// -----------------------------------------------------------------------------
void DenseLayer::backpropagate(const DenseLayer& nextLayer)
{
    // Throw an exception on mismatch between the shapes of the dense layers.
    if (nextLayer.weightCount() != nodeCount())
    {
        throw std::invalid_argument(
            "The shape of the next layer does not match the current layer!");
    }

    // Calculate the error for each node.
    for (std::size_t i{}; i < nodeCount(); ++i)
    {
        double error{};

        // Accumulate the error by using weights and error values of next layer.
        for (std::size_t j{}; j < nextLayer.nodeCount(); ++j)
        {
            error += nextLayer.error()[j] * nextLayer.weights()[j][i];
        }

        // Pass calculated error value through the activation function filter.
        myError[i] = error * actFuncGradient(myActFunc, myOutput[i]);
    }
}

// -----------------------------------------------------------------------------
void DenseLayer::optimize(const std::vector<double>& input, const double learningRate)
{
    // Throw an exception on mismatch between the input and the shape of the dense layer.
    if (input.size() != weightCount())
    {
        throw std::invalid_argument(
            "Optimization input does not match the shape of the dense layer!");
    }

    // Throw an exception if the learning rate is invalid.
    if (learningRate <= 0.0)
    {
        throw std::invalid_argument("The learning rate must exceed 0!");
    }

    // Update the bias and weights for each node.
    for (std::size_t i{}; i < nodeCount(); ++i)
    {
        // Update the bias by using calculated error value and the learning rate.
        myBias[i] += myError[i] * learningRate;

        // Update each weight by using calculated error, the learning rate and the associated input.
        for (std::size_t j{}; j < weightCount(); ++j)
        {
            myWeights[i][j] += myError[i] * learningRate * input[j];
        }
    }
}

// -----------------------------------------------------------------------------
void DenseLayer::print(std::ostream& ostream, const std::size_t decimalCount) const
{
    ostream << "--------------------------------------------------------------------------------\n";
    ostream << "Output:\t\t\t";
    utils::vector::print(myOutput, ostream, "\n", decimalCount);
    ostream << "Error:\t\t\t";
    utils::vector::print(myError, ostream, "\n", decimalCount);
    ostream << "Bias:\t\t\t";
    utils::vector::print(myBias, ostream, "\n", decimalCount);
    ostream << "Weights:\t\t";
    utils::vector::print(myWeights, ostream, "\n", decimalCount);
    ostream << "Activation function:\t" << actFuncName(myActFunc) << "\n";
    ostream << "--------------------------------------------------------------------------------\n\n";
}

} // namespace ml