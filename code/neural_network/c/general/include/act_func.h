/*******************************************************************************
 * @brief Implementation of activation functions for neural networks.
 ******************************************************************************/
#ifndef ACT_FUNC_INCLUDED
#define ACT_FUNC_INCLUDED

#ifdef __cplusplus__
extern "C" {
#endif

/*******************************************************************************
 * @brief Enum representing the different activation functions available for
 *        layers in neural networks.
 ******************************************************************************/
enum act_func
{
    ACT_FUNC_RELU, /* Rectified Linear Unit (ReLU). */
    ACT_FUNC_TANH  /* Hyperbolic tangent (tanh). */
};

/*******************************************************************************
 * @brief Provides the activation function output for a given input.
 *
 * @param number   The number for which to calculate the activation function 
 *                 output.
 * @param act_func The activation function used.
 *
 * @return The activation function output as a double.
 *         If an invalid activation function is specified, 0.0 is returned. 
 ******************************************************************************/
double act_func_output(const double number, const enum act_func act_func);

/*******************************************************************************
 * @brief Provides the activation function gradient for a given input.
 *
 * @param number   The number for which to calculate the activation 
 *                 function gradient.
 * @param act_func The activation function used.
 *
 * @return The activation function gradient as a double.
 *         If an invalid activation function is specified, 0.0 is returned. 
 ******************************************************************************/
double act_func_gradient(const double number, const enum act_func act_func);

/*******************************************************************************
 * @brief Provides the name of the activation function as a string.
 *
 * @param act_func The activation function enum value.
 * 
 * @return The name of the activation function as a string. If an invalid 
 *         activation function is specified, "Unknown" is returned.
 ******************************************************************************/
const char* act_func_string(const enum act_func act_func);

#ifdef __cplusplus__
}
#endif

#endif /* ACT_FUNC_INCLUDED */