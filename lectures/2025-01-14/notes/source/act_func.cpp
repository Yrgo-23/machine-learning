/*******************************************************************************
 * @brief Implementation details for activation function calculations.
 ******************************************************************************/
#include <stdexcept>

#include "act_func.h"
#include "utils.h"

namespace ml
{

// -----------------------------------------------------------------------------
double actFuncOutput(const ActFunc actFunc, const double number)
{
    switch (actFunc)
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
double actFuncGradient(const ActFunc actFunc, const double number)
{
    switch (actFunc)
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
const char* actFuncName(const ActFunc actFunc)
{
    switch (actFunc)
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