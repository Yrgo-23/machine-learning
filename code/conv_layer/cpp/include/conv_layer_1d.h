/********************************************************************************
 * @brief Implementation of one-dimensional convolutional layers to filter
 *        attributes from images.
 ********************************************************************************/
#pragma once 

#include <vector>

namespace ml
{

/********************************************************************************
 * @brief Class for implementation of one-dimensional convolutional layers.
 *        The size of the images to filter is dynamic. The number of strides
 *        is always set to one and padding is used, hence the size of the filtered
 *        image is unchanged during feature extraction.
 * 
 *        This class is non-copyable and non-movable.
 ********************************************************************************/
class ConvLayer1D
{
public:

    /********************************************************************************
     * @brief Creates new convolutional layer.
     * 
     * @param kernelSize The size of the kernel used to filter the image.
     ********************************************************************************/
    explicit ConvLayer1D(const std::size_t kernelSize) noexcept;

    /********************************************************************************
     * @brief Deletes convolutional layer.
     ********************************************************************************/
    ~ConvLayer1D() noexcept = default;

    /********************************************************************************
     * @brief Provides the input image padded with zeros.
     * 
     * @return A reference to the padded input image.
     ********************************************************************************/
    const std::vector<double>& inputPadded() const noexcept;

    /********************************************************************************
     * @brief Provides the kernel used to filter the image.
     * 
     * @return A reference to the kernel.
     ********************************************************************************/
    const std::vector<double>& kernel() const noexcept;

    /********************************************************************************
     * @brief Provides the output of the convolutional layer, i.e. the attributes
     *        extracted from the input image.
     * 
     * @return A reference to the output of the convolutional layer.
     ********************************************************************************/
    const std::vector<double>& output() const noexcept;

    /********************************************************************************
     * @brief Provides the calculated kernel error used to optimize the layer.
     * 
     * @return A reference to the calculated kernel error.
     ********************************************************************************/
    const std::vector<double>& kernelError() const noexcept;

    /********************************************************************************
     * @brief Provides the calculated input error used to optimize the previous
     *        convolutional layer (if there is any).
     * 
     * @return A reference to the calculated input error.
     ********************************************************************************/
    const std::vector<double>& inputError() const noexcept;

    /********************************************************************************
     * @brief Provides the size of the last filtered image without padding.
     * 
     * @return The size of the last filtered image as an unsigned integer.
     ********************************************************************************/
    std::size_t imageSize() const noexcept;

    /********************************************************************************
     * @brief Provides the size of the kernel.
     * 
     * @return The kernel size an unsigned integer.
     ********************************************************************************/
    std::size_t kernelSize() const noexcept;

    /********************************************************************************
     * @brief Extracts features out of specified input image.
     * 
     * @param input Reference to the image to extract features from.
     ********************************************************************************/
    void feedforward(const std::vector<double>& input) noexcept;

    /********************************************************************************
     * @brief Calculates kernel and input error for optimization.
     * 
     * @param outputError Calculated input error of the next convolutional layer.
     ********************************************************************************/
    void backpropagate(const std::vector<double>& outputError) noexcept;

    /********************************************************************************
     * @brief Modifies the kernel parameters to increase the precision of the 
     *        feature extraction.
     * 
     * @param learningRate The adjustment rate of the kernel parameters (default = 1 %).
     ********************************************************************************/
    bool optimize(const double learningRate = 0.01) noexcept;

    ConvLayer1D()                              = delete; // No default constructor.
    ConvLayer1D(const ConvLayer1D&)            = delete; // No copy constructor.
    ConvLayer1D(ConvLayer1D&&)                 = delete; // No move constructor.
    ConvLayer1D& operator=(const ConvLayer1D&) = delete; // No copy assignment.
    ConvLayer1D& operator=(ConvLayer1D&&)      = delete; // No move assignment.

private:

    void initKernel(const std::size_t kernelSize) noexcept;
    void setInputPadded(const std::vector<double>& input) noexcept;
    std::size_t paddingCount() const noexcept;

    void calculateKernelError() noexcept;
    std::vector<double> pad(const std::vector<double>& data) noexcept;

    std::vector<double> myInputPadded; // Vector holding the padded input.
    std::vector<double> myKernel;      // Vector representing the layer's kernel/filter. 
    std::vector<double> myOutput;      // Vector holding the calculated output.
    std::vector<double> myInputError;  // Vector holding the calculated input error.
    std::vector<double> myKernelError; // Vector holding the calculated kernel error.
};

} // namespace ml