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
    init();
    static_assert(std::is_arithmetic<T>::value, 
        "Non-arithmetic type selected for new random number!");

    if (min > max) 
    { 
        throw std::invalid_argument(
            "Cannot generate random number when min is more than max!"); 
    }

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
    static_assert(std::is_arithmetic<T>::value, 
        "Cannot assign random numbers for non-arithmetic types!");
    if (size == 0U)
    {
        throw std::invalid_argument(
            "Vector size must exceed 0 for random initialization!");
    }
    vector.resize(size);
    for (auto& i : vector) { i = random::getNumber<T>(min, max); }
}

// -----------------------------------------------------------------------------
template <typename T> 
void initRandom(std::vector<std::vector<T>>& vector, 
                const std::size_t columnCount, const std::size_t rowCount, 
                const T min, const T max) 
{
    static_assert(std::is_arithmetic<T>::value, 
        "Cannot assign random numbers for non-arithmetic types!");

    if ((columnCount == 0U) || (rowCount == 0U))
    {
        throw std::invalid_argument(
            "Vector row and column count must both exceed 0 for random initialization!");
    }
    vector.resize(columnCount, std::vector<T>(rowCount));

    for (auto& i : vector) 
    {
        for (auto& j : i) { j = random::getNumber<T>(min, max); }
    }
}

// -----------------------------------------------------------------------------
template <typename T>
void shuffle(std::vector<T>& vector) 
{
    for (std::size_t i{}; i < vector.size(); ++i) 
    {
        const auto r{static_cast<std::size_t>(std::rand() % vector.size())};
        const auto temp{vector[i]};
        vector[i] = vector[r];
        vector[r] = temp;
    }
}

// -----------------------------------------------------------------------------
template <typename T>
void shuffle(std::vector<std::vector<T>>& vector) 
{
    for (std::size_t i{}; i < vector.size(); ++i) 
    {
        const auto r{static_cast<std::size_t>(std::rand() % vector.size())};
        const auto temp{vector[i]};
        vector[i] = vector[r];
        vector[r] = temp;
    }
}

// -----------------------------------------------------------------------------
template <typename T>
void print(const std::vector<T>& vector, std::ostream& ostream, 
           const char* end, const std::size_t decimalCount)
{
    static_assert(std::is_arithmetic<T>::value || utils::type_traits::is_string<T>::value,
        "Function utils::vector::print only supports arithmetic types and strings!");

    if (std::is_floating_point<T>::value && decimalCount > 0U) 
    { 
        ostream << std::fixed << std::setprecision(decimalCount) << "[";
    }
    else { ostream << "["; }

    constexpr auto roundNearZeroValue = [](const T value, const double threshold = 0.001) -> T
    {
        if constexpr (std::is_floating_point<T>::value)
        {
            return (value < threshold) && (value > -threshold) ? 0.0 : value;
        }
        else { return value; }
    };

    for (std::size_t i{}; i < vector.size(); ++i)
    {
        const auto value{roundNearZeroValue(vector[i])};
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
    static_assert(std::is_arithmetic<T>::value || utils::type_traits::is_string<T>::value,
        "Function utils::vector::print only supports arithmetic types and strings!");
    ostream << "[";

    for (std::size_t i{}; i < vector.size(); ++i)
    {
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
    static_assert(std::is_arithmetic<T>::value, 
        "Cannot perform mathematical operations with non-arithmetic types!");
    return number >= 0 ? number : -number; 
}

// -----------------------------------------------------------------------------
template <typename T, typename... Numbers>
constexpr T add(const Numbers&... numbers) {
    static_assert(std::is_arithmetic<T>::value, 
        "Cannot perform mathematical operations with non-arithmetic types!");
    T sum{};
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
    static_assert(std::is_arithmetic<T>::value, 
        "Cannot perform mathematical operations with non-arithmetic types!");
    T sum{};

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
    static_assert(std::is_arithmetic<T>::value, 
        "Cannot perform mathematical operations with non-arithmetic types!");
    T sum{1};

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
    static_assert(std::is_arithmetic<T1>::value && std::is_arithmetic<T2>::value, 
        "Cannot perform mathematical operations with non-arithmetic types!");
    return divisor != 0 ? dividend / (static_cast<double>(divisor)) : 0;
}

// -----------------------------------------------------------------------------
template <typename T>
constexpr T round(const double number) 
{
    static_assert(std::is_arithmetic<T>::value, 
        "Cannot round to non-arithmetic type!");
    return static_cast<T>(number + 0.5);
}

// -----------------------------------------------------------------------------
constexpr double relu(const double number) 
{ 
    return number > 0.0 ? number : 0.0; 
}

// -----------------------------------------------------------------------------
constexpr double reluGradient(const double number) 
{ 
    return number > 0.0 ? 1.0 : 0.0; 
}

// -----------------------------------------------------------------------------
constexpr double tanh(const double number) 
{ 
    return std::tanh(number); 
}

// -----------------------------------------------------------------------------
constexpr double tanhGradient(const double number) 
{ 
    return 1.0 - std::pow(std::tanh(number), 2); 
}

} // namespace math
} // namespace
} // namespace utils