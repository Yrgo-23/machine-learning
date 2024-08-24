/********************************************************************************
 * @brief Implementation type traits for static checking of data types.
 ********************************************************************************/
#pragma once

#include <stdint.h>

namespace type_traits 
{

/********************************************************************************
 * @brief Indicates if specified type T is of unsigned integral type.
 *
 * @param value Constant set to true for unsigned integral types, 
 *              false for everything else.
 ********************************************************************************/
template <typename T>
struct is_unsigned 
{
    static const bool value{false};
};

/********************************************************************************
 * @brief Declares bool as a valid unsigned integral type.
 ********************************************************************************/
template <>
struct is_unsigned<bool> 
{
   static const bool value{true};
};

/********************************************************************************
 * @brief Declares uint8_t as a valid unsigned integral type.
 ********************************************************************************/
template <>
struct is_unsigned<uint8_t> 
{
    static const bool value{true};
};

/********************************************************************************
 * @brief Declares uint16_t as a valid unsigned integral type.
 ********************************************************************************/
template <>
struct is_unsigned<uint16_t> 
{
    static const bool value{true};
};

/********************************************************************************
 * @brief Declares uint32_t as a valid unsigned integral type.
 ********************************************************************************/
template <>
struct is_unsigned<uint32_t> 
{
    static const bool value{true};
};

/********************************************************************************
 * @brief Declares uint64_t as a valid unsigned integral type.
 ********************************************************************************/
template <>
struct is_unsigned<uint64_t> 
{
    static const bool value{true};
};

/********************************************************************************
 * @brief Indicates if specified type T is of signed integral type.
 *
 * @param value Constant set to true for signed integral types, 
 *              false for everything else.
 ********************************************************************************/
template <typename T>
struct is_signed 
{
    static const bool value{false};
};

/********************************************************************************
 * @brief Declares int8_t as a valid signed integral type.
 ********************************************************************************/
template <>
struct is_signed<int8_t> 
{
    static const bool value{true};
};

/********************************************************************************
 * @brief Declares int16_t as a valid signed integral type.
 ********************************************************************************/
template <>
struct is_signed<int16_t> 
{
    static const bool value{true};
};

/********************************************************************************
 * @brief Declares int32_t as a valid signed integral type.
 ********************************************************************************/
template <>
struct is_signed<int32_t> 
{
    static const bool value{true};
};

/********************************************************************************
 * @brief Declares int64_t as a valid signed integral type.
 ********************************************************************************/
template <>
struct is_signed<int64_t> 
{
    static const bool value{true};
};

/********************************************************************************
 * @brief Indicates if specified type T is of integral type, which encompasses
 *        both signed and unsigned integers.
 *
 * @param value Constant set to true for integral types, false for 
 *              everything else.
 ********************************************************************************/
template <typename T>
struct is_integral 
{
    static const bool value{is_unsigned<T>::value || is_signed<T>::value};
};

/********************************************************************************
 * @brief Indicates if specified type T is of floating-point type.
 *
 * @param value Constant set to true for floating-point types, false for
 *              everything else.
 ********************************************************************************/
template <typename T>
struct is_floating_point 
{
    static const bool value{false};
};

/********************************************************************************
 * @brief Declares float as a valid floating-point type.
 ********************************************************************************/
template <>
struct is_floating_point<float> 
{
    static const bool value{true};
};

/********************************************************************************
 * @brief Declares double as a valid floating-point type.
 ********************************************************************************/
template <>
struct is_floating_point<double> 
{
    static const bool value{true};
};

/********************************************************************************
 * @brief Indicates if specified type T is of arithmetic type, i.e. integral
 *        or floating-point type.
 *
 * @param value Constant set to true for arithmetic types, false for
 *              everything else.
 ********************************************************************************/
template <typename T>
struct is_arithmetic 
{
    static const bool value{is_integral<T>::value || is_floating_point<T>::value};
};

/********************************************************************************
 * @brief Indicates if specified type T is of string type.
 * 
 * @tparam T The type to check.
 *
 * @param value Constant set to true for string types, false for everything else.
 ********************************************************************************/
template <typename T>
struct is_string
{
    static const bool value{false};
};

/********************************************************************************
 * @brief Declares const char* as a valid string type.
 ********************************************************************************/
template <>
struct is_string<const char*> 
{
    static const bool value{true};
};

/********************************************************************************
 * @brief Declares char* as a valid string type.
 ********************************************************************************/
template <>
struct is_string<char*> 
{
    static const bool value{true};
};

/******************************************************************************** 
 * @brief Indicates if specified type T is a pointer.
 * 
 * @tparam T The type to check.
 *
 * @param value Constant set to true for pointers, false for everything else.
 ********************************************************************************/
template <typename T>
struct is_pointer
{
    static const bool value{false};
};

/********************************************************************************
 * @brief Declares all pointer types to be pointers.
 * 
 * @param T The pointer type.
 ********************************************************************************/
template <typename T>
struct is_pointer<T*>
{
    static const bool value{true};
};

/********************************************************************************
 * @brief Indicates if specified type T is a reference.
 * 
 * @tparam T The type to check.
 *
 * @param value Constant set to true for references, false for everything else.
 ********************************************************************************/
template <typename T>
struct is_reference
{
    static const bool value{false};
};

/********************************************************************************
 * @brief Declares all reference types to be references.
 * 
 * @param T The reference type.
 ********************************************************************************/
template <typename T>
struct is_reference<T&>
{
    static const bool value{true};
};

} // namespace type_traits
