/********************************************************************************
 * @brief Utility functions for convolutional layers.
 ********************************************************************************/
#pragma once

#include <iostream>
#include <iomanip>
#include <type_traits>
#include <vector>

namespace ml
{
namespace utils
{

/********************************************************************************
 * @brief Enables function if specified type is an integral type.
 * 
 * @tparam T The specified type used for the function (default = int).
 * @tparam R The return type of the function (default = void).
 ********************************************************************************/
template <typename T = int, typename R = void>
using enable_if_integral = typename std::enable_if<std::is_integral<T>::value, R>::type;

/********************************************************************************
 * @brief Enables function if specified type is a floating-point type.
 * 
 * @tparam T The specified type used for the function (default = double).
 * @tparam R The return type of the function (default = void).
 ********************************************************************************/
template <typename T = double, typename R = void>
using enable_if_float = typename std::enable_if<std::is_floating_point<T>::value, R>::type;

namespace 
{

/********************************************************************************
 * @brief Returns the number of paddings to add to each size of an image to keep
 *        the image size unchanged when filtering via a convolutional layer.
 * 
 * @param kernelSize The size of the convolutional layer's kernel.
 * 
 * @return The number of paddings to add to each size of the image.
 ********************************************************************************/
constexpr std::size_t paddingCount(const std::size_t kernelSize) noexcept;

/********************************************************************************
 * @brief Returns the number of paddings to add to each size of an image to keep
 *        the image size unchanged when filtering via a convolutional layer.
 * 
 * @tparam T The type of the values stored in the kernel (must be arithmetic).
 * 
 * @param kernel Reference to the convolutional layer's kernel.
 * 
 * @return The number of paddings to add to each size of the image.
 ********************************************************************************/
template <typename T>
std::size_t paddingCount(const std::vector<T>& kernel) noexcept;

/********************************************************************************
 * @brief Returns the number of paddings to add to each size of an image to keep
 *        the image size unchanged when filtering via a convolutional layer.
 * 
 * @tparam T The type of the values stored in the kernel (must be arithmetic).
 * 
 * @param kernel Reference to the convolutional layer's kernel.
 * 
 * @return The number of paddings to add to each size of the image.
 ********************************************************************************/
template <typename T>
std::size_t paddingCount(const std::vector<std::vector<T>>& kernel) noexcept;

/********************************************************************************
 * @brief Provides a padded copy of referenced vector.
 * 
 * @tparam T The vector type (must be arithmetic).
 * 
 * @param data        Reference to the vector to copy.
 * @param paddingCount The number of paddings to add to each side of the copy.
 * @param padValue    The value to pad the copy with (default = 0).
 * 
 * @return The padded copy.
 ********************************************************************************/
template <typename T>
std::vector<T> pad(const std::vector<T>& data, const std::size_t paddingCount = 1,
                   const T padValue = 0) noexcept;

/********************************************************************************
 * @brief Provides a padded copy of referenced vector.
 * 
 * @tparam T The vector type (must be arithmetic).
 * 
 * @param data     Reference to the vector to copy.
 * @param kernel   Reference to the kernel used to filter the image.
 * @param padValue The value to pad the copy with (default = 0).
 * 
 * @return The padded copy.
 ********************************************************************************/
template <typename T>
std::vector<T> pad(const std::vector<T>& data, const std::vector<T>& kernel, 
                   const T padValue = 0) noexcept;

/********************************************************************************
 * @brief Provides a padded copy of referenced vector.
 * 
 * @tparam T The vector type (must be arithmetic).
 * 
 * @param data        Reference to the vector to copy.
 * @param paddingCount The number of paddings to add to each side of the copy.
 * @param padValue    The value to pad the copy with (default = 0).
 * 
 * @return The padded copy.
 ********************************************************************************/
template <typename T>
std::vector<std::vector<T>> pad(const std::vector<std::vector<T>>& data, 
                                const std::size_t paddingCount,
                                const T padValue = 0) noexcept;
            
/********************************************************************************
 * @brief Provides a padded copy of referenced vector.
 * 
 * @tparam T The vector type (must be arithmetic).
 * 
 * @param data     Reference to the vector to copy.
 * @param kernel   Reference to the kernel used to filter the image.
 * @param padValue The value to pad the copy with (default = 0).
 * 
 * @return The padded copy.
 ********************************************************************************/           
template <typename T>
std::vector<std::vector<T>> pad(const std::vector<std::vector<T>>& data, 
                                const std::vector<std::vector<double>>& kernel,
                                const T padValue = 0) noexcept;

/********************************************************************************
 * @brief Prints number held by referenced one-dimensional vector. 
 * 
 * @tparam T The vector type (must be arithmetic).
 * 
 * @param data         Reference to the vector holding the numbers to print.
 * @param decimalCount The decimal precision (default = 0).
 * @param ostream      Reference to output stream (default = terminal print).
 * @param end          Ending characters to print (default = new line).
 ********************************************************************************/
template <typename T>
void print(const std::vector<T>& data, const std::size_t decimalCount = 0U, 
           std::ostream& ostream = std::cout, const char* const end = "\n") noexcept;

/********************************************************************************
 * @brief Prints number held by referenced two-dimensional vector. 
 * 
 * @tparam T The vector type (must be arithmetic).
 * 
 * @param data         Reference to the vector holding the numbers to print.
 * @param decimalCount The decimal precision (default = 0).
 * @param ostream      Reference to output stream (default = terminal print).
 ********************************************************************************/
template <typename T>
void print(const std::vector<std::vector<T>>& data, const std::size_t decimalCount = 0U, 
           std::ostream& ostream = std::cout) noexcept;

/********************************************************************************
 * @brief Initialized the random generator used for generating random numbers.
 ********************************************************************************/
inline void initRandomGenerator() noexcept;

/********************************************************************************
 * @brief Provides a randomly generated integer in specified range [min, max].
 * 
 * @tparam The type of the generated integer (default = int).
 * 
 * @param min The minimum value of the generated random integer (default = 0).
 * @param max The maximum value of the generated random integer (default = 100).
 * 
 * @return The generated random integer.
 ********************************************************************************/
template <typename T = int>
enable_if_integral<T, T> random(const T min = 0, const T max = 100) noexcept;

/********************************************************************************
 * @brief Provides a randomly generated floating-point number in specified 
 *        range [min, max].
 * 
 * @tparam The type of the generated floating-point number (default = double).
 * 
 * @param min The minimum value of the generated random number (default = 0.0).
 * @param max The maximum value of the generated random number (default = 1.0).
 * 
 * @return The generated random floating-point number.
 ********************************************************************************/
template <typename T = double>
enable_if_float<T, T> random(const T min = 0.0, const T max = 1.0) noexcept;

} // namespace
} // namespace utils
} // namespace ml

#include "conv_utils_impl.h"