/*******************************************************************************
 * @brief Demonstration of simple linear regression model in C++.
 ******************************************************************************/
#include <iostream>
#include <vector>

#include "lin_reg.h"

/*******************************************************************************
 * @brief Trains a linear regression model to predict the pattern y = 2x + 2.
 *        The results are printed in the terminal after training is completed.
 * 
 * @return Success code 0 upon termination of the program.
 ******************************************************************************/
int main()
{
    const std::vector<double> input{0, 1, 2, 3, 4};
    const std::vector<double> output{2, 4, 6, 8, 10};
    ml::LinReg linReg{input, output};
    linReg.train(10, 0.1); 

    for (const auto& x : input)
    {
        std::cout << "Input: " << x << ", "
            "prediction: " << linReg.predict(x) << "\n";
    }

    return 0;
}