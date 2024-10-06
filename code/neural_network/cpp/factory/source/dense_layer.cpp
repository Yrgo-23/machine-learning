/*******************************************************************************
 * @brief Implementation details of the ml::DenseLayer class.
 ******************************************************************************/
#include "act_func_calc.h"
#include "dense_layer.h"
#include "factory.h"
#include "utils.h"

namespace ml
{

// -----------------------------------------------------------------------------
DenseLayer::DenseLayer(const std::size_t nodeCount, const std::size_t weightCount,
                       const ActFunc actFunc)
    : myOutput{factory::parameterVector(nodeCount)}
    , myError{factory::parameterVector(nodeCount)}
    , myBias{factory::randomParameterVector(nodeCount)}
    , myWeights{factory::randomParameterVector(nodeCount, weightCount)}
    , myActFuncCalc{factory::actFuncCalc(actFunc)}
{
    if (nodeCount == 0U) 
    {
        throw std::invalid_argument("Cannot create dense layer without nodes!");
    }
    if (weightCount == 0U)
    {
        throw std::invalid_argument("Cannot create dense layer without weights!");
    }
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
ActFunc DenseLayer::actFunc() const { return (*myActFuncCalc).actFunc(); }

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
    if (input.size() != weightCount())
    {
        throw std::invalid_argument(
            "Feedforward input does not match the shape of the dense layer!");
    }

    for (std::size_t i{}; i < nodeCount(); ++i)
    {
        auto sum{myBias[i]};
        for (std::size_t j{}; j < weightCount(); ++j)
        {
            sum += input[j] * myWeights[i][j];
        }
        myOutput[i] = (*myActFuncCalc).output(sum);
    }
}

// -----------------------------------------------------------------------------
void DenseLayer::backpropagate(const std::vector<double>& reference)
{
    if (reference.size() != nodeCount())
    {
        throw std::invalid_argument(
            "Backpropagation reference does not match the shape of the dense layer!");
    }

    for (std::size_t i{}; i < nodeCount(); ++i)
    {
        const auto error{reference[i] - myOutput[i]};
        myError[i] = error * (*myActFuncCalc).gradient(myOutput[i]);
    }
}

// -----------------------------------------------------------------------------
void DenseLayer::backpropagate(const DenseLayerInterface& nextLayer)
{
    if (nextLayer.weightCount() != nodeCount())
    {
        throw std::invalid_argument(
            "The shape of the next layer does not match the current layer!");
    }

    for (std::size_t i{}; i < nodeCount(); ++i)
    {
        double error{};
        for (std::size_t j{}; j < nextLayer.nodeCount(); ++j)
        {
            error += nextLayer.error()[j] * nextLayer.weights()[j][i];
        }
        myError[i] = error * (*myActFuncCalc).gradient(myOutput[i]);
    }
}

// -----------------------------------------------------------------------------
void DenseLayer::optimize(const std::vector<double>& input, const double learningRate)
{
    if (input.size() != weightCount())
    {
        throw std::invalid_argument(
            "Optimization input does not match the shape of the dense layer!");
    }
    if (learningRate <= 0.0)
    {
        throw std::invalid_argument("The learning rate must exceed 0!");
    }

    for (std::size_t i{}; i < nodeCount(); ++i)
    {
        myBias[i] += myError[i] * learningRate;
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
    ostream << "Activation function:\t" << (*myActFuncCalc).actFuncName() << "\n";
    ostream << "--------------------------------------------------------------------------------\n\n";
}

} // namespace ml