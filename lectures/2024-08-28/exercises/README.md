# 2024-08-28 - Övningsuppgifter

## Uppgiftsbeskrivning
Du ska skapa en klass döpt *Device*, kan lagra följande data gällande en enhet:
* Tillverkare i form av text.
* Modellnamn i form av text.
* Revision i form av ett heltal.
* Tillverkningsår i form av ett heltal.
* Färg i form av text.
* Enhetens produktionsstatus i form av en enumerationsklass *ProductStatus*, se mer information i uppgift 2.

*Använd gärna en makefil för kompilering och körning av programmet, se underkatalogen *person* under dagens lektion.*

### Uppgift 1
Skapa en fil döpt *device.h*. Se till att filens innehåll bara definieras en gång. 

### Uppgift 2
I filen *device.h*, definiera enumerationsklassen *ProductStatus,* så att denna kan användas för att indikera om en given produkt för tillfället är en prototyp, aktiv eller om produktion har upphört via enumeratorer *Prototype, Active* samt *Discontinued.*

### Uppgift 3
Deklarera klassen *Device* i filen *device.h*.  Lägg till ett publikt samt ett privat segment i klassen.  

### Uppgift 4
Definiera klassens samtliga medlemsvariabler, se till att de är privata.  
Välj beskrivande namn med prefixet *my.*, exempelvis *myManufacturer.*

### Uppgift 4
Radera klassens default-konstruktor så att man inte kan skapa ett objekt utan enhetsdata.

### Uppgift 5
Definiera en konstruktor som ska kunna användas för att skapa ett Device-objekt:
* Enhetens tillverkare, modellnamn, revision, tillverkningsår samt färg måste passeras vid anropet.
* Enhetens produktionsstatus måste inte skickas med vid anropet; som default ska enheten sättas till att vara aktiv.

Det ska fungera att initiera ett Device-objekt som lagrar information om Arduino Uno Rev 3 så här:

```cpp
Device device1{"Arduino", "Uno", 3, 2012, "Green"};
```

Notera att denna vi inte skickade något produktionsstatus, denna ska då som default sättas till *ProductStatus::Active.* 

### Uppgift 6
* Deklarera get-metoder för samtliga medlemsvariabler så att man kan läsa samtliga parametrar.
* Deklarera set-metoder för add kunna byta produktens färg samt produktionsstatus.

## Uppgift 7
Deklarera en metod döpt *print,* som möjliggör att man kan skriva ut information om enheten *device1* såsom visas nedan:

```
--------------------------------------------------------------------------------
Manufacturer:           Arduino
Model:                  Uno
Revision:               3
Year of manufacture:    2012
Color:                  Green
Product status:         Active
--------------------------------------------------------------------------------
```

Som default ska utskrift ske i terminalen, men det ska också gå att skriva till en fil (med ett fstream-objekt).

### Uppgift 8
Definiera samtliga metoder deklarerade i klassen.
Vid behov, definiera ytterligare metoder. Sätt dessa till privata i klassen om de bara ska användas internt.

### Uppgift 9
Skapa enheten *device1* så som visas ovan. 
Skriv ut lagrad enhetsdata i terminalen samt till en fil döpt *device.txt.*

Se lösningsförslag i underkatalogen `solution`.