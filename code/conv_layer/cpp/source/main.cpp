/********************************************************************************
 * @brief Demonstration of a two-dimensional convolutional layer trained with
 *        a 3 x 3 image. The image size is reduced via a pooling layer. The
 *        reduced image is flattened to one dimension via a flatten layer. 
 *        The flattened output could be used as input to a sequential dense 
 *        layer in a neural network. 
 ********************************************************************************/
#include <iostream>
#include <vector>

#include "conv_layer_2d.h"
#include "conv_utils.h"
#include "flatten_layer.h"
#include "pooling_layer_2d.h"

using namespace ml::utils;

/********************************************************************************
 * @brief Creates a two-dimensional convolutional layer with kernel size 2 x 2.
 *        The convolutional layer is fed with a 3 x 3 image. Kernel and input
 *        error values are calculated with error values from an arbitrary next
 *        layer. The kernel parameters are then modified via optimization with 
 *        a 1 % learning rate. 
 * 
 *        The image size is reduced to size 2 x 2 via a pooling layer. 
 *        The output of the flattened layer is flattened to one dimension via 
 *        a flatten layer.
 * 
 *        The output and kernel of the convolutional layer are printed, along with
 *        the output of the pooling layer and flatten layer respectively, 
 *        before terminating the program.
 * 
 * @return Success code 0 upon termination of the program.
 ********************************************************************************/
int main()
{
    ml::ConvLayer2D convLayer{2U};
    ml::PoolingLayer2D poolingLayer{2U};
    ml::FlattenLayer flattenLayer{};
    const std::vector<std::vector<double>> input{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const std::vector<std::vector<double>> outputError(input.size(), 
        std::vector<double>(input.size(), 1));

    std::cout << "\nPadded input:\n";
    print(convLayer.inputPadded());
    std::cout << "Convolutional layer kernel before optimization:\n";
    print(convLayer.kernel(), 1);
    convLayer.feedforward(input);
    std::cout << "Convolutional layer output before optimization:\n";
    print(convLayer.output());

    convLayer.feedforward(input);
    convLayer.backpropagate(outputError);
    convLayer.optimize(0.01);
    convLayer.feedforward(input);
    poolingLayer.feedforward(convLayer.output());
    flattenLayer.feedforward(poolingLayer.output());

    std::cout << "Convolutional layer kernel after optimization:\n";
    print(convLayer.kernel(), 1U);
    std::cout << "Convolutional layer output after optimization:\n";
    print(convLayer.output());
    std::cout << "Pooling layer output:\n";
    print(poolingLayer.output());
    std::cout << "Flattened output:\n";
    print(flattenLayer.output());
    return 0;
}