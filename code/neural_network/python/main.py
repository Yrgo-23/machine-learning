"""Demonstration of a simple neural network."""
from neural_network import NeuralNetwork, ActFunc

def main() -> None:
    """Creates and initializes a small neural network, which is trained to detect a 2-bit XOR pattern. 
    
    The network consists of:
    - An input layer with two nodes.
    - A hidden layer with three nodes, using the hyperbolic tangent (tanh) as activation function.
    - An output layer with one node, using the ReLU (Rectified Linear Unit) as activation function.
    
    Training is performed until the network's accuracy exceeds 99,99 %. 
    Training results are printed in the terminal upon completion.
    """
    training_input       = [[0, 0], [0, 1], [1, 0], [1, 1]]
    training_output      = [[0], [1], [1], [0]]
    network              = NeuralNetwork(2, 3, 1, ActFunc.TANH)
    network.add_training_data(training_input, training_output)
    while network.train(1000) <= 0.9999:
        pass
    network.print_results()
    

# Calls the main function if this is the startup script of the application:
if __name__ == "__main__":
    main()