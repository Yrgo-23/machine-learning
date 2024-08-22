# 2024-08-23 - Lektion 2

## Dagordning
* Funktionstemplates med *constraints* i C++ (återigen med vektorer).
* Inlämningsuppgift innefattande program med vektorer i C++.
* Installation av WSL för att kunna använda klassrepot lokalt.

## Mål med lektionen
* Kunna implementera funktionstemplates i C++.
* Kunna använda *type traits* för att sätta *constraints* gällande vilka datatyper som är giltiga för en given funktion (och generera ett kompileringsfel med tillhörande felmeddelande om en icke tillåten datatyp används).
* Ha genomfört och lämnat in inlämningsuppgift 1 (innan kl. 16:00).

## Instruktioner
* Läs om funktionstemplates i detta dokument, alternativt kolla min [video tutorial](https://www.youtube.com/watch?v=mbRiN_QmjUY).  
  ***OBS!** Denna video behandlar inte *constraints* via så kallade *type traits*, se information om detta nedan!*
* Inlämningsuppgift 1 är tillgänglig på Classroom kl. 10:00.
* Se `README.md` i roten av detta repo för instruktioner gällande installation av WSL. Jag kommer vid behov hjälpa er med installationen under lektionens gång, men har du tid får du gärna genomföra installtionen innan lektionen.

## Utvärdering
* Några synpunkter på lektionen i sig?

## Nästa lektion
* Grundläggande objektorientering i C++: klasser, inkapsling med mera.
* Övningsuppgifter innefattande skapande av klasser i C++.

## Funktionstemplates i C++

Funktionstemplates ger oss möjligheten att göra datatypen för ingående argument eller returtypen till en funktion valbar.
Som exempel kan funktioner som behandlar tal med fördel göras möjliga att använda för alla numeriska typer.

Som exempel skapade vi en funktion döpt `print` för att skriva ut heltal lagrade i en vektor föregående lektion. Denna funktion visas nedan:

```cpp
/*******************************************************************************
 * @brief Prints numbers held by referenced vector. Each number is printed
 *        on a separate line.
 * 
 * @param numbers Reference to vector holding the numbers to print.
 * @param ostream Reference to output stream (default = terminal print).
 ******************************************************************************/
void print(const std::vector<int>& numbers, std::ostream& ostream = std::cout)
{
    if (numbers.empty()) { return; }
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& number : numbers)
    {
        ostream << number << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}
```

Notera att denna funktion bara fungerar för vektorer innehållande heltal av datatypen `int`. Vektorns datatyp är därmed implementerad som `std::vector<int>`.  Via så kallade templates kan vi göra så att denna datatyp i stället är valbar, se nedan:

```cpp
/*******************************************************************************
 * @brief Prints numbers held by referenced vector. Each number is printed
 *        on a separate line.
 *
 * @tparam T The type of the data held in the vector.
 * 
 * @param numbers Reference to vector holding the numbers to print.
 * @param ostream Reference to output stream (default = terminal print).
 ******************************************************************************/
template <typename T>
void print(const std::vector<T>& numbers, std::ostream& ostream = std::cout)
{
    if (numbers.empty()) { return; }
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& number : numbers)
    {
        ostream << number << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}
```

Notera att:
* Vi skriver `template <typename T>` direkt innan funktionshuvudet för att deklarerar att vi vill ha en valbar datatyp T, som i detta fall kallas T.
* Framför typen T skriver vi nyckelordet `typename` (eller `class`).
* Vi kan sätta ett defaultvärde på datatypen T i ett funktionstemplate genom att skriva detta som defaultvärden till en funktion. Exempelvis T = `int` medför att T som default sätts till `int` om inget annat specificeras eller T sätts via argumentlistan.

### Implementering av funktionstemplates i körbara filer

Kompilatorn kommer skapa en kopia av denna funktion för varje datatyp som vi passerar. Detta innebär att om vi aldrig anropar funktionen `print` kommer denna implementeras i aktuell binär (det körbara programmet som skapas efter kompilering och länkning). 

Däremot om vi anropar funktionen `print` med vektorer innehållande datatyper `int` och `double` kommer två kopior av denna funktion skapas, en där T = `int` och en där T = `double`:

```cpp
const std::vector<int> v1{1, 2, 3};
const std::vector<double> v2{0.5, 1.5, 2.5};

print(v1); // Calls print with T = int.
print(v2); // Calls print with T = double.
```

Anropet av `print` med vektor v1 innehållande heltal av datatypen `int` medför att följande kopia av funktionen `print` kommer genereras i binären:

```cpp
void print(const std::vector<int>& numbers, std::ostream& ostream = std::cout)
{
    if (numbers.empty()) { return; }
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& number : numbers)
    {
        ostream << number << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}
```

På samma sätt gäller att anropet av `print` med vektor v2 innehållande flyttal av datatypen `double` medför att följande kopia av funktionen `print` kommer genereras i binären:

```cpp
void print(const std::vector<double>& numbers, std::ostream& ostream = std::cout)
{
    if (numbers.empty()) { return; }
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& number : numbers)
    {
        ostream << number << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}
```

Detta innebär givetvis att storleken på våra binärer kan öka avsevärt om multipla kopior av ett funktionstemplate anropas, framförallt om funktionen är större. Detta kan särskilt vara ett problem i inbyggda system, vilket medför att man ibland försöker undvika templates i sådana applikationer. 

Ett annat alternativ är att använda så kallade *constraints* för att begränsa vilka datatyper som kan användas (och därmed begränsa antalet möjliga kopior av funktionen), vilket behandlas i nästa del.

### *Type traits* för att generera *constraints*
Funktionen `print` ovan går att att använda för vilken datatyp som helst. En funktion som denna fungerar ypperligt för numeriska typer och även strängar, men den kommer också fungera att anropa för egenskapade typer och annat, som eventuellt inte går att skriva ut.

Via så kallade *type traits* kan vi också sätta så kallade *constraints* (begränsningar) på vilka datatyper som är tillåtna för en viss funktion.
Som exempel vore det dumt att kunna passera text till en funktion som ska utföra en eller flera aritmetiska operationer.

Det finns ett flertal *type traits* inbyggda i C++ standardbibliotek. För att använda dessa behöver vi inkludera standardheadern `<type_traits>`:

```cpp
#include <type_traits>
```

Några vanliga *type traits* presenteras nedan:
* `std::is_arithmetic`: Indikerar ifall en specifik datatyp T är aritmetisk/numerisk, både heltals- och flyttalsdatatyper.
* `std::is_integral`: Indikerar ifall en specifik datatyp T är av heltalstyp, antingen signerad eller osignerad.
* `std::is_unsigned`: Indikerar ifall en specifik datatyp T är av osignerad heltalstyp, såsom `std::uint8_t` och `std::uint32_t`.
* `std::is_unsigned`: Indikerar ifall en specifik datatyp T är av signerad heltalstyp, såsom `int` och `long`.
* `std::is_floating_point`: Indikerar ifall en specifik datatyp T är en flyttalsdatatyp. 

Fler *type traits* hittar du [här](https://en.cppreference.com/w/cpp/header/type_traits).

Vi kan använda en eller flera av ovanstående *type traits* i funktionen `print` ovan för att generera ett kompileringsfel med ett felmeddelande om något annat än en vektor innehållande en numerisk typ passeras. Detta gör vi via ett så kallat påstående *(assertion)* som medför att vi kontrollerar datatypen T under kompileringen via ett påstående med hjälp av  *std::is_arithmetic.* Specifikt kollar vi om medlemmen *value* från typen *std::is_arithmetic* är `true` för datatypen T med följande syntax:

```cpp
std::is_arithmetic<T>::value
```

Det går så klart att kontrollera ifall medlemmen *value* är `true` explicit:

```cpp
std::is_arithmetic<T>::value == true
```

I resten av detta avsnitt kommer vi dock slopa explicit kontroll av booleska värden.

Eftersom kontrollen genomförs vid kompilering använder vi inte en if-sats för att kontrollera påståendet. I stället gör vi en statisk kontroll av påståendet, alltså en kontroll redan under kompileringen, via deklarationen `static_assert`:

```cpp
static_assert(std::is_arithmetic<T>::value);
```

Ovanstående deklaration kommer medföra ett kompileringsfel om datatypen T (så som den har blivit implementerad i aktuell funktion) inte är av aritmetisk/numerisk typ. Vill vi också skriva ut ett felmeddelande tillsammans med kompileringsfelet kan vi lägga till detta direkt efter påståendet. 

Som exempel, nedanstående deklaration medför att felmeddelandet `Non-arithmetic data type specified!` i samband med kompileringsfelet:

```cpp
static_assert(std::is_arithmetic<T>::value, "Non-arithmetic data type specified!");
```

I praktiken placerar vi med fördel våra påståenden längst upp i våra funktionstemplates. Nedan visas hur vi genererar ett kompilinergsfel med felmeddelandet `Cannot print non-arithmetic types!` ifall en vektor innehållande något annat än heltal passeras till funktionen `print`:

```cpp
/*******************************************************************************
 * @brief Prints numbers held by referenced vector. Each number is printed
 *        on a separate line.
 *
 * @tparam T The type of the data held in the vector.
 *
 * @param numbers Reference to vector holding the numbers to print.
 * @param ostream Reference to output stream (default = terminal print).
 ******************************************************************************/
template <typename T>
void print(const std::vector<T>& numbers, std::ostream& ostream = std::cout)
{
    static_assert(std::is_arithmetic<T>::value, "Cannot print non-arithmetic types!");
    if (numbers.empty()) { return; }
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& number : numbers)
    {
        ostream << number << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}
```

Notera att:
* Datatypen T kan i praktiken vara vad som helst. Denna datatyp sätts utefter vilken datatyp som vektorn vi passerar har. Vi begränsar dock antalet giltiga datatyper till denna funktion till enbart numeriska sådana. 
* Vi gör ett påstående (en *assertion*) gällande datatypen T vid kompileringen. Om T inte är numerisk kompilerar inte programmet och ett felmeddelande genereras. Annars kör allt på som normalt.

### Skapa egna *type traits*
Ibland händer det att det inte finns ett *type trait* i standardbiblioteket som täcker allt man vill ha. Det går då utmärkt att skapa egna *type traits*. Att göra detta underlättar också förståelsen av *type traits*.

Ett *type trait* är inte något annat än ett structtemplate med en enda statisk medlem av datatypen `bool` döpt *value*. Värdet på *value* är satt till `false` som default. Bara för de typer vi vill sätter vi variabeln *value* till `true`.

Anta att vi vill skapa ett *type trait* för att kontrollera ifall en datatyp T är text, alltså av datatypen `const char*` eller `std::string`. Vi döper detta *type trait* till *is_string*. Ett structtemplate för denna typ visas nedan:

```cpp
template <typename T>
struct is_string
{
    static const bool value{false};
};
```

För en given datatyp T kommer variabeln *value* vara `false`. Vi ser sedan till att *value* är `true` då T = `const char*` samt T = `std::string` via nedanstående överlagringar:

```cpp
template <>
struct is_string<const char*>
{
    static const bool value{true};
};

template <>
struct is_string<std::string>
{
    static const bool value{true};
};
```

Vi testar att använda vårt nya *type trait* i funktionen `print` så att datatypen T kan vara aritmetisk eller text. Notera i påståendet att det räcker nu att T är aritmetisk *eller* av strängtyp. 

Vi byter också namn på ingående argument *numbers* till *data*, då det nödvändigtvis inte är tal i vektorn längre. Vi ändrar också felmeddelandet vid kompileringsfel till `Cannot print values other than numbers and text!`:

```cpp
/*******************************************************************************
 * @brief Prints data held by referenced vector. 
 * 
 * @tparam T The type of the data held in the vector.
 * 
 * @param data Reference to vector holding the data to print.
 * @param ostream Reference to output stream (default = terminal print).
 ******************************************************************************/
template <typename T>
void print(const std::vector<T>& data, std::ostream& ostream = std::cout)
{
    static_assert(std::is_arithmetic<T>::value || is_string<T>::value, 
        "Cannot print values other than numbers and text!");
    if (data.empty()) { return; }
    
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& element : data)
    {
        ostream << element << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}
```

#### Slutförd komimplementation
Nedan visas hur funktionen `print`, här implementerad i en namnrymd döpt `vector`, används för att skriva ut tal (hel- och flyttal) samt text. Vårt *type trait* `is_string` har här implementerats i en namnrymd namngiven `type_traits`:

```cpp
#include <iostream>
#include <type_traits>
#include <vector>

namespace type_traits
{

/*******************************************************************************
 * @brief Type trait for checking if specified type is of string type.
 * 
 * @tparam T The type to check.
 * 
 * @param value True if type T is of string type, else false.
 *******************************************************************************/
template <typename T>
struct is_string
{
    static const bool value{false};
};

/*******************************************************************************
 * @brief Overload for is_string, where T = const char*.
 *******************************************************************************/
template <>
struct is_string<const char*>
{
    static const bool value{true};
};

/*******************************************************************************
 * @brief Overload for is_string, where T = std::string.
 *******************************************************************************/
template <>
struct is_string<std::string>
{
    static const bool value{true};
};
} // namespace type_traits

namespace vector
{
    
/*******************************************************************************
 * @brief Prints data held by referenced vector. 
 * 
 * @tparam T The type of the data held in the vector.
 * 
 * @param data Reference to vector holding the data to print.
 * @param ostream Reference to output stream (default = terminal print).
 ******************************************************************************/
template <typename T>
void print(const std::vector<T>& data, std::ostream& ostream = std::cout)
{
    static_assert(std::is_arithmetic<T>::value || type_traits::is_string<T>::value, 
        "Cannot print values other than numbers and text!");
    if (data.empty()) { return; }
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& element : data)
    {
        ostream << element << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}
} // namespace vector

/*******************************************************************************
 * @brief Prints content of vectors holding numbers and text via the 
 *        vector::print function template.
 ******************************************************************************/
int main()
{
    const std::vector<int> v1{1, 2, 3};
    const std::vector<double> v2{0.5, 1.5, 2.5};
    const std::vector<const char*> v3{"C++", "programming", "is", "fun!"};
    
    vector::print(v1);
    vector::print(v2);
    vector::print(v3);
    return 0;
}
```

Koden ovan finns tillgänglig tillsammans med en makefil för kompilering och körning av koden i underkatalogen `function_template`. 
Instruktioner för byggande samt körande av koden finns i bifogad README-fil.

