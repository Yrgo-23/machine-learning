/*******************************************************************************
 * @brief Implementation details of class Person.
 ******************************************************************************/
#include "person.h"

// -----------------------------------------------------------------------------
Person::Person(const char* name, const unsigned age, const Gender gender,
               const char* address, const char* occupation, const bool single)
    : myName{name}
    , myAge{age}
    , myGender{gender}
    , myAddress{address}
    , myOccupation{occupation}
    , myIsSingle{single} {}

// -----------------------------------------------------------------------------
const char* Person::name() const { return myName; }

// -----------------------------------------------------------------------------
unsigned Person::age() const { return myAge; }

// -----------------------------------------------------------------------------
Gender Person::gender() const { return myGender; }

// -----------------------------------------------------------------------------
const char* Person::address() const { return myAddress; }

// -----------------------------------------------------------------------------
const char* Person::occupation() const { return myOccupation; }

// -----------------------------------------------------------------------------
bool Person::isSingle() const { return myIsSingle; }

// -----------------------------------------------------------------------------
void Person::setAddress(const char* newAddress) { myAddress = newAddress; }

// -----------------------------------------------------------------------------
void Person::setOccupation(const char* newOccupation) { myOccupation = newOccupation; }

// -----------------------------------------------------------------------------
void Person::setSingleStatus(const bool single) { myIsSingle = single; }

// -----------------------------------------------------------------------------
void Person::print(std::ostream& ostream) const
{
    ostream << "--------------------------------------------------------------------------------\n";
    ostream << "Name:\t\t" << myName << "\n";
    ostream << "Age:\t\t" << myAge << "\n";
    ostream << "Gender:\t\t" << genderAsText() << "\n";
    ostream << "Address:\t" << myAddress << "\n";
    ostream << "Occupation:\t" << myOccupation << "\n";
    ostream << "Single:\t\t" << isSingleAsText() << "\n"; 
    ostream << "--------------------------------------------------------------------------------\n\n";
}

// -----------------------------------------------------------------------------
const char* Person::genderAsText() const
{
    if (myGender == Gender::Male) { return "Male"; }
    else if (myGender == Gender::Female) { return "Female"; }
    else { return "Other"; }
}

// -----------------------------------------------------------------------------
const char* Person::isSingleAsText() const { return myIsSingle ? "Yes" : "No"; }
