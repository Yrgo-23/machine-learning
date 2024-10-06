/*******************************************************************************
 * @brief Implementation details of class ml::ActFuncCalc.
 ******************************************************************************/
#include <stdexcept>

#include "act_func_calc.h"
#include "utils.h"

namespace ml
{

// -----------------------------------------------------------------------------
ActFuncCalc::ActFuncCalc(const ActFunc actFunc)
    : myActFunc{actFunc}
{
    if (actFunc >= ActFunc::Count)
    {
        throw std::invalid_argument("Invalid activation function!\n");
    }
}

// -----------------------------------------------------------------------------
ActFunc ActFuncCalc::actFunc() const { return myActFunc; }

// -----------------------------------------------------------------------------
double ActFuncCalc::output(const double number) const
{
    switch (myActFunc)
    {
        case ActFunc::Relu:
            return utils::math::relu(number);
        case ActFunc::Tanh:
            return utils::math::tanh(number);
        default:
            throw std::invalid_argument("Invalid activation function!\n");       
    }
}

// -----------------------------------------------------------------------------
double ActFuncCalc::gradient(const double number) const
{
    switch (myActFunc)
    {
        case ActFunc::Relu:
            return utils::math::reluGradient(number);
        case ActFunc::Tanh:
            return utils::math::tanhGradient(number);
        default:
            throw std::invalid_argument("Invalid activation function!\n");       
    }
}

// -----------------------------------------------------------------------------
const char* ActFuncCalc::actFuncName() const
{
    switch (myActFunc)
    {
        case ActFunc::Relu:
            return "Rectified Linear Unit (ReLU)";
        case ActFunc::Tanh:
            return "Hyperbolic tangent (tanh)";
        default:
            throw std::invalid_argument("Invalid activation function!\n");       
    }
}

} // namespace ml