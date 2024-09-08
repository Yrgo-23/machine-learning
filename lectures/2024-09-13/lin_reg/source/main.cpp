/*******************************************************************************
 * @brief Demonstration of simple linear regression model in C++ (in progress).
 ******************************************************************************/
#include <iomanip>
#include <iostream>
#include <vector>

#include "lin_reg.h"

/*******************************************************************************
 * @brief Trains linear regression model to predict the pattern y = 2x + 2
 *        The model predicts with 100 % precision after 30 epochs.
 * 
 * @return Success code 0 upon termination of the program.
 ******************************************************************************/
int main()
{
    const std::vector<double> input{0, 1, 2, 3, 4};
    const std::vector<double> output{2, 4, 6, 8, 10};
    ml::LinReg linReg{input, output};
    while (!linReg.train(30));
    linReg.printTrainingResult();
    return 0;
}