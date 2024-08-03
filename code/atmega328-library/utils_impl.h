/********************************************************************************
 * @brief Implementation details of miscellaneous utility function templates.
 * 
 * @note Don't include this file directly.
 ********************************************************************************/
#pragma once

namespace utils
{
namespace
{

// -----------------------------------------------------------------------------
template <typename T>
constexpr T&& forward(typename RemoveReference<T>::type& value)
{
    return static_cast<T&&>(value);
}

// -----------------------------------------------------------------------------
template <typename T>
constexpr T&& forward(typename RemoveReference<T>::type&& value)
{
    return static_cast<T&&>(value);
}

// -----------------------------------------------------------------------------
inline void globalInterruptEnable(void) { asm("SEI"); }

// -----------------------------------------------------------------------------
inline void globalInterruptDisable(void) { asm("CLI"); }

// -----------------------------------------------------------------------------
template <typename T>
constexpr void set(volatile T& reg, const uint8_t bit)  
{
    static_assert(type_traits::is_unsigned<T>::value, 
        "Invalid data type used for bit manipulation!");
	reg |= (1ULL << bit);
}

// -----------------------------------------------------------------------------
template <typename T, typename... Bits>
constexpr void set(volatile T& reg, const uint8_t bit, const Bits&&... bits)  
{
    static_assert(type_traits::is_unsigned<T>::value, 
        "Invalid data type used for bit manipulation!");
    set(reg, bit);
	set(reg, forward<const Bits>(bits)...);
}

// -----------------------------------------------------------------------------
template <typename T>
constexpr void clear(volatile T& reg, const uint8_t bit)  
{
    static_assert(type_traits::is_unsigned<T>::value, 
        "Invalid data type used for bit manipulation!");
    reg &= ~(1ULL << bit);
}

// -----------------------------------------------------------------------------
template <typename T, typename... Bits>
constexpr void clear(volatile T& reg, const uint8_t bit, const Bits&&... bits)  
{
    static_assert(type_traits::is_unsigned<T>::value, 
        "Invalid data type used for bit manipulation!");
    clear(reg, bit);
	clear(reg, forward<const Bits>(bits)...);
}

// -----------------------------------------------------------------------------
template <typename T>
constexpr void toggle(volatile T& reg, const uint8_t bit)  
{
    static_assert(type_traits::is_unsigned<T>::value, 
        "Invalid data type used for bit manipulation!");
    reg ^= (1ULL << bit);
}

// -----------------------------------------------------------------------------
template <typename T, typename... Bits>
constexpr void toggle(volatile T& reg, const uint8_t bit, const Bits&&... bits)  
{
    toggle(reg, bit);
	toggle(reg, forward<const Bits>(bits)...);
}

// -----------------------------------------------------------------------------
template <typename T>
constexpr bool read(const volatile T& reg, const uint8_t bit)  
{
    static_assert(type_traits::is_unsigned<T>::value, 
        "Invalid data type used for bit manipulation!");
    return reg & (1ULL << bit);
}

// -----------------------------------------------------------------------------
template <typename T, typename... Bits>
constexpr bool read(const volatile T& reg, const uint8_t bit, const Bits&&... bits) 
{
    static_assert(type_traits::is_unsigned<T>::value, 
        "Invalid data type used for bit manipulation!");
    return read(reg, bit) | read(reg, forward<const Bits>(bits)...);
}

// -----------------------------------------------------------------------------
template <typename T1, typename T2, typename T3>
T3 power(const T1 base, const T2 exponent) 
{
	static_assert(type_traits::is_arithmetic<T1>::value &&
	              type_traits::is_arithmetic<T2>::value &&
	              type_traits::is_arithmetic<T3>::value,
	              "Calculation of power only possible for arithmetic types!");
	T1 num{1};
	for (uint16_t i{}; i < exponent; ++i) 
    {
	    num *= base;
    }
    return static_cast<T3>(num);
}

// -----------------------------------------------------------------------------
template <typename T1, typename T2>
constexpr T1 round(const T2 value) 
{
    static_assert(type_traits::is_integral<T1>::value && 
                  type_traits::is_arithmetic<T2>::value, 
	              "Rounding only possible for arithmetic types!");
    return static_cast<T1>(value + 0.5);
}

// -----------------------------------------------------------------------------
template <typename T>
inline T* newMemory(const size_t size) 
{
    return static_cast<T*>(malloc(sizeof(T) * size));
}

// -----------------------------------------------------------------------------
template <typename T>
inline T* reallocMemory(T* block, const size_t new_size) 
{
    return static_cast<T*>(realloc(block, sizeof(T) * new_size));
}

// -----------------------------------------------------------------------------
template <typename T>
inline void deleteMemory(T* &block) 
{
    free(block);
    block = nullptr;
}

// -----------------------------------------------------------------------------
template <typename T>
inline T move(T&& source) 
{
    T copy{source};
    source = {};
    return copy;
}

} // namespace
} // namespace utils