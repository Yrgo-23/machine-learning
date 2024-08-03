/********************************************************************************
 * @brief Contains miscellaneous utility functions for bit operations, 
 *        mathematical operations and generating delays.
 ********************************************************************************/
#pragma once

#define F_CPU 16000000UL

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "type_traits.h"

namespace utils 
{

/********************************************************************************
 * @brief Blocks the calling thread for the specified time measured in seconds.
 *
 * @param delayTimeS The time to block the thread in seconds.
 ********************************************************************************/
void delayS(const uint16_t& delayTimeS);

/********************************************************************************
 * @brief Blocks the calling thread for the specified time measured in 
 *        milliseconds.
 *
 * @param delayTimeMs The time to block the thread in milliseconds.
 ********************************************************************************/
void delayMs(const uint16_t& delayTimeMs);

/********************************************************************************
 * @brief Blocks the calling thread for the specified time measured in 
 *        microseconds.
 *
 * @param delayTimeUs The time to block the thread in microseconds.
 ********************************************************************************/
void delayUs(const uint16_t& delayTimeUs);

namespace 
{

/********************************************************************************
 * @brief Structure used for removing references in order to maintain value
 *        categories between function calls.
 ********************************************************************************/
template <typename T>
struct RemoveReference
{
    typedef T type;
};

/********************************************************************************
 * @brief Maintains the value category of specified value.
 *
 * @param value The value whose value category is to maintain.
 *
 * @return Specified value with maintained value category.
 ********************************************************************************/
template <typename T>
constexpr T&& forward(typename RemoveReference<T>::type& value);

/********************************************************************************
 * @brief Maintains the value category of specified value.
 *
 * @param value The value whose value category is to maintain.
 *
 * @return Specified value with maintained value category.
 ********************************************************************************/
template <typename T>
constexpr T&& forward(typename RemoveReference<T>::type&& value);

/********************************************************************************
 * @brief Enables interrupts globally.
 ********************************************************************************/
inline void globalInterruptEnable(void);

/********************************************************************************
 * @brief Disables interrupts globally.
 ********************************************************************************/
inline void globalInterruptDisable(void);

/********************************************************************************
 * @brief Sets specified bit of selected register.
 *
 * @param reg
 *        The destination register.
 * @param bit
 *        The specified bit to set.
 ********************************************************************************/
template <typename T = uint8_t>
constexpr void set(volatile T& reg, const uint8_t bit);

/********************************************************************************
 * @brief Sets specified bits of selected register.
 *
 * @param reg  The destination register.
 * @param bit  The first bit to set.
 * @param bits The others bits to set.
 ********************************************************************************/
template <typename T = uint8_t, typename... Bits>
constexpr void set(volatile T& reg, const uint8_t bit, const Bits&&... bits);

/********************************************************************************
 * @brief Clears specified bit of selected register.
 *
 * @param reg The destination register.
 * @param bit The specified bit to clear.
 ********************************************************************************/
template <typename T = uint8_t>
constexpr void clear(volatile T& reg, const uint8_t bit);

/********************************************************************************
 * @brief Clears specified bits of selected register.
 *
 * @param reg  The destination register.
 * @param bit  The first bit to clear.
 * @param bits The others bits to clear.
 ********************************************************************************/
template <typename T = uint8_t, typename... Bits>
constexpr void clear(volatile T& reg, const uint8_t bit, const Bits&&... bits);

/********************************************************************************
 * @brief Toggles specified bit of selected register.
 *
 * @param reg The destination register.
 * @param bit The specified bit to toggle.
 ********************************************************************************/
template <typename T = uint8_t>
constexpr void toggle(volatile T& reg, const uint8_t bit);

/********************************************************************************
 * @brief Toggles specified bits of selected register.
 *
 * @param reg  The destination register.
 * @param bit  The first bit to toggle.
 * @param bits The others bits to toggle.
 ********************************************************************************/
template <typename T = uint8_t, typename... Bits>
constexpr void toggle(volatile T& reg, const uint8_t bit, const Bits&&... bits);

/********************************************************************************
 * @brief Reads specified bit of selected register.
 *
 * @param reg The destination register.
 * @param bit The specified bit to read.
 *
 * @return True if the specified bit is high, else false.
 ********************************************************************************/
template <typename T = uint8_t>
constexpr bool read(const volatile T& reg, const uint8_t bit);

/********************************************************************************
 * @brief Reads specified bits of selected register.
 *
 * @param reg  The destination register.
 * @param bit  The first bit to read.
 * @param bits The other bits to read.
 *
 * @return True if at least one of the specified bits is high, else false.
 ********************************************************************************/
template <typename T = uint8_t, typename... Bits>
constexpr bool read(const volatile T& reg, const uint8_t bit, const Bits&&... bits);

/********************************************************************************
 * @brief Calculates the power of specified base and exponent, where
 *
 *                           power = base ^ exponent
 *
 * @param base     Specified base.
 * @param exponent Specified exponent.
 *
 * @return The corresponding power.
 ********************************************************************************/
template <typename T1 = double, typename T2 = double, typename T3 = double>
T3 power(const T1 base, const T2 exponent);

/********************************************************************************
 * @brief Rounds the specified number to the nearest integer.
 *
 * @param number The number to round.
 *
 * @return The corresponding rounded number.
 ********************************************************************************/
template <typename T1 = int32_t, typename T2 = double>
constexpr T1 round(const T2 value);

/********************************************************************************
 * @brief Allocates a new block of on the heap.
 *
 * @param size The size of the allocated block in number of elements it can hold
 *             (default = one element).
 *
 * @return A pointer to the allocated block at success, else a null pointer.
 ********************************************************************************/
template <typename T>
inline T* newMemory(const size_t size = 1);

/********************************************************************************
 * @brief Resizes referenced heap allocated block via reallocation.
 *
 * @param block    The block to resize.
 * @param new_size The new size of the allocated block, i.e. the number of
 *                 elements it can hold after reallocation.
 *
 * @return A pointer to the resized block at success, else a null pointer.
 ********************************************************************************/
template <typename T>
inline T* reallocMemory(T* block, const size_t new_size);

/********************************************************************************
 * @brief Deletes heap allocated block via deallocation. The pointer to the
 *        block is set to null after deallocation.
 *
 * @param block Reference to the block to delete.
 ********************************************************************************/
template <typename T>
inline void deleteMemory(T* &block);

/********************************************************************************
 * @brief Moves memory from specified source to a copy. The copy will gain
 *        ownership of the memory and the source will be emptied.
 *
 * @param source Reference to the source whose memory is moved.
 *
 * @return The copy of the source.
 ********************************************************************************/
template <typename T>
inline T move(T&& source);

} // namespace
} // namespace utils

#include "utils_impl.h"