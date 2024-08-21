/*******************************************************************************
 * @brief Solution for exercise 1, 2024-08-21.
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

} // namespace vector

/*******************************************************************************
 * @brief Tests the vector::getSmallestInt function.
 * 
 * @return Success code 0 upon termination of the program.
 ******************************************************************************/
int main()
{
    const std::vector<int> v1{3, 6, 4, 8, 6, 8, -2, -1}; 
    const std::vector<int> v2{1, 2, -1, -1, 0};          
    const std::vector<int> v3{};   

    std::cout << "Smallest integer in v1: " << vector::getSmallestInt(v1) << "\n";
    std::cout << "Smallest integer in v2: " << vector::getSmallestInt(v2) << "\n";
    std::cout << "Smallest integer in v3: " << vector::getSmallestInt(v3) << "\n";
    return 0;
}