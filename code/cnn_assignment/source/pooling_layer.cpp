#include <stdexcept>

#include "conv_layer.h"
#include "pooling_layer.h"

namespace ml
{

// -----------------------------------------------------------------------------
PoolingLayer::PoolingLayer(const std::size_t size, const std::size_t stride) 
{
    if ((size == 0U) || (stride == 0U))
    {
        throw std::invalid_argument("Invalid dimensions of pooling layer (pooling size and stride must exceed 0)!");
    }
}

// -----------------------------------------------------------------------------
bool PoolingLayer::feedforward(const std::vector<std::vector<double>>& input, const Type poolingType) noexcept
{
    if (input.size() < myOutput.size()) 
    {
        std::cerr << "Input image cannot be smaller than pooling layer size!\n\n";
        return false;
    } 

    return true;
}

// -----------------------------------------------------------------------------
void PoolingLayer::print(std::ostream& ostream, const int decimalCount) const noexcept 
{
    if (myOutput.empty()) { return; }
    ostream << "------------------------------------------------------------------------------\n";
    ostream << "Pooling layer size: " << myOutput.size() << " x " << myOutput.size() << "\n\n";
    ostream << "Feature map:\n";
    ConvLayer::printMatrix(myOutput, ostream, decimalCount);
    ostream << "------------------------------------------------------------------------------\n\n";
}

} // namespace ml