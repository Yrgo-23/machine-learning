/*******************************************************************************
 * @brief Demonstration of function templates, type traits and static assert.
 ******************************************************************************/
#include <iostream>
#include <type_traits>
#include <vector>

/*******************************************************************************
 * @brief Namespace containing type traits.
 ******************************************************************************/
namespace type_traits
{

/*******************************************************************************
 * @brief Type train for checking is a specific type T is of string type.
 * 
 * @tparam T The type to check.
 ******************************************************************************/
template <typename T>
struct is_string
{
    static const bool value{false};
};

/*******************************************************************************
 * @brief Overload for string type const char*.
 ******************************************************************************/
template <>
struct is_string<const char*>
{
   static const bool value{true};
};

/*******************************************************************************
 * @brief Overload for string type std::string.
 ******************************************************************************/
template <>
struct is_string<std::string>
{
   static const bool value{true};
};

} // namespace type_traits

/*******************************************************************************
 * @brief Namespace containing vector functions.
 ******************************************************************************/
namespace vector
{

/*******************************************************************************
 * @brief Prints content held by specified vector.
 * 
 * @tparam T The type of the content held by the vector.
 * 
 * @param data Reference to the vector in question.
 * @param ostream Reference to output stream (default = terminal print).
 ******************************************************************************/
template <typename T>
void print(const std::vector<T>& data, std::ostream& ostream = std::cout)
{
    static_assert(std::is_arithmetic<T>::value || type_traits::is_string<T>::value, 
        "Invalid type specified in function call to vector::print!");
    if (data.empty()) { return; }
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& i : data) { ostream << i << "\n"; }
    ostream << "--------------------------------------------------------------------------------\n\n";
}

} // namespace vector

/*******************************************************************************
 * @brief Prints contents held by vectors of different types by overloading
 *        function template vector::print.
 *  
 * @return Success code 0 upon termination of the program.
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