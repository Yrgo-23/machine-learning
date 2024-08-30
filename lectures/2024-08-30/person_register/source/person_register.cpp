/*******************************************************************************
 * @brief Implementation details of class PersonRegister.
 ******************************************************************************/
#include "person_register.h"

// -----------------------------------------------------------------------------
PersonRegister::PersonRegister()
    : myPersons{} {}

// -----------------------------------------------------------------------------
PersonRegister::PersonRegister(const std::vector<Person*>& persons)
    : myPersons{} { addPersons(persons); }

// -----------------------------------------------------------------------------
const std::vector<Person>& PersonRegister::persons() const { return myPersons; }

// -----------------------------------------------------------------------------
std::size_t PersonRegister::personCount() const { return myPersons.size(); }

// -----------------------------------------------------------------------------
bool PersonRegister::isEmpty() const { return myPersons.empty(); }

// -----------------------------------------------------------------------------
void PersonRegister::clear() { myPersons.clear(); }

// -----------------------------------------------------------------------------
bool PersonRegister::personExists(const char* name) const
{
    return getPerson(name) != nullptr;
}

// -----------------------------------------------------------------------------
const Person* PersonRegister::getPerson(const char* name) const
{
    for (const auto& person : myPersons)
    {
        if (person.name() == name) { return &person; }
    }
    return nullptr;
}

// -----------------------------------------------------------------------------
bool PersonRegister::addPerson(const Person& person)
{
    if (personExists(person.name())) { return false; }
    myPersons.push_back(person);
    return true;
}

// -----------------------------------------------------------------------------
std::size_t PersonRegister::addPersons(const std::vector<Person*>& persons)
{
    const auto previousPersonCount{personCount()};
    for (const auto& person : persons)
    {
        if (person != nullptr) { addPerson(*person); }
    }
    return personCount() - previousPersonCount;
}

// -----------------------------------------------------------------------------
bool PersonRegister::removePerson(const char* name)
{
    for (auto person{myPersons.begin()}; person < myPersons.end(); ++person)
    {
        if (person->name() == name) 
        {
            myPersons.erase(person);
            return true;
        }
    }
    return false;
}

// -----------------------------------------------------------------------------
void PersonRegister::print(std::ostream& ostream)
{
    for (const auto& person : myPersons)
    {
        person.print(ostream);
    }
}