/*******************************************************************************
 * @brief Contains miscellaneous utility functions for generation of random
 *        numbers, initialization of vectors and mathematical operations.
 ******************************************************************************/
#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace utils 
{
namespace 
{

namespace random
{

/*******************************************************************************
 * @brief Generates a random number in the range of specified min and max values.
 * 
 * @tparam T The type of the random number to generate.
 * 
 * @param min The minimum permitted random number (default = 0).
 * @param max The maximum permitted random number (default = 100).
 * 
 * @return The generated random number.
 ******************************************************************************/
template <typename T>
T getNumber(const T min = 0, const T max = 100);

} // namespace random

namespace vector
{

/*******************************************************************************
 * @brief Initializes one-dimensional vector with random numbers.
 * 
 * @tparam T The vector type.
 * 
 * @param vector Reference to the vector to initialize.
 * @param size   The new size of the vector.
 * @param min    The minimum permitted random number (default = 0).
 * @param max    The maximum permitted random number (default = 100).
 ******************************************************************************/
template <typename T> 
void initRandom(std::vector<T>& vector, const std::size_t size, 
          const T min = 0, const T max = 100);

/*******************************************************************************
 * @brief Initializes two-dimensional vector with random numbers.
 * 
 * @tparam T The vector type.
 * 
 * @param vector      Reference to the vector to initialize.
 * @param columnCount The new number of columns of the vector.
 * @param rowCount    The new number of rows of the vector.
 * @param min         The minimum permitted random number (default = 0).
 * @param max         The maximum permitted random number (default = 100).
 ******************************************************************************/
template <typename T> 
void initRandom(std::vector<std::vector<T>>& vector, 
                const std::size_t columnCount, const std::size_t rowCount, 
                const T min = 0, const T max = 100);

/*******************************************************************************
 * @brief Shuffle the content of one-dimensional vector.
 * 
 * @tparam T The vector type.
 * 
 * @param vector Reference to the vector whose content will be shuffled.
 ******************************************************************************/
template <typename T>
void shuffle(std::vector<T>& vector);

/*******************************************************************************
 * @brief Shuffle the content of two-dimensional vector.
 * 
 * @tparam T The vector type.
 * 
 * @param vector Reference to the vector whose content will be shuffled.
 ******************************************************************************/
template <typename T>
void shuffle(std::vector<std::vector<T>>& vector);

/*******************************************************************************
 * @brief Prints content of one-dimensional vector.
 * 
 * @tparam T The vector type.
 * 
 * @note This function only works for arithmetic types and strings.
 * 
 * @param vector       Reference to the vector whose content will be printed.
 * @param ostream      Reference to output stream (default = terminal print).
 * @param end          Ending characters (default = new line).
 * @param decimalCount Number of decimals to print when using floating
 *                     point numbers (default = 1).
 ******************************************************************************/
template <typename T>
void print(const std::vector<T>& vector, std::ostream& ostream = std::cout, 
           const char* end = "\n", const std::size_t decimalCount = 1U);

/*******************************************************************************
 * @brief Prints content of two-dimensional vector.
 * 
 * @tparam T The vector type.
 * 
 * @note This function only works for arithmetic types and strings.
 * 
 * @param vector       Reference to the vector whose content will be printed.
 * @param ostream      Reference to output stream (default = terminal print).
 * @param end          Ending characters (default = new line).
 * @param decimalCount Number of decimals to print when using floating
 *                     point numbers (default = 1).
 ******************************************************************************/
template <typename T>
void print(const std::vector<std::vector<T>>& vector, 
           std::ostream& ostream = std::cout, const char* end = "\n",
           const std::size_t decimalCount = 1U);

} // namespace vector

namespace math 
{

/*******************************************************************************
 * @brief Provides the absolute value of number.
 * 
 * @tparam T       The type of the number.
 * 
 * @param numbers The number whose absolute value is to be calculated.
 * 
 * @return The absolute value of the number.
 ******************************************************************************/
template <typename T>
constexpr T absoluteValue(const T& number);

/*******************************************************************************
 * @brief Provides the sum of an arbitrary amount of numbers.
 * 
 * @tparam T       The type of the numbers.
 * @tparam Numbers Value type for parameter pack.
 * 
 * @param numbers Parameter pack holding numbers.
 * 
 * @return The sum of the numbers.
 ******************************************************************************/
template <typename T, typename... Numbers>
constexpr T add(const Numbers&... numbers);

/*******************************************************************************
 * @brief Provides the difference of an arbitrary amount of numbers.
 * 
 * @tparam T       The type of the numbers.
 * @tparam Numbers Value type for parameter pack.
 * 
 * @param numbers Parameter pack holding numbers.
 * 
 * @return The difference of the numbers.
 ******************************************************************************/
template <typename T, typename... Numbers>
constexpr T subtract(const Numbers&... numbers);

/*******************************************************************************
 * @brief Provides the product of an arbitrary amount of numbers.
 * 
 * @tparam T       The type of the numbers.
 * @tparam Numbers Value type for parameter pack.
 * 
 * @param numbers Parameter pack holding numbers.
 * 
 * @return The product of the numbers.
 ******************************************************************************/
template <typename T, typename... Numbers>
constexpr T multiply(const Numbers&... numbers);

/*******************************************************************************
 * @brief Provides the quotient of specified numbers.
 * 
 * @tparam T1 The type of the dividend.
 * @tparam T2 The type of the divisor.

 * @param dividend The dividend/numerator.
 * @param divisor  The divisor/denominator.
 * 
 * @return The quotient of the numbers or 0 if the divisor is 0.
 ******************************************************************************/
template <typename T1, typename T2>
constexpr double divide(const T1 dividend, const T2 divisor);

/*******************************************************************************
 * @brief Rounds floating-point number to the nearest integer.
 * 
 * @tparam T The integral type to round to (default = std::int32_t).
 * 
 * @param number The floating-point number to round.
 * 
 * @return The nearest integer.
 ******************************************************************************/
template <typename T = std::int32_t>
constexpr T round(const double number);

/*******************************************************************************
 * @brief Provides the Rectified Linear Unit (ReLU) activation for a 
 *        given input.
 * 
 * @param number The number for which to calculate the Relu.
 * 
 * @return The ReLU activation as a float.
 ******************************************************************************/
constexpr double relu(const double number);

/*******************************************************************************
 * @brief Provides the gradient of the Rectified Linear Unit (ReLU) function 
 *        for a given input.
 * 
 * @param number The number for which to calculate the ReLU gradient.
 * 
 * @return The ReLU gradient as a float.
 ******************************************************************************/
constexpr double reluGradient(const double number);

/*******************************************************************************
 * @brief Provides the hyperbolic tangent (tanh) for a given input.
 * 
 * @param number The number for which to calculate the hyperbolic tangent.
 * 
 * @return The hyperbolic tangent as a float.
 ******************************************************************************/
constexpr double tanh(const double number);

/*******************************************************************************
 * @brief Provides the gradient of the hyperbolic tangent (tanh) for a 
 *        given input.
 * 
 * @param number The number for which to calculate the gradient of the 
 *               hyperbolic tangent.
 * 
 * @return The gradient of the hyperbolic tangent as a float.
 ******************************************************************************/
constexpr double tanhGradient(const double number);

} // namespace math

namespace type_traits
{

/*******************************************************************************
 * @brief Indicates if specified type T is of string type.
 *
 * @tparam T The type to check.
 ******************************************************************************/
template<typename T>
struct is_string 
{
    static const bool value = false; // Value set to false for non-string types.
};

/*******************************************************************************
 * @brief Declares const char* a valid string type.
 ******************************************************************************/
template<>
struct is_string<const char *> 
{
    static const bool value = true;  // Value set to true for const char*.
};

/*******************************************************************************
 * @brief Declares char* a valid string type.
 ******************************************************************************/
template<>
struct is_string<char *> 
{
    static const bool value = true; // Value set to true for char*.
};

/*******************************************************************************
 * @brief Declares std::string a valid string type.
 ******************************************************************************/
template<>
struct is_string<std::string> 
{
    static const bool value = true; // Value set to true for std::string. 
};

} // namespace type_traits
} // namespace
} // namespace utils

#include "utils_impl.h"