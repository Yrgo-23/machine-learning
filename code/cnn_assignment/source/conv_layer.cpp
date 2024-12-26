#include <iomanip>
#include <stdexcept>

#include "conv_layer.h"

namespace ml
{

// -----------------------------------------------------------------------------
ConvLayer::ConvLayer(const std::size_t imageSize, const std::size_t kernelSize) 
{ 
    if ((imageSize == 0U) || (kernelSize == 0U))
    {
        throw std::invalid_argument("Invalid dimensions of convolutional layer (image and kernel size must exceed 0)!");
    }
}

// -----------------------------------------------------------------------------
const std::vector<std::vector<double>>& ConvLayer::image() const noexcept { return myImage; }

// -----------------------------------------------------------------------------
const std::vector<std::vector<double>>& ConvLayer::kernel() const noexcept { return myKernel; }

// -----------------------------------------------------------------------------
const std::vector<std::vector<double>>& ConvLayer::output() const noexcept { return myOutput; }

// -----------------------------------------------------------------------------
double ConvLayer::kernelBias() const noexcept { return myKernelBias; }

// -----------------------------------------------------------------------------
bool ConvLayer::feedforward(const std::vector<std::vector<double>>& input) noexcept { return false; }

// -----------------------------------------------------------------------------
void ConvLayer::print(std::ostream& ostream, const int decimalCount) const noexcept 
{
    if (myImage.empty()) { return; }
    ostream << std::fixed;

    ostream << "------------------------------------------------------------------------------\n";
    ostream << "Image size: " << myImage.size() - 2U << " x " << myImage.size() - 2U << "\n";
    ostream << "Kernel size: " << myKernel.size() << " x " << myKernel.size() << "\n\n";

    ostream << "Image:\n";
    printMatrix(myImage, ostream, decimalCount, 1U);
    ostream << "\nKernel:\n";
    printMatrix(myKernel, ostream, decimalCount);

    ostream << "\nFeature map:\n";
    printMatrix(myOutput, ostream, decimalCount);
    ostream << "------------------------------------------------------------------------------\n\n";
}

// -----------------------------------------------------------------------------
void ConvLayer::printMatrix(const std::vector<std::vector<double>>& matrix, std::ostream& ostream,
                            const int decimalCount, const std::size_t paddingCount) noexcept
{
    for (std::size_t i{paddingCount}; i < matrix.size() - paddingCount; ++i) 
    {
        for (std::size_t j{paddingCount}; j < matrix.size() - paddingCount; ++j) 
        {
            ostream << std::setprecision(decimalCount) << matrix[j][i] << " ";
        }
        ostream << "\n";
    }
}

} // namespace ml