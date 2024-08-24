/********************************************************************************
 * @brief Implementation details of the ATmega328P ADC driver.
 ********************************************************************************/
#include "adc.h"
#include "type_traits.h"

namespace driver 
{
namespace adc 
{
namespace 
{

constexpr uint16_t MinVal{0U};
constexpr uint16_t MaxVal{1023U};
constexpr uint8_t AdcPortOffset{14U};

// -----------------------------------------------------------------------------
constexpr bool isPinNumberValid(const uint8_t pin) 
{
    return (pin >= Pin::A0 && pin <= Pin::A5) || 
        (pin >= Port::C0 && pin <= Port::C5);
}

// -----------------------------------------------------------------------------
constexpr uint8_t isPinAdjustedForOffset(const uint8_t pin) 
{
    return pin <= Pin::A5 ? pin : pin - AdcPortOffset;
}
} // namespace 

// -----------------------------------------------------------------------------
void init(void) { read(Pin::A0); }

// -----------------------------------------------------------------------------
double getDutyCycle(const uint8_t pin) 
{ 
    return read(pin) / static_cast<double>(MaxVal); 
}

// -----------------------------------------------------------------------------
uint16_t read(const uint8_t pin) 
{
   if (!isPinNumberValid(pin)) { return 0U; }
   ADMUX = (1 << REFS0) | isPinAdjustedForOffset(pin);
   utils::set(ADCSRA, ADEN, ADSC, ADPS0, ADPS1, ADPS2);
   while (!utils::read(ADCSRA, ADIF));
   utils::set(ADCSRA, ADIF);
   return ADC;
}

// -----------------------------------------------------------------------------
bool getDutyCycleParameters_ms(const uint8_t pin, 
                               const uint8_t pwmPeriodMs, 
                               uint8_t& pwmOnTimeMs, 
                               uint8_t& pwmOffTimeMs) 
{
    if (!isPinNumberValid(pin)) { return false; }
    pwmOnTimeMs = utils::round<uint8_t>(pwmPeriodMs * getDutyCycle(pin));
    pwmOffTimeMs = pwmPeriodMs - pwmOnTimeMs;
    return true;
}

// -----------------------------------------------------------------------------
bool getDutyCycleParameters_us(const uint8_t pin, 
                               const uint16_t pwmPeriodUs, 
                               uint16_t& pwmOnTimeUs,
                               uint16_t& pwmOffTimeUs) {
    if (!isPinNumberValid(pin)) { return false; }
    pwmOnTimeUs = utils::round<uint16_t>(pwmPeriodUs * getDutyCycle(pin));
    pwmOffTimeUs = pwmPeriodUs - pwmOnTimeUs;
    return true;
}

} // namespace adc
} // namespace driver
