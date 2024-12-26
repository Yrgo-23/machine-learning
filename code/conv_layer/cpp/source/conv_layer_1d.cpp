/********************************************************************************
 * @brief Implementation details of the ml::ConvLayer1D class.
 ********************************************************************************/
#include "conv_layer_1d.h"
#include "conv_utils.h"

namespace ml
{

// -----------------------------------------------------------------------------
ConvLayer1D::ConvLayer1D(const std::size_t kernelSize) noexcept
    : myInputPadded{}
    , myKernel{}
    , myOutput{}
    , myInputError{}
    , myKernelError{}
{
    utils::initRandomGenerator();
    initKernel(kernelSize);
}

// -----------------------------------------------------------------------------
const std::vector<double>& ConvLayer1D::inputPadded() const noexcept { return myInputPadded; }

// -----------------------------------------------------------------------------
const std::vector<double>& ConvLayer1D::kernel() const noexcept { return myKernel; }

// -----------------------------------------------------------------------------
const std::vector<double>& ConvLayer1D::output() const noexcept { return myOutput; }

// -----------------------------------------------------------------------------
const std::vector<double>& ConvLayer1D::kernelError() const noexcept { return myKernelError; }

// -----------------------------------------------------------------------------
const std::vector<double>& ConvLayer1D::inputError() const noexcept { return myInputError; }

// -----------------------------------------------------------------------------
std::size_t ConvLayer1D::imageSize() const noexcept { return myOutput.size(); }

// -----------------------------------------------------------------------------
std::size_t ConvLayer1D::kernelSize() const noexcept { return myKernel.size(); }

// -----------------------------------------------------------------------------
void ConvLayer1D::feedforward(const std::vector<double>& input) noexcept 
{
    myInputPadded = pad(input);
    myOutput.resize(input.size(), 0.0);
    
    for (std::size_t i{}; i < imageSize(); ++i)
    {
        for (std::size_t j{}; j < kernelSize(); ++j)
        {
            myOutput[i] += myInputPadded[i + j] * myKernel[j];
        }
    }
}

// -----------------------------------------------------------------------------
void ConvLayer1D::backpropagate(const std::vector<double>& outputError) noexcept 
{
    std::vector<double> outputErrorPadded{pad(outputError)};

    myKernelError.resize(kernelSize(), 0.0);
    myInputError.resize(imageSize(), 0.0);

    for (std::size_t i{}; i < imageSize(); ++i)
    {
        for (std::size_t j{}; j < kernelSize(); ++j)
        {
            myKernelError[j] += myInputPadded[i + j] * outputError[i];
            myInputError[i] += outputErrorPadded[kernelSize() - 1 + i - j] * myKernel[j];
        }
    }
}

// -----------------------------------------------------------------------------
bool ConvLayer1D::optimize(const double learningRate) noexcept 
{
    if (learningRate <= 0.0) { return false; }
    for (std::size_t i{}; i < kernelSize(); ++i)
    {
        myKernel[i] -= myKernelError[i] * learningRate;
    }
    return true;
}

// -----------------------------------------------------------------------------
void ConvLayer1D::initKernel(const std::size_t kernelSize) noexcept 
{
    myKernel.resize(kernelSize);
    for (auto& i : myKernel)
    {
        i = utils::random<double>(0.0, 1.0);
    }
}

// -----------------------------------------------------------------------------
void ConvLayer1D::setInputPadded(const std::vector<double>& input) noexcept 
{
    myInputPadded.resize(paddingCount() * 2U + input.size(), 0.0);
    for (std::size_t i{}; i < input.size(); ++i)
    {
        myInputPadded[i + paddingCount()] = input[i];
    }
}

// -----------------------------------------------------------------------------
std::size_t ConvLayer1D::paddingCount() const noexcept  { return kernelSize() / 2U; }

// -----------------------------------------------------------------------------
std::vector<double> ConvLayer1D::pad(const std::vector<double>& data) noexcept 
{
    return utils::pad<double>(data, paddingCount());
}

} // namespace ml