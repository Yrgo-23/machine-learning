/********************************************************************************
 * @brief Implementation of two-dimensional convolutional layers to filter
 *        attributes from images.
 ********************************************************************************/
#pragma once

#include <vector>

namespace ml
{

/********************************************************************************
 * @brief Class for implementation of two-dimensional convolutional layers.
 *        The size of the images to filter is dynamic. The number of strides
 *        is always set to one and padding is used, hence the size of the filtered
 *        image is unchanged during feature extraction.
 * 
 *        This class is non-copyable and non-movable.
 ********************************************************************************/
class ConvLayer2D
{
public:

    /********************************************************************************
     * @brief Creates new convolutional layer.
     * 
     * @param kernelSize The size of the kernel used to filter the image.
     ********************************************************************************/
    explicit ConvLayer2D(const std::size_t kernelSize) noexcept;

    /********************************************************************************
     * @brief Deletes convolutional layer.
     ********************************************************************************/
    ~ConvLayer2D() noexcept = default;

    /********************************************************************************
     * @brief Provides the input image padded with zeros.
     * 
     * @return A reference to the padded input image.
     ********************************************************************************/
    const std::vector<std::vector<double>>& inputPadded() const noexcept;

    /********************************************************************************
     * @brief Provides the kernel used to filter the image.
     * 
     * @return A reference to the kernel.
     ********************************************************************************/
    const std::vector<std::vector<double>>& kernel() const noexcept;

    /********************************************************************************
     * @brief Provides the output of the convolutional layer, i.e. the attributes
     *        extracted from the input image.
     * 
     * @return A reference to the output of the convolutional layer.
     ********************************************************************************/
    const std::vector<std::vector<double>>& output() const noexcept;

    /********************************************************************************
     * @brief Provides the calculated kernel error used to optimize the layer.
     * 
     * @return A reference to the calculated kernel error.
     ********************************************************************************/
    const std::vector<std::vector<double>>& inputError() const noexcept;

    /********************************************************************************
     * @brief Provides the calculated input error used to optimize the previous
     *        convolutional layer (if there is any).
     * 
     * @return A reference to the calculated input error.
     ********************************************************************************/
    const std::vector<std::vector<double>>& kernelError() const noexcept;

    /********************************************************************************
     * @brief Provides the image width.
     * 
     * @return The image width an unsigned integer.
     ********************************************************************************/
    std::size_t imageWidth() const noexcept;

     /********************************************************************************
     * @brief Provides the image height.
     * 
     * @return The image height an unsigned integer.
     ********************************************************************************/
    std::size_t imageHeight() const noexcept;

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
    void feedforward(const std::vector<std::vector<double>>& input) noexcept;

    /********************************************************************************
     * @brief Calculates kernel and input error for optimization.
     * 
     * @param outputError Calculated input error of the next convolutional layer.
     ********************************************************************************/
    void backpropagate(const std::vector<std::vector<double>>& outputError) noexcept;

    /********************************************************************************
     * @brief Modifies the kernel parameters to increase the precision of the 
     *        feature extraction.
     * 
     * @param learningRate The adjustment rate of the kernel parameters (default = 1 %).
     ********************************************************************************/
    void optimize(const double learningRate = 0.01) noexcept;

    ConvLayer2D()                              = delete; // No default constructor.
    ConvLayer2D(const ConvLayer2D&)            = delete; // No copy constructor.
    ConvLayer2D(ConvLayer2D&&)                 = delete; // No move constructor.
    ConvLayer2D& operator=(const ConvLayer2D&) = delete; // No copy assignment.
    ConvLayer2D& operator=(ConvLayer2D&&)      = delete; // No move assignment.

private:
    void initKernel(const std::size_t kernelSize) noexcept;
    std::vector<std::vector<double>> pad(const std::vector<std::vector<double>>& input) noexcept;
    std::size_t paddingCount() const noexcept;

    static std::size_t width(const std::vector<std::vector<double>>& input) noexcept;
    static std::size_t height(const std::vector<std::vector<double>>& input) noexcept;

    std::vector<std::vector<double>> myInputPadded; // Vector holding the padded input.
    std::vector<std::vector<double>> myKernel;      // Vector representing the layer's kernel/filter. 
    std::vector<std::vector<double>> myOutput;      // Vector holding the calculated output.
    std::vector<std::vector<double>> myInputError;  // Vector holding the calculated input error.
    std::vector<std::vector<double>> myKernelError; // Vector holding the calculated kernel error.
};

} // namespace ml