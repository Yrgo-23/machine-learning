/*******************************************************************************
 * @brief Implementation of vector functions.
 ******************************************************************************/
#pragma once

#include <iostream>
#include <type_traits>
#include <vector>

#include "type_traits.h"

/** Namespace containing vector functions. */
namespace vector 
{

/*******************************************************************************
 * @brief Assigns number to the vector.
 * 
 * @tparam T The type of the vector.
 * 
 * @param data    Reference to the vector to assign.
 * @param newSize The size of the vector after the assignment.
 * @param startVal The first value to add in the vector (default = 0).
 * @param stepVal  The step value, i.e. the difference between each added
 *                 number (default = 1).
 * 
 * @note This function only works for arithmetic types.
 ******************************************************************************/
template <typename T>
void assign(std::vector<T>& data, const std::size_t newSize,
            const T startVal = 0, const T stepVal = 1)
{
     static_assert(std::is_arithmetic<T>::value, 
         "Function vector::assign supports arithmetic types only!\n");
     auto num{startVal}; 
     data.resize(newSize);

     for (auto& i : data)
     {
         i = num; 
         num += stepVal;   
     }
}

/*******************************************************************************
 * @brief Prints content held by vector.
 * 
 * @tparam T The type of the vector.
 * 
 * @param data    Reference to the vector.
 * @param ostream Reference to output stream (default = terminal print).
 * 
 * @note This function only works for arithmetic types and strings.
 ******************************************************************************/
template <typename T>
void print(const std::vector<T>& data, std::ostream& ostream = std::cout)
{
    static_assert(std::is_arithmetic<T>::value || type_traits::is_string<T>::value, 
         "Function vector::print supports arithmetic and string types only!\n");
    ostream << "[";
    for (std::size_t i{}; i < data.size(); ++i)
    {
        ostream << data[i];
        if (i != data.size() - 1) { ostream << ", "; }
    }
    ostream << "]\n";
}
} // namespace vector
