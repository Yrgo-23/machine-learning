/*******************************************************************************
 * @brief Demonstration of dense layer usage in C.
 ******************************************************************************/
#include "dense_layer.h"

/*******************************************************************************
 * @brief Creates a dense layer consisting of two nodes and three weights
 *        per node. The dense layer is trained to dense layer to predict {2, 2} 
 *        when the input is {1, 1, 1} during 200 epochs. The result is printed
 *        in the terminal before terminating the program.
 * 
 * @return Success code 0 upon successful execution of the program. If the
 *         dense layer couldn't be created due to lack of memory, error code 1
 *         is returned.
 ******************************************************************************/
int main(void)
{
    struct dense_layer* d1 = dense_layer_new(2, 3, ACT_FUNC_RELU);
    if (!d1) { return 1; }

    const double input[]      = {1, 1, 1};
    const double output[]     = {2, 2};
    const size_t input_count  = sizeof(input) / sizeof(double);
    const size_t output_count = sizeof(output) / sizeof(double);

    for (size_t i = 0U; i < 200U; ++i)
    {
        dense_layer_feedforward(d1, input, input_count);
        dense_layer_backpropagate_output(d1, output, output_count);
        dense_layer_optimize(d1, input, input_count, 0.01);
    }

    dense_layer_print(d1, 0);
    dense_layer_delete(&d1);
    return 0;
}