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

} // namespace ml
