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

    /*******************************************************************************
     * @brief Initializes training order by assigning the index of each training
     *        set to the training order vector.
     ******************************************************************************/
    void initTrainingOrder();

    /*******************************************************************************
     * @brief Randomizes the training order by shuffling the training order vector.
     ******************************************************************************/
    void randomizeTrainingOrder();

    /*******************************************************************************
     * @brief Optimizes the model by adjusting the model parameters. The model's
     *        performance is measured by comparing the predicted value for a given
     *        input with the corresponding reference value. The parameters are
     *        adjusted in accordance with the measured error.
     * 
     * @param input        The input for which to predict.
     * @param reference    Output reference, i.e. the value we want the model
     *                     to predict for given input.
     * @param learningRate Adjustment rate of the model's parameters.
     ******************************************************************************/
    void optimize(const double input, const double reference, const double learningRate);

    std::vector<std::size_t> myTrainingOrder;    // Vector holding the training order via index.
    const std::vector<double>& myTrainingInput;  // Reference to vector holding training input.
    const std::vector<double>& myTrainingOutput; // Reference to vector holding training output.
    double myWeight;                             // The weight of the model (k-value).
    double myBias;                               // The bias of the model (m-value).
};

} // namespace ml