/********************************************************************************
 * @brief Implementation details for ATmega328P EEPROM driver.
 *
 * @note Don't include this file directly.
 ********************************************************************************/
#pragma once

#include "type_traits.h"

namespace driver 
{
namespace eeprom 
{
namespace
{
namespace detail 
{

// -----------------------------------------------------------------------------
template <typename T = uint8_t>
bool constexpr isAddressValid(const uint16_t address) 
{
	return address <= AddressWidth - sizeof(T);
}

// -----------------------------------------------------------------------------
void writeByte(const uint16_t address, const uint8_t data) 
{
    while (utils::read(EECR, EEPE));
	EEAR = address;
	EEDR = data;
	utils::globalInterruptDisable();
	utils::set(EECR, EEMPE);
	utils::set(EECR, EEPE);
    utils::globalInterruptEnable();
}

// -----------------------------------------------------------------------------
uint8_t readByte(const uint16_t address) 
{
    while (utils::read(EECR, EEPE));
	EEAR = address;
	utils::set(EECR, EERE);
	return EEDR;
}

} // namespace detail

// -----------------------------------------------------------------------------
template <typename T = uint8_t>
bool write(const uint16_t address, const T& data) 
{
    static_assert(type_traits::is_unsigned<T>::value, 
                  "EEPROM write only permitted for unsigned data types!");
    if (!detail::isAddressValid<T>(address)) { return false; }
	for (size_t i{}; i < sizeof(T); ++i)
     {
	    detail::writeByte(address + i, static_cast<uint8_t>(data >> (8 * i)));
	}
	return true;
}

// -----------------------------------------------------------------------------
template <typename T = uint8_t>
bool read(const uint16_t address, T& data) 
{
    static_assert(type_traits::is_unsigned<T>::value, 
                  "EEPROM read only permitted for unsigned data types!");
    if (!detail::isAddressValid<T>(address)) { return false; }
	data = {};
	for (size_t i{}; i < sizeof(T); ++i) {
	    data |= static_cast<T>(detail::readByte(address + i) << (8 * i));
	}
	return true;
}

} // namespace
} // namespace eeprom
} // namespace driver
