/*******************************************************************************
 * @brief Implementation of activation functions for neural networks.
 ******************************************************************************/
#pragma once

namespace ml
{

/*******************************************************************************
 * @brief Enum representing the different activation functions available for
 *        layers in neural networks.
 ******************************************************************************/
enum class ActFunc : unsigned
{
    Relu,  // Rectified Linear Unit (ReLU).
    Tanh,  // Hyperbolic tangent (tanh).
    Count, // The number of activation functions available.
};

/*******************************************************************************
 * @brief Provides the activation function output for a given input.
 *
 * @param actFunc The activation function to use for the calculation.
 * @param number  The number for which to calculate the activation function 
 *                output.
 *
 * @return The activation function output as a double.
 ******************************************************************************/
double actFuncOutput(const ActFunc actFunc, const double number);

/*******************************************************************************
 * @brief Provides the activation function gradient for a given input.
 *
 * @param actFunc The activation function to use for the calculation.
 * @param number The number for which to calculate the activation 
 *               function gradient.
 *
 * @return The activation function gradient as a double.
 ******************************************************************************/
double actFuncGradient(const ActFunc actFunc, const double number);

/*******************************************************************************
 * @brief Provides the name of a given activation function.
 * 
 * @param actFunc The activation function in question.
 * 
 * @return The name of the activation function used as a string.
 ******************************************************************************/
const char* actFuncName(const ActFunc actFunc);

} // namespace ml
