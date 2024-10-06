/*******************************************************************************
 * @brief Implementation details of the ml::NeuralNetwork class.
 ******************************************************************************/
#include <iomanip>
#include <stdexcept>

#include "dense_layer.h"
#include "factory.h"
#include "neural_network.h"
#include "utils.h"

namespace
{

// -----------------------------------------------------------------------------
void checkTrainingSets(const std::vector<std::vector<double>>& trainingInput,
                       const std::vector<std::vector<double>>& trainingOutput)
{
    if (trainingInput.size() != trainingOutput.size())
    {
        throw(std::invalid_argument("Mismatching training sets!"));
    }
    if (trainingInput.empty())
    {
        throw(std::invalid_argument("Training sets missing!"));
    }
}

// -----------------------------------------------------------------------------
void checkTrainingParameters(const std::size_t epochCount, const double learningRate)
{
    if (epochCount == 0U)
    {
        throw(std::invalid_argument("Invalid epoch count 0!"));
    }
    if (learningRate <= 0)
    {
        throw(std::invalid_argument("Invalid learning rate <= 0!"));
    }
}

// -----------------------------------------------------------------------------
void checkVectorsMatching(const std::vector<double>& vec1, const std::vector<double>& vec2)
{
    if (vec1.size() != vec2.size())
    {
        throw(std::invalid_argument("Mismatching vectors!"));
    }
}
} // namespace

namespace ml
{

// -----------------------------------------------------------------------------
NeuralNetwork::NeuralNetwork(const std::size_t inputCount, 
                             const std::size_t hiddenNodesCount,
                             const std::size_t outputCount, 
                             const ActFunc actFuncHidden, 
                             const ActFunc actFuncOutput)
    : myHiddenLayer{factory::denseLayer(hiddenNodesCount, inputCount, actFuncHidden)} 
    , myOutputLayer{factory::denseLayer(outputCount, hiddenNodesCount, actFuncOutput)}
    , myTrainingOrder{}
    , myTrainingInput{nullptr}
    , myTrainingOutput{nullptr} {}

// -----------------------------------------------------------------------------
std::size_t NeuralNetwork::inputCount() const 
{ 
    return (*myHiddenLayer).weightCount(); 
}

// -----------------------------------------------------------------------------
std::size_t NeuralNetwork::hiddenNodesCount() const
{
    return (*myHiddenLayer).nodeCount();
}

// -----------------------------------------------------------------------------
std::size_t NeuralNetwork::outputCount() const
{
    return (*myOutputLayer).nodeCount();
}

// -----------------------------------------------------------------------------
const std::vector<double>& NeuralNetwork::output() const
{
    return (*myOutputLayer).output();
}

// -----------------------------------------------------------------------------
std::size_t NeuralNetwork::trainingSetCount() const
{
    return myTrainingOrder.size();
}

// -----------------------------------------------------------------------------
const std::vector<double>& NeuralNetwork::predict(const std::vector<double>& input)
{
    feedforward(input);
    return output();
}

// -----------------------------------------------------------------------------
void NeuralNetwork::addTrainingSets(const std::vector<std::vector<double>>& trainingInput,
                                    const std::vector<std::vector<double>>& trainingOutput)
{
    checkTrainingSets(trainingInput, trainingOutput);
    myTrainingInput  = &trainingInput;
    myTrainingOutput = &trainingOutput;
    initTrainingOrder();
}

// -----------------------------------------------------------------------------
double NeuralNetwork::train(const std::size_t epochCount, const double learningRate)
{
    checkTrainingParameters(epochCount, learningRate);

    for (std::size_t epoch{}; epoch < epochCount; ++epoch)
    {
        randomizeTrainingOrder();

        for (const auto& i : myTrainingOrder)
        {
            feedforward((*myTrainingInput)[i]);
            backpropagate((*myTrainingOutput)[i]);
            optimize((*myTrainingInput)[i], learningRate);
        }
    }
    return accuracy();
}

// -----------------------------------------------------------------------------
double NeuralNetwork::accuracy()
{
    if (trainingSetCount() == 0U) { return 0.0; }
    double sum{};

    for (std::size_t i{}; i < trainingSetCount(); ++i)
    {
        sum += averageError((*myTrainingInput)[i], (*myTrainingOutput)[i]);
    }
    return 1.0 - sum / trainingSetCount();
}

// -----------------------------------------------------------------------------
void NeuralNetwork::printResults(std::ostream& ostream, const std::size_t decimalCount)
{
    ostream << std::fixed << std::setprecision(decimalCount);
    ostream << "--------------------------------------------------------------------------------\n";
    ostream << "Prediction accuracy: " << accuracy() * 100 << "%\n";

    for (std::size_t i{}; i < trainingSetCount(); ++i)
    {
        ostream << "Input: "; 
        utils::vector::print((*myTrainingInput)[i], ostream, ", ", decimalCount);
        ostream << "prediction: ";
        utils::vector::print(predict((*myTrainingInput)[i]), ostream, ", ", decimalCount);
        ostream << "reference: ";
        utils::vector::print((*myTrainingOutput)[i], ostream, ", ", decimalCount);
        ostream << "error: " << averageError((*myTrainingInput)[i], (*myTrainingOutput)[i]) << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}

// -----------------------------------------------------------------------------
void NeuralNetwork::initTrainingOrder()
{
    myTrainingOrder.resize(myTrainingInput->size());

    for (std::size_t i{}; i < myTrainingOrder.size(); ++i) 
    { 
        myTrainingOrder[i] = i; 
    }
}

// -----------------------------------------------------------------------------
void NeuralNetwork::randomizeTrainingOrder()
{
    utils::vector::shuffle(myTrainingOrder);
}

// -----------------------------------------------------------------------------
void NeuralNetwork::feedforward(const std::vector<double>& input)
{
    (*myHiddenLayer).feedforward(input);
    (*myOutputLayer).feedforward((*myHiddenLayer).output());
}

// -----------------------------------------------------------------------------
void NeuralNetwork::backpropagate(const std::vector<double>& reference)
{
    (*myOutputLayer).backpropagate(reference);
    (*myHiddenLayer).backpropagate(*myOutputLayer);
}

// -----------------------------------------------------------------------------
void NeuralNetwork::optimize(const std::vector<double>& input, const double learningRate)
{
    (*myHiddenLayer).optimize(input, learningRate);
    (*myOutputLayer).optimize((*myHiddenLayer).output(), learningRate);
}

// -----------------------------------------------------------------------------
double NeuralNetwork::averageError(const std::vector<double>& input, 
                                   const std::vector<double>& reference)
{
    double sum{};
    const auto prediction{predict(input)};
    checkVectorsMatching(reference, prediction);

    for (std::size_t i{}; i < prediction.size(); ++i)
    {
        sum += utils::math::absoluteValue(reference[i] - prediction[i]);
    }
    return sum / input.size();
}

} // namespace ml