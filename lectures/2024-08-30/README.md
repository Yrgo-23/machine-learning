# 2024-08-30 - Lektion 4

## Dagordning
* Komposition i C++.
* Inlämningsuppgift innefattande skapandet av klasser i C++.

## Mål med lektionen
* Kunna implementera nya typer med attribut av tidigare egenskapade typer.
* Ha genomfört och lämnat in inlämningsuppgift 2.

## Instruktioner
* Läs om komposition i C++ i detta dokument.
* Inlämningsuppgift 2 är tillgänglig på Classroom kl. 10:00.

## Utvärdering
* Några synpunkter på lektionen i sig?

## Nästa lektion
* Vad är maskininlärning?
* Linjär regression – träning för hand, prediktion, epoker, lärhastighet med mera.

## Komposition i C++

### Bakgrund
När man ska implementera komplexa typer är det ofta smidigt att använda tidigare befintliga typer för implementeringen.
Som exempel, föregående lektion skapade vi en typ döpt `Person` för att lagra persondata för en enskilt person. 

Om vi exempelvis ska lagra och modifiera persondata i ett register kan vi med fördel skapa en ny typ döpt `PersonRegister`.
För implementeringen kan vi lagra multipla objekt av typen `Person`, med fördel i en vektor. För att vektorn ska lagra Person-objekt sätter vi därmed vektorns datatyp till `std::vector<Person>`.

### Implementering
För demonstrations skull implementeras i detta avsnitt en klass döpt `PersonRegister`. Vi börjar med att lägga till en ny headerfil döpt `person_register.h` för att definiera klassen. Metoddefinitionerna kommer senare implementeras i en källkodsfil döpt `person_register.cpp`. 

***Tips:** Se materialet från föregående lektion gällande klasser samt hur dessa delas upp i en headerfil samt en källkodsfil.*

#### Filen `person_register.h`

Längst upp i filen placerar vi direktivet #pragma once, som ser att vi inte råkar definiera multipla kopior av innehållet i denna headerfil om den inkluderas i flera olika filer:

```cpp
#pragma once
```

Därefter inkluderar vi nödvändiga standardheaders. Eftersom vi vill kunna lagra persondata i en vektor inkluderar vi `<vector>`. För att kunna skriva ut persondatan inkluderar vi också `<iostream>`. Vi placerar dessa i bokstavsordning för strukturens skull:

```cpp
#include <iostream>
#include <vector>
```

För att kunna använda oss utav vår tidigare skapade klass `Person` inkluderar vi också headerfilen `<person.h>`. Eftersom detta inte är ett standardbibliotek omger vi `person.h` med citattecken i stället för <>, som medför att headerfilen söks bland våra lokala filer:

```cpp
#include "person.h"
```

Därefter lägger vi till den grundläggande strukturen för klassen `PersonRegister`:


```cpp
/*******************************************************************************
 * @brief Class for implementation of person registers.
 ******************************************************************************/
class PersonRegister
{
public:
private:
};
```

Vi lägger till en medlemsvariabel i form av en vektor, `myPersons` för att lagra persondata i form av objekt av klassen `Person`:


```cpp
/*******************************************************************************
 * @brief Class for implementation of person registers.
 ******************************************************************************/
class PersonRegister
{
public:
private:
    std::vector<Person> myPersons; // Vector holding persons in the register.
};
```

Därefter deklarerar vi klassens konstruktorer. För att ett givet personregister ska kunna starta tomt implementerar vi i detta fall defaultkonstruktorn `PersonRegister()`:


```cpp
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
    
private:
    std::vector<Person> myPersons; // Vector holding persons in the register.
};
```

Defaultkonstruktorn ovan innebär att man kan skapa ett personregister så som visas nedan:

```cpp
PersonRegister personRegister{};
```

Vi kan också lägga till ytterligare en konstruktor, som möjliggör att man kan lägga till multipla personer direkt vid start. Denna persondata måste då vara lagrat i en vektor. Vi lägger därför till konstruktorn `PersonRegister(const std::vector<Person*>& persons)`, där ingående argument `persons` utgörs av en referens till en vektor innehållande persondata, i praktiken via pekare till Person-objekt:

```cpp
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
    
private:
    std::vector<Person> myPersons; // Vector holding persons in the register.
};
```

Vi denna konstruktor kan man sedan lagra persondata i en vektor, för att sedan skapa ett personregister med denna data. 
För att undvika att lägga kopior av Person-objekten i vektorn använder vi oss utav pekare:

```cpp
Person person1{"Marie Nilsson", 42, Gender::Female,
               "Juristgatan 17", "Lawyer"};
Person person2{"Sven Andersson", 37, Gender::Male,
               "Kunskapsgatan 4", "Teacher", false};
Person person3{"Gustaf Svensson", 67, Gender::Male,
               "Polisgatan 2", "Police officer"};
std::vector<Person*> persons{&person1, &person2, &person3};
PersonRegister personRegister{persons};
```
Vi kan sedan i denna konstruktor se till att man inte kan lägga till samma person flera gånger, exempelvis genom att kontrollera personens namn; finns personen redan i registret läggs hen inte till ytterligare en gång exempelvis.

Vi lägger därefter till en get-metod döpt `persons`, som möjliggör att man kan läsa persondatan från klassen. Vi ser dock till att man inte kan skriva genom att returnera en konstant referens (till vår personlista):

```cpp
/*******************************************************************************
 * @brief Provides persons stored in the register.
 *
 * @return Reference to vector holding the persons stored in the register.
 ******************************************************************************/
const std::vector<Person>& persons() const;
```
Vi ser till att man kan ta reda på antalet personer i registret via en metod döpt `personCount`, som returnerar antalet personer i registret som ett osignerat heltal:

```cpp
/*******************************************************************************
 * @brief Provides the number of people stored in the register.
 *
 * @return The number of people stored in the register as an unsigned integer.
 ******************************************************************************/
std::size_t personCount() const;
```

Vi kan implementera en metod `isEmpty`, som indikerar om personregistret är tomt.
I så fall returneras `true`, annars `false`:

```cpp
/*******************************************************************************
 * @brief Indicates if the registry is empty.
 * 
 * @return True if the registry is empty, else false.
 ******************************************************************************/
bool isEmpty() const;
```

Vi kan med fördel skapa en metod `clear`, som möjliggör att man kan tömma personregistret.
Vid anrop till denna metod kommer alltså all persondata raderas:

```cpp
/*******************************************************************************
 * @brief Clears person register.
 ******************************************************************************/
void clear();
```

Vi kan sedan lägga till en metod `personExists` för att kontrollera ifall en person med angivet namn finns. Om så är fallet returneras `true`, annars `false`:

```cpp  
/*******************************************************************************
 * @brief Indicates if a person with specified name exists in the register.
 *
 * @param name The name of the person to look for.
 *
 * @return True if the person exists in the register, else false.
 ******************************************************************************/
bool personExists(const char* name) const;
```

Vi kan också implementera en metod `getPerson` som möjliggör att man kan läsa persondata för en given person om denna finns i registret. Exempelvis kan vi då returnera en pekare till Person-objektet för denna person, alternativt en nullpekare om denna person inte finns i registret:

```cpp
/*******************************************************************************
 * @brief Provides person data stored for person with specified name.
 *
 * @param name The name of the person in question.
 *
 * @return Pointer to object holding the person data if the person exists
 *         in the register, else a nullptr.
 ******************************************************************************/
const Person* getPerson(const char* name) const;
```

Vi kan också lägga till en metod `addPerson` för att lägga till en person i personregistret. 
Persondatan måste då skickas som ett Person-objekt. 
Om personen inte finns i registret läggs denna person till och vi returnerar `true`, annars returnerar vi `false`:


```cpp
/*******************************************************************************
 * @brief Adds new person to the register.
 *
 * @param person The person to add.
 *
 * @return True if the person was added, false if the person already exists 
 *         in the register.
 ******************************************************************************/
bool addPerson(const Person& person);
```

Vi kan även lägga till en metod `addPersons` för att lägga till multipla personer.
Dessa personer måste då vara implementerade som Person-objekt lagrade i en vektor. Vi returnerar antalet tillagda personer:

```cpp
/*******************************************************************************
 * @brief Adds new persons to the register.
 *
 * @param persons Reference to vector holding the persons to add.
 *
 * @return The number of persons added to the register.
 ******************************************************************************/
std::size_t addPersons(const std::vector<Person>& persons);
```

Därefter kan vi lägga till en metod för att ta bort en person ur registret. Vi döper denna metod till `removePerson` och man måste ange personens namn för att ta bort denna. Vi returnerar `true` om personens togs bort, annars false om hen inte finns i registret:


```cpp
/*******************************************************************************
 * @brief Removes person from the register.
 *
 * @param name Name of the person to remove.
 *
 * @return True if the person was removed, false if the person wasn't found.
 ******************************************************************************/
bool removePerson(const char* name);
```

Slutligen kan vi lägga till en metod `print` för att skriva ut lagrad persondata.
Vi använder ett ingående argument i form av en reference till ett objekt av typen `std::ostream`
så att utströmmen vi skriver till är valbar. Som default sker utskrift i terminalen (till `std::cout`) men vid behov kan man även skriva till en fil: 

```cpp
/*******************************************************************************
 * @brief Prints stored person data.
 *
 * @param ostream Reference to output stream (default = terminal print).
 ******************************************************************************/
void print(std::ostream& ostream = std::cout);
```

##### Slutförd klassdeklaration

Den slutförda klassdeklarationern implementerad i `person_register.h` visas nedan:

```cpp
/*******************************************************************************
 * @brief Implementation of person registers.
 ******************************************************************************/
#pragma once

#include <iostream>
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
```

#### Filen `person_register.cpp`

I filen `person_register.cpp` lägger vi sedan implementeringsdetaljerna för klassen `PersonRegister`
i form av metoddefinitioner. Vi ser till att implementera funktionerna i enlighet med beskrivningen
ovan (samt tillhörande dokumentation). 

Exempelvis kan filen `person_register.cpp` implementeras så som visas nedan. 

***Tips:** Se materialet från föregående lektion gällande hur metoddefinitioner utanför klassen.*

```cpp
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
    auto previousPersonCount{personCount()};
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
```

#### Filen `main.cpp`

Vi ska testa att spara persondata i ett personregister samt skriva ut denna data i terminalen samt till en fil döpt `persons.txt`.

Vi börjar med att inkludera de headerfiler vi behöver för implementationen, nämligen `<fstream>`, `<vector>`, `<person.h>` samt `<person_register.h>`. 

Notera att i nuvarande implementation får vi `<vector>` samt `<person.h>` inkluderat indirekt när vi inkluderar `<person_register.h>`. Ifall `<person_register.h>` ändras senare kanske dock inte detta är fallet och vi kan då behöva skriva om koden. Därmed är det en bra idé att inte förlita sig på indirekta beroenden. Vi inkluderar därmed allt vi vill använda i `main.cpp` direkt.

```cpp
#include <fstream>
#include <vector>

#include "person.h"
#include "person_register.h"
```

Vi definierar sedan funktionen `main`. I `main` testar vi vår personregisterimplementering genom att göra följande:
* **1.** Vi skapar ett tomt personregister.
* **2.** Vi skapar tre Person-objekt för lagring av persondata för tre personer.
* **3.** Vi lägger till pekare till Person-objekten i en vektor.
* **4.** Vi lagrar persondatan i personregistret genom att kalla på metoden `PersonRegister::addPersons`.
* **5.** Vi skriver ut persondatan i terminalen samt till en fil döpt `persons.txt`.

Funktionen `main` kan därmed inkluderas så som visas nedan:

```cpp
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
```

Därmed kan filen `main.cpp` implementeras så som visas nedan:

```cpp
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
```

### Slutförd komimplementation
Filer `person_register.h`, `person_register.cpp`, `main.cpp` finns tillgängliga tillsammans med tidigare skapade filer `person.h` samt `person.cpp` i underkatalogen `person_register`:
* Samtliga headerfiler (`.h`) har placerats i en underkatalog döpt `include`.
* Samtliga källkodsfiler (`.cpp`) har placerats i en underkatalog döpt `source`.
* En makefil för kompilering och körning av koden är bifogad. Instruktioner för byggande samt körande av koden finns i bifogad README-fil.

#### Sammanfattning
Efter att ha gått igenom detta stycke bör du som läsare ha tillräckligt med kunskap gällande komposition för att kunna skapa nya klasser med hjälp av tidigare skapande klasser.  

#### Fördjupning
Det finns mycket mer att lära sig om klasser och objektorientering än vad som presenterades här; detta ämne hade kunnat täcka en hel kurs. 
För mer information:
* Se boken [*The C++ Programming Language*](https://www.adlibris.com/se/bok/c-programming-language-the-9780321958327) av Bjarne Stroustrup, skapare av C++. Denna bok täcker det mesta som behöver kännas till om modern C++ (förutom sådant som har kommit till efter att den senaste upplagan släpptes), inte bara klasser. 
* En hel del fördjupad information finns också i klass-avsnittet på [*cplusplus.com*](https://cplusplus.com/doc/tutorial/classes/).  

