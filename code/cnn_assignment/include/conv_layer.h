/*******************************************************************************
 * @brief Implementation of convolutional layers.
 ******************************************************************************/  
#pragma once

#include <iostream>
#include <vector>

namespace ml
{

/*******************************************************************************
 * @brief Class implementation of one-dimensional convolutional layers.
 * 
 *        This class is non-copyable and non-movable.
 ******************************************************************************/  
class ConvLayer 
{
public:

    /*******************************************************************************
     * @brief Creates new convolutional layer.
     * 
     * @param imageSize  The size of the image in pixels.
     * @param kernelSize The size of the kernel in pixels.
     ******************************************************************************/
    explicit ConvLayer(const std::size_t imageSize, const std::size_t kernelSize);

    /*******************************************************************************
     * @brief Deletes convolutional layer.
     ******************************************************************************/
    ~ConvLayer() noexcept = default;

    /*******************************************************************************
     * @brief Provides the image currently being filtered by the convolutional layer.
     * 
     * @return Reference to vector holding the image currently being filtered.
     ******************************************************************************/
    const std::vector<std::vector<double>>& image() const noexcept;

    /*******************************************************************************
     * @brief Provides the convolutional layer's kernel/filter.
     * 
     * @return Reference to vector representing the kernel.
     ******************************************************************************/
    const std::vector<std::vector<double>>& kernel() const noexcept;

    /*******************************************************************************
     * @brief Provides the convolutional layer's filtered output. 
     * 
     * @return Reference to vector holding the filtered output. 
     ******************************************************************************/
    const std::vector<std::vector<double>>& output() const noexcept;

    /*******************************************************************************
     * @brief Provides the bias of the convolutional layer's kernel/filter.
     * 
     * @return The bias of the kernel as a double.
     ******************************************************************************/    
    double kernelBias() const noexcept;

    /*******************************************************************************
     * @brief Performs feedforward with given input.
     * 
     * @param input Reference to vector holding the input to use for the
     *              feedforward operation.
     * 
     * @return True if feedforward was performed, otherwise false.
     ******************************************************************************/    
    bool feedforward(const std::vector<std::vector<double>>& input) noexcept;

    /*******************************************************************************
     * @brief Prints the content of the convolutional layer.
     * 
     * @param ostream      Reference to output stream (default = terminal print).
     * @param decimalCount The number of decimal points to print each 
     *                     floating-point value with (default = 1).
     ******************************************************************************/    
    void print(std::ostream& ostream = std::cout, const int decimalCount = 1) const noexcept;

    /*******************************************************************************
     * @brief Prints content of two-dimensional matrix.
     * 
     * @param matrix       Reference to the matrix whose content is to be printed.
     * @param ostream      Reference to output stream (default = terminal print).
     * @param decimalCount The number of decimal points to print each 
     *                     floating-point value with (default = 1).
     * @param paddingCount The padding count of the matrix (default = 0).
     ******************************************************************************/    
    static void printMatrix(const std::vector<std::vector<double>>& matrix, std::ostream& ostream = std::cout,
                            const int decimalCount = 1, const std::size_t paddingCount = 0U) noexcept;

    ConvLayer()                            = delete; // No default constructor.
    ConvLayer(const ConvLayer&)            = delete; // No copy constructor.
    ConvLayer(ConvLayer&&)                 = delete; // No move constructor.
    ConvLayer& operator=(const ConvLayer&) = delete; // No copy assignment.
    ConvLayer& operator=(ConvLayer&&)      = delete; // No move assignment.

private:
    std::vector<std::vector<double>> myImage;  // Vector holding the image being filtered.
    std::vector<std::vector<double>> myKernel; // Vector representing the layer's kernel/filter.
    std::vector<std::vector<double>> myOutput; // Vector holding the layer's filtered output.
    double myKernelBias;                       // Kernel bias.
};

} // namespace ml
