#include <fstream>

#include "person.h"

/*******************************************************************************
 * @brief Prints personal data in the terminal and to file "person.txt".
 ******************************************************************************/
int main()
{
    Person person1{"Marie Nilsson", 42, Gender::Female,
                   "Juristgatan 17", "Lawyer"};
    Person person2{"Sven Andersson", 37, Gender::Male,
                   "Kunskapsgatan 4", "Teacher", false};
    
    person1.print();
    person2.print();
    std::ofstream ofstream{"person.txt"};
    person1.print(ofstream);
    person2.print(ofstream);
    return 0;
}