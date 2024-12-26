# 2025-01-17 - Lektion 20 - 21

## Dagordning
* **Projekt 2** - Neuralt nätverk i ett inbyggt system (del I - II).

## Mål med lektionen
* Ha fått en övergripande blick över aktuellt system.
* Ha kommit en bit på vägen gällande projektet, exempelvis genom att ha slutfört något av följande:  
    &nbsp;&nbsp;&nbsp;&nbsp;**a)** Ha lagt till ett fungerande neuralt nätverk och testkört på Raspberry Pi.  
    &nbsp;&nbsp;&nbsp;&nbsp;**b)** Ha implementerat nödvändig hårdvarufunktionalitet i systemet.  

## Instruktioner
* Läs uppgiftsbeskrivningen nedan (eller på Classroom).

## Utvärdering
* Några synpunkter på lektionen i sig?

## Nästa lektion
* Fortsatt arbete med **Projekt 2**.

## Projekt II - Neuralt nätverk i ett inbyggt system

### Uppgiftsbeskrivning
Ni arbetar som embeddedutvecklare på ett företag i Göteborg. Er chef, Erik Pihl, har gett dig och din kollega i uppgift att skapa ett POC (Proof Of Concept), med syftet implementera ett neuralt nätverk i ett inbyggt system, tillämpat på en Raspberry Pi med programkod skriven i C++.

Detta nätverk ska kunna prediktera en utsignal via insignaler från 4 - 5 tryckknappar (beroende på betygsnivå). Vid nedtryckning ska en given tryckknapp medföra insignal 1.0, annars 0.0. Nätverkets prediktion ska utgöras av en enda signal, som ska användas för att styra en lysdiod.

Nätverket ska implementeras från grunden, alltså utan användning av externa bibliotek. För det neurala nätverket ska användaren kunna välja lärhastighet, antalet epoker samt antalet noder i in- och utgångslagret samt befintliga dolda lager. 

Drivrutiner från libgpiod (C++) ska användas för avläsning av tryckknapparna samt styrning av lysdioden. Drivrutiner för lysdioder samt tryckknappar med eventdetektering i C++ kan laddas ned [här](../../code/rpi-driver/).

Nätverket ska tränas till ett detektera ett 4- eller 5-bitars XOR-mönster. Om ett ojämnt antal tryckknappar är nedtryckta ska lysdioden tändas, annars ska den vara släckt. Därmed ska det neurala nätverket tränas till att prediktera en hög utsignal om en, tre eller fem knappar är nedtryckta, annars en låg utsignal.  

Samtidigt som lysdioden tänds eller släcks ska det neurala nätverkets predikterade utsignal skrivas ut i Linuxterminalen, tillsammans med information gällande om lysdioden tänds eller släcks. Prediktion ska enbart ske vid förändring av insignalerna.

Se till träning sker direkt när systemet startar och att nedtryckning av någon eller några av tryckknapparna inte medför någon prediktion förrän träningen är slutförd.

Era tasks är följande:
* Skapa en egen implementation av ett neuralt nätverk. Dokumentera all publik kod. 
* Använd drivrutiner från libgpiod för att styra tryckknapparna och lysdioden.
* Finn en lämplig lärhastighet samt antal epoker att träna modellen med hög precision (> 99.9 %).
* När modellen har tränats ska prediktion ske på använd träningsdata och skrivas ut i terminalen, exempelvis så som visas i bilaga A (för prediktion av ett 5-bitars XOR-mönster).

Koden ska levereras till er chef, som också vill ha en demonstration av systemet. Leveransen ska ske via GitHub.

### Genomförande och examination
* Ni ska jobba i team om två på uppgiften. 
* Ni får rådfråga er chef, som är en gammal utvecklare, för handledning gällande konstruktionen.
* Det färdiga systemet ska visas för er chef innan det levereras till kunden.
* Ni är välkomna att ta inspiration från externa källor, vilket även innefattar kod från klassrepot, men ni ska göra en egen implementering. Kopiera alltså inte någon annans kod.
* Den uppdaterade kodbasen tillsammans med rapporten ska lämnas in via ett privat repo på GitHub. 
**OBS!** Bjud in "er chef" till repot så att han kan titta på koden.

**Tips:** Installera [Git Bash](https://git-scm.com/download/win) för att enkelt kunna använda Git i Windows.

### Utvärdering
I samband med inlämningen, vänligen lämna in en kort diskussion i en README-fil där ni beskriver följande:  
&nbsp;&nbsp;&nbsp;&nbsp;**1.** Vad lärde ni er av projektet?  
&nbsp;&nbsp;&nbsp;&nbsp;**2.** Vad var lätt/svårt?  
&nbsp;&nbsp;&nbsp;&nbsp;**3.** Vad hade ni velat ha lärt er mer innan projektet?  
&nbsp;&nbsp;&nbsp;&nbsp;**4.** Övriga kommentarer?

### Betyg
För uppgiften ges maximalt 4p, varav G = 2p samt VG = 4p.

#### Godkänt (G) – 2p
Projektet uppfyller tidigare uppställda krav. Nätverket kan alltså prediktera ett 4-bitars XOR-mönster.  
I systemet erhålls sedan insignaler från fyra tryckknappar, där den predikterade utsignalen skrivs till en lysdiod.

#### Väl godkänt (VG) – 4p
Förutom kraven för godkänt ska man kunna lägga till ett godtyckligt antal dolda lager i nätverket. Nätverket ska sedan via 3 – 5 dolda lager kunna prediktera ett 5-bitars XOR-mönster.  
I systemet erhålls sedan insignaler från fem tryckknappar, där den predikterade utsignalen skrivs till en lysdiod.

### Bilaga A – Exempelutskrift av predikterade värden

Nedan visas utskrift av predikterade värden från ett neuralt nätverk innefattande fem inportar samt en utport.  
Nätverket har tränats till att prediktera ett 5-bitars XOR-mönster.  Efter träning är precisionen uppe i 100 %:

```
--------------------------------------------------------------------------------
Prediction accuracy: 100.0%  
Input: [0.0, 0.0, 0.0, 0.0, 0.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [0.0, 0.0, 0.0, 0.0, 1.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [0.0, 0.0, 0.0, 1.0, 0.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [0.0, 0.0, 0.0, 1.0, 1.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [0.0, 0.0, 1.0, 0.0, 0.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [0.0, 0.0, 1.0, 0.0, 1.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [0.0, 0.0, 1.0, 1.0, 0.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [0.0, 0.0, 1.0, 1.0, 1.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [0.0, 1.0, 0.0, 0.0, 0.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [0.0, 1.0, 0.0, 0.0, 1.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [0.0, 1.0, 0.0, 1.0, 0.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [0.0, 1.0, 0.0, 1.0, 1.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [0.0, 1.0, 1.0, 0.0, 0.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [0.0, 1.0, 1.0, 0.0, 1.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [0.0, 1.0, 1.0, 1.0, 0.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [0.0, 1.0, 1.0, 1.0, 1.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [1.0, 0.0, 0.0, 0.0, 0.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [1.0, 0.0, 0.0, 0.0, 1.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [1.0, 0.0, 0.0, 1.0, 0.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [1.0, 0.0, 0.0, 1.0, 1.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [1.0, 0.0, 1.0, 0.0, 0.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [1.0, 0.0, 1.0, 0.0, 1.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [1.0, 0.0, 1.0, 1.0, 0.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [1.0, 0.0, 1.0, 1.0, 1.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [1.0, 1.0, 0.0, 0.0, 0.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [1.0, 1.0, 0.0, 0.0, 1.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [1.0, 1.0, 0.0, 1.0, 0.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [1.0, 1.0, 0.0, 1.0, 1.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [1.0, 1.0, 1.0, 0.0, 0.0], prediction: [1.0], reference: [1.0], error: 0.0  
Input: [1.0, 1.0, 1.0, 0.0, 1.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [1.0, 1.0, 1.0, 1.0, 0.0], prediction: [0.0], reference: [0.0], error: 0.0  
Input: [1.0, 1.0, 1.0, 1.0, 1.0], prediction: [1.0], reference: [1.0], error: 0.0  
--------------------------------------------------------------------------------  
```
