"""Implementation of flatten layers for neural networks."""

class FlattenLayer:
    """Class implementation of flatten layers."""

    # ------------------------------------------------------------------------------
    def __init__(self) -> None:
        """Creates a new flatten layer."""
        self._output = []

    # ------------------------------------------------------------------------------
    def output(self) -> tuple[float]:
        """Provides the layer's flattened output.

        :return: Tuple holding the output of the flatten layer.
        """
        return tuple(self._output)
    
    # ------------------------------------------------------------------------------
    def size(self) -> int:
        """Provides the size of the flatten layer in number of elements.

        :return: The size of the flatten layer as an integer.
        """
        return len(self._output)
    
    # ------------------------------------------------------------------------------
    def feedforward(self, input: tuple[tuple[float]]) -> None:
        """Performs feedforward with given input.

        :param input: Tuple holding the input for the feedforward operation.
        """
        assert len(input) > 0 and len(input[0]) > 0, "Invalid matrix dimensions!"
        self._output.clear()
        for row in input:
            for value in row:
                self._output.append(value)

            
    # ------------------------------------------------------------------------------
    def print(self, decimalCount: int = 1) -> None:
        """Prints the content of the flatten layer.

        :param decimalCount: The number of decimals for which to print each element (default = 1).
        """
        assert decimalCount >= 0, "Invalid number of decimals!"
        if self.size() == 0: return
        print("--------------------------------------------------------------------------------")
        for value in self._output:
            print(round(value, decimalCount), end = " ")
        print("\n--------------------------------------------------------------------------------\n")
