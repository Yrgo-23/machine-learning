/********************************************************************************
 * @brief Implementation details of the ml::FlattenLayer class.
 ********************************************************************************/
#include "conv_utils.h"
#include "flatten_layer.h"

namespace ml
{

// -----------------------------------------------------------------------------
FlattenLayer::FlattenLayer() noexcept
    : myOutput{}
    , myError{} {}

// -----------------------------------------------------------------------------
FlattenLayer::FlattenLayer(const std::vector<std::vector<double>>& input) noexcept
{
    feedforward(input);
}

// -----------------------------------------------------------------------------
const std::vector<double>& FlattenLayer::output() const noexcept { return myOutput; }

// -----------------------------------------------------------------------------
const std::vector<double>& FlattenLayer::error() const noexcept { return myError; }

// -----------------------------------------------------------------------------
void FlattenLayer::feedforward(const std::vector<std::vector<double>>& input) noexcept
{
    myOutput.clear();
    for (const auto& i : input)
    {
        for (const auto& j : i)
        {
            myOutput.push_back(j);
        }
    }
}

// -----------------------------------------------------------------------------
void FlattenLayer::backpropagate(const std::vector<double>& nextLayerError) noexcept
{
    myError = nextLayerError;
}

} // namespace ml