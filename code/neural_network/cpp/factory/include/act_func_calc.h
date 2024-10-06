/*******************************************************************************
 * @brief Implementation of calculators for activation functions in
 *        neural networks.
 ******************************************************************************/
#pragma once

#include "act_func.h"

namespace ml
{

/*******************************************************************************
 * @brief Class implementation of activation function calculator.
 * 
 *        This class is non-copyable and non-movable.
 ******************************************************************************/
class ActFuncCalc
{
public:

    /*******************************************************************************
     * @brief Creates new activation function calculator.
     * 
     * @param actFunc The type of activation function to use for the calculations.
     ******************************************************************************/
    ActFuncCalc(const ActFunc actFunc);

    /*******************************************************************************
     * @brief Deletes activation function calculator.
     ******************************************************************************/
    ~ActFuncCalc() = default;

    /*******************************************************************************
     * @brief Provides the type of activation function used for the calculations.
     * 
     * @return The activation function used for the calculations represented as 
     *         an enum of enum class ActFun.
     ******************************************************************************/
    ActFunc actFunc() const;
    
    /*******************************************************************************
     * @brief Provides the activation function output for a given input.
     *
     * @param number The number for which to calculate the activation function 
     *               output.
     *
     * @return The activation function output as a double.
     ******************************************************************************/
    double output(const double number) const;

    /*******************************************************************************
     * @brief Provides the activation function gradient for a given input.
     *
     * @param number The number for which to calculate the activation 
     *               function gradient.
     *
     * @return The activation function gradient as a double.
     ******************************************************************************/
    double gradient(const double number) const;

    /*******************************************************************************
     * @brief Provides the name of the activation function used for the calculations
     *        as a string.
     * 
     * @return The name of the activation function used as a string.
     ******************************************************************************/
    const char* actFuncName() const;

    ActFuncCalc()                              = delete; // No default constructor.
    ActFuncCalc(const ActFuncCalc&)            = delete; // No copy constructor.
    ActFuncCalc(ActFuncCalc&&)                 = delete; // No move constructor.
    ActFuncCalc& operator=(const ActFuncCalc&) = delete; // No copy assignment.
    ActFuncCalc& operator=(ActFuncCalc&&)      = delete; // No move assignment.

private:
    ActFunc myActFunc; // Activation function used.
};

} // namespace ml
