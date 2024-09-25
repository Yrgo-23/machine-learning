/*******************************************************************************
 * @brief Demonstration of simple linear regression model in C.
 ******************************************************************************/
#include "lin_reg.h"

/*******************************************************************************
 * @brief Trains linear regression model to predict the pattern y = 2x + 2
 *        The model is trained until it's accuracy exceeds 99.00 %.
 *        The training result is printed in the terminal post training.
 * 
 * @return Success code 0 upon termination of the program. If the linear
 *         regression model couldn't be created due to lack of memory,
 *         error code 1 is returned.
 ******************************************************************************/
int main()
{
    const double input[]   = {0, 1, 2, 3, 4};
    const double output[]  = {2, 4, 6, 8, 10};
    const size_t set_count = sizeof(input) / sizeof(double);

    struct lin_reg* lin_reg = lin_reg_new(input, output, set_count);
    if (!lin_reg) { return 1; }

    while (lin_reg_train(lin_reg, 30U, 0.01) < 0.9999);
    lin_reg_print_results(lin_reg, 0);
    lin_reg_delete(&lin_reg);
    return 0;
}