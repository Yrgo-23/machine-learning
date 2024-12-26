/********************************************************************************
 * @brief Implementation of flatten layers for conversion of two-dimensional 
 *        vectors to one dimension. The one-dimensional output can be used
 *        as input on a conventional neural network.
 ********************************************************************************/
#pragma once

#include <vector>

namespace ml
{

/********************************************************************************
 * @brief Class for implementation of flatten layers. The size of the vectors 
 *        to flatten is dynamic.
 * 
 *        This class is non-copyable and non-movable.
 ********************************************************************************/
class FlattenLayer
{
public:

    /********************************************************************************
     * @brief Creates new flatten layer.
     ********************************************************************************/
    FlattenLayer() noexcept;

    /********************************************************************************
     * @brief Deletes flatten layer.
     ********************************************************************************/
    ~FlattenLayer() noexcept = default;

    /********************************************************************************
     * @brief Creates new flatten layer and flattens referenced input.
     * 
     * @param input Reference to vector holding the input data to flatten.
     ********************************************************************************/
    FlattenLayer(const std::vector<std::vector<double>>& input) noexcept;

    /********************************************************************************
     * @brief Provides the one-dimensional output of the flatten layer.
     * 
     * @return Reference to vector holding the output of the flatten layer.
     ********************************************************************************/
    const std::vector<double>& output() const noexcept;

    /********************************************************************************
     * @brief Provides the error values from the next layer (which should be a
     *        dense layer).
     * 
     * @return Reference to vector holding the error values from next layer. 
     ********************************************************************************/
    const std::vector<double>& error() const noexcept;

    /********************************************************************************
     * @brief Flattens referenced input.
     * 
     * @param input Reference to vector holding the input data to flatten.
     ********************************************************************************/
    void feedforward(const std::vector<std::vector<double>>& input) noexcept;

    /********************************************************************************
     * @brief Stored error values from next layer (which should be a dense layer).
     * 
     * @param nextLayerError Reference to vector holding error values from next layer.
     ********************************************************************************/
    void backpropagate(const std::vector<double>& nextLayerError) noexcept;

    FlattenLayer(const FlattenLayer&)            = delete; // No copy constructor.
    FlattenLayer(FlattenLayer&&)                 = delete; // No move constructor.
    FlattenLayer& operator=(const FlattenLayer&) = delete; // No copy assignment.
    FlattenLayer& operator=(FlattenLayer&&)      = delete; // No move assignment.

private:

    std::vector<double> myOutput; // Vector holding the the flattened output.
    std::vector<double> myError;  // Vector holding the calculated error.
};

} // namespace ml