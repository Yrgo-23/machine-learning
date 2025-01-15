/*******************************************************************************
 * @brief Implementation details for utility functions.
 * 
 * @note Do not include this file in any application!
 ******************************************************************************/
#pragma once

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <type_traits>

namespace utils 
{
namespace 
{
namespace random
{

// -----------------------------------------------------------------------------
inline void init() 
{
    static auto generatorInitialized{false};

    // Only initialize the random generator once.
    if (!generatorInitialized) 
    {
        std::srand(std::time(nullptr));
        generatorInitialized = true;
    }
}

// -----------------------------------------------------------------------------
template <typename T>
T getNumber(const T min, const T max) 
{
    // Generate a compilation error if given type is not arithmetic.
    static_assert(std::is_arithmetic<T>::value, 
        "Non-arithmetic type selected for new random number!");

    // Throw an exception is given min value is larger than given max value.
    if (min > max) 
    { 
        throw std::invalid_argument(
            "Cannot generate random number when min is more than max!"); 
    }
    
    // Initialize the random generator (if not previously initialized).
    init();

    // Return value between min and max.
    if constexpr (std::is_integral<T>::value) 
    {
        return static_cast<T>((std::rand() % (max + 1 - min)) + min);
    } 
    else 
    {
        return (std::rand() / static_cast<T>(RAND_MAX)) * (max - min) + min;
    }
}

} // namespace random

namespace vector
{

// -----------------------------------------------------------------------------
template <typename T> 
void initRandom(std::vector<T>& vector, const std::size_t size, 
                const T min, const T max) 
{
    // Generate a compilation error if given type is not arithmetic.
    static_assert(std::is_arithmetic<T>::value, 
        "Cannot assign random numbers for non-arithmetic types!");

    // Throw an exception if specified size is zero.
    if (size == 0U)
    {
        throw std::invalid_argument(
            "Vector size must exceed 0 for random initialization!");
    }

    // Resize the vector to given size.
    vector.resize(size);

    // Fill the vector with random values between min and max.
    for (auto& i : vector) { i = random::getNumber<T>(min, max); }
}

// -----------------------------------------------------------------------------
template <typename T> 
void initRandom(std::vector<std::vector<T>>& vector, 
                const std::size_t columnCount, const std::size_t rowCount, 
                const T min, const T max) 
{
    // Generate a compilation error if given type is not arithmetic.
    static_assert(std::is_arithmetic<T>::value, 
        "Cannot assign random numbers for non-arithmetic types!");

    // Throw an exception if any parameter is invalid.
    if ((columnCount == 0U) || (rowCount == 0U))
    {
        throw std::invalid_argument(
            "Vector row and column count must both exceed 0 for random initialization!");
    }

    // Resize the vector to a 2D vector with given column and row count.
    vector.resize(columnCount, std::vector<T>(rowCount));

    // Fill the vector with random values between min and max.
    for (auto& i : vector) 
    {
        for (auto& j : i) { j = random::getNumber<T>(min, max); }
    }
}

// -----------------------------------------------------------------------------
template <typename T>
void shuffle(std::vector<T>& vector) 
{
    // Swap each element one by one.
    for (std::size_t i{}; i < vector.size(); ++i) 
    {
        // Generate random index to used for swapping.
        const auto r{static_cast<std::size_t>(std::rand() % vector.size())};

        // Store temporary copy of the first value.
        const auto temp{vector[i]};

        // Overwrite old value at index i with random value at index r.
        vector[i] = vector[r];

        // Move stored away value to index r.
        vector[r] = temp;
    }
}

// -----------------------------------------------------------------------------
template <typename T>
void shuffle(std::vector<std::vector<T>>& vector) 
{
    // Swap each element one by one.
    for (std::size_t i{}; i < vector.size(); ++i) 
    {
        // Generate random index to used for swapping.
        const auto r{static_cast<std::size_t>(std::rand() % vector.size())};

        // Store temporary copy of the first value.
        const auto temp{vector[i]};

        // Overwrite old value at index i with random value at index r.
        vector[i] = vector[r];
        
         // Move stored away value to index r.
        vector[r] = temp;
    }
}

// -----------------------------------------------------------------------------
template <typename T>
void print(const std::vector<T>& vector, std::ostream& ostream, 
           const char* end, const std::size_t decimalCount)
{
    // Generate a compilation error if given type is not of arithmetic or string type.
    static_assert(std::is_arithmetic<T>::value || utils::type_traits::is_string<T>::value,
        "Function utils::vector::print only supports arithmetic types and strings!");

    // Round values very close to 0.
    constexpr auto roundNearZeroValue = [](const T value, const double threshold = 0.001) -> T
    {
        if constexpr (std::is_floating_point<T>::value)
        {
            return (value < threshold) && (value > -threshold) ? 0.0 : value;
        }
        else { return value; }
    };

    // Set decimal precision.
    if (std::is_floating_point<T>::value && decimalCount > 0U) 
    { 
        ostream << std::fixed << std::setprecision(decimalCount) << "[";
    }
    else { ostream << "["; }

    // Print each element in the vector one by one, rounded to given precision.
    for (std::size_t i{}; i < vector.size(); ++i)
    {
        const auto value{roundNearZeroValue(vector[i])};

        // Separate each element with a comma.
        if (i < vector.size() - 1U) { ostream << value << ", "; }
        else { ostream << value; }
    }

    ostream << "]";
    if (end != nullptr) { ostream << end; }
}

// -----------------------------------------------------------------------------
template <typename T>
void print(const std::vector<std::vector<T>>& vector, std::ostream& ostream, 
           const char* end, const std::size_t decimalCount)
{
    // Generate a compilation error if given type is not of arithmetic or string type.
    static_assert(std::is_arithmetic<T>::value || utils::type_traits::is_string<T>::value,
        "Function utils::vector::print only supports arithmetic types and strings!");
    ostream << "[";

    // Print each dimension of the vector separated by brackets.
    for (std::size_t i{}; i < vector.size(); ++i)
    {
         // Print each element separated with a comma.
        if (i < vector.size() - 1U) { print<T>(vector[i], ostream, ", ", decimalCount); }
        else { print<T>(vector[i], ostream, "", decimalCount); }
    }
    ostream << "]";
    if (end != nullptr) { ostream << end; }
}

} // namespace vector

namespace math 
{

// -----------------------------------------------------------------------------
template <typename T>
constexpr T absoluteValue(const T& number) 
{ 
    // Generate a compilation error if given type is not arithmetic.
    static_assert(std::is_arithmetic<T>::value, 
        "Cannot perform mathematical operations with non-arithmetic types!");
    return number >= 0 ? number : -number; 
}

// -----------------------------------------------------------------------------
template <typename T, typename... Numbers>
constexpr T add(const Numbers&... numbers) 
{
    // Generate a compilation error if given type is not arithmetic.
    static_assert(std::is_arithmetic<T>::value, 
        "Cannot perform mathematical operations with non-arithmetic types!");
    T sum{};

    // Add the value from each number in the parameter pack.
    for (const auto& number : {numbers...}) 
    { 
        static_assert(std::is_same<const T&, decltype(number)>::value,
             "Type mismatch between during addition!");
        sum += number;
    }
    return sum;
}

// -----------------------------------------------------------------------------
template <typename T, typename... Numbers>
constexpr T subtract(const Numbers&... numbers) 
{
    // Generate a compilation error if given type is not arithmetic.
    static_assert(std::is_arithmetic<T>::value, 
        "Cannot perform mathematical operations with non-arithmetic types!");
    T sum{};

    // Subtract the value from each number in the parameter pack.
    for (const auto& number : {numbers...}) 
    { 
        static_assert(std::is_same<const T&, decltype(number)>::value,
             "Type mismatch between during subtraction!");
        sum -= number; 
    }
    return sum;
}

// -----------------------------------------------------------------------------
template <typename T, typename... Numbers>
constexpr T multiply(const Numbers&... numbers) 
{
    // Generate a compilation error if given type is not arithmetic.
    static_assert(std::is_arithmetic<T>::value, 
        "Cannot perform mathematical operations with non-arithmetic types!");
    T sum{1};

    // Multiply the value from each number in the parameter pack.
    for (const auto& number : {numbers...}) 
    { 
        static_assert(std::is_same<const T&, decltype(number)>::value,
             "Type mismatch between during multiplication!");
        sum *= number; 
    }
    return sum;
}

// -----------------------------------------------------------------------------
template <typename T1, typename T2>
constexpr double divide(const T1 dividend, const T2 divisor) 
{
    // Generate a compilation error if given type is not arithmetic.
    static_assert(std::is_arithmetic<T1>::value && std::is_arithmetic<T2>::value, 
        "Cannot perform mathematical operations with non-arithmetic types!");

    // Perform division only if the division is not equal to 0.
    return divisor != 0 ? dividend / (static_cast<double>(divisor)) : 0;
}

// -----------------------------------------------------------------------------
template <typename T>
constexpr T round(const double number) 
{
    // Generate a compilation error if given type is not arithmetic.
    static_assert(std::is_arithmetic<T>::value, "Cannot round to non-arithmetic type!");
    return static_cast<T>(number + 0.5);
}

// -----------------------------------------------------------------------------
constexpr double relu(const double number) { return number > 0.0 ? number : 0.0; }

// -----------------------------------------------------------------------------
constexpr double reluGradient(const double number) { return number > 0.0 ? 1.0 : 0.0; }

// -----------------------------------------------------------------------------
constexpr double tanh(const double number) { return std::tanh(number); }

// -----------------------------------------------------------------------------
constexpr double tanhGradient(const double number) { return 1 - std::pow(std::tanh(number), 2); }

} // namespace math
} // namespace
} // namespace utils