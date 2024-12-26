"""Demonstration of a two-dimensional convolutional layer trained with 3 x 3 image. The image size 
   is reduced via a pooling layer. The reduced image is flattened to one dimension via a flatten layer. 
   The flattened output could be used as input to a sequential dense layer in a neural network. 
"""
from conv_layer import ConvLayer2D, printMatrix
from pooling_layer import PoolingLayer2D
from flatten_layer import FlattenLayer

# ------------------------------------------------------------------------------
def main() -> None:
    """ Creates a two-dimensional convolutional layer with kernel size 2 x 2.
        The convolutional layer is fed with a 3 x 3 image. Kernel and input
        error values are calculated with error values from an arbitrary next layer. 
        The kernel parameters are then modified via optimization with a 1 % learning rate. 
 
        The image size is reduced to size 2 x 2 via a pooling layer. The output of the flattened layer 
        is flattened to one dimension via a flatten layer.
 
        The output and kernel of the convolutional layer are printed, along with the output of the 
        pooling layer and flatten layer respectively, before terminating the program.
    """
    matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    outputError = [[1, 1, 1], [1, 1, 1], [1, 1, 1]]
    convLayer = ConvLayer2D(2)
    poolingLayer = PoolingLayer2D(2)
    flattenLayer = FlattenLayer()

    convLayer.feedforward(matrix)
    convLayer.backpropagate(outputError)
    convLayer.optimize(0.001)
    convLayer.feedforward(matrix)

    poolingLayer.feedforward(convLayer.output())
    flattenLayer.feedforward(poolingLayer.output())

    printMatrix(convLayer.output())
    printMatrix(poolingLayer.output())
    flattenLayer.print()

# ------------------------------------------------------------------------------
if __name__ == "__main__":
    main()