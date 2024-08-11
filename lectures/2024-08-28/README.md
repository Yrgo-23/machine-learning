# 2024-08-28 - Lektion 3

## Dagordning
* Grundläggande objektorientering i C++: klasser, inkapsling med mera.
* Övningsuppgifter innefattande skapande av klasser i C++.

## Mål med lektionen
* Kunna skapa enkla klasser i C++.
* Känna till innebörden av orden såsom *konstruktor* och *inkapsling*.
* Kunna använda enumerationsklasser.

## Instruktioner
* Läs om klasser i detta dokument.
* Se övningsuppgifter i underkatalogen *exercises*.

## Utvärdering
* Några synpunkter på lektionen i sig?

## Nästa lektion
* Komposition i C++.
* Inlämningsuppgift innefattande skapandet av klasser i C++.

## Klasser i C++

### Bakgrund
För att hålla god struktur i större program finns ett ökat behov av att lagra relaterad data som en enhet via enskilda datastrukturer i stället för multipla separata variabler. Som exempel kan det vara fördelaktigt att lagra persondata i form av namn, ålder, adress och dylikt för en person som en enhet i stället för separata variabler för varenda attribut. 

Inom programmering utgörs de vanligaste datastrukturerna för lagring av relaterad data som en enhet av så kallade *struktar* och *klasser:* 
* *Struktar* (strukturer) används främst i C (begreppet klass existerar inte överhuvudtaget i C).
* Klasser används nästan exklusivt i programspråk som skapades efter C, såsom C++, Java och Python. 
* Klasser kan ses som en vidareutveckling av struktar, som är relativt simpla. Sett till uppbyggnad är dock dessa datastrukturer väldigt lika.

Språk som innehar stöd för klasser sägs inneha stöd för objektorientering, eller OOP *(Object Oriented Programming.)* C sägs vara ett procedurellt språk, då det bygger på programmering via funktioner. Via struktar kan dock vissa objektorienterade principer efterliknas, vilket kommer demonstreras nedan.

En del objektorienterade språk, exempelvis Java och C# är rent objektorienterade, vilket innebär att klasser måste användas. Andra programspråk, såsom C++ och Python, sägs utgöra multiparadigmspråk, då det finns möjlighet att programmera båda objektorienterat (såsom i Java) samt procedurellt (såsom i C) eller en kombination av dem.

### Struktar i C
För att förstå hur klasser fungerar är det enklast att börja med den enklaste datastrukturen. Därmed börjar vi med struktar. Struktar i C fungerar likt arrayer, med skillnaden att datatyperna på medlemmarna i en strukt kan vara olika, medan samtliga element i en array måste vara samma. 

Därmed gäller att ett struktobjekt kan inneha en kombination av text, tal, boolvariabler med mera, exempelvis för att lagra en persons namn (text), ålder (heltal), om personen är singel (sant eller falskt) med mera.

Struktar implementeras via nyckelordet *struct.* Nedan visas en strukt döpt *person*, vars syfte är att lagra persondata:

```c
/*******************************************************************************
 * @brief Structure for holding personal data for a single person.
 * 
 * @param name       The person's name.
 * @param age        The person's age.
 * @param address    The person's home address.
 * @param occupation The person's occupation.
 ******************************************************************************/
struct person
{
    const char* name;
    unsigned age;
    const char* address;
    const char* occupation;
};
```

Via strukten *person* ovan kan vi lagra namn, ålder, address samt yrke för en given person. Som exempel, för en 42-årig advokat döpt Marie Nilsson som bor på Juristgatan 17 kan vi skapa ett objekt döpt *person1* så som visas nedan. Notera att initieringen är väldigt likt hur vi hade initierat en array i C:

```c
struct person person1 = {"Marie Nilsson", 42, "Juristgatan 17", "Lawyer"};
```

Notera att vi passerar attributen, såsom "Marie Nilsson" för namnet och 42 för åldern, i samma ordning som de har deklarerats i strukten.

Till skillnad mot arrayer använder vi inte index för att nå innehållet i struktobjektet. I stället använder vi den så kallade punktoperatorn, som utgörs av en punkt mellan objektets namn och attributet vi söker. 

Därmed gäller att om vi vill få tillgång till namnet på *person1* skriver vi *person1.name*, då namnet är lagrat via attributet *name*. På samma sätt gäller att vi skriver *person1.age* för att få tillgång till personens ålder, *person1.address* för att få tillgång till persons adress och så vidare.

Nedan visas hur vi skriver ut persondatan för *person1* i terminalen via anrop av funktionen *print* från standardheadern *stdio.h*:

```c
    struct person person1 = {"Marie Nilsson", 42, "Juristgatan 17", "Lawyer"};
    printf("Name:\t\t%s\n", person1.name);
    printf("Age:\t\t%u\n", person1.age);
    printf("Address:\t%s\n", person1.address);
    printf("Occupation:\t%s\n", person1.occupation);
```

Utskriften blir:

```
Name:           Marie Nilsson
Age:            42
Address:        Juristgatan 17
Occupation:     Lawyer
```

Kortfattat gällande ovanstående kodsnutt:
* **\t** medför ett tabtecken.
* **\n** medför ett nyradstecken.
* **%s** är formatspecificerare för text.
* **%u** utgör formatspecificerare för osignerade heltal.

Vi kan lägga till fler parametrar vid behov. Som exempel kan vi lägga till en boolvariabel *single*, som indikerar ifall personen i fråga är singel eller inte via booleska värden *true* och *false*. För att göra detta måste vi inkludera standardheadern *stdbool:*

```c
#include <stdbool.h>
```

Därefter kan vi lägga till parametern *single* så som visas nedan:

```c
/*******************************************************************************
 * @brief Structure for holding personal data for a single person.
 * 
 * @param name       The person's name.
 * @param age        The person's age.
 * @param address    The person's home address.
 * @param occupation The person's occupation.
 * @param single     Indicates if the person is single (true = single).
 ******************************************************************************/
struct person
{
    const char* name;
    unsigned age;
    const char* address;
    const char* occupation;
    bool single;
};
```

Vi kan även lägga till parametrar av egna typer också. Anta att vi vill ha en typ för personens kön, där giltiga värden är man, kvinna eller annat. 

I C hade vi kunnat göra detta med en enumeration döpt *gender,* där enumeratorerna föregås av prefixes GENDER för att undvika namnkrockar i större program. En sådan enumeration hade kunnat se ut så som visas nedan:

```c
/*******************************************************************************
 * @brief Enumeration för implementing genders.
 * 
 * @param GENDER_MALE   Male gender.
 * @param GENDER_FEMALE Female gender.
 * @param GENDER_OTHER  Other gender.
 ******************************************************************************/
enum gender
{
    GENDER_MALE,
    GENDER_FEMALE,
    GENDER_OTHER
};
```

Vi lägger till parametern *gender* för personens kön efter åldern, så att den mest basala datan (namn, ålder och kön) hamnar först:

```c
/*******************************************************************************
 * @brief Structure for holding personal data for a single person.
 * 
 * @param name       The person's name.
 * @param age        The person's age.
 * @param gender     The person's gender.
 * @param address    The person's home address.
 * @param occupation The person's occupation.
 * @param single     Indicates if the person is single (true = single).
 ******************************************************************************/
struct person
{
    const char* name;
    unsigned age;
    enum gender gender;
    const char* address;
    const char* occupation;
    bool single;
};
```

Anta att personen Marie Nilsson implementerad via objektet *person1* tidigare är kvinna och singel. I så fall hade associerat objekt *person1* kunnat implementeras så som visas nedan. Notera att vi passerar attributen i samma ordning som de har deklarerats i strukten:

```c
struct person person1 = {"Marie Nilsson", 42, GENDER_FEMALE,
                         "Juristgatan 17", "Lawyer", true};
```

#### Exempelprogram

Nedan visas ett program, där persondatan lagrad via ovanstående objekt *person1* skrivs ut i terminalen. Vi implementerar en funktion döpt *gender_str* för att erhålla kön i textform.

```c
#include <stdio.h>
#include <stdbool.h>

/*******************************************************************************
 * @brief Enumeration för implementing genders.
 * 
 * @param GENDER_MALE   Male gender.
 * @param GENDER_FEMALE Female gender.
 * @param GENDER_OTHER  Other gender.
 ******************************************************************************/
enum gender
{
    GENDER_MALE,
    GENDER_FEMALE,
    GENDER_OTHER
};

/*******************************************************************************
 * @brief Structure for holding personal data for a single person.
 * 
 * @param name       The person's name.
 * @param age        The person's age.
 * @param gender     The person's gender.
 * @param address    The person's home address.
 * @param occupation The person's occupation.
 * @param single     Indicates if the person is single (true = single).
 ******************************************************************************/
struct person
{
    const char* name;
    unsigned age;
    enum gender gender;
    const char* address;
    const char* occupation;
    bool single;
};

/*******************************************************************************
 * @brief Provides specified gender as a string, i.e. as text.
 * 
 * @param gender The specified gender.
 * 
 * @return The specified gender as text.
 ******************************************************************************/
const char* gender_str(const enum gender gender)
{
    if (gender == GENDER_MALE) { return "Male"; }
    else if (gender == GENDER_FEMALE) { return "Female"; }
    else { return "Other"; }
}

/*******************************************************************************
 * @brief Prints personal data in the terminal.
 ******************************************************************************/
int main()
{
    struct person person1 = {"Marie Nilsson", 42, GENDER_FEMALE,
                             "Juristgatan 17", "Lawyer", true};
    printf("Name:\t\t%s\n", person1.name);
    printf("Age:\t\t%u\n", person1.age);
    printf("Gender:\t\t%s\n", gender_str(person1.gender));
    printf("Address:\t%s\n", person1.address);
    printf("Occupation:\t%s\n", person1.occupation);
    printf("Single:\t\t%s\n", person1.single ? "Yes" : "No");
    return 0;
}
```

Utskriften blir:

```
Name:           Marie Nilsson
Age:            42
Gender:         Female
Address:        Juristgatan 17
Occupation:     Lawyer
Single:         Yes
```



### Associerade funktioner till struktar
I C är det vanligt att skapa funktioner associerade med en strukt. Dessa funktioner skapas då för att användas med objekt av motsvarande strukt. 

Exempelvis kan vi skapa en funktion döpt *person_print* för att skriva ut persondata i terminalen. Detta kommer både göra programmet enklare att läsa, samtidigt som vi slipper skriva samma kod igen ifall vi vill skriva ut persondata för fler personer.

Vi lägger till prefixet *person* på alla funktioner associerade med strukten *person* av två anledningar:
* **1.** För att tydliggöra att funktionen är associerad med strukten *person.*
* **2.** För att undvika namnkrockar, vilket vi hade fått om en annan C-funktion heter *print.* Därmed ser vi till att samtliga funktioner har undika namn. Som exempel, skapar vi en till struct som heter exempelvis *device* kan vi döpa motsvarande utskriftsfunktion till *device_print.*

Funktionen *person_print* visas nedan:

```c
/*******************************************************************************
 * @brief Prints personal data in the terminal.
 * 
 * param self Reference to object holding the personal data.
 ******************************************************************************/
void person_print(const struct person* self)
{
    printf("--------------------------------------------------------------------------------\n");
    printf("Name:\t\t%s\n", self->name);
    printf("Age:\t\t%u\n", self->age);
    printf("Gender:\t\t%s\n", gender_str(self->gender));
    printf("Address:\t%s\n", self->address);
    printf("Occupation:\t%s\n", self->occupation);
    printf("Single:\t\t%s\n", self->single ? "Yes" : "No");
    printf("--------------------------------------------------------------------------------\n\n");
}

```

Notera att:
* Vi sätter ingående argument *self* till en pekare, då person-objekt är relativt större. Därmed föredrar vi *pass-by-reference* (med pekare) i stället för *pass-by-value* (som hade medfört att vi skapat och sedan skickat en kopia av person-objektet vars innehåll vi vill skriva ut). 
* Eftersom vi bara vill läsa persondatan utan att modifiera något sätter vi person-objektet till en konstant via nyckelordet *const.*
* Vi döper ingående argument till *self* för att indikera att detta är själva objektet som den associerade funktionen är till för. Vanliga andra namn är *this* och *me,* men givetvis kan vi döpa detta argument till *person* om vi föredrar det.
* Eftersom ingående argument *self* är en pekare till person-objektet, inte själva objektet i sig, använder vi piloperatorn -> för att enkelt få tillgång till person-attributen. Som exempel, via piloperatorn kan vi få tillgång till personens namn genom att skriva *self->name* i stället för *(*self).name* för att först läsa innehållet som pekaren *self* pekar på *(.self)*, följt av att använda punktoperatorn för att få tillgång till attributen.

När vi anropar funktionen *person_print* måste vi skicka adressen till person-objektet vi vill skriva ut. Detta gör vi med den så kallade adressoperatorn &. Som exempel, för att kalla på *person_print* med adressen till objektet *person1* kan följande instruktion användas:

```c
person_print(&person1);
```

#### Exempelprogram

Vi lägger till funktionen *person_print* i ovanstående program. Vi lägger också till ytterligare en person, en 37-årig gift man, som heter "Sven Andersson", bor på "Kunskapsgatan 4" och jobbar som lärare. Vi skriver sedan ut persondatan för respektive person genom att anropa *person_print.* Programmet visas nedan:

```c
#include <stdio.h>
#include <stdbool.h>

/*******************************************************************************
 * @brief Enumeration för implementing genders.
 * 
 * @param GENDER_MALE   Male gender.
 * @param GENDER_FEMALE Female gender.
 * @param GENDER_OTHER  Other gender.
 ******************************************************************************/
enum gender
{
    GENDER_MALE,
    GENDER_FEMALE,
    GENDER_OTHER
};

/*******************************************************************************
 * @brief Structure for holding personal data for a single person.
 * 
 * @param name       The person's name.
 * @param age        The person's age.
 * @param gender     The person's gender.
 * @param address    The person's home address.
 * @param occupation The person's occupation.
 * @param single     Indicates if the person is single (true = single).
 ******************************************************************************/
struct person
{
    const char* name;
    unsigned age;
    enum gender gender;
    const char* address;
    const char* occupation;
    bool single;
};

/*******************************************************************************
 * @brief Provides specified gender as text.
 * 
 * @param gender The specified gender.
 * 
 * @return The specified gender as text.
 ******************************************************************************/
const char* gender_str(const enum gender gender)
{
    if (gender == GENDER_MALE) { return "Male"; }
    else if (gender == GENDER_FEMALE) { return "Female"; }
    else { return "Other"; }
}

/*******************************************************************************
 * @brief Prints personal data in the terminal.
 * 
 * param self Reference to object holding the personal data.
 ******************************************************************************/
void person_print(const struct person* self)
{
    printf("--------------------------------------------------------------------------------\n");
    printf("Name:\t\t%s\n", self->name);
    printf("Age:\t\t%u\n", self->age);
    printf("Gender:\t\t%s\n", gender_str(self->gender));
    printf("Address:\t%s\n", self->address);
    printf("Occupation:\t%s\n", self->occupation);
    printf("Single:\t\t%s\n", self->single ? "Yes" : "No");
    printf("--------------------------------------------------------------------------------\n\n");
}

/*******************************************************************************
 * @brief Prints personal data in the terminal.
 ******************************************************************************/
int main()
{
    struct person person1 = {"Marie Nilsson", 42, GENDER_FEMALE,
                             "Juristgatan 17", "Lawyer", true};
    struct person person2 = {"Sven Andersson", 37, GENDER_MALE,
                             "Kunskapsgatan 4", "Teacher", false};
    person_print(&person1);
    person_print(&person2);
    return 0;
}
```

Utskriften visas nedan:

```
--------------------------------------------------------------------------------
Name:           Marie Nilsson
Age:            42
Gender:         Female
Address:        Juristgatan 17
Occupation:     Lawyer
Single:         Yes
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
Name:           Sven Andersson
Age:            37
Gender:         Male
Address:        Kunskapsgatan 4
Occupation:     Teacher
Single:         No
--------------------------------------------------------------------------------
```

### Klasser i C++

#### Terminologi
Som skrevs tidigare används klasser i stället för struktar i de flesta konventionella programspråk som skapades efter C. 

I C++ är dock struktar nästintill identiska med klasser; den enda skillnaden är att för klasser är samtliga attribut icke åtkomliga utanför klassen som default. Struktar i C++ kan dock användas på samma sätt som struktar i C. För att minska förvirring i resten av detta avsnitt gäller följande:
* **Strukt** syftar till den enkla datastruktur som har demonstrerats hittills (C-strukt).
* **Klass** syftar till en mer avancerad variant av den datastrukt vi har sett hittills.

#### Skillnader mellan klasser och struktar

Klasser kan ses som en vidareutveckling av struktar. Därmed är klasser och struktar lika sett till den grundläggande uppbyggnaden, men klasser erbjuder mycket mer funktionalitet samt flexibilitet. I detta avsnitt ska vi titta på den mest grundläggande funktionalitet som klasser erbjuder.

Några av de mest betydande skillnaderna mellan klasser och struktar är:
* **Klasser innehar stöd för inkapsling,** vilket innebär att man kan välja vad som är åtkomligt/synligt utanför klassen. Därmed kan hemlig data eller information som inte är relevant utanför klassen (såsom implementationsdetaljer) döljas.
* **Klasser kan innehålla funktioner,** vilket innebär att vi inte behöver implementeras associerade funktioner med struktpekare, så som visades nedan.
* **Klasser erbjuda funktionalitet för arv,** vilket innebär att en ny klass kan erhålla innehållet från en basklass. Detta kan minska mängden kod som behovs avsevärt.
* **Klasser kan implemeteras via så kallade klasstemplates för att göra en eller flera datatyper valbara, likt de funktionstemplates vi såg tidigare. Ett exempel på ett klasstemplate i standardbiblioteket är *std::vector,* som medför att vi kan välja vad som ska lagras i en given vektor.

#### Grundläggande struktur för en klass

Vi implementerar motsvarigheten till strukten *person* i C++ via en klass döpt *Person*. Vi kommer använda oss utav *camelCase* i stället för *snake_case,* vilket medför att:
* Vi använder oss utav stora bokstäver i stället för understreck i funktions- och typnamn. Så i stället för ett funktionsnamn så som *print_numbers* kommer vi döpa denna funktion *printNumbers*.
* Samma mönster följs för typer så som struktar, klasser och enumerationer. En skillnad är dock att namnet på typer kommer börja med en stor bokstav, exempelvis *Person* i stället för *person,* *LedController* i stället för *led_controller* med mera.

##### 1. Lägg till inkluderingsdirektiv
Vi börjar med att inkludera standardheader *iostream,* så att vi kan generera utskrifter samt får tillgång till vanliga typer så som *std::size_t*:

```cpp
#include <iostream>
```

##### 2. Skapa enumerationsklassen *Gender*
Därefter skapar vi enumerationsklassen *Gender* för implementering av kön. Denna enumerationsklass motsvarar enumerationen *gender* vi implementerade i C förut. 

```cpp
/*******************************************************************************
 * @brief Enumeration class för implementing genders.
 ******************************************************************************/
enum class Gender { Male, Female, Other };
```

Anledningen till att vi väljer att implementera *Gender* som en enumerationsklass i stället för en traditionell enumeration är att vi slipper använda prefix för att undvika namnkrockar; i stället är det inbyggt i språket. 

Notera ovan enumeratorerna nu är döpta *Male, Female* samt *Other* i stället för GENDER_MALE, GENDER_FEMALE samt GENDER_OTHER. Med enumerationsklassen ovan skriver vi i stället *Gender::Male, Gender::Female* samt *Gender::Other.* Notera att vi använder separatorn :: mellan prefixet *Gender* samt enumeratorerna *(Male, Female* samt *Other)*.

I allmänhet är det rekommenderat att använda enumerationsklasser i stället för traditionella enumerationer om man programmerar i modern C++, alltså C++11 och framåt.

##### 3. Definiera klassen *Person*
Därefter definierar vi klassen *Person* via nyckelordet *class:*

```cpp
/*******************************************************************************
 * @brief Class for implementing a person in software.
 ******************************************************************************/
class Person
{
public:

private:

};
```

Vi har lagt till två nyckelord i klassen, *public* och *private*:
* Allt som faller under nyckelordet *public* är synligt och åtkomligt utanför klassen. Allt som vi vill att "användaren" av klassen ska kunna se och använda ska deklareras här, exempelvis metoder (funktioner) för att läsa personens namn, ålder med mera, samt för att kunna skriva ut person datan i terminalen.
* Allt som faller under nyckelordet *private* är inte synligt eller åtkomligt utanför klassen. Här placerar vi allt som vi vill vara icke åtkomligt för "användaren" av klassen, exempelvis hemlig data eller implementationsdetaljer. I vårt fall placerar vi samtliga medlemsvariabler här, då vi inte vill att "användaren" ska kunna ändra på dessa hur som helst. Vi kan också placera metoder som bara ska användas internt i klassen här. Att döja information på detta sätt kallas *inkapsling.*

Som default är allt i en klass privat. Normalt placeras allt som är publikt först i klassen, så att "användaren" vid behov enkelt kan kolla in vad för metoder och annat som hen har till sitt förfogande. Implementationsdetaljerna placerar vi efteråt i den privata delen av klassen och meningen är att användaren inte ens ska behöva (eller vilja) läsa ned hit. 

Oftast dokumenteras enbart den publika delen av klassen; resten av klassen är implementationsdetaljer som enbart är av intresse för utvecklaren av klassen och dokumenteras därmed inte. Eftersom detta är ett typexempel dokumenteras dock all kod.

##### 4. Lägg till medlemsvariabler
Under den privata delen lägger vi till medlemsvariablerna, alltså de variabler i klassen som lagrar personens namn, ålder, kön med mera.
Notera att vi använder prefixet *my*, för att undvika namnkrockar med senare metoder vi kommer lägga till (annars behöver vi använda pekaren *this* likt hur vi använde struktpekaren *self* i C tidigare):

```cpp
/*******************************************************************************
 * @brief Class for implementing a person in software.
 ******************************************************************************/
class Person
{
public:

private:
    const char* myName;       // The person's name.
    unsigned myAge;           // The person's age.
    Gender myGender;          // The person's gender.
    const char* myAddress;    // The person's address.
    const char* myOccupation; // The person's occupation.
    bool myIsSingle;          // Indicates if the person is single.
};
```

Medlemsvariablerna är privata, så att "användaren" inte kan läsa och skriva dem hur som helst. Vi kommer senare lägga till så kallade get- och set-metoder för att styra vad "användaren" kan läsa och skriva. Som exempel bör man kunna ändra personens singelstatus eller yrke, men nödvändigtvis inte hens namn eller kön (inte i denna implementering i alla fall).

##### 5. Lägg till konstruktorer
Men innan vi lägger till några get- och set-metoder lägger vi till konstruktorer, vilket kan ses som initieringsrutiner som anropas automatiskt när ett objekt av klassen skapas.

Först och främst raderar vi den så kallade default-konstruktorn, så att man inte kan skapa ett person-objekt utan att skicka med namn, ålder med mera.

Under den publika delen lägger vi därmed följande:

```cpp
public:
    /** Default constructor deleted. */
    Person() = delete;
```

Man kallar denna konstruktor för default-konstruktor, då den inte har några ingående argument. Därmed är det inte möjligt att skapa ett tomt objekt så som visas nedan:

```cpp
Person person{}; // Won't compile, since the default constructor is deleted.
```

Klassen ser nu ut så här:

```cpp
/*******************************************************************************
 * @brief Class for implementing a person in software.
 ******************************************************************************/
class Person
{
public:
    /** Default constructor deleted. */
    Person() = delete;
    
private:
    const char* myName;       // The person's name.
    unsigned myAge;           // The person's age.
    Gender myGender;          // The person's gender.
    const char* myAddress;    // The person's address.
    const char* myOccupation; // The person's occupation.
    bool myIsSingle;          // Indicates if the person is single.
};
```

Vi vill att användaren ska ange persondatan direkt när ett person-objekt skapas. Vi skapar då en konstruktor som tar personens namn, ålder, kön, adress, yrke samt singel-status som ingående argument. Vi sätter singelstatusen till default-värdet *true,* så "användaren" behöver inte ange just denna (om hen inte anger något antar vi att personen är singel):

```cpp
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
           const char* address, const char* occupation, const bool single = true)
    {
    }
```

I konstruktorn ovan initierar vi medlemsvariablerna så att:
* *myName* tilldelas namnet som refereras till av ingående argument *name.*
* *myAge* tilldelas värdet som lagras av ingående argument *age.*
* *myGender* tilldelas värdet som lagras av ingående argument *gender.*
* *myAddress* tilldelas adressen som refereras till av ingående argument *address.*
* *myOccupation* tilldelas yrket som refereras till av ingående argument *ocupation.*
* *myIsSingle* tilldelas värdet som lagras av ingående argument *single.* Som default är *single* satt till *true*.

Detta åstadkommer vi genom att lägga till en initieringsdel  mellan funktionshuvudet samt funktionskroppen (markerad via måsvingar {}). Notera att vi börjar initieringsdelen med ett kolon, initierar med måsvingar (så *myName{name}* betyder i praktiken att *myName = name)* och separerar initieringen av varje medlemsvariabel med ett kommatecken:

```cpp
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
           const char* address, const char* occupation, const bool single = true)
        : myName{name}
        , myAge{age}
        , myGender{gender}
        , myAddress{address}
        , myOccupation{occupation}
        , myIsSingle{single} {}
```

Om vi behöver göra något ytterligare efter initieringen av medlemsvariablerna hade vi kunnat placera detta i konstruktorns funktionskropp. I detta fall vill vi dock enbart initiera medlemsvariablerna, så vi behöver inte lägga till något ytterligare. Vi placerar därmed med fördel måsvingarna på sista initieringsraden för att inte uppta onödigt mycket blanka rader. 

Man kan nu använda konstruktorn som visas ovan för att initiera person-objekt. Nedan visas hur vi initierar objektet *person1* för att lagra persondata gällande den 42-åriga juristen Marie Nilsson, som är singel:

```cpp
Person person1{"Marie Nilsson", 42, Gender::Female,
               "Juristgatan 17", "Lawyer"};
```
                   
Eftersom Marie är singel och default-värdet för det ingående argumentet som lagrar singelstatusen är *true* struntade vi att tilldela ett värde gällande singelstatusen explicit ovan. Vi hade dock kunnat lägga till *true* som sista ingående argument:

```cpp
Person person1{"Marie Nilsson", 42, Gender::Female,
               "Juristgatan 17", "Lawyer", true};
```

Vi kan också använda konstruktorn för att initiera objektet *person2* för att lagra persondata gällande den 37-åriga läraren Sven Andersson.
Eftersom han inte är singel sätter vi värdet *false* på singelstatusen (det sista ingående argumentet) explicit.

```cpp
Person person2{"Sven Andersson", 37, Gender::Male,
               "Kunskapsgatan 4", "Teacher", false};
```

Klassen ser nu åt så som visas nedan:

```cpp
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
           const char* address, const char* occupation, const bool single = true)
        : myName{name}
        , myAge{age}
        , myGender{gender}
        , myAddress{address}
        , myOccupation{occupation}
        , myIsSingle{single} {}
    
private:
    const char* myName;       // The person's name.
    unsigned myAge;           // The person's age.
    Gender myGender;          // The person's gender.
    const char* myAddress;    // The person's address.
    const char* myOccupation; // The person's occupation.
    bool myIsSingle;          // Indicates if the person is single.
};
```

##### 5. Lägg till get- och set-metoder
För att vi ska kunna styra vilka av medlemsvariablerna vars innehåll enbart kan läsas och vilka som både kan läsas och skrivas använder vi så kallade get- och setmetoder:
* Get-metoder ger oss möjlighet att läsa innehållet av en medlemsvariabel. Som exempel, en get-metod döpt *name* kan användas för att låta "användaren" av klassen ta reda på personens namn.
* Set-metoder ger oss möjlighet att skriva/ändra innehållet på en medlemsvariabel. Som exempel, en set-metod döpt *setOccupation* hade kunnat användas för att byta personens yrke från "Lawyer" till "Judge".

Get-metoder returnerar värdet som ska läsas, exempelvis personens namn, medan set-metoder tar det nya värdet som ska skrivas som ingående argument.

För att get- och set-metoderna ska vara åtkomliga utanför klassen placeras dessa i den publika delen av klassen, direkt efter konstruktorn. 

Nedan visas exempel på get-metoder *name* samt *age,* som returnerar det lagrade namnet samt åldern:

```cpp
/*******************************************************************************
 * @brief Provides the person's name.
 * 
 * @return Reference to string holding the person's name.
 ******************************************************************************/
const char* name() const { return myName; }

/*******************************************************************************
 * @brief Provides the person's age.
 * 
 * @return The person's age as an integer.
 ******************************************************************************/
unsigned age() const { return myAge; }
```

Notera att vi skriver nyckelordet *const* direkt efter funktionshuvudet, då vi ser till att klassen innehåll bara ska kunna läsas. Vi kan därmed inte av misstag råka ändra någon av klassmedlemmarna (hade vi gjort det hade ett kompileringsfel genererats).

Vi hade kunnat använda get-metoderna ovan för att läsa och skriva ut åldern på Marie Nilsson, som tidigare implementerades i mjukvaran via objektet *person1:*

```cpp
int main()
{
    Person person1{"Marie Nilsson", 42, Gender::Female,
                   "Juristgatan 17", "Lawyer"};
    std::cout << "Name:\t" << person1.name() << "\n";
    std::cout << "Age:\t" << person1.age() << "\n";
    return 0;
}
```

Utskriften blir följande:

```
Name:   Marie Nilsson
Age:    42
```

Vi lägger till get-metoder för övriga medlemsvariabler. Vi döper dessa till *gender, address, occupation* samt *isSingle:*

```cpp
/*******************************************************************************
 * @brief Provides the person's gender.
 * 
 * @return The person's gender as an enumerator of enumeration class Gender.
 ******************************************************************************/
Gender gender() const { return myGender; }

/*******************************************************************************
 * @brief Provides the person's home address.
 * 
 * @return Reference to string holding the person's home address.
 ******************************************************************************/
const char* address() const { return myAddress; }

/*******************************************************************************
 * @brief Provides the person's occupation.
 * 
 * @return Reference to string holding the person's occupation.
 ******************************************************************************/
const char* occupation() const { return myOccupation; }

/*******************************************************************************
 * @brief Indicates if the person is single.
 * 
 * @return True if the person is single, else false.
 ******************************************************************************/
bool isSingle() const { return myIsSingle; }
```

Vi lägger därefter till set-metoder för att kunna ändra personens hemadress, yrke samt singelstatus. Vi lägger till prefixet set på dessa för att tydliggöra att dessa ska användas för att sätta ett värde (det hade dock fungerat utmärkt att döpa dessa samma som motsvarande get-metoder, då C++-kompilatorn kan tolka vilken av metoderna du avser att anropa utefter argumentlistan):

```cpp
/*******************************************************************************
 * @brief Sets new home address.
 * 
 * @param newAddress Reference to string holding the new address.
 ******************************************************************************/
void setAddress(const char* newAddress) { myAddress = newAddress; }

/*******************************************************************************
 * @brief Sets new occupation.
 * 
 * @param newOccupation Reference to string holding the new occupation.
 ******************************************************************************/
void setOccupation(const char* newOccupation) { myOccupation = newOccupation; }

/*******************************************************************************
 * @brief Updates the person's single status.
 * 
 * @param single True if the person now is single.
 ******************************************************************************/
void setSingleStatus(const bool single) { myIsSingle = single; }
```

Om vi exempelvis kallar på *setAddress* ser vi till att medlemsvariabeln *myAddress* tilldelas den nya adress som refereras till av ingående argument *newAddress*. 

Vi kallar på *setAddress* för att ändra Maria Nilssons hemadress från Juristgatan 17 till Kaggeledsgatan 3*. Vi skriver ut hennes hemadress både innan och efter anropet:

```cpp
int main()
{
    Person person1{"Marie Nilsson", 42, Gender::Female,
                   "Juristgatan 17", "Lawyer"};
    std::cout << "Name:\t\t" << person1.name() << "\n";
    std::cout << "Age:\t\t" << person1.age() << "\n";
    std::cout << "Old address:\t" << person1.address() << "\n";
    
    person1.setAddress("Kaggeledsgatan 3");
    std::cout << "New address:\t" << person1.address() << "\n";
    return 0;
}
```

Utskriften blir följande:

```
Name:           Marie Nilsson
Age:            42
Old address:    Juristgatan 17
New address:    Kaggeledsgatan 3
```

Efter tillägg av get- och set-metoderna ser klassen *Person* ut så här:

```cpp
/*******************************************************************************
 * @brief Class for implementing a person in software.
 ******************************************************************************/
class Person
{
public:

    Person() = delete; // Default constructor deleted.
    
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
           const char* address, const char* occupation, const bool single = true)
        : myName{name}
        , myAge{age}
        , myGender{gender}
        , myAddress{address}
        , myOccupation{occupation}
        , myIsSingle{single} 
    {}

    /*******************************************************************************
     * @brief Provides the person's name.
     * 
     * @return Reference to string holding the person's name.
     ******************************************************************************/
    const char* name() const { return myName; }

    /*******************************************************************************
     * @brief Provides the person's age.
     * 
     * @return The person's age as an integer.
     ******************************************************************************/
    unsigned age() const { return myAge; }

    /*******************************************************************************
     * @brief Provides the person's gender.
     * 
     * @return The person's gender as an enumerator of enumeration class Gender.
     ******************************************************************************/
    Gender gender() const { return myGender; }

    /*******************************************************************************
     * @brief Provides the person's home address.
     * 
     * @return Reference to string holding the person's home address.
     ******************************************************************************/
    const char* address() const { return myAddress; }

    /*******************************************************************************
     * @brief Provides the person's occupation.
     * 
     * @return Reference to string holding the person's occupation.
     ******************************************************************************/
    const char* occupation() const { return myOccupation; }

    /*******************************************************************************
     * @brief Indicates if the person is single.
     * 
     * @return True if the person is single, else false.
     ******************************************************************************/
    bool isSingle() const { return myIsSingle; }

    /*******************************************************************************
     * @brief Sets new home address.
     * 
     * @param newAddress Reference to string holding the new address.
     ******************************************************************************/
    void setAddress(const char* newAddress) { myAddress = newAddress; }

    /*******************************************************************************
     * @brief Sets new occupation.
     * 
     * @param newOccupation Reference to string holding the new occupation.
     ******************************************************************************/
    void setOccupation(const char* newOccupation) { myOccupation = newOccupation; }
    
    /*******************************************************************************
     * @brief Updates the person's single status.
     * 
     * @param single True if the person now is single.
     ******************************************************************************/
    void setSingleStatus(const bool single) { myIsSingle = single; }

private:
    const char* myName;       // The person's name.
    unsigned myAge;           // The person's age.
    Gender myGender;          // The person's gender.
    const char* myAddress;    // The person's address.
    const char* myOccupation; // The person's occupation.
    bool myIsSingle;          // Indicates if the person is single.
};
```

##### 6. Lägg till generella metoder
Vi kan sedan lägga till övriga metoder för att hantera eller använda persondatan. Vi lägger därmed till metoden *print* för att skriva ut den lagrade persondatan:

```cpp
/*******************************************************************************
 * @brief Prints personal data about the specific person.
 * 
 * @param ostream Reference to output stream (default = terminal print).
 ******************************************************************************/
void print(std::ostream& ostream = std::cout) const
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
```

Notera att vi använder ett ingående argument i form av en referens till en utström, *ostream*, för att kunna välja vart datan ska skrivas. Som default skriver vi till terminalen, så defaultvärdet sätts till *std::cout*. Men om man vi kan man exempelvis skriva till en fil.

Notera i detta fall att vi kallar på egna metoder *genderAsText* samt *isSingleAsText* för att erhålla personens kön samt om hen är singel som text. Dessa metoder ska enbart användas internt för användning i metoden *print* och bör bör då med fördel implementeras som privata metoder. 

Vi lägger därmed till dessa metoder under nyckelordet *private,* ovanför medlemsvariablerna:

```cpp
private:

/*******************************************************************************
 * @brief Provides the person's gender as text.
 * 
 * @return Reference to string holding the person's gender.
 ******************************************************************************/
const char* genderAsText() const
{
    if (myGender == Gender::Male) { return "Male"; }
    else if (myGender == Gender::Female) { return "Female"; }
    else { return "Other"; }
}

/*******************************************************************************
 * @brief Provides string indicating if the person is single.
 * 
 * @return "Yes" if the person is single, else "No".
 ******************************************************************************/
const char* isSingleAsText() const { return myIsSingle ? "Yes" : "No"; }
```

Vi kan sedan enkelt skriva ut Marie Nilssons persondata genom att kalla på metoden *print* i stället för att göra terminalutskriften i *main:*

```cpp
int main()
{
    Person person1{"Marie Nilsson", 42, Gender::Female,
                   "Juristgatan 17", "Lawyer"};
    person1.print();
    return 0;
}
```

Vi hade också kunnat skriva persondatan till filen *person.txt* via en filström av datatypen *std::ofstream* från standardheader *fstream*. Vi inkluderar därmed *fstream* i aktuell fil:

```cpp
#include <fstream>
```

I funktionen *main* skapar vi sedan en filström döpt *ofstream* för att öppna filen *person.txt* för skrivning. Om filen inte finns skapas den nu:

```cpp
std::ofstream ofstream{"person.txt"};
```

Vi skriver sedan persondatan till filen *person.txt* genom att anropa metoden *print* med *ofstream* som ingående argument:

```cpp
person1.print(ofstream);
```

Nedan visas hur vi kan skriva persondatan både till terminalen samt till filen *person.txt* via två anrop av metoden *print*:

```cpp
int main()
{
    Person person1{"Marie Nilsson", 42, Gender::Female,
                   "Juristgatan 17", "Lawyer"};
    std::ofstream ofstream{"person.txt"};
    person1.print();         // Prints in the terminal.
    person1.print(ofstream); // Writes to file "person.txt".
    return 0;
}
```

Klassen *Person* ser nu ut så som visas nedan:

```cpp
/*******************************************************************************
 * @brief Class for implementing a person in software.
 ******************************************************************************/
class Person
{
public:

    Person() = delete; // Default constructor deleted.
    
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
           const char* address, const char* occupation, const bool single = true)
        : myName{name}
        , myAge{age}
        , myGender{gender}
        , myAddress{address}
        , myOccupation{occupation}
        , myIsSingle{single} 
    {}

    /*******************************************************************************
     * @brief Provides the person's name.
     * 
     * @return Reference to string holding the person's name.
     ******************************************************************************/
    const char* name() const { return myName; }

    /*******************************************************************************
     * @brief Provides the person's age.
     * 
     * @return The person's age as an integer.
     ******************************************************************************/
    unsigned age() const { return myAge; }

     /*******************************************************************************
     * @brief Provides the person's gender.
     * 
     * @return The person's gender as an enumerator of enumeration class Gender.
     ******************************************************************************/
    Gender gender() const { return myGender; }

    /*******************************************************************************
     * @brief Provides the person's home address.
     * 
     * @return Reference to string holding the person's home address.
     ******************************************************************************/
    const char* address() const { return myAddress; }

    /*******************************************************************************
     * @brief Sets new home address.
     * 
     * @param newAddress Reference to string holding the new address.
     ******************************************************************************/
    void setAddress(const char* newAddress) { myAddress = newAddress; }

    /*******************************************************************************
     * @brief Provides the person's occupation.
     * 
     * @return Reference to string holding the person's occupation.
     ******************************************************************************/
    const char* occupation() const { return myOccupation; }

    /*******************************************************************************
     * @brief Sets new occupation.
     * 
     * @param newOccupation Reference to string holding the new occupation.
     ******************************************************************************/
    void setOccupation(const char* newOccupation) { myOccupation = newOccupation; }

    /*******************************************************************************
     * @brief Indicates if the person is single.
     * 
     * @return True if the person is single, else false.
     ******************************************************************************/
    bool isSingle() const { return myIsSingle; }

    /*******************************************************************************
     * @brief Updates the person's single status.
     * 
     * @param single True if the person now is single.
     ******************************************************************************/
    void setSingleStatus(const bool single) { myIsSingle = single; }

    /*******************************************************************************
     * @brief Prints personal data about the specific person.
     * 
     * @param ostream Reference to output stream (default = terminal print).
     ******************************************************************************/
    void print(std::ostream& ostream = std::cout) const
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

private:

    /*******************************************************************************
     * @brief Provides the person's gender as text.
     * 
     * @return Reference to string holding the person's gender.
     ******************************************************************************/
    const char* genderAsText() const
    {
        if (myGender == Gender::Male) { return "Male"; }
        else if (myGender == Gender::Female) { return "Female"; }
        else { return "Other"; }
    }

    /*******************************************************************************
     * @brief Provides string indicating if the person is single.
     * 
     * @return "Yes" if the person is single, else "No".
     ******************************************************************************/
    const char* isSingleAsText() const { return myIsSingle ? "Yes" : "No"; }

    const char* myName;       // The person's name.
    unsigned myAge;           // The person's age.
    Gender myGender;          // The person's gender.
    const char* myAddress;    // The person's address.
    const char* myOccupation; // The person's occupation.
    bool myIsSingle;          // Indicates if the person is single.
};
```

##### Exempelprogram

Nedan visas ett program, där Marie Nilssons och Sven Anderssons personuppgifter skrivs ut i terminalen samt till en fil döpt *person.txt.* Allt är implementerat i en enda fil:

```cpp
#include <fstream>
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

    Person() = delete; // Default constructor deleted.
    
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
           const char* address, const char* occupation, const bool single = true)
        : myName{name}
        , myAge{age}
        , myGender{gender}
        , myAddress{address}
        , myOccupation{occupation}
        , myIsSingle{single} 
    {}

    /*******************************************************************************
     * @brief Provides the person's name.
     * 
     * @return Reference to string holding the person's name.
     ******************************************************************************/
    const char* name() const { return myName; }

    /*******************************************************************************
     * @brief Provides the person's age.
     * 
     * @return The person's age as an integer.
     ******************************************************************************/
    unsigned age() const { return myAge; }

     /*******************************************************************************
     * @brief Provides the person's gender.
     * 
     * @return The person's gender as an enumerator of enumeration class Gender.
     ******************************************************************************/
    Gender gender() const { return myGender; }

    /*******************************************************************************
     * @brief Provides the person's home address.
     * 
     * @return Reference to string holding the person's home address.
     ******************************************************************************/
    const char* address() const { return myAddress; }

    /*******************************************************************************
     * @brief Sets new home address.
     * 
     * @param newAddress Reference to string holding the new address.
     ******************************************************************************/
    void setAddress(const char* newAddress) { myAddress = newAddress; }

    /*******************************************************************************
     * @brief Provides the person's occupation.
     * 
     * @return Reference to string holding the person's occupation.
     ******************************************************************************/
    const char* occupation() const { return myOccupation; }

    /*******************************************************************************
     * @brief Sets new occupation.
     * 
     * @param newOccupation Reference to string holding the new occupation.
     ******************************************************************************/
    void setOccupation(const char* newOccupation) { myOccupation = newOccupation; }

    /*******************************************************************************
     * @brief Indicates if the person is single.
     * 
     * @return True if the person is single, else false.
     ******************************************************************************/
    bool isSingle() const { return myIsSingle; }

    /*******************************************************************************
     * @brief Updates the person's single status.
     * 
     * @param single True if the person now is single.
     ******************************************************************************/
    void setSingleStatus(const bool single) { myIsSingle = single; }

    /*******************************************************************************
     * @brief Prints personal data about the specific person.
     * 
     * @param ostream Reference to output stream (default = terminal print).
     ******************************************************************************/
    void print(std::ostream& ostream = std::cout) const
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

private:

    /*******************************************************************************
     * @brief Provides the person's gender as text.
     * 
     * @return Reference to string holding the person's gender.
     ******************************************************************************/
    const char* genderAsText() const
    {
        if (myGender == Gender::Male) { return "Male"; }
        else if (myGender == Gender::Female) { return "Female"; }
        else { return "Other"; }
    }

    /*******************************************************************************
     * @brief Provides string indicating if the person is single.
     * 
     * @return "Yes" if the person is single, else "No".
     ******************************************************************************/
    const char* isSingleAsText() const { return myIsSingle ? "Yes" : "No"; }

    const char* myName;       // The person's name.
    unsigned myAge;           // The person's age.
    Gender myGender;          // The person's gender.
    const char* myAddress;    // The person's address.
    const char* myOccupation; // The person's occupation.
    bool myIsSingle;          // Indicates if the person is single.
};

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
```

Utskriften i terminalen samt filinnehållet i filen *person.txt* blir följande:

```
--------------------------------------------------------------------------------
Name:		Marie Nilsson
Age:		42
Gender:		Female
Address:	Juristgatan 17
Occupation:	Lawyer
Single:		Yes
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
Name:		Sven Andersson
Age:		37
Gender:		Male
Address:	Kunskapsgatan 4
Occupation:	Teacher
Single:		No
--------------------------------------------------------------------------------
```

#### Uppdelning i header- och källkodsfiler för klasser
Ofta används objekt av många olika klasser i ett program. Dessa klasser är dessutom ofta större än klassen *person* som demonstrerades tidigare. Det är därmed opraktiskt att implementera samtliga klasser i en enda fil. 

Oftast skapar main en headerfil dedikerad för en specifik klass. Som exempel, för klassen *Person* kan vi med fördel lägga till headerfilen *person.h* och implementera denna klass där i.

Längst upp i *person.h* placerar vi direktivet #pragma once, som ser att vi inte råkar definiera multipla kopior av innehållet i denna headerfil om den inkluderas i flera olika filer, på samma sätt som header guards fungerar i C. Innehållet i *person.h* kommer därmed endast defineras en enda gång:

##### Filen *person.h*

```cpp
#pragma once
```

Vi klistrar sedan in klassen *Person* i denna fil. Vi lägger också till standardheader *iostream,* annars kommer inte *std::ostream* samt *std::cout* i metoden *print* att kännas igen, vilket kommer leda till ett kompileringsfel:

```cpp
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

    Person() = delete; // Default constructor deleted.
    
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
           const char* address, const char* occupation, const bool single = true)
        : myName{name}
        , myAge{age}
        , myGender{gender}
        , myAddress{address}
        , myOccupation{occupation}
        , myIsSingle{single} 
    {}

    /*******************************************************************************
     * @brief Provides the person's name.
     * 
     * @return Reference to string holding the person's name.
     ******************************************************************************/
    const char* name() const { return myName; }

    /*******************************************************************************
     * @brief Provides the person's age.
     * 
     * @return The person's age as an integer.
     ******************************************************************************/
    unsigned age() const { return myAge; }

     /*******************************************************************************
     * @brief Provides the person's gender.
     * 
     * @return The person's gender as an enumerator of enumeration class Gender.
     ******************************************************************************/
    Gender gender() const { return myGender; }

    /*******************************************************************************
     * @brief Provides the person's home address.
     * 
     * @return Reference to string holding the person's home address.
     ******************************************************************************/
    const char* address() const { return myAddress; }

    /*******************************************************************************
     * @brief Sets new home address.
     * 
     * @param newAddress Reference to string holding the new address.
     ******************************************************************************/
    void setAddress(const char* newAddress) { myAddress = newAddress; }

    /*******************************************************************************
     * @brief Provides the person's occupation.
     * 
     * @return Reference to string holding the person's occupation.
     ******************************************************************************/
    const char* occupation() const { return myOccupation; }

    /*******************************************************************************
     * @brief Sets new occupation.
     * 
     * @param newOccupation Reference to string holding the new occupation.
     ******************************************************************************/
    void setOccupation(const char* newOccupation) { myOccupation = newOccupation; }

    /*******************************************************************************
     * @brief Indicates if the person is single.
     * 
     * @return True if the person is single, else false.
     ******************************************************************************/
    bool isSingle() const { return myIsSingle; }

    /*******************************************************************************
     * @brief Updates the person's single status.
     * 
     * @param single True if the person now is single.
     ******************************************************************************/
    void setSingleStatus(const bool single) { myIsSingle = single; }

    /*******************************************************************************
     * @brief Prints personal data about the specific person.
     * 
     * @param ostream Reference to output stream (default = terminal print).
     ******************************************************************************/
    void print(std::ostream& ostream = std::cout) const
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

private:

    /*******************************************************************************
     * @brief Provides the person's gender as text.
     * 
     * @return Reference to string holding the person's gender.
     ******************************************************************************/
    const char* genderAsText() const
    {
        if (myGender == Gender::Male) { return "Male"; }
        else if (myGender == Gender::Female) { return "Female"; }
        else { return "Other"; }
    }

    /*******************************************************************************
     * @brief Provides string indicating if the person is single.
     * 
     * @return "Yes" if the person is single, else "No".
     ******************************************************************************/
    const char* isSingleAsText() const { return myIsSingle ? "Yes" : "No"; }

    const char* myName;       // The person's name.
    unsigned myAge;           // The person's age.
    Gender myGender;          // The person's gender.
    const char* myAddress;    // The person's address.
    const char* myOccupation; // The person's occupation.
    bool myIsSingle;          // Indicates if the person is single.
};
```

##### Filen main.cpp
Vi inkluderar sedan filen *person.h* i samma fil som funktionen *main* ligger i, alltså *main.cpp*. Innehållet i denna fil kan då reduceras till följande:

```cpp
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
```

Programmet fungerar i övrigt på samma sätt som tidigare.

##### Metoddefinitioner i filen *person.cpp*

Ofta placeras klassenS metoddefinitioner i en separat källkodsfil för att hålla headerfilen mer läsbart. Som exempel, för att hålla filen *person.h* läsbar kan vi med fördel placera metoddefinitionerna i en källkodsfil döpt *person.cpp*. 

Längst upp i denna källkodsfil inkluderar vi headerfilen *person.h:*

```cpp
#include "person.h"
```

Därefter placerar vi metoddefinitionerna från klassen *Person* i denna fil.
Vi kopierar därmed samtliga metoder från klassen *Person* till denna fil. Värt att notera är att:
* För att kompilatorn ska förstå att respektive metod tillhör klassen *Person* måste vi använder prefixet *Person. Så metoden *print* måste definieras som *Person::print* som exempel. 
* Värt att notera är också att defaultvärden på ingående argument bara ska skrivas i funktionsdeklarationen i headerfilen.

Vi börjar med metoden *print*. I headerfilen *person.h* låter vi metodhuvudet inklusive dokumentationen kvarstå:

```cpp
/*******************************************************************************
 * @brief Prints personal data about the specific person.
 * 
 * @param ostream Reference to output stream (default = terminal print).
 ******************************************************************************/
void print(std::ostream& ostream = std::cout) const;
```

I källkodsfilen *person.cpp* placerar vi därmed metoddefinitionen:

```cpp
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
```

Notera att defaultvärdet på ingående argument *ostream* endast definieras i funktionsdeklarationen i headerfilen. Om vi hade haft kvar defaultvärdet i funktionsdeklarationen när de är separerade hade ett kompilatorfel genererats.

Vi implementerar definitioner för övriga metoder i källkodsfilen *person.cpp.* Vi placerar en rad med bindestreck mellan varje metod för att visuellt separera dessa nu när metoddokumentationen inte är med. 

##### Filen *person.cpp*
Efter att ha lagt till samtliga metoddefinitioner ser filen *person.cpp* ut så här:

```cpp
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
```

##### Filen *person.h*
Läsbarheten i headerfilen *person.h* ökar nu, då vi har tagit bort en stor del av implementeringsdetaljerna i och med metoddefinitionerna. Vi måste dock fortfarande ha var metoddeklarationer samt definition av medlemsvariablerna innanför klassen:

```cpp
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
```

##### Filen *main.cpp*
Att vi delade upp klassen *Person* i en headerfil *person.h* samt källkodsfil *person.cpp* har ingen påverkan på filen *main.cpp.* Återigen behöver vi enbart inkludera filen *person.h,* därefter kan vi skapa personobjekt, skriva ut innehåll med mera:

```cpp
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
```

#### Slutförd komimplementation
Filer *person.h,* *person.cpp* samt *main.cpp* finns tillgängliga i underkatalogen *person*, tillsammans med en makefil för kompilering och körning av koden.   Instruktioner för byggande samt körande av koden finns i bifogad README-fil.

#### Sammanfattning
Efter att ha gått igenom detta stycke bör du som läsare ha tillräckligt med kunskap för att skapa en mindre klass.
* Kunna styra vad som är synligt respektive inte synligt utanför en klass.
* Dölja hemlig data samt informationsdetaljer i en klass via inkapsling.
* Kunna skapa konstruktorer för att initiera objekt av klassen i fråga.
* Kunna styra vad som kan läsas samt vad som kan läsas och skrivas via get- och set-metoder.
* Dela upp en klass i en headerfil samt en källkodsfil.
* Skapa enumerationsklasser.

Testa gärna dina kunskaper genom att genomföra övningsuppgiften i underkatalogen *exercise.* 

#### Fördjupning
Det finns mycket mer att lära sig om klasser och objektorientering än vad som presenterades här; detta ämne hade kunnat täcka en hel kurs. 
För mer information:
* Se boken [*The C++ Programming Language*](https://www.adlibris.com/se/bok/c-programming-language-the-9780321958327) av Bjarne Stroustrup, skapare av C++. Denna bok täcker det mesta som behöver kännas till om modern C++ (förutom sådant som har kommit till efter att den senaste upplagan släpptes), inte bara klasser. 
* En hel del fördjupad information finns också i klass-avsnittet på [*cplusplus.com*](https://cplusplus.com/doc/tutorial/classes/).  




