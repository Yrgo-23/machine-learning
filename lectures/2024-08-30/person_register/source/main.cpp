/*******************************************************************************
 * @brief Demonstration of the PersonRegistry class.
 ******************************************************************************/
#include <fstream>
#include <vector>

#include "person.h"
#include "person_register.h"

/*******************************************************************************
 * @brief Prints personal data stored in a registry in the terminal and to
 *        a file named "persons.txt".
 ******************************************************************************/
int main()
{
    PersonRegister personRegister{};
    Person person1{"Marie Nilsson", 42, Gender::Female,
               "Juristgatan 17", "Lawyer"};
    Person person2{"Sven Andersson", 37, Gender::Male,
                "Kunskapsgatan 4", "Teacher", false};
    Person person3{"Gustaf Svensson", 67, Gender::Male,
                "Polisgatan 2", "Police officer"};
    std::vector<Person*> persons{&person1, &person2, &person3};
    std::ofstream ostream{"persons.txt"};
    
    personRegister.addPersons(persons);
    personRegister.print();
    personRegister.print(ostream);
    return 0;
}