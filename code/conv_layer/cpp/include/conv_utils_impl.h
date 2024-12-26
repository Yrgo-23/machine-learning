/********************************************************************************
 * @brief Implementation details function templates in ml::utils.
 ********************************************************************************/
#pragma once

namespace ml
{
namespace utils
{
namespace 
{

// -----------------------------------------------------------------------------
constexpr std::size_t paddingCount(const std::size_t kernelSize) noexcept
{
    return static_cast<std::size_t>(kernelSize / 2U);    
}

// -----------------------------------------------------------------------------
template <typename T>
std::size_t paddingCount(const std::vector<T>& kernel) noexcept
{
    static_assert(std::is_arithmetic<T>::value, 
        "Function ml::paddingCount does not support non-arithmetic types!");
    return paddingCount(kernel.size());
}

// -----------------------------------------------------------------------------
template <typename T>
std::size_t paddingCount(const std::vector<std::vector<T>>& kernel) noexcept
{
    static_assert(std::is_arithmetic<T>::value, 
        "Function ml::paddingCount does not support non-arithmetic types!");
    return paddingCount(kernel.size());
}

// -----------------------------------------------------------------------------
template <typename T>
std::vector<T> pad(const std::vector<T>& data, const std::size_t paddingCount, 
                   const T padValue) noexcept
{
    static_assert(std::is_arithmetic<T>::value, 
        "Function ml::pad does not support non-arithmetic types!");
    std::vector<T> padded(paddingCount * 2U + data.size(), padValue);

    for (std::size_t i{}; i < data.size(); ++i)
    {
        padded[paddingCount + i] = data[i];
    }
    return padded;
}

// -----------------------------------------------------------------------------
template <typename T>
std::vector<T> pad(const std::vector<T>& data, const std::vector<T>& kernel,
                   const T padValue) noexcept
{
    static_assert(std::is_arithmetic<T>::value, 
        "Function ml::pad does not support non-arithmetic types!");
    return pad<T>(data, paddingCount(kernel), padValue);
}

// -----------------------------------------------------------------------------
template <typename T>
std::vector<std::vector<T>> pad(const std::vector<std::vector<T>>& data, 
                                const std::size_t paddingCount,
                                const T padValue) noexcept
{
    static_assert(std::is_arithmetic<T>::value, 
        "Function ml::pad does not support non-arithmetic types!");
    if (data.empty()) { return {}; }

    const auto valuesPerRowCount(paddingCount * 2U + data[0U].size());
    std::vector<std::vector<double>> padded(paddingCount * 2U + data.size(), 
        std::vector<double>(valuesPerRowCount, padValue));
        
    for (std::size_t i{}; i < data.size(); ++i)
    {
        for (std::size_t j{}; j < data[0].size(); ++j)
        {
            padded[paddingCount + i][paddingCount + j] = data[i][j];
        }
    }
    return padded;
}

// -----------------------------------------------------------------------------
template <typename T>
std::vector<std::vector<T>> pad(const std::vector<std::vector<T>>& data, 
                                const std::vector<std::vector<double>>& kernel,
                                const T padValue) noexcept
{
    static_assert(std::is_arithmetic<T>::value, 
        "Function ml::pad does not support non-arithmetic types!");
    return pad(data, paddingCount(kernel), padValue);
}

// -----------------------------------------------------------------------------
template <typename T>
void print(const std::vector<T>& data, const std::size_t decimalCount, 
           std::ostream& ostream, const char* const end) noexcept
{
    static_assert(std::is_arithmetic<T>::value, 
        "Function ml::print does not support non-arithmetic types!");
    ostream << std::fixed << std::setprecision(decimalCount);
    ostream << "[";

    for (const auto& i : data)
    {
        ostream << i;
        if (&i != &data[data.size() - 1]) { ostream << ", "; }
    }
    ostream << "]";
    if (end) { ostream << end; }
}

// -----------------------------------------------------------------------------
template <typename T>
void print(const std::vector<std::vector<T>>& data, const std::size_t decimalCount, 
           std::ostream& ostream) noexcept
{
    static_assert(std::is_arithmetic<T>::value, 
        "Function ml::print does not support non-arithmetic types!");

    ostream << std::fixed << std::setprecision(decimalCount);
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& i : data) { print(i, decimalCount, ostream); }
    ostream << "--------------------------------------------------------------------------------\n\n";
}

// -----------------------------------------------------------------------------
inline void initRandomGenerator() noexcept
{ 
    static bool randomGeneratorInitialized{false};
    if (randomGeneratorInitialized) { return; }
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    randomGeneratorInitialized = true;
}

// -----------------------------------------------------------------------------
template <typename T>
enable_if_integral<T, T> random(const T min, const T max) noexcept
{
    static_assert(std::is_integral<T>::value);
    return std::rand() % (max + 1 - min) - min; 
}

// -----------------------------------------------------------------------------
template <typename T>
enable_if_float<T, T> random(const T min, const T max) noexcept
{
    static_assert(std::is_floating_point<T>::value);
    return (static_cast<T>(std::rand()) / RAND_MAX) * (max - min) - min;
}

} // namespace
} // namespace utils
} // namespace ml