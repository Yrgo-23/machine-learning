#include <fstream>
#include <iostream>
#include <vector>

namespace vector
{
  
/*******************************************************************************
 * @brief Assigns numbers to referenced vector.
 * 
 * @param numbers  Reference to vector to assign.
 * @param size     The desired size of the vector in number of elements.
 * @param startVal The value of the first element (default = 0).
 * @param stepVal  The difference between each added element (default = 1).
 ******************************************************************************/  
void assign(std::vector<int>& numbers, 
            const std::size_t size, 
            const int startVal = 0,
            const int stepVal = 1)
{
    numbers.resize(size);
    auto nextNumber{startVal};
    
    for (auto& number : numbers)
    {
        number = nextNumber;
        nextNumber += stepVal;
    }
}

/*******************************************************************************
 * @brief Prints numbers held by referenced vector. Each number is printed
 *        on a separate line.
 * 
 * @param numbers Reference to vector holding the numbers to print.
 * @param ostream Reference to output stream (default = terminal print).
 ******************************************************************************/
void print(const std::vector<int>& numbers, std::ostream& ostream = std::cout)
{
    if (numbers.empty()) { return; }
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& number : numbers)
    {
        ostream << number << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}
} // namespace vector

/*******************************************************************************
 * @brief Creates a vector holding twenty integers in the range [100, 198].
 *        The numbers are printed both in the terminal and to a file named 
 *        "numbers.txt".
 ******************************************************************************/
int main()
{
    std::vector<int> numbers{};
    std::ofstream ostream{"numbers.txt"};
    vector::assign(numbers, 50, 100, 2);
    vector::print(numbers);
    vector::print(numbers, ostream);
    return 0;
}