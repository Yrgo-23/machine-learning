/********************************************************************************
 * @brief Implementation of a node for a neural network.
 ********************************************************************************/
#include <vector>
#include <iostream>

#include "node.h"

/********************************************************************************
 * @brief Trains neural node to predict {1} when it's inputs are set to {1, 0}.
 *        The node is trained for 1000 epochs with a learning rate of 10 %.
 *        The node output is printed before terminating the program.
 * 
 * @return Success code 0 upon termination of the program.
 ********************************************************************************/
int main() 
{
    const std::vector<double> input{1, 0};
    const double reference{1};
    ml::Node node{2U};

    for (std::size_t i{}; i < 1000U; ++i) 
    {
        node.feedforward(input);
        node.backpropagate(reference);
        node.optimize(input);
    }

    std::cout << "Output: " << node.output() << "\n";
    return 0;
}