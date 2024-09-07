"""
Linear regression implementation.
"""
import random

def _min(x: int | float, y: int | float) -> int | float:
    """Provides the minimum of two arithmetic values.
    
    :param x: The first value.
    :param y: The second value.
    """
    return x if x <= y else y

class LinReg:
    """Class implementation of linear regression model."""

    def __init__(self, training_input: list[float], training_output: list[float]) -> None:
        """Creates new linear regression model.

        :param training_input: List holding training input.
        :param training_output: List holding training output.

        """
        self._training_input  = training_input
        self._training_output = training_output
        self._training_order  = []
        self._bias            = self._random_start_val()
        self._weight          = self._random_start_val()
        self._check_training_sets()
        self._init_training_order()

    def training_input(self) -> tuple[float]:
        """Provides training input.

        :return: List holding training input
        """
        return tuple(self._training_input)
    
    def training_output(self) -> tuple[float]:
        """Provides training output.
        
        :return: List holding training output
        """
        return tuple(self._training_output)
    
    def bias(self) -> float:
        """Provides the model's bias.
        
        :return: Bias value as a floating point number.
        """
        return self._bias

    def weight(self) -> float:
        """Provides the model's weight.
        
        :return: The model's weight a floating point number.
        """
        return self._weight
    
    def set_count(self) -> int:
        """Provides the number of stored training sets.
        
        :return: The number of stored sets as an integer.
        """
        return len(self._training_order)
    
    def predict(self, input: float) -> float:
        """Performs prediction in regards to specified input.
        
        :param input: The input value to perform prediction with.
        
        :return: The predicted output as a floating point value.
        """
        return self._weight * input + self._bias
    
    def train(self, epoch_count: int, learning_rate: float = 0.01) -> float:
        """Trains the model during specified number of epochs.
        
        :param epoch_count: The number of epochs to train the model.
        :param learning_rate: The learning rate, which determines the adjustment (default = 1 %).

        :return: The model's accuracy post training as a floating point number between 0 - 1.
        """
        if self.set_count() == 0 or epoch_count <= 0 or learning_rate <= 0:
            return False
        for _ in range(epoch_count):
            self._randomize_training_order()
            for index in self._training_order:
                self._optimize(self._training_input[index], self._training_output[index], learning_rate)
        return self.accuracy()

    def accuracy(self) -> float:
        """Provides the model's accuracy post training.
        
        :return: The accuracy as a floating point number between 0 - 1.
        """
        if self.set_count() == 0:
            return 0
        error = 0
        for i in range(self.set_count()):
            error += abs(self._training_output[i] - self.predict(self._training_input[i]))
        return 1 - error / self.set_count()
    
    def print_results(self) -> None:
        """Prints post training results."""
        print_set = lambda x, y: print(
            f"Input: {x:.1f}    "
            f" reference: {y:.1f} \t\t" 
            f"prediction: {self.predict(x):.1f} \t"
            f"error: {y - self.predict(x):.1f}")
        print("--------------------------------------------------------------------------------")
        for i in range(self.set_count()):
            print_set(self._training_input[i], self._training_output[i])
        print("--------------------------------------------------------------------------------\n")
    
    def _check_training_sets(self) -> None:
        """Ensures that the size of the training sets match"""
        num_sets              = _min(len(self._training_input), len(self._training_output))
        self._training_input  = self._training_input[:num_sets]
        self._training_output = self._training_output[:num_sets]

    def _init_training_order(self) -> None:
        """Init list holding training order index."""
        for i in range(len(self._training_input)):
            self._training_order.append(i)

    def _randomize_training_order(self) -> None:
        """Randomizes training order."""
        for i in range(self.set_count()):
            r                       = random.randint(0, self.set_count() - 1)
            temp                    = self._training_order[i]
            self._training_order[i] = self._training_order[r]
            self._training_order[r] = temp

    def _optimize(self, input, reference, learning_rate) -> None:
        """Optimizes the model by adjusting the parameters.
        
        :param input: The model's input value.
        :param reference: The model's reference value.
        :param learning_rate: The learning rate, which determines the amount of adjustment.
        """
        if input == 0:
            self._bias = reference
        else:
            error        = reference - self.predict(input)
            self._bias   += error * learning_rate
            self._weight += error * learning_rate * input

    @staticmethod
    def _random_start_val() -> float:
        """
        Provides random number between 0 and 1.

        :return: A random floating point number between 0 and 1.
        """
        return random.random()