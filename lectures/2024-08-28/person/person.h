/*******************************************************************************
 * @brief Software implementation of people in software. 
 ******************************************************************************/
#pragma once

#include <iostream>

/*******************************************************************************
 * @brief Enumeration class för implementing genders.
 ******************************************************************************/
enum class Gender { Male, Female, Other };

/*******************************************************************************
 * @brief Class for implementing a person in software.
 ******************************************************************************/
class Person
{
public:

    /** Default constructor deleted. */
    Person() = delete;
    
    /*******************************************************************************
     * @brief Creates new person.
     * 
     * @param name       Reference to string holding the person's name.
     * @param name       The person's age.
     * @param gender     The person's gender.
     * @param address    The person's home address.
     * @param occupation The person's occupation.
     * @param single     Indicates if the person is single (default = true).
     ******************************************************************************/
    Person(const char* name, const unsigned age, const Gender gender,
           const char* address, const char* occupation, const bool single = true);

    /*******************************************************************************
     * @brief Provides the person's name.
     * 
     * @return Reference to string holding the person's name.
     ******************************************************************************/
    const char* name() const;

    /*******************************************************************************
     * @brief Provides the person's age.
     * 
     * @return The person's age as an integer.
     ******************************************************************************/
    unsigned age() const;

     /*******************************************************************************
     * @brief Provides the person's gender.
     * 
     * @return The person's gender as an enumerator of enumeration class Gender.
     ******************************************************************************/
    Gender gender() const;

    /*******************************************************************************
     * @brief Provides the person's home address.
     * 
     * @return Reference to string holding the person's home address.
     ******************************************************************************/
    const char* address() const;

    /*******************************************************************************
     * @brief Provides the person's occupation.
     * 
     * @return Reference to string holding the person's occupation.
     ******************************************************************************/
    const char* occupation() const;

    /*******************************************************************************
     * @brief Indicates if the person is single.
     * 
     * @return True if the person is single, else false.
     ******************************************************************************/
    bool isSingle() const;

    /*******************************************************************************
     * @brief Sets new home address.
     * 
     * @param newAddress Reference to string holding the new address.
     ******************************************************************************/
    void setAddress(const char* newAddress);

    /*******************************************************************************
     * @brief Sets new occupation.
     * 
     * @param newOccupation Reference to string holding the new occupation.
     ******************************************************************************/
    void setOccupation(const char* newOccupation);

    /*******************************************************************************
     * @brief Updates the person's single status.
     * 
     * @param single True if the person now is single.
     ******************************************************************************/
    void setSingleStatus(const bool single);

    /*******************************************************************************
     * @brief Prints personal data about the specific person.
     * 
     * @param ostream Reference to output stream (default = terminal print).
     ******************************************************************************/
    void print(std::ostream& ostream = std::cout) const;

private:

    /*******************************************************************************
     * @brief Provides the person's gender as text.
     * 
     * @return Reference to string holding the person's gender.
     ******************************************************************************/
    const char* genderAsText() const;

    /*******************************************************************************
     * @brief Provides string indicating if the person is single.
     * 
     * @return "Yes" if the person is single, else "No".
     ******************************************************************************/
    const char* isSingleAsText() const;

    const char* myName;       // The person's name.
    unsigned myAge;           // The person's age.
    Gender myGender;          // The person's gender.
    const char* myAddress;    // The person's address.
    const char* myOccupation; // The person's occupation.
    bool myIsSingle;          // Indicates if the person is single.
};
