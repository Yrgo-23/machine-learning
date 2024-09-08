/*******************************************************************************
 * @brief Utility function testing.
 ******************************************************************************/
#include <vector>

#include "utils.h"

/*******************************************************************************
 * @brief Tests several utility functions.
 * 
 * @return Success code 0 upon termination of the program.
 ******************************************************************************/
int main()
{
    std::vector<double> numbers{};
    utils::vector::initRandom<double>(numbers, 10, 0, 1);
    utils::vector::print(numbers);
    utils::vector::shuffle(numbers);
    utils::vector::print(numbers);

    const std::vector<std::string> text{"Neural", "network", "implementation"};
    utils::vector::print(text);
    return 0;
}