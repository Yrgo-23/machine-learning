/*******************************************************************************
 * @brief Implementation of person registers.
 ******************************************************************************/
#pragma once

#include <iostream>
#include <type_traits>
#include <vector>

#include "person.h"

/*******************************************************************************
 * @brief Class for implementation of person registers.
 ******************************************************************************/
class PersonRegister
{
public:
    /*******************************************************************************
     * @brief Creates empty person register.
     ******************************************************************************/
    PersonRegister();
    
    /*******************************************************************************
     * @brief Creates person register holding specified person data.
     *
     * @param persons Reference to vector holding persons to add to the register.
     ******************************************************************************/
    PersonRegister(const std::vector<Person*>& persons);

    /*******************************************************************************
     * @brief Creates person register holding specified person data.
     *
     * @tparam Persons Parameter pack containing persons.
     * 
     * @param persons Persons to add to the register.
     ******************************************************************************/
    template <typename... Persons>
    PersonRegister(const Persons&... persons);
    
    /*******************************************************************************
     * @brief Provides persons stored in the register.
     *
     * @return Reference to vector holding the persons stored in the register.
     ******************************************************************************/
    const std::vector<Person>& persons() const;
    
    /*******************************************************************************
     * @brief Provides the number of people stored in the register.
     *
     * @return The number of people stored in the register as an unsigned integer.
     ******************************************************************************/
    std::size_t personCount() const;

    /*******************************************************************************
     * @brief Indicates if the registry is empty.
     * 
     * @return True if the registry is empty, else false.
     ******************************************************************************/
    bool isEmpty() const;

    /*******************************************************************************
     * @brief Clears person register.
     ******************************************************************************/
    void clear();
    
    /*******************************************************************************
     * @brief Indicates if a person with specified name exists in the register.
     *
     * @param name The name of the person to look for.
     *
     * @return True if the person exists in the register, else false.
     ******************************************************************************/
    bool personExists(const char* name) const;
    
    /*******************************************************************************
     * @brief Provides person data stored for person with specified name.
     *
     * @param name The name of the person in question.
     *
     * @return Pointer to object holding the person data if the person exists
     *         in the register, else a nullptr.
     ******************************************************************************/
    const Person* getPerson(const char* name) const;
    
    /*******************************************************************************
     * @brief Adds new person to the register.
     *
     * @param person The person to add.
     *
     * @return True if the person was added, false if the person already exists 
     *         in the register.
     ******************************************************************************/
    bool addPerson(const Person& person);
    
    /*******************************************************************************
     * @brief Adds new persons to the register.
     *
     * @param persons Reference to vector holding the persons to add.
     *
     * @return The number of persons added to the register.
     ******************************************************************************/
    std::size_t addPersons(const std::vector<Person*>& persons);

    /*******************************************************************************
     * @brief Adds new persons to the register.
     *
     * @tparam Persons Parameter pack containing persons.
     * 
     * @param persons Persons to add to the register.
     * 
     * @return The number of persons added to the register.
     ******************************************************************************/
    template <typename... Persons>
    std::size_t addPersons(const Persons&... persons);

    /*******************************************************************************
     * @brief Removes person from the register.
     *
     * @param name Name of the person to remove.
     *
     * @return True if the person was removed, false if the person wasn't found.
     ******************************************************************************/
    bool removePerson(const char* name);

    /*******************************************************************************
     * @brief Prints stored person data.
     *
     * @param ostream Reference to output stream (default = terminal print).
     ******************************************************************************/
    void print(std::ostream& ostream = std::cout);
    
private:
    std::vector<Person> myPersons; // Vector holding persons in the register.
};

/*******************************************************************************
 * @brief Implementation of variadic template constructor.
 ******************************************************************************/
template <typename... Persons>
PersonRegister::PersonRegister(const Persons&... persons)
    : myPersons{}
{
    addPersons(persons...);
}

 /*******************************************************************************
 * @brief Implementation of overloaded method addPersons with variadic template.
 ******************************************************************************/
template <typename... Persons>
std::size_t PersonRegister::addPersons(const Persons&... persons)
{
    const auto previousPersonCount{personCount()};
    for (const auto& person : {persons...})
    {
        static_assert(std::is_same<decltype(person), const Person&>::value,
            "Cannot add non-person objects to the person register!");
        addPerson(person);
    }
    return personCount() - previousPersonCount;
}