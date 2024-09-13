/*******************************************************************************
 * @brief Implementation details of the ml::LinReg class.
 ******************************************************************************/
#include <stdexcept>

#include "lin_reg.h"


namespace ml
{

// -----------------------------------------------------------------------------
LinReg::LinReg(const std::vector<double>& trainingInput,
               const std::vector<double>& trainingOutput)
    : myTrainingInput{trainingInput}
    , myTrainingOutput{trainingOutput}
    , myBias{0.5} 
    , myWeight{0.5}
{
    if (myTrainingInput.size() != myTrainingOutput.size())
    {
        throw(std::invalid_argument(
            "Mismatch between training input and output!"));
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
        for (auto i{0U}; i < myTrainingInput.size(); ++i)
        {
            const auto& input{myTrainingInput[i]};
            const auto& reference{myTrainingOutput[i]};

            if (input == 0) { myBias = reference; }
            else
            {
                const auto prediction{myWeight * input + myBias}; 
                const auto error{reference - prediction};
                myBias   += error * learningRate; 
                myWeight += error * learningRate * input;
            }
        }
    }
}

// -----------------------------------------------------------------------------
double LinReg::predict(const double input) const
{
    return myWeight * input + myBias;
}

} // namespace ml