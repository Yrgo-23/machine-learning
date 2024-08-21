/*******************************************************************************
 * @brief Program displaying the content covered during the lecture 2024-08-21.
 *******************************************************************************/
#include <iostream>
#include <vector>

/*******************************************************************************
 * @brief Implements all vector functions inside a namespace called vector.
 * 
 * @note Use prefix "vector" When calling any of these functions, i.e. type
 *       vector::print() to call the print function, vector::sort() to call
 *       the sort function etc.
 *******************************************************************************/
namespace vector
{

/*******************************************************************************
 * @brief Prints the content held by specified vector.
 * 
 * @param data Reference to the vector in question.
 ******************************************************************************/
void print(const std::vector<int>& data)
{
    std::cout << "--------------------------------------------------------------------------------\n";
    for (const auto& i : data)
    {
        std::cout  << i << "\n";
    }
    std::cout << "--------------------------------------------------------------------------------\n\n";
}

/*******************************************************************************
 * @brief Erases all instances of a specific number in referenced vector.
 * 
 * @param data   Reference to the vector in question.
 * @param number The number to erase.
 * 
 * @return The number of removed instances.
 ******************************************************************************/
std::size_t eraseNumber(std::vector<int>& data, const int number)
{
    std::size_t eraseCount{};
    while (1)
    {
        const auto eraseCountAtLoopStart{eraseCount};

        for (auto i{data.begin()}; i < data.end(); ++i)
        {
            if (*i == number) 
            { 
                data.erase(i); 
                eraseCount++;
            }
        }
        if (eraseCountAtLoopStart == eraseCount) { break; }
    }
    return eraseCount;
}

/*******************************************************************************
 * @brief Sorts vector in ascending order.
 * 
 * @param data Reference to the vector to sort. 
 *******************************************************************************/
void sort(std::vector<int>& data)
{
    for (std::size_t i{}; i < data.size() - 1U; ++i)
    {
        for (std::size_t j{i + 1U}; j < data.size(); ++j)
        {
            if (data[i] > data[j])
            {
                const auto temp{data[i]};
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
}

} // namespace

/*******************************************************************************
 * @brief Performs different vector operations and function calls.
 * 
 * @return Success code 0 upon termination of the program.
 *******************************************************************************/
int main()
{
    std::vector<int> data{1, 2, 3}; // Initializes vector with three values.
    data.push_back(100);            // Pushes the value 100 to the back of the vector.
    vector::print(data);            // Prints the vector content.

    data.pop_back();              // Removes the last value stored in the vector.
    data.erase(data.begin() + 1); // Erases the number at index 1.
    vector::print(data);          // Prints the vector content again.>

    std::cout << "Current size: " << data.size() << "\n\n"; // Prints the size of the vector.
    data.clear();                                           // Clears the vector.
    std::cout << "New size: " << data.size() << "\n\n";     // Prints the size of the vector.

    if (data.empty()) // Prints if the vector is empty or not.
    { 
        std::cout << "The vector is empty!\n\n"; 
    }
    else 
    { 
        std::cout << "The vector isn't empty!\n\n"; 
    }

    data.resize(10, 5);  // Resizes the vector to 10, sets new elements to 5.
    data[0] = 1000;      // Sets the first element of the vector to 500.
    data[1] = 500;       // Sets the second element of the vector to 1000.
    data[9] = 250;       // Sets the 10th element of the vector to 250.
    data[8] = 2000;      // Sets the 9th element of the vector to 2000.
    vector::print(data); // Prints the vector content once again.

    vector::sort(data);  // Sorts the vector in ascending order.
    vector::print(data); // Prints the vector content once again.

    vector::eraseNumber(data, 5);                   // Removes all 5's in the vector.
    vector::print(data);                            // Prints the vector content once again.
    data.erase(data.begin() + 1, data.begin() + 3); // Removes elements at index 1 - 2.
    vector::print(data);                            // Prints the vector content one final time.
    return 0;
}