/*******************************************************************************
 * @brief Implementation details of the ml::NeuralNetwork class.
 ******************************************************************************/
#include "neural_network.h"
#include "utils.h"

namespace ml
{

// -----------------------------------------------------------------------------
NeuralNetwork::NeuralNetwork(const std::size_t inputCount, 
                             const std::size_t hiddenCount,
                             const std::size_t outputCount,
                             const ActFunc actFuncHidden,
                             const ActFunc actFuncOutput)
    : myHiddenLayer{hiddenCount, inputCount, actFuncHidden}
    , myOutputLayer{outputCount, hiddenCount, actFuncOutput}
    , myTrainingInput{}
    , myTrainingOutput{} {}

// -----------------------------------------------------------------------------
std::size_t NeuralNetwork::inputCount() const noexcept
{
    // Input count = the weight count in the hidden layer.
    return myHiddenLayer.weightCount();
}

// -----------------------------------------------------------------------------
std::size_t NeuralNetwork::outputCount() const noexcept
{
    // Output count = the node count in the output layer.
    return myOutputLayer.nodeCount();
}

// -----------------------------------------------------------------------------
std::size_t NeuralNetwork::trainingSetCount() const noexcept
{
    // Training set count = the size of the input and output vectors.
    return myTrainingInput.size();
}

// -----------------------------------------------------------------------------
bool NeuralNetwork::train(const std::size_t epochCount, const double learningRate)
{
    // If the given parameters are invalid or training sets are missing, return false.
    if ((epochCount == 0U) || (learningRate <= 0.0) || myTrainingInput.empty())
    {
        return false;
    }

    // Train the network given number of epochs.
    for (std::size_t i{}; i < epochCount; ++i)
    {
        // Train the network with each set one by one.
        for (std::size_t j{}; j < trainingSetCount(); ++j)
        {
            feedforward(myTrainingInput[j]); 
            backpropagate(myTrainingOutput[j]);
            optimize(myTrainingInput[j], learningRate);
        }
    }
    // Indicate that training was performed successfully.
    return true;
}

// -----------------------------------------------------------------------------
const std::vector<double>& NeuralNetwork::predict(const std::vector<double>& input)
{
    // Update the outputs of the nodes in all layers.
    feedforward(input);

    // Return the output of the output layer.
    return myOutputLayer.output();
}

// -----------------------------------------------------------------------------
bool NeuralNetwork::addTrainingData(const std::vector<std::vector<double>>& input,
                                    const std::vector<std::vector<double>>& output)
{
    // Assign given data to our member variables.
    myTrainingInput  = input;
    myTrainingOutput = output;

    // If there is a mismatch between the input and output, remove the superfluous value.
    if (input.size() != output.size())
    {
        // Reduce the size of the larger vector to match the smaller one.
        const auto setCount{input.size() < output.size() ? input.size() : output.size()};
        myTrainingInput.resize(setCount);
        myTrainingOutput.resize(setCount);
    }
    // Return true if one or more training sets are stored.
    return trainingSetCount() > 0U;
}

// -----------------------------------------------------------------------------
void NeuralNetwork::printResults(std::ostream& printSource)
{
    // Iterate through or training sets one by one and print the predicted value.
    for (const auto& input : myTrainingInput)
    {
        printSource << "Input: ";
        utils::vector::print(input, printSource, ", ");
        printSource << "prediction: ";
        utils::vector::print(predict(input), printSource);
    }
}

// -----------------------------------------------------------------------------
void NeuralNetwork::feedforward(const std::vector<double>& input)
{
    // Perform feedforward for the hidden layer with given input.
    myHiddenLayer.feedforward(input);

    // Perform feedforward for the output layer, use the output of the hidden layer as input.
    myOutputLayer.feedforward(myHiddenLayer.output());
}

// -----------------------------------------------------------------------------
void NeuralNetwork::backpropagate(const std::vector<double>& output)
{
    // Perform backpropagation for the output layer with given output.
    myOutputLayer.backpropagate(output);

    // Perform backpropagation for the hidden layer, use values from the output layer.
    myHiddenLayer.backpropagate(myOutputLayer);
}

// -----------------------------------------------------------------------------
void NeuralNetwork::optimize(const std::vector<double>& input, const double learningRate)
{
    // Optimize the hidden layer with given input.
    myHiddenLayer.optimize(input, learningRate);

    // Optimize the output layer with the output of the hidden layer as input.
    myOutputLayer.optimize(myHiddenLayer.output(), learningRate);
}

} // namespace ml