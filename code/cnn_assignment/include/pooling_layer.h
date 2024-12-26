/*******************************************************************************
 * @brief Implementation of pooling layers.
 ******************************************************************************/  
#pragma once

#include <iostream>
#include <vector>

namespace ml
{

/*******************************************************************************
 * @brief Class implementation of pooling layers.
 * 
 *        This class is non-copyable and non-movable.
 ******************************************************************************/  
class PoolingLayer
{
public:

    /*******************************************************************************
     * @brief Enum class representing the available pooling types.
     ******************************************************************************/ 
    enum class Type 
    { 
        Max,     // Max pooling - The most significant attributes are stored.
        Average, // Average pooling - The average of the extracted attributes are stored.
    };

    /*******************************************************************************
     * @brief Creates new pooling layer.
     * 
     * @param size   The size of the pooling layer in pixels (default = 2).
     * @param stride The number of pixels to move across the input matrix when 
     *               pooling (default = 1).
     ******************************************************************************/
    explicit PoolingLayer(const std::size_t size = 2U, const std::size_t stride = 1U);

    /*******************************************************************************
     * @brief Deletes pooling layer.
     ******************************************************************************/
    ~PoolingLayer() noexcept = default;

    /*******************************************************************************
     * @brief Performs feedforward operation with given input matrix.
     * 
     * @param input Reference to input matrix used for the feedforward operation.
     * @param poolingType The pooling type to used (default = max pooling).
     * 
     * @return True if feedforward was performed, otherwise false.
     ******************************************************************************/
    bool feedforward(const std::vector<std::vector<double>>& input,
                     const Type poolingType = Type::Max) noexcept;

    /*******************************************************************************
     * @brief Prints the content of the pooling layer.
     * 
     * @param ostream      Reference to output stream (default = terminal print).
     * @param decimalCount The number of decimal points to print each 
     *                     floating-point value with (default = 1).
     ******************************************************************************/    
    void print(std::ostream& ostream = std::cout, const int decimalCount = 1) const noexcept;

    PoolingLayer()                               = delete; // No default constructor.
    PoolingLayer(const PoolingLayer&)            = delete; // No copy constructor.
    PoolingLayer(PoolingLayer&&)                 = delete; // No move constructor.
    PoolingLayer& operator=(const PoolingLayer&) = delete; // No copy assignment.
    PoolingLayer& operator=(PoolingLayer&&)      = delete; // No move assignment.

private:   
    std::vector<std::vector<double>> myOutput; // Vector holding the pooled output.
    std::size_t myStride;                      // The stride to use when pooling.
};

} // namespace ml