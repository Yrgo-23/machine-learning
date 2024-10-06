/*******************************************************************************
 * @brief Machine learning factory for creation of neural networks, 
 *        dense layers, etc.
 ******************************************************************************/
#pragma once

#include <memory>

#include "act_func_calc.h"
#include "dense_layer_interface.h"
#include "neural_network_interface.h"

namespace ml
{
namespace factory
{

/*******************************************************************************
 * @brief Creates new neural network.
 * 
 * @param inputCount       The number of inputs in the neural network.
 * @param hiddenNodesCount The number of nodes in in the network's single 
 *                         hidden layer.
 * @param outputCount      The number of output in the neural network.
 * @param actFuncHidden    Activation function of the hidden layer 
 *                         (default = ReLU).
 * @param actFuncOutput    Activation function of the output layer 
 *                         (default = ReLU).
 * 
 * @return Pointer to the new neural network.
 ******************************************************************************/
std::unique_ptr<NeuralNetworkInterface> neuralNetwork(const std::size_t inputCount, 
                                                      const std::size_t hiddenNodesCount,
                                                      const std::size_t outputCount, 
                                                      const ActFunc actFuncHidden = ActFunc::Relu, 
                                                      const ActFunc actFuncOutput = ActFunc::Relu);

/*******************************************************************************
 * @brief Creates new dense layer.
 *
 * @param nodeCount   The number of nodes in the new layer.
 * @param weightCount The number of weights per node in the new layer.
 * @param actFunc     The activation function of the layer (default = ReLU).
 * 
 * @return Pointer to the new dense layer.
 ******************************************************************************/
std::unique_ptr<DenseLayerInterface> denseLayer(const std::size_t nodeCount, 
                                                const std::size_t weightCount, 
                                                const ActFunc actFunc = ActFunc::Relu);

/*******************************************************************************
 * @brief Creates new activation function calculator.
 * 
 * @param actFunc The type of activation function to use for the calculations.
 * 
 * @return Pointer to the new activation function calculator.
 ******************************************************************************/
std::unique_ptr<ActFuncCalc> actFuncCalc(const ActFunc actFunc);

/*******************************************************************************
 * @brief Creates and initializes one-dimensional parameter vector.
 * 
 * @param size       The size of the vector.
 * @param startValue The starting value for each parameter (default = 0.0).
 * 
 * @return New initialized one-dimensional vector.
 ******************************************************************************/
std::vector<double> parameterVector(const std::size_t size, 
                                    const double startValue = 0.0);

/*******************************************************************************
 * @brief Creates and initializes two-dimensional parameter vector.
 * 
 * @param columnCount The number of columns of the vector.
 * @param rowCount    The number of rows of the vector.
 * @param startValue  The starting value for each parameter (default = 0.0).
 * 
 * @return New initialized two-dimensional vector.
 ******************************************************************************/
std::vector<std::vector<double>> parameterVector(const std::size_t columnCount,
                                                 const std::size_t rowCount,
                                                 const double startValue = 0.0);

/*******************************************************************************
 * @brief Creates one-dimensional parameter vector initialized with randomly 
 *        generated values in specified range [min, max].
 * 
 * @param size The size of the vector.
 * @param min  The minimum permitted random value (default = 0.0).
 * @param max  The maximum permitted random value (default = 1.0).
 * 
 * @return New one-dimensional parameter vector initialized with randomly 
 *         generated values.
 ******************************************************************************/
std::vector<double> randomParameterVector(const std::size_t size, 
                                          const double min = 0.0, 
                                          const double max = 1.0);

/*******************************************************************************
 * @brief Creates two-dimensional parameter vector initialized with randomly 
 *        generated values in range [min, max].
 * 
 * @param columnCount The number of columns of the vector.
 * @param rowCount    The number of rows of the vector.
 * @param min         The minimum permitted random value (default = 0.0).
 * @param max         The maximum permitted random value (default = 1.0).
 * 
 * @return New two-dimensional parameter vector initialized with randomly 
 *         generated values.
 ******************************************************************************/
std::vector<std::vector<double>> randomParameterVector(const std::size_t columnCount,
                                                       const std::size_t rowCount,
                                                       const double min = 0.0, 
                                                       const double max = 1.0);
} // namespace factory
} // namespace ml