/*******************************************************************************
 * @brief Implementation of neural node for machine learning applications.
 ******************************************************************************/
#pragma once

namespace ml
{

/*******************************************************************************
 * @brief Class implementation of neural node.
 ******************************************************************************/
class Node 
{
public:
    /*******************************************************************************
     * @brief Default constructor deleted.
     ******************************************************************************/

    /*******************************************************************************
     * @brief Creates new neural node and initializes the bias and weights.
     * 
     * @param weightCount The number of node weights.
     ******************************************************************************/

    /*******************************************************************************
     * @brief Provides the number of node weights.
     * 
     * @return The number of node weights as an unsigned integer.
     ******************************************************************************/

    /*******************************************************************************
     * @brief Provides the node weights.
     * 
     * @return Reference to vector holding the node weights.
     ******************************************************************************/

    /*******************************************************************************
     * @brief Provides the node bias.
     * 
     * @return The node bias as a floating-point number.
     ******************************************************************************/

    /*******************************************************************************
     * @brief Provides the current node error.
     * 
     * @return The current node error as a floating-point number.
     ******************************************************************************/

    /*******************************************************************************
     * @brief Provides the node output.
     * 
     * @return The node output as a floating-point number.
     ******************************************************************************/

    /*******************************************************************************
     * @brief Performs feedforward to update the node output.
     * 
     * @param input Reference to vector holding the new input values of the node.
     ******************************************************************************/

    /*******************************************************************************
     * @brief Performs backpropagation to calculate the current node error.
     * 
     * @param reference The reference value, i.e. the desired value of the output.
     ******************************************************************************/

    /*******************************************************************************
     * @brief Performs optimization to improve the models accuracy.
     * 
     * @param input        Reference to vector holding input values.
     * @param learningRate Learning rate for the optimization (default = 10 %).
     ******************************************************************************/

private:
    // Node weights.
    // Node bias.
    // Node error.
    // Node output.
};

} // namespace ml