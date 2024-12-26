/********************************************************************************
 * @brief Implementation details of the ml::PoolingLayer2D class.
 ********************************************************************************/
#include "pooling_layer_2d.h"

namespace ml
{

// -----------------------------------------------------------------------------
PoolingLayer2D::PoolingLayer2D(const std::size_t size, const PoolType type) noexcept
    : myOutput(size, std::vector<double>(size, 0.0))
    , myType(type) {}

// -----------------------------------------------------------------------------
const std::vector<std::vector<double>>& PoolingLayer2D::output() const noexcept
{
    return myOutput;
}

// -----------------------------------------------------------------------------
PoolType PoolingLayer2D::type() const noexcept { return myType; }

// -----------------------------------------------------------------------------
std::size_t PoolingLayer2D::size() const noexcept { return myOutput.size(); }

// -----------------------------------------------------------------------------
bool PoolingLayer2D::feedforward(const std::vector<std::vector<double>>& input) noexcept
{
    if (isInputInValid(input)) { return false; }

    for (std::size_t i{}; i < size(); ++i)
    {
        for (std::size_t j{}; j < size(); ++j)
        {
            myOutput[j][i] = pool(input, j, i);
        }
    }
    return true;
}

// -----------------------------------------------------------------------------
std::size_t PoolingLayer2D::paddingCount() const noexcept { return size() - 1U; }

// -----------------------------------------------------------------------------
bool PoolingLayer2D::isInputInValid(const std::vector<std::vector<double>>& input) noexcept
{
    return input.empty() || input[0U].empty() || 
        input.size() <= size() || input[0U].size() <= size();
}

// -----------------------------------------------------------------------------
double PoolingLayer2D::pool(const std::vector<std::vector<double>>& input, const std::size_t j, 
                            const std::size_t i) noexcept
{
    const auto x{j * size()};
    const auto y{i * size()};
    if (!isWithinRange(input, x, y)) { return 0.0; }
    return myType == PoolType::Max ? poolMax(input, x, y) : poolAverage(input, x, y);
}

// -----------------------------------------------------------------------------
double PoolingLayer2D::poolMax(const std::vector<std::vector<double>>& input, const std::size_t x, 
                               const std::size_t y) noexcept
{
    auto maxVal{input[x][y]};
    for (std::size_t i{}; i < iterationWidth(input); ++i)
    {
        for (std::size_t j{}; j < iterationHeight(input); ++j)
        {
            if ((x + i < input.size()) && (y + j < input[0].size()))
            {
                if (input[x + i][y + j] > maxVal) 
                { 
                    maxVal = input[x + i][y + j]; 
                }
            }
        }
    }
    return maxVal;
}

// -----------------------------------------------------------------------------
double PoolingLayer2D::poolAverage(const std::vector<std::vector<double>>& input, const std::size_t x, 
                                   const std::size_t y) noexcept
{
    double averageVal{};
    for (std::size_t i{}; i < iterationWidth(input); ++i)
    {
        for (std::size_t j{}; j < iterationHeight(input); ++j)
        {
            averageVal += input[x + i][y + j];
        }
    }
    return averageVal / (size() * size());
}

// -----------------------------------------------------------------------------
std::size_t PoolingLayer2D::iterationWidth(const std::vector<std::vector<double>>& input) noexcept
{
    return size() < input.size() ? input.size() / size() + 1U : input.size() / size();
}

// -----------------------------------------------------------------------------
std::size_t PoolingLayer2D::iterationHeight(const std::vector<std::vector<double>>& input) noexcept
{
    return size() < input[0U].size() ? input[0U].size() / size() + 1U : input[0U].size() / size();
}

// -----------------------------------------------------------------------------
bool PoolingLayer2D::isWithinRange(const std::vector<std::vector<double>>& input, const std::size_t x, 
                                   const std::size_t y) noexcept
{
    return x < input.size() && y < input[0U].size();
}

} // namespace ml