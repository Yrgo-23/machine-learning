/*******************************************************************************
 * @brief Implementation of custom type traits.
 ******************************************************************************/
#pragma once

#include <string>

/** @brief Namespace containing custom type traits. */
namespace type_traits
{

/*******************************************************************************
 * @brief Type type indicating if a type is string.
 * 
 * @param T The type to check.
 ******************************************************************************/
template <typename T>
struct is_string
{
    /** Value set to false for all non-string types. */
    static const bool value{false}; 
};

template <>
struct is_string<const char*>
{
    /** Value set to true for const char*. */
    static const bool value{true}; 
};

template <>
struct is_string<char*>
{
    /** Value set to true for char*. */
    static const bool value{true}; 
};

template <>
struct is_string<std::string>
{
    /** Value set to true for std::string. */
    static const bool value{true}; 
};

} // namespace type_traits
