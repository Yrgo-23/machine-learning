"""Implementation of neural networks."""
from dense_layer import DenseLayer, ActFunc, Random

class NeuralNetwork:
    """Class implementation of neural networks with a single hidden layer."""

    def __init__(self, input_count: int, hidden_nodes_count: int, output_count: int,
                 act_func_hidden: ActFunc = ActFunc.RELU, 
                 act_func_output: ActFunc = ActFunc.RELU) -> None:
        """Creates new neural network.
        
        :param input_count : The number of inputs in the neural network.
        :param hidden_nodes_count: The number of nodes in in the network's single hidden layer.
        :param output_count: The number of output in the neural network.
        :param act_func_hidden: Activation function of the hidden layer (default = ReLU).
        :param act_func_output: Activation function of the output layer (default = ReLU).
        """
        self._hidden_layer    = DenseLayer(hidden_nodes_count, input_count, act_func_hidden)
        self._output_layer    = DenseLayer(output_count, hidden_nodes_count, act_func_output)
        self._training_input  = []
        self._training_output = []
        self._training_order  = []

    def input_count(self) -> int:
        """Provides the number of inputs in the neural network.
        
        :return: The number of inputs as an integer.
        """
        return self._hidden_layer.weight_count()
    
    def hidden_nodes_count(self) -> int:
        """Provides the number of nodes in the network's hidden layer.
        
        :return: The number of hidden nodes as an integer.
        """
        return self._hidden_layer.node_count()
    
    def output_count(self) -> int:
        """Provides the number of outputs in the neural network.
        
        :return: The number of outputs as an integer.
        """
        return self._output_layer.node_count()
    
    def output(self) -> tuple[float]:
        """Provides the output of the neural network.
        
        :return: Tuple holding the output of the network.
        """
        return self._output_layer.output()

    def training_set_count(self) -> int:
        """Provides the number of stored training sets.
        
        :return: The number of training sets as an integer.
        """
        return len(self._training_order)
    
    def predict(self, input) -> tuple[float]:
        """Performs prediction based on given input.
        
        :param input: List holding the input on which to predict.
        
        :return: Tuple holding the predicted output.
        """
        self._feedforward(input)
        return self.output()

    def add_training_data(self, training_input: list[list[float]], 
                          training_output: list[list[float]]) -> None:
        """Adds sets of training data. 
        
        :param training_input: List holding training input.
        :param training_output: Lost holding training output.
        """
        if len(training_input) != len(training_output):
            raise ValueError(f"Non-matching training sets!")
        if len(training_input) == 0:
            raise ValueError(f"Empty training sets!")
        self._training_input  = training_input
        self._training_output = training_output
        self._training_order = list(range(len(self._training_input)))

    def train(self, epoch_count: int, learning_rate: float = 0.01) -> float:
        """Trains the neural network.
        
        :param epoch_count: The number of epochs to perform training.
        :param: learning_rate: The rate with witch to optimize the network parameters (default = 0.01).

        :return: The accuracy post training as a float in the range 0 - 1 , which corresponds to 0 - 100 %.
        """
        if epoch_count <= 0 or learning_rate <= 0:
            raise ValueError(f"Invalid training parameters!")
        for _ in range(epoch_count):
            Random.shuffle_list(self._training_order)
            for i in self._training_order:
                self._feedforward(self._training_input[i])
                self._backpropagate(self._training_output[i])
                self._optimize(self._training_input[i], learning_rate)
        return self.accuracy()
    
    def accuracy(self) -> float:
        """Provides the accuracy of the network by using the stored training data.
        
        :return: The accuracy as a float in the range 0 - 1, which corresponds to 0 - 100 %.
        """
        if self.training_set_count() == 0:
            return 0.0
        sum = 0.0
        for i in range(self.training_set_count()):
            sum += self._average_error(self._training_input[i], self._training_output[i])
        return 1.0 - sum / self.training_set_count()
    
    def print_results(self) -> None:
        """Prints training results in the terminal."""
        formatted_list = lambda list: ", ".join([f"{number:.1f}" for number in list])
        print(f"--------------------------------------------------------------------------------")
        print(f"Prediction accuracy: {self.accuracy() * 100:.1f} %\n")
        for i in range(self.training_set_count()):
            print(f"Input: [{formatted_list(self._training_input[i])}]", end=", ")
            print(f"prediction: [{formatted_list(self.predict(self._training_input[i]))}]", end=", ")
            print(f"reference: [{formatted_list(self._training_output[i])}]", end=", ")
            print(f"error: [{self._average_error(self._training_input[i], self._training_output[i]):.1f}]")
        print(f"--------------------------------------------------------------------------------\n")

    def _randomize_training_order(self) -> None:
        """Randomizes the order of the training sets for next epoch."""
        import random
        random.shuffle(self._training_order)

    def _feedforward(self, input: list[float]) -> None:
        """Performs feedforward to calculate new output for each node.
        
        :param input: List holding the network's current input.
        """
        self._hidden_layer.feedforward(input)
        self._output_layer.feedforward(self._hidden_layer.output())

    def _backpropagate(self, reference: list[float]) -> None:
        """Performs backpropagation to calculate new error for each node.
        
        :param reference: List holding the network's current reference values.
        """
        self._output_layer.backpropagate_output(reference)
        self._hidden_layer.backpropagate_hidden(self._output_layer)

    def _optimize(self, input: list[float], learning_rate: float) -> None:
        """Performs optimization by adjusting the network's parameters.
        
        :param input: List holding the network's current input.
        :param learning_rate: The rate to adjust the network's parameters.
        """
        self._hidden_layer.optimize(input, learning_rate)
        self._output_layer.optimize(self._hidden_layer.output(), learning_rate)

    def _average_error(self, input: list[float], reference: list[float]) -> float:
        """Calculates the average error for given training set.
        
        :param input: List holding training set input.
        :param reference: List holding training set output.

        :return: The average error of given training set as a float.
        """
        average = lambda data: abs(sum(data)) / len(data) if len(data) > 0 else 0.0
        prediction = self.predict(input)
        error_list = _subtract_lists(reference, prediction)
        return average(error_list)
    
def _subtract_lists(lst1: list[float], lst2: list[float]) -> list[float]:
    """Subtracts the content of two lists and provides the difference in another list.
    
    :param lst1: The first list.
    :param lst2: The second list.

    :return: List holding the difference between the numbers in the aforementioned lists.
    """
    difference = []
    for i in range(min(len(lst1), len(lst2))):
        difference.append(lst1[i] - lst2[i])
    return difference

def _average(data: list[float]) -> float:
    """Provides the average of numbers held by a list.
    
    :param data: List for which to calculate the average.

    :return: The calculated average value of the list.
    """
    return sum(data) / len(data) if len(data) > 0 else 0.0