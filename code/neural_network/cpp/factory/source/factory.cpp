/*******************************************************************************
 * @brief Implementation details of machine learning factory.
 ******************************************************************************/
#include "dense_layer.h"
#include "factory.h"
#include "neural_network.h"
#include "utils.h"

namespace ml
{
namespace factory
{

// -----------------------------------------------------------------------------
std::unique_ptr<NeuralNetworkInterface> neuralNetwork(const std::size_t inputCount, 
                                                      const std::size_t hiddenNodesCount,
                                                      const std::size_t outputCount, 
                                                      const ActFunc actFuncHidden, 
                                                      const ActFunc actFuncOutput)
{
    return std::unique_ptr<NeuralNetworkInterface>{
        std::make_unique<NeuralNetwork>(inputCount, hiddenNodesCount, outputCount, 
                                        actFuncHidden,actFuncOutput)};
}

// -----------------------------------------------------------------------------
std::unique_ptr<DenseLayerInterface> denseLayer(const std::size_t nodeCount, 
                                                const std::size_t weightCount,
                                                const ActFunc actFunc)
{
    return std::unique_ptr<DenseLayerInterface>{
        std::make_unique<DenseLayer>(nodeCount, weightCount, actFunc)};
}

// -----------------------------------------------------------------------------
std::unique_ptr<ActFuncCalc> actFuncCalc(const ActFunc actFunc)
{
    return std::make_unique<ActFuncCalc>(actFunc);
}

// -----------------------------------------------------------------------------
std::vector<double> parameterVector(const std::size_t size, 
                                    const double startValue)
{
    return std::vector<double>(size, startValue);
}

// -----------------------------------------------------------------------------
std::vector<std::vector<double>> parameterVector(const std::size_t columnCount,
                                                 const std::size_t rowCount,
                                                 const double startValue)
{
    return std::vector<std::vector<double>>(columnCount, std::vector<double>(rowCount, startValue));
}

// -----------------------------------------------------------------------------
std::vector<double> randomParameterVector(const std::size_t size, 
                                          const double min, 
                                          const double max)
{
    std::vector<double> parameters{};
    utils::vector::initRandom<double>(parameters, size, min, max);
    return parameters;
}

// -----------------------------------------------------------------------------
std::vector<std::vector<double>> randomParameterVector(const std::size_t columnCount,
                                                       const std::size_t rowCount,
                                                       const double min, 
                                                       const double max)
{
    std::vector<std::vector<double>> parameters{};
    utils::vector::initRandom<double>(parameters, columnCount, rowCount, min, max);
    return parameters;
}

} // namespace factory
} // namespace ml