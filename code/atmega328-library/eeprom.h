/********************************************************************************
 * @brief Driver for utilization of the ATmega328P EEPROM.
 ********************************************************************************/
#pragma once

#include "utils.h"

namespace driver 
{
namespace eeprom 
{
namespace 
{

/********************************************************************************
 * @brief Parameters for the EEPROM memory.
 *
 * @param AddressWidth The address width of the EEPROM memory.
 * @param AddressMin   Minimum permitted EEPROM address.
 * @param AddressMax   Maximum permitted EEPROM address.
 ********************************************************************************/
constexpr uint16_t AddressWidth{1024};
constexpr uint16_t AddressMin{0};
constexpr uint16_t AddressMax{AddressWidth - 1};

/********************************************************************************
 * @brief Writes data to specified address in EEPROM. If more than one byte is
 *        to be written, the other bytes are written to the consecutive addresses 
 *        until all bytes are stored.
 *
 * @param address The destination address.
 * @param data    The data to write to the destination address.
 *
 * @return True upon successful write, false if an invalid address was specified.
 ********************************************************************************/
template <typename T = uint8_t>
bool write(const uint16_t address, const T& data);

/********************************************************************************
 * @brief Reads data from specified address in EEPROM. If more than one byte is
 *        to be read, the consecutive addresses are read until all bytes are read.
 *
 * @param address The destination address.
 * @param data    Reference to variable for storing the data read from 
 *                specified address.
 *
 * @return True upon successful read, false if an invalid address was specified.
 ********************************************************************************/
template <typename T = uint8_t>
bool read(const uint16_t address, T& data);

} // namespace
} // namespace eeprom
} // namespace driver

#include "eeprom_impl.h"
