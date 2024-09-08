/*******************************************************************************
 * @brief Implementation of linear regression model.
 ******************************************************************************/
#pragma once

#include <iostream>
#include <vector>

namespace ml
{

/*******************************************************************************
 * @brief Class implementation of linear regression model.
 ******************************************************************************/
class LinReg
{
public:

    /*******************************************************************************
     * @brief Default destructor deleted.
     ******************************************************************************/
    LinReg() = delete;

    /*******************************************************************************
     * @brief Creates new linear regression model.
     * 
     * @param trainingInput  Reference to vector holding the training input.
     * @param trainingOutput Reference to vector holding the training output.
     ******************************************************************************/
    LinReg(const std::vector<double>& trainingInput, const std::vector<double>& trainingOutput);

    /*******************************************************************************
     * @brief Provides the number of available training sets.
     * 
     * @return The number of available training sets.
     ******************************************************************************/
    std::size_t trainingSetCount() const;

    /*******************************************************************************
     * @brief Performs prediction based on specified input.
     * 
     * @param input The input to predict with.
     * 
     * @return The predicted output.
     ******************************************************************************/
    double predict(const double input) const;

    /*******************************************************************************
     * @brief Trains the model with available training data.
     * 
     * @param epochCount   The number of epochs to train the model.
     * @param learningRate The learning rate to train with (default = 1 %).
     * 
     * @return The model's accuracy post training as a float between 0 - 1,
     *         which corresponds to 0 - 100 %.
     ******************************************************************************/
    double train(const std::size_t epochCount, const double learningRate = 0.01);

    /*******************************************************************************
     * @brief Provides the accuracy of the model based on available training data.
     * 
     * @return The accuracy as a floating point number between 0 - 1.
     ******************************************************************************/
    double accuracy() const;

    /*******************************************************************************
     * @brief Prints the training result.
     * 
     * @param ostream      Reference to output stream (default = terminal print).
     * @param decimalCount The number of decimals to print with (default = 1).
     ******************************************************************************/
    void printTrainingResult(std::ostream& ostream = std::cout,
                             const std::size_t decimalCount = 1U) const;

private:

    void initTrainingOrder();
    void randomizeTrainingOrder();
    void optimize(const double input, const double reference, const double learningRate);

    std::vector<std::size_t> myTrainingOrder;
    const std::vector<double>& myTrainingInput;
    const std::vector<double>& myTrainingOutput;
    double myWeight;
    double myBias;
};

} // namespace ml