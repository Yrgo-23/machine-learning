/*******************************************************************************
 * @brief Implementation details of the ml::LinReg class.
 ******************************************************************************/
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <stdexcept>

#include "lin_reg.h"

namespace 
{

// -----------------------------------------------------------------------------
void initRandomGenerator()
{
    static bool randomGeneratorInitialized{false};
    if (!randomGeneratorInitialized)
    {
        std::srand(std::time(nullptr));
        randomGeneratorInitialized = true;
    }
}
} // namespace 


namespace ml
{

// -----------------------------------------------------------------------------
LinReg::LinReg(const std::vector<double>& trainingInput,
               const std::vector<double>& trainingOutput)
    : myTrainingInput{trainingInput}
    , myTrainingOutput{trainingOutput}
    , myTrainingOrder{}
    , myBias{0.5} 
    , myWeight{0.5}
{
    initRandomGenerator();

    if (myTrainingInput.size() != myTrainingOutput.size())
    {
        throw(std::invalid_argument(
            "Mismatch between training input and output!"));
    }

    myTrainingOrder.resize(myTrainingInput.size());

    for (auto i{0U}; i < myTrainingOrder.size(); ++i)
    {
        myTrainingOrder[i] = i;
    }
}

// -----------------------------------------------------------------------------
const std::vector<double>& LinReg::trainingInput() const
{
    return myTrainingInput;
}

// -----------------------------------------------------------------------------
const std::vector<double>& LinReg::trainingOutput() const
{
    return myTrainingOutput;
}

// -----------------------------------------------------------------------------
void LinReg::train(const std::size_t epochCount, const double learningRate)
{
    if (epochCount == 0U)
    {
        throw(std::invalid_argument(
            "Cannot train model with epochCount = 0!"));
    }
    if (learningRate <= 0)
    {
        throw(std::invalid_argument(
            "Cannot train model with learning rate <= 0!"));
    }

    for (auto epoch{0U}; epoch < epochCount; ++epoch)
    {
        randomizeTrainingOrder();

        for (const auto& i : myTrainingOrder)
        {
            optimize(myTrainingInput[i], myTrainingOutput[i], learningRate);
        }
    }
}

// -----------------------------------------------------------------------------
double LinReg::predict(const double input) const
{
    return myWeight * input + myBias;
}

// -----------------------------------------------------------------------------
void LinReg::printPredictions(const std::vector<double>& inputs, 
                              std::ostream& ostream,
                              const std::size_t decimalCount)
{
    if (inputs.empty()) 
    {
        throw(std::invalid_argument("Cannot perform prediction without inputs!"));
    }
    
    ostream << std::fixed << std::setprecision(decimalCount);
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& input: inputs)
    {
        ostream << "Input: " << input << ", output: " << predict(input) << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}

// -----------------------------------------------------------------------------
void LinReg::optimize(const double input, const double reference, 
                      const double learningRate)
{
    if (input == 0) { myBias = reference; }
    else
    {
        const auto prediction{myWeight * input + myBias}; 
        const auto error{reference - prediction};
        myBias   += error * learningRate; 
        myWeight += error * learningRate * input;
    }
}

// -----------------------------------------------------------------------------
void LinReg::randomizeTrainingOrder()
{
    for (auto i{0U}; i < myTrainingOrder.size(); ++i)
    {
        const auto r{std::rand() % myTrainingOrder.size()};
        const auto temp{myTrainingOrder[i]}; 
        myTrainingOrder[i] = myTrainingOrder[r];
        myTrainingOrder[r] = temp;
    }
}

} // namespace ml