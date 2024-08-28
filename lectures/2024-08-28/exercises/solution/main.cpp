/*******************************************************************************
 * @brief Test of solution for exercise 2024-08-28.
 ******************************************************************************/
#include <fstream>

#include "device.h"

/*******************************************************************************
 * @brief Stored device data for an Arduino Uno Rev 3 via a Device object.
 *        The device data is printed in the terminal and to file "device.txt".
 * 
 * @return Success code 0 upon termination of the program.
 ******************************************************************************/
int main()
{
    std::ofstream ostream{"device.txt"};              
    Device device1{"Arduino", "Uno", 3, 2012, "Green"};
    device1.print();
    device1.print(ostream);
    return 0;
}