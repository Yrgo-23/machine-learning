"""Implementation of convolutional layers for neural networks."""

# ------------------------------------------------------------------------------
def newMatrix(width: int, height: int, startVal: float = 0.0) -> list[list[float]]:
    """Creates a new matrix with given dimensions.

    :param width: The width of the new matrix.
    :param height: The height of the new matrix.
    :param startVal: Initial value of parameter in the matrix (default = 0.0).

    :return: The newly creates matrix.
    """
    assert width >= 0 and height >= 0, "Invalid matrix dimensions!"
    matrix = []
    for i in range(width):
        row = []
        for j in range(height):
            row.append(startVal)
        matrix.append(row)
    return matrix

# ------------------------------------------------------------------------------
def pad(matrix: tuple[tuple[float]], paddingCount: int = 1) -> list[list[float]]:
    """Pads given matrix.

    :param matrix: The matrix to copy.
    :param paddingCount: The number of pads per side of the matrix (default = 1).

    :return: A padded copy of given matrix.
    """
    assert len(matrix) > 0 and len(matrix[0]) > 0, "Invalid matrix dimensions!"
    assert paddingCount >= 0, "Invalid number of paddings specified!"
    padded = newMatrix(len(matrix) + paddingCount * 2, len(matrix[0]) + paddingCount * 2)
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            padded[i + paddingCount][j + paddingCount] = matrix[i][j]
    return padded

# ------------------------------------------------------------------------------
def roundMatrix(matrix: tuple[tuple[float]], decimalCount: int = 1) -> tuple[list[float]]:
    """Rounds the elements of given matrix.

    :param matrix: The matrix whose elements are to be rounded.
    :param decimalCount: The number of decimal places to round to (default = 1).

    :return: A rounded copy of given matrix.
    """
    assert len(matrix) > 0 and len(matrix[0]) > 0, "Invalid matrix dimensions!"
    assert decimalCount >= 0, "Invalid number of decimals for rounding!"
    rounded = matrix
    for i in range(len(rounded)):
        for j in range(len(rounded[0])):
            rounded[i][j] = round(rounded[i][j], decimalCount)
    return tuple(rounded) 

# ------------------------------------------------------------------------------
def printMatrix(matrix: tuple[tuple[float]], decimalCount: int = 1, end: str = "\n") -> None:
    """Prints the content of given matrix.

    :param matrix: The matrix whose content is to print.
    :param decimalCount: The number of decimals for which to print each element (default = 1).
    :param end: Ending characters (default = new line).
    """
    assert len(matrix) > 0 and len(matrix[0]) > 0, "Invalid matrix dimensions!"
    assert decimalCount >= 0, "Invalid number of decimals for rounding!"
    rounded = roundMatrix(matrix, decimalCount)
    print("--------------------------------------------------------------------------------", end="")
    for i in range(len(rounded)):
        print()
        for j in range(len(rounded[i])):
            print(rounded[j][i], end=" ")
    print("\n--------------------------------------------------------------------------------")

class ConvLayer2D:
    """Class implementation of two-dimensional convolutional layers."""

    # ------------------------------------------------------------------------------
    def __init__(self, kernelSize: int) -> None:
        """Creates new convolutional layer.

        :param kernelSize: The size of the layer's kernel/filter. Must be integral.
        """
        assert kernelSize > 0, "Kernel size must exceed 0!"
        self._inputPadded = []
        self._kernel = []
        self._output = []
        self._inputError = []
        self._kernelError = []
        self._initKernel(kernelSize)

    # ------------------------------------------------------------------------------
    def inputPadded(self) -> tuple[list[float]]:
        """Provides the convolutional layer's padded input.

        :return: Tuple holding the padded input of the convolutional layer.
        """
        return tuple(self._inputPadded)
    
    # ------------------------------------------------------------------------------
    def kernel(self) -> tuple[list[float]]:
        """Provides the convolutional layer's kernel/filter.

        :return: Tuple holding the kernel of the convolutional layer.
        """
        return tuple(self._kernel)
    
     # ------------------------------------------------------------------------------
    def output(self) -> tuple[list[float]]:
        """Provides the convolutional layer's filtered output.

        :return: Tuple holding the output of the convolutional layer.
        """
        return tuple(self._output)
    
     # ------------------------------------------------------------------------------
    def inputError(self) -> tuple[list[float]]:
        """Provides the convolutional layer's calculated input error.

        :return: Tuple holding the input error of the convolutional layer.
        """
        return tuple(self._inputError)
    
     # ------------------------------------------------------------------------------
    def kernelError(self) -> tuple[list[float]]:
        """Provides the convolutional layer's calculated kernel error.

        :return: Tuple holding the kernel error of the convolutional layer.
        """
        return tuple(self._kernelError)
    
    # ------------------------------------------------------------------------------
    def imageWidth(self) -> int:
        """Provides the convolutional layer's image width.

        :return: The image width of the convolutional layer as an integer.
        """
        return len(self._output)
    
    # ------------------------------------------------------------------------------
    def imageHeight(self) -> int:
        """Provides the convolutional layer's image height.

        :return: The image height of the convolutional layer as an integer.
        """
        return len(self._output[0]) if len(self._output) > 0 else 0
    
    # ------------------------------------------------------------------------------
    def kernelSize(self) -> int:
        """Provides the convolutional layer's kernel size.

        :return: The kernel size of the convolutional layer as an integer.
        """
        return len(self._kernel)
    
    # ------------------------------------------------------------------------------
    def paddingCount(self) -> int:
        """Provides the number of paddings used for the input of the convolutional layer.

        :return: The number of paddings used as an integer.
        """
        return self.kernelSize() // 2
    
    # ------------------------------------------------------------------------------
    def feedforward(self, input: tuple[tuple[float]]) -> None:
        """Performs feedforward with given input.

        :param input: Tuple holding the input for the feedforward operation.
        """
        assert len(input) > 0, "Invalid size of input matrix!"
        self._inputPadded = self._pad(input)
        self._output = newMatrix(len(input), len(input[0]))
        for i in range(self.imageWidth()):
            for j in range(self.imageHeight()):
                for k in range(self.kernelSize()):
                    for l in range(self.kernelSize()):
                        self._output[i][j] += self._inputPadded[i + k][j + l] * self._kernel[k][l]
    
    # ------------------------------------------------------------------------------
    def backpropagate(self, outputError: tuple[tuple[float]]) -> None:
        """Performs backpropagation with given output error.

        :param outputError: Tuple holding calculated output error.
        """
        assert len(outputError) >= 0 and len(outputError) == self.imageWidth() \
            and len(outputError[0]) == self.imageHeight(), "Invalid size of outputError matrix!"
        outputErrorPadded = self._pad(outputError)
        offset = self.kernelSize() - 1
        self._kernelError = newMatrix(self.kernelSize(), self.kernelSize())
        self._inputError = newMatrix(self.imageWidth(), self.imageHeight())
        for i in range(self.imageWidth()):
            for j in range(self.imageHeight()):
                for k in range(self.kernelSize()):
                    for l in range(self.kernelSize()):
                        self._kernelError[k][l] += self._inputPadded[i + k][j + l] * outputError[i][j]
                        self._inputError[i][j] += self._kernel[k][l] * \
                            outputErrorPadded[offset + i - k][offset + j - l]          
    
    # ------------------------------------------------------------------------------
    def optimize(self, learningRate: float = 0.01) -> None:
        """Performs optimization with given learning rate.

        :param learningRate: The rate used to modify the layer's parameters (default = 1 %).
        """
        assert learningRate > 0, "Learning rate must exceed 0!"
        for i in range(self.kernelSize()):
            for j in range(self.kernelSize()):
                self._kernel[i][j] += self._kernelError[i][j] * learningRate

    # ------------------------------------------------------------------------------
    def _initKernel(self, kernelSize: int) -> None:
        import random
        self._kernel = newMatrix(kernelSize, kernelSize)
        for i in range(kernelSize):
            for j in range(kernelSize):
                self._kernel[i][j] = random.random() * 10

    # ------------------------------------------------------------------------------
    def _pad(self, matrix: tuple[tuple[float]]) -> list[list[float]]:
        return pad(matrix, self.paddingCount())