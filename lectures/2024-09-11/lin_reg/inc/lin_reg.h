/*******************************************************************************
 * @brief Implementation of linear regression model.
 ******************************************************************************/
#pragma once

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

     LinReg() = delete; // Default constructor deleted.

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
     * @brief Performs prediction bases on input.
     * 
     * @param input The input for which to predict.
     ******************************************************************************/
    double predict(const double input) const;

private:
    std::vector<double> myTrainingInput;  // Training input.
    std::vector<double> myTrainingOutput; // Training output.
    double myBias;                        // Bias (m-value).
    double myWeight;                      // Weight (k-value).
};

} // namespace ml