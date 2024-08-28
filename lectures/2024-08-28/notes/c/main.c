/*******************************************************************************
 * @brief Demonstration of simple vector struct in C.
 ******************************************************************************/
#include <stdio.h>

#include "vector.h"

/*******************************************************************************
 * @brief Creates a vector holding ten integers 0 - 9.
 *        The vector content is printed in the terminal and to file "data.txt".
 * 
 * @return Success code 0 upon termination of the program.
 ******************************************************************************/
int main(void)
{
    struct int_vector v1 = {0, 0};
    FILE* ostream = fopen("data.txt", "w");

    for (int i = 0; i < 10; ++i)
    {
        int_vector_push_back(&v1, i);
    }

    int_vector_print(&v1, 0);
    int_vector_print(&v1, ostream);
    int_vector_clear(&v1);
    return 0;
}