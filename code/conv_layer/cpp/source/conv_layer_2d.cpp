/********************************************************************************
 * @brief Implementation details of the ml::ConvLayer2D class.
 ********************************************************************************/
#include "conv_layer_2d.h"
#include "conv_utils.h"

namespace ml
{

// -----------------------------------------------------------------------------
ConvLayer2D::ConvLayer2D(const std::size_t kernelSize) noexcept
    : myInputPadded{}
    , myKernel{}
    , myOutput{}
    , myInputError{}
    , myKernelError{}
{
    initKernel(kernelSize);
}

// -----------------------------------------------------------------------------
const std::vector<std::vector<double>>& ConvLayer2D::inputPadded() const noexcept
{
    return myInputPadded;
}

// -----------------------------------------------------------------------------
const std::vector<std::vector<double>>& ConvLayer2D::kernel() const noexcept
{
    return myKernel;
}

// -----------------------------------------------------------------------------
const std::vector<std::vector<double>>& ConvLayer2D::output() const noexcept
{
    return myOutput;
}

// -----------------------------------------------------------------------------
const std::vector<std::vector<double>>& ConvLayer2D::inputError() const noexcept
{
    return myInputError;
}

// -----------------------------------------------------------------------------
const std::vector<std::vector<double>>& ConvLayer2D::kernelError() const noexcept
{
    return myKernelError;
}

// -----------------------------------------------------------------------------
std::size_t ConvLayer2D::imageWidth() const noexcept { return myOutput.size(); }

// -----------------------------------------------------------------------------
std::size_t ConvLayer2D::imageHeight() const noexcept
{
    return myOutput.size() > 0U ? myOutput[0U].size() : 0U;
}

// -----------------------------------------------------------------------------
std::size_t ConvLayer2D::kernelSize() const noexcept { return myKernel.size(); }

// -----------------------------------------------------------------------------
void ConvLayer2D::feedforward(const std::vector<std::vector<double>>& input) noexcept
{
    if (input.empty()) { return; }
    myInputPadded = pad(input);
    myOutput.resize(input.size(), std::vector<double>(input[0U].size(), 0.0));

    for (std::size_t i{}; i < imageWidth(); ++i)
    {
        for (std::size_t j{}; j < imageHeight(); ++j)
        {
            for (std::size_t k{}; k < kernelSize(); ++k)
            {
                for (std::size_t l{}; l < kernelSize(); ++l)
                {
                    myOutput[i][j] += myInputPadded[i + k][j + l] * myKernel[k][l];
                }
            }
        }
    }
}

// -----------------------------------------------------------------------------
void ConvLayer2D::backpropagate(const std::vector<std::vector<double>>& outputError) noexcept
{
    myKernelError.resize(kernelSize(), std::vector<double>(kernelSize(), 0));
    myInputError.resize(imageWidth(), std::vector<double>(imageHeight(), 0));
    const std::vector<std::vector<double>> outputErrorPadded{pad(outputError)};
    const auto offset{kernelSize() - 1U};

    for (std::size_t i{}; i < imageWidth(); ++i)
    {
        for (std::size_t j{}; j < imageHeight(); ++j)
        {
            for (std::size_t k{}; k < kernelSize(); ++k)
            {
                for (std::size_t l{}; l < kernelSize(); ++l)
                {
                    myKernelError[k][l] += myInputPadded[i + k][j + l] * outputError[i][j];
                    myInputError[i][j] += 
                        outputErrorPadded[offset + i - k][offset + j - l] * myKernel[k][l];
                }
            }
        }
    }
}

// -----------------------------------------------------------------------------
void ConvLayer2D::optimize(const double learningRate) noexcept
{
    for (std::size_t i{}; i < kernelSize(); ++i)
    {
        for (std::size_t j{}; j < kernelSize(); ++j)
        {
            myKernel[i][j] += myKernelError[i][j] * learningRate;
        }
    }
}

// -----------------------------------------------------------------------------
void ConvLayer2D::initKernel(const std::size_t kernelSize) noexcept
{
    myKernel.resize(kernelSize, std::vector<double>(kernelSize));

    for (auto& i : myKernel)
    {
        for (auto& j : i)
        {
            j = utils::random<double>(0.0, 1.0);
        }
    }
}

// -----------------------------------------------------------------------------
std::vector<std::vector<double>> ConvLayer2D::pad(const std::vector<std::vector<double>>& input) noexcept
{
    return utils::pad<double>(input, myKernel);
}

// -----------------------------------------------------------------------------
std::size_t ConvLayer2D::paddingCount() const noexcept
{
    return kernelSize() / 2U;
}

// -----------------------------------------------------------------------------
std::size_t ConvLayer2D::width(const std::vector<std::vector<double>>& input) noexcept
{
    return input.size();
}

// -----------------------------------------------------------------------------
std::size_t ConvLayer2D::height(const std::vector<std::vector<double>>& input) noexcept
{
    return input.size() > 0U ? input[0U].size() : 0U;
}

} // namespace ml