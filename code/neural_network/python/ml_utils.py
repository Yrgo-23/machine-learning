"""Miscellaneous utilities for machine learning applications."""
from enum import Enum
from typing import Union, List
import math
import random

class ActFunc(Enum):
    """Activation functions layers in neural networks"""
    RELU = 0
    TANH = 1

    def __str__(self):
        """Provide the ActFunc enumerator as text.
        
        :return: The ActFunc enumerator as a string.
        """
        return self.name

class Math:
    """Class holding static methods for mathematical operations"""

    @staticmethod
    def relu(number: float) -> float:
        """Provides the Rectified Linear Unit (ReLU) activation for a given input.
        
        :param number: The number for which to calculate the Relu.

        :return: The ReLU activation as a float.
        """
        return number if number > 0.0 else 0.0
    
    @staticmethod
    def relu_gradient(number: float) -> float:
        """Provides the gradient of the Rectified Linear Unit (ReLU) function for a given input.
        
        :param number: The number for which to calculate the ReLU gradient.

        :return: The ReLU gradient as a float.
        """
        return 1.0 if number > 0.0 else 0.0
    
    @staticmethod
    def tanh(number: float) -> float:
        """Provides the hyperbolic tangent (tanh) for a given input.

        :param number: The number for which to calculate the hyperbolic tangent.

        :return: The hyperbolic tangent as a float.
        """
        return math.tanh(number)
    
    @staticmethod
    def tanh_gradient(number: float) -> float:
        """Provides the gradient of the hyperbolic tangent (tanh) for a given input.

        :param number: The number for which to calculate the gradient of the hyperbolic tangent.

        :return: The gradient of the hyperbolic tangent as a float.
        """
        return 1.0 - pow(math.tanh(number), 2)
    
    @staticmethod
    def act_func_output(number: float, actFunc: ActFunc) -> float:
        """Provides the activation function output for a given input.
        
        :param number: The number for which to calculate the activation function output.
        :param actFunc: The activation function used.

        :return: The activation function output as a float.
        """
        return Math.relu(number) if actFunc == ActFunc.RELU else Math.tanh(number)
    
    @staticmethod
    def act_func_gradient(number: float, actFunc: ActFunc) -> float:
        """Provides the activation function gradient for a given input.
        
        :param number: The number for which to calculate the activation function gradient.
        :param actFunc: The activation function used.

        :return: The activation function gradient as a float.
        """
        return Math.relu_gradient(number) if actFunc == ActFunc.RELU else Math.tanh_gradient(number)

class Random:
    """Class holding static methods for generating random numbers"""

    @staticmethod
    def number(min:  Union[int, float] = 0, max:  Union[int, float] = 100) ->  Union[int, float]:
        """Provides a random number in specified range.
        
        :param min: The minimum number of specified range (default = 0).
        :param max: The maximum number of specified range (default = 100).

        :return: Random number in specified range [min, max].
        """
        if min > max:
            raise ValueError("Cannot generate random number when min is more than max!")
        return random.uniform(min, max) if isinstance(min, float) or isinstance(max, float) else random.randint(min, max)

    @staticmethod
    def list(size: int, min: Union[int, float] = 0, max: Union[int, float]= 100) -> list[Union[int, float]]:
        """Provides new one-dimensional list holding random numbers in specified range.
        
        :param size: The size of the new list.
        :param min: The minimum number of specified range (default = 0).
        :param max: The maximum number of specified range (default = 100).

        :return: List holding random numbers in specified range [min, max].
        """
        return [Random.number(min, max) for _ in range(size)]
    
    @staticmethod
    def list_2d(row_count: int, column_count: int, min: Union[int, float] = 0, 
                max: Union[int, float] = 100) -> List[List[Union[int, float]]]:
        """Provides new two-dimensional list holding random numbers in specified range.
        
        :param row_count: The row of columns of the new list.
        :param column_count: The number of columns of the new list.
        :param min: The minimum number of specified range (default = 0).
        :param max: The maximum number of specified range (default = 100).

        :return: List holding random numbers in specified range [min, max].
        """
        return [Random.list(column_count, min, max) for _ in range(row_count)]
    
    @staticmethod
    def shuffle_list(lst: List[Union[int, float]]) -> None:
        """Shuffles the content of a list.
        
        :param list: The list to shuffle.
        """
        random.shuffle(lst)
