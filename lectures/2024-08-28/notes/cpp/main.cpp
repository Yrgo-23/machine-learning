/*******************************************************************************
 * @brief Demonstration of simple vector implementation in C++.
 ******************************************************************************/
#include <fstream>

#include "vector.h"

/*******************************************************************************
 * @brief Creates vectors of different data types and prints the content
 *        in the terminal and to a file named "data.txt".
 * 
 * @tparam Success code 0 upon termination of the program.
 ******************************************************************************/
int main()
{
    std::ofstream ostream{"data.txt"};
    const yrgo::vector<int> v1{1, 2, 3, 4, 5};
    v1.print();
    v1.print(ostream);
    
    yrgo::vector<double> v2{};
    for (double i{}; i < 5.0; i += 0.5) { v2.push_back(i); }
    v2.print();
    v2.print(ostream);

    yrgo::vector<const char*> v3{"Hi there", "how are you?"};
    v3.print();
    v3.print(ostream);
    return 0;
}