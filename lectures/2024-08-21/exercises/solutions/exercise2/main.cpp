/*******************************************************************************
 * @brief Solution for exercise 2, 2024-08-21.
 *******************************************************************************/
#include <iostream>
#include <vector>

namespace vector
{

/*******************************************************************************
 * @brief Provides the smallest integer held by specified vector.
 * 
 * @param data Reference to the vector in question.
 * 
 * @return The smallest integer in the vector (or 0 if the vector is empty).
 ******************************************************************************/
int getSmallestInt(const std::vector<int>& data)
{
    if (data.empty()) { return 0; }
    auto smallest{data[0U]};
    
    for (const auto& num : data)
    {
        if (num < smallest) { smallest = num; }
    }
    return smallest;
}

/*******************************************************************************
 * @brief Prints the content held by specified vector.
 * 
 * @param data    Reference to the vector in question.
 * @param ostream Reference to output stream (default = terminal print).
 ******************************************************************************/
void print(const std::vector<int>& data, std::ostream& ostream = std::cout)
{
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& i : data)
    {
        ostream << i << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}
} // namespace vector

/*******************************************************************************
 * @brief Removes the smallest integer held by a specific vector.
 * 
 * @return Success code 0 upon termination of the program.
 *******************************************************************************/
int main()
{
    std::vector<int> numbers{1, 2, 5, 4, 8, 9, 0, -3, -5, -2};
    const auto smallest{vector::getSmallestInt(numbers)};

    for (auto i{numbers.begin()}; i < numbers.end(); ++i) 
    {
        if (*i == smallest) { numbers.erase(i); }
    }

    vector::print(numbers);
    return 0;
}