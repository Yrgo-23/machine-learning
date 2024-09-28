/*******************************************************************************
 * @brief Implementation details of activation function calculations.
 ******************************************************************************/
#include <math.h>

#include "act_func.h"

// -----------------------------------------------------------------------------
static inline double relu(const double number)
{
    return number > 0.0 ? number : 0.0; 
}

// -----------------------------------------------------------------------------
static inline double relu_gradient(const double number)
{
    return number > 0.0 ? 1.0 : 0.0;
}

// -----------------------------------------------------------------------------
static inline double tanh_gradient(const double number)
{
    return 1.0 - pow(tanh(number), 2.0);
}

// -----------------------------------------------------------------------------
double act_func_output(const double number, const enum act_func act_func)
{
    switch (act_func)
    {
        case ACT_FUNC_RELU:
            return relu(number);
        case ACT_FUNC_TANH:
            return tanh(number);
        default:
            return 0.0;
    }
}

// -----------------------------------------------------------------------------
double act_func_gradient(const double number, const enum act_func act_func)
{
    switch (act_func)
    {
        case ACT_FUNC_RELU:
            return relu_gradient(number);
        case ACT_FUNC_TANH:
            return tanh_gradient(number);
        default:
            return 0.0;
    }
}

// -----------------------------------------------------------------------------
const char* act_func_string(const enum act_func act_func)
{
    switch (act_func)
    {
        case ACT_FUNC_RELU:
            return "Rectified Linear Unit (ReLU)";
        case ACT_FUNC_TANH:
            return "Hyperbolic tangent (tanh)";
        default:
            return "Unknown";
    }
}
