#include <iostream>
#include <type_traits>
#include <vector>

namespace type_traits
{

/*******************************************************************************
 * @brief Type traits for checking if specified type is of string type.
 * 
 * @tparam T The type to check.
 * 
 * @param value True if type T is of string type, else false.
 *******************************************************************************/
template <typename T>
struct is_string
{
    static const bool value{false};
};

/*******************************************************************************
 * @brief Overload for is_string, where T = const char*.
 *******************************************************************************/
template <>
struct is_string<const char*>
{
    static const bool value{true};
};

/*******************************************************************************
 * @brief Overload for is_string, where T = std::string.
 *******************************************************************************/
template <>
struct is_string<std::string>
{
    static const bool value{true};
};
} // namespace type_traits

namespace vector
{
    
/*******************************************************************************
 * @brief Prints data held by referenced vector. 
 * 
 * @tparam T The type of the data held in the vector.
 * 
 * @param data Reference to vector holding the data to print.
 * @param ostream Reference to output stream (default = terminal print).
 ******************************************************************************/
template <typename T>
void print(const std::vector<T>& data, std::ostream& ostream = std::cout)
{
    static_assert(std::is_arithmetic<T>::value || type_traits::is_string<T>::value, 
        "Cannot print values other than numbers and text!");
    if (data.empty()) { return; }
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& element : data)
    {
        ostream << element << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}
} // namespace vector

/*******************************************************************************
 * @brief Prints content of vectors holding numbers and text via the 
 *        vector::print function template.
 ******************************************************************************/
int main()
{
    const std::vector<int> v1{1, 2, 3};
    const std::vector<double> v2{0.5, 1.5, 2.5};
    const std::vector<const char*> v3{"C++", "programming", "is", "fun!"};
    
    vector::print(v1);
    vector::print(v2);
    vector::print(v3);
    return 0;
}