/*******************************************************************************
 * @brief Implementation details of the ml::LinReg class.
 ******************************************************************************/
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <type_traits>

#include "lin_reg.h"

namespace 
{

// -----------------------------------------------------------------------------
void initRandomGenerator()
{
    static auto generatorInitialized{false};

    if (!generatorInitialized)
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        generatorInitialized = true;
    }
}

// -----------------------------------------------------------------------------
double getRandomStartVal()
{
    initRandomGenerator();
    return static_cast<double>(std::rand()) / RAND_MAX;
}

template <std::size_t exponent = 6U>
constexpr double roundToZero(const double value)
{
    static_assert(exponent > 0, "Cannot round to zero with exponent set to 0!");
    const auto threshold{1.0 / (10 * exponent)};
    return (value < threshold) && (value > -threshold) ? 0.0 : value;
}

} // namespace

namespace ml
{

// -----------------------------------------------------------------------------
LinReg::LinReg(const std::vector<double>& trainingInput, 
               const std::vector<double>& trainingOutput)
    : myTrainingOrder{}
    , myTrainingInput{trainingInput}
    , myTrainingOutput{trainingOutput}
    , myWeight{getRandomStartVal()}
    , myBias{getRandomStartVal()}
{
    if (trainingInput.size() != trainingOutput.size())
    {
        throw(std::invalid_argument("Mismatching training sets!\n"));
    }
    if (trainingInput.size() == 0U)
    {
        throw(std::invalid_argument(
            "Cannot create linear regression model without training data!"));
    }
    initTrainingOrder();
}

// -----------------------------------------------------------------------------
std::size_t LinReg::trainingSetCount() const { return myTrainingOrder.size(); }

// -----------------------------------------------------------------------------
double LinReg::predict(const double input) const
{
    return myWeight * input + myBias;
}

// -----------------------------------------------------------------------------
double LinReg::train(const std::size_t epochCount, const double learningRate)
{
    if (epochCount == 0U)
    {
        throw(std::invalid_argument("Epoch count must exceed 0!"));
    }
    if (learningRate <= 0)
    {
        throw(std::invalid_argument("Learning rate must exceed 0!"));
    }

    for (std::size_t i{}; i < epochCount; ++i)
    {
        randomizeTrainingOrder();

        for (const auto& j : myTrainingOrder)
        {
            optimize(myTrainingInput[j], myTrainingOutput[j], learningRate);
        }
    }
    return accuracy();
}

// -----------------------------------------------------------------------------
double LinReg::accuracy() const
{
    if (trainingSetCount() == 0U) 
    {
        throw(std::invalid_argument("Cannot calculate accuracy without training sets!"));
    }

    double errorSum{};
    for (std::size_t i{}; i < trainingSetCount(); ++i)
    {
        errorSum += myTrainingOutput[i] - predict(myTrainingInput[i]);
    }
    return 1.0 - errorSum / trainingSetCount();
}

// -----------------------------------------------------------------------------
void LinReg::printTrainingResult(std::ostream& ostream, const std::size_t decimalCount) const
{
    ostream << std::fixed << std::setprecision(decimalCount);
    ostream << "--------------------------------------------------------------------------------\n";
    ostream << "Accuracy: " << accuracy() * 100 << "%\n\n";

    for (std::size_t i{}; i < trainingSetCount(); ++i)
    {
        ostream << "Input: " << myTrainingInput[i] << "\t"
                << "Predicted output: " << predict(myTrainingInput[i]) << "\t"
                << "Reference output: " << myTrainingOutput[i] << "\t"
                << "Error: " << roundToZero(myTrainingOutput[i] - predict(myTrainingInput[i])) << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}

// -----------------------------------------------------------------------------
void LinReg::initTrainingOrder()
{
    myTrainingOrder.resize(myTrainingInput.size());
    
    for (std::size_t i{}; i < myTrainingOrder.size(); ++i) 
    {
        myTrainingOrder[i] = i;
    }
}

// -----------------------------------------------------------------------------
void LinReg::randomizeTrainingOrder()
{
    for (std::size_t i{}; i < trainingSetCount(); ++i)
    {
        const auto r{std::rand() % trainingSetCount()};
        const auto temp{myTrainingOrder[i]};
        myTrainingOrder[i] = myTrainingOrder[r];
        myTrainingOrder[r] = temp;
    }
}

// -----------------------------------------------------------------------------
void LinReg::optimize(const double input, const double reference, const double learningRate)
{
    if (input == 0) { myBias = reference; }
    else 
    {
        const auto error{reference - predict(input)};
        myBias += error * learningRate;
        myWeight += error * learningRate * input;
    }
}

} // namespace ml