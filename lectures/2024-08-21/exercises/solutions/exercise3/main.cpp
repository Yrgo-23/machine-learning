/*******************************************************************************
 * @brief Solution for exercise 3, 2024-08-21.
 *******************************************************************************/
#include <fstream>
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

/*******************************************************************************
 * @brief Erases the smallest integer held by specified vector.
 *        Potential duplicates of the smallest integer are also removed.
 * 
 * @param data    Reference to the vector in question.
 ******************************************************************************/
void eraseSmallestInt(std::vector<int>& data)
{
    if (data.empty()) { return; }
    const auto smallest{vector::getSmallestInt(data)};

    while (1)
    {
        for (auto i{data.begin()}; i < data.end(); ++i) 
        {
            if (*i == smallest) { data.erase(i); }
        }
        if (smallest != vector::getSmallestInt(data)) { break; }
    }
}

} // namespace vector

/*******************************************************************************
 * @brief Removes the smallest integer (including duplicates) held by a 
 *        specific vector. The vector content is printed in the terminal
 *        and to a file named "numbers.txt".
 * 
 * @return Success code 0 upon termination of the program.
 *******************************************************************************/
int main()
{
    std::vector<int> numbers{1, 2, -5, 5, 4, 8, 9, 0, -3, -5, -5, -5, -2};
    std::ofstream ostream{"numbers.txt"};
    vector::eraseSmallestInt(numbers);
    vector::print(numbers);
    vector::print(numbers, ostream);
    return 0;
}