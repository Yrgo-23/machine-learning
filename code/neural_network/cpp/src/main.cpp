/*******************************************************************************
 * @brief Dense layer test.
 ******************************************************************************/
#include <vector>

#include "dense_layer.h"

/*******************************************************************************
 * @brief Tests creating and training a dense layer.
 * 
 * @return Success code 0 upon termination of the program.
 ******************************************************************************/
int main()
{
    const std::vector<double> input{0, 0, 0};
    const std::vector<double> output{1};
    ml::DenseLayer denseLayer{1, 3};

    for (std::size_t i{}; i < 1001U; ++i)
    {
        denseLayer.feedforward(input);
        denseLayer.backpropagate(output);
        denseLayer.optimize(input);
    }
    denseLayer.print();
    return 0;
}