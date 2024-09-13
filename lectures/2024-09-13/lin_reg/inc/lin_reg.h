/*******************************************************************************
 * @brief Implementation of linear regression model.
 ******************************************************************************/
#pragma once

#include <iostream>
#include <vector>

namespace ml
{

/*******************************************************************************
 * @brief Class implementation of linear regression model predicting 
 *        according to the equation y = kx + m.
 ******************************************************************************/
class LinReg
{
public:

     // Default constructor deleted.
     LinReg() = delete;

     /*******************************************************************************
      * @brief Creates a linear regression model.
      * 
      * @param trainingInput  Reference to vector holding training input.
      * @param trainingOutput Reference to vector holding training output.
      ******************************************************************************/
     LinReg(const std::vector<double>& trainingInput,
            const std::vector<double>& trainingOutput);

    /*******************************************************************************
     * @brief Provides training input.
     * 
     * @return Reference to vector holding training input.
     ******************************************************************************/
    const std::vector<double>& trainingInput() const;

    /*******************************************************************************
     * @brief Provides training output.
     * 
     * @return Reference to vector holding training input.
     ******************************************************************************/
    const std::vector<double>& trainingOutput() const;

    /*******************************************************************************
     * @brief Trains regression model.
     * 
     * @param epochCount   The number of epochs to train the model.
     * @param learningRate Learning rate to use (default = 1 %).
     ******************************************************************************/
     void train(const std::size_t epochCount, const double learningRate = 0.01);

    /*******************************************************************************
     * @brief Performs prediction based on input.
     * 
     * @param input The input for which to predict.
     ******************************************************************************/
    double predict(const double input) const;

    /*******************************************************************************
     * @brief Prints predictions based on inputs.
     * 
     * @param inputs       Reference to vector holding inputs for which to predict.
     * @param ostream      Reference to output stream (default = terminal print).
     * @param decimalCount The number of decimals for which to print numbers
     *                     (default = 1).
     ******************************************************************************/
    void printPredictions(const std::vector<double>& inputs, 
                          std::ostream& ostream = std::cout,
                          const std::size_t decimalCount = 1U);

private:

    /*******************************************************************************
     * @brief Performs optimization based on input and reference value.
     * 
     * @param input        The input for which to predict.
     * @param reference    The value we want the model to predict.
     * @param learningRate The adjustment rate of the parameters.
     ******************************************************************************/
    void optimize(const double input, const double reference, 
                  const double learningRate);

    /*******************************************************************************
     * @brief Randomizes vector holding the training order via index.
     ******************************************************************************/
    void randomizeTrainingOrder();

    std::vector<double> myTrainingInput;  // Training input.
    std::vector<double> myTrainingOutput; // Training output.
    std::vector<int> myTrainingOrder;     // Stores training order by index.
    double myBias;                        // Bias (m-value).
    double myWeight;                      // Weight (k-value).
};

} // namespace ml