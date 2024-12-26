/********************************************************************************
 * @brief Implementation of two-dimensional pooling layers to reduce the size
 *        of images while keeping the sharpness.
 ********************************************************************************/
#pragma once

#include <vector>

namespace ml
{

/********************************************************************************
 * @brief Enumeration class representing available pooling types.
 ********************************************************************************/
enum class PoolType
{
    Max,     // Max pooling - The most significant attributes are stored.
    Average, // Average pooling - The average of the extracted attributes are stored.
};

/********************************************************************************
 * @brief Class for implementation of two-dimensional pooling layers.
 *        The size of the images to pool is dynamic. Both max pooling and
 *        average pooling is supported.
 * 
 *        This class is non-copyable and non-movable.
 ********************************************************************************/
class PoolingLayer2D
{
public:

    /********************************************************************************
     * @brief Creates new pooling layer.
     * 
     * @param size The size of the pooling layer.
     * @param type The pooling type to use (default = max pooling).
     ********************************************************************************/
    explicit PoolingLayer2D(const std::size_t size, const PoolType type = PoolType::Max) noexcept;

    /********************************************************************************
     * @brief Provides the pooling layer output.
     * 
     * @return Reference to a vector holding the pooling layer output.
     ********************************************************************************/
    const std::vector<std::vector<double>>& output() const noexcept;

    /********************************************************************************
     * @brief Provides the pooling layer type.
     * 
     * @return The pooling layer type as an enumerator of enumeration class PoolType.
     ********************************************************************************/
    PoolType type() const noexcept;

     /********************************************************************************
     * @brief Provides the pooling layer size.
     * 
     * @return The size of the pooling layer as an unsigned integer.
     ********************************************************************************/
    std::size_t size() const noexcept;
    
     /********************************************************************************
     * @brief Performs pooling of referenced input image.
     * 
     * @param input Reference to image to pool.
     * 
     * @return True if pooling was performed.
     ********************************************************************************/
    bool feedforward(const std::vector<std::vector<double>>& input) noexcept;

    PoolingLayer2D()                                 = delete; // No default constructor.
    PoolingLayer2D(const PoolingLayer2D&)            = delete; // No copy constructor.
    PoolingLayer2D(PoolingLayer2D&&)                 = delete; // No move constructor.
    PoolingLayer2D& operator=(const PoolingLayer2D&) = delete; // No copy assignment.
    PoolingLayer2D& operator=(PoolingLayer2D&&)      = delete; // No move assignment.

private:
    std::size_t paddingCount() const noexcept;
    bool isInputInValid(const std::vector<std::vector<double>>& input) noexcept;
    double pool(const std::vector<std::vector<double>>& input, const std::size_t j, 
                const std::size_t i) noexcept;
    double poolMax(const std::vector<std::vector<double>>& input, const std::size_t x, 
                   const std::size_t y) noexcept;
    double poolAverage(const std::vector<std::vector<double>>& input, const std::size_t x, 
                       const std::size_t y) noexcept;
    std::size_t iterationWidth(const std::vector<std::vector<double>>& input) noexcept;
    std::size_t iterationHeight(const std::vector<std::vector<double>>& input) noexcept;
    bool isWithinRange(const std::vector<std::vector<double>>& input, const std::size_t x, 
                       const std::size_t y) noexcept;

    std::vector<std::vector<double>> myOutput; // Vector holding the pooled output.
    const PoolType myType;                     // Pooling type used for this layer.
};

} // namespace ml