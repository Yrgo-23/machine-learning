#include <fstream>
#include <iostream>
#include <type_traits>
#include <vector>

namespace vector
{

/*******************************************************************************
 * @brief Assigns number to a vector.
 * 
 * 
 ******************************************************************************/
template <typename T>
void assign(std::vector<T>& data, const std::size_t size,
            const T startVal = 0, const T stepVal = 1)
{
     static_assert(std::is_arithmetic<T>::value, 
         "Cannot assign non-arithmetic values in vector::assign!\n");
     auto num{startVal}; 
     data.resize(size);

     for (auto& i : data)
     {
         i = num; 
         num += stepVal;   
     }
}

template <typename T>
void print(const std::vector<T>& data, std::ostream& ostream = std::cout)
{
    ostream << "[";
    for (std::size_t i{}; i < data.size(); ++i)
    {
        ostream << data[i];
        if (i != data.size() - 1) { ostream << ", "; }
    }
    ostream << "]\n";
}

} // namespace vector

int main()
{
    std::vector<int> v1{};
    std::vector<double> v2{};
    std::ofstream ostream{"data.txt"};

    vector::assign(v1, 20);
    vector::assign(v2, 10, 0.0, 0.5);
    vector::print(v1);
    vector::print(v1, ostream);
}