# 2024-08-21 - Övningsuppgifter

*Använd gärna en makefil för kompilering och körning av programmet, se instruktioner i README-filen i roten av detta repo.*

## Uppgift 1
Skapa en fil döpt *main.cpp*. I denna fil, skapa en funktion döpt *getSmallestInt*, som returnerar det minst talet i en vektor innehållande heltal av datatypen *int*.  

Som exempel:
* Om en vektor innehållande talen {3, 6, 4, 8, 6, 8, -2, -1} passeras ska heltalet -2 returneras.
* Om en vektor innehållande talen {1, 2, -1, -1, 0} passeras ska heltalet -1 returneras.
* Om en tom vektor passeras vid funktionsanropet ska heltalet 0 returneras.

Placera denna funktion i en namnrymd döpt *vector*.  

Testa att fuktionen fungerar korrekt genom att skriva ut returvärdet vid anrop med följande vektorer:

```cpp
const std::vector<int> v1{3, 6, 4, 8, 6, 8, -2, -1}; 
const std::vector<int> v2{1, 2, -1, -1, 0};          
const std::vector<int> v3{};                        
```

## Uppgift 2 
Använd funktionen *getSmallestInt* för att radera det minsta talet ur följande vektor:

```cpp
std::vector<int> numbers{1, 2, 5, 4, 8, 9, 0, -3, -5, -2};
```

Skriv ut vektorns innehåll och se till att talet -5 har raderats.

### Tips
* Iterera genom vektorn med en C++-iterator och radera det minsta talet via vektor-metoden *erase*.  
* Iteration genom en vektor med C++-iteratorer kan du implementera via en for-loop tillsammans med vektor-metoder *begin* samt *end*.

## Uppgift 3
Se till att även om det det finns flera exemplar av det minsta talet i en given vektor ska samtliga dessa raderas. 

Använd funktionen *getSmallestInt* för att radera det minsta talet -5 ur följande vektor:

```cpp
std::vector<int> numbers{1, 2, -5, 5, 4, 8, 9, 0, -3, -5, -5, -5, -2};
```

Skriv ut vektorns innehåll och se till att samtliga exemplar av talet -5 har raderats.

### Tips
* Kör en kontinuerlig loop, som raderar det nuvarande minsta talet i vektorn så länge det nuvarande minsta talet är samma som det det ursprungliga minsta talet.
* Exempelvis kan du använda en kontinuerlig while-sats, som avbryts när det nuvarande minsta talet inte är lika med det ursprungliga minsta talet via kommandot *break*.




