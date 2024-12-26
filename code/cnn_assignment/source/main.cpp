/*******************************************************************************
 * @brief Test code for assignment involving convolutional and pooling layers.
 ******************************************************************************/  
#include "conv_layer.h"
#include "pooling_layer.h"
 
/********************************************************************************
 * @brief Creates a 5 x 5 convolutional layer with a 3 x 3 kernel. 
 *        The convolutional layer is fed with a 5 x 5 image. 
 * 
 *        The filtered image size is reduced to size 3 x 3 via a pooling layer. 
 *        
 *        The output and kernel of the convolutional layer are printed, along with
 *        the output of the pooling layer, before terminating the program.
 * 
 * @return Success code 0 upon termination of the program.
 ********************************************************************************/
int main(void) 
{
    const std::vector<std::vector<double>> input{{0, 1, 2, 4, 5}, 
                                                 {6, 7, 8, 9, 10}, 
                                                 {-1, 0, 5, 2, 6},
                                                 {10, 15, 2, 6, 8}, 
                                                 {34, 3, 2, 5.6, 7}};
    ml::ConvLayer conv1{5U, 3U};
    ml::PoolingLayer pool1{3U, 1U};
    conv1.feedforward(input);
    conv1.print();
    pool1.feedforward(conv1.output());
    pool1.print();
    return 0;
}
