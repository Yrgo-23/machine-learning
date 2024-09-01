# 2024-09-20 - Lektion 10

## Dagordning
* **Projekt 1** - Implementering av linjär regression för prediktion av temperatur på ATmega328P (del II).

## Mål med lektionen
* Ha slutfört större delen eller hela projekt I.

## Instruktioner
* Läs uppgiftsbeskrivningen nedan (eller på Classroom).

## Utvärdering
* Några synpunkter på lektionen i sig?

## Nästa lektion
* Introduktion till neurala nätverk – *feedforward*, *backpropagation*, *gradient descent*, aktiveringsfunktioner.
* Träning av neurala nätverk för hand.

## Projekt I - Implementering av linjär regression för prediktion av temperatur på ATmega328P

### Uppgiftsbeskrivning
Ni arbetar som embeddedutvecklare på ett företag i Göteborg. En av era kunder har tidigare köpt ett inbyggt system av ditt företag. Detta system utgörs av en ATMega328P processor samt omkringliggande hårdvara.

Systemet används inom transportsektorn och fungerar i dagsläget mestadels bra. Den använda temperatursensorn TMP36 har dock visat sig inte vara helt konsistent beroende på omgivning, fukt med mera. Denna sensors insignaler varierar därmed över tid, varvid det inte är möjligt att beräkna temperaturen med en exakt ekvation.

I stället för att byta hårdvara, vilket hade varit väldigt dyrt, då det rör sig om många system, har kunden bestämt sig för en mjukvarulösning. Det har därför ombett ditt företag att implementera en enkel maskininlärningsalgoritm i befintlig kodbas för att prediktera rumstemperaturen utefter indata från temperatursensorn. Vid behov av kalibrering kan då en utvecklare enkelt träna om modellen genom att manipulera träningsdatan, kompilera och köra om programmet.

Träningsdatan ska bestå utav 10 - 15 träningsuppsättningar bestående av:
* **Indata** i form av insignalen från temperatursensorn (behöver beräknas via den A/D-omvandlade insignalen).
* **Utdata** bestående av aktuell rumstemperatur i grader Celsius. 

Utgå vid träning att förhållandet mellan inspänningen från temperatursensorn samt aktuell rumstemperatur överensstämmer med databladet, se bifogad `bilaga A`. Träningen ska ske i början av programmet innan omkringliggande hårdvara initieras. Så fort avvikelser i den uppmätta temperaturen visar sig i fält ska en utvecklare enbart behöva manipulera träningsdatan i filen `main.cpp`, kompilera och köra programmet. Därefter ska temperaturen predikteras med hög precision.

Er chef Erik Pihl har därför bett dig samt en kollega att implementera en linjär regressionsmodell för kunden enligt beskrivningen ovan. Denna implementering ska läggas till i befintlig kodbas, som utgörs av diverse drivrutiner samt containerklasser skrivna i C++. Denna kod hittar ni i i underkatalogen [`code/atmega328p-library`](../../code/atmega328-library).

Era tasks är följande:
* Implementera en linjär regressionsmodell i aktuell kodbas. All tillagd kod ska hålla samma stil som befintlig kod, vilket också gäller kommentarer.
* Finn en lämplig lärhastighet samt antal epoker att träna modellen med för hög precision. 
* När modellen har tränats ska temperaturen predikteras och skrivas ut i en seriell terminal vid nedtryckning av en tryckknapp eller 60 sekunder efter senaste prediktionen. Oavsett knapptryckning eller inte ska alltså temperaturen skrivas ut var 60:e sekund.

***OBS!** Koden ägs av ditt företag och är konfidentiell; de enda som har tillgång till koden förutom er är era kunder. Mata därmed INTE in befintlig kod i ChatGPT eller annat AI-verktyg (då har Google sedan tillgång till koden). Att göra detta kan utföra skäl till uppsägning.*

Som nämndes tidigare ska träningen ske direkt när systemet startar, alltså innan initiering av omgivande hårdvara. Vid träning ska därmed nedtryckning av tidigare nämnd tryckknapp inte medföra någon temperaturmätning.

Innan koden levereras till kunden vill er chef ha en demonstration av systemet. Kunden vill ha den uppdaterade kodbasen tillsammans med en kort rapport på 1 – 2 sidor gällande era uppdateringar, hur regressionsmodellen är uppbyggd och Beskriv i ord samtliga publika metoder samt hur de ska ändra träningsdatan vid kalibrering. Rapporten ska skrivas på engelska. Leveransen ska ske via GitHub.


### Genomförande och examination 
* Ni ska jobba i team om två på uppgiften. 
* Ni får rådfråga er chef, som är en gammal utvecklare, för handledning gällande konstruktionen.
* Det färdiga systemet ska visas för er chef innan det levereras till kunden.
* Den uppdaterade kodbasen tillsammans med rapporten ska lämnas in via ett privat repo på GitHub.  
**OBS!** Bjud in er chef till repot så att han kan titta på koden.


### Utvärdering
I samband med inlämningen, vänligen lämna in en kort diskussion i en README-fil där ni beskriver följande:  
&nbsp;&nbsp;&nbsp;&nbsp;**1.** Vad lärde ni er av projektet?  
&nbsp;&nbsp;&nbsp;&nbsp;**2.** Vad var lätt/svårt?  
&nbsp;&nbsp;&nbsp;&nbsp;**3.** Vad hade ni velat ha lärt er mer innan projektet?  
&nbsp;&nbsp;&nbsp;&nbsp;**4.** Övriga kommentarer?

### Betyg
För uppgiften ges maximalt 2p, varav G = 1p samt VG = 2p.

#### Godkänt (G) – 1p
Leveransen uppfyller tidigare uppställda krav. 

#### Väl godkänt (VG) – 2p
Förutom föregående leverans har er kund beställt ett flertal olika features till systemet, som ska tas fram inom en snar framtid. En del av dessa features kräver heapallokering, precis som används av vektorer samt listor. 

Din chef ger er i uppgift att efter slutförandet av aktuell leverans genomföra en studie för att se över om det vore fördelaktigt att hålla sig till statisk minnesallokering i er regressionsmodell, primärt genom att ersätta samtliga vektorer med statiska arrayer, antingen med arrayer av den befintliga container-typen `container::Array<T>` eller C-arrayer. 

För att detta ska fungera bör er regressionsimplementering göras om till ett klasstemplate, där en templateparameter döpt `TrainingSetCount` avgör storleken på samtliga statiska arrayer i systemet. Därmed gäller att om en regressionsmodell `linReg` av klassen `ml::LinReg` ska tränas med tio träningsuppsättningar ska denna kunna skapas enligt nedan:

```cpp
ml::LinReg<12U> linReg{trainingInput, trainingOutput};
```

Samtliga arrayer som används för regressionsmodellen ska därmed ha storleken 12 satta vid kompileringen.

För att genomföra studien behöver du och din kollega skapa en ny prototyp av koden, vilket ska lagras i en branch döpt prototype (vid behov, be er chef om hjälp med Git). När denna prototyp är slutförd ska ni mäta minnesanvändningen för de två revisionerna av koden. Ni ska skriva en kort rapport på max en A4-sida, där ni redogör för minnesanvändningen samt för- och nackdelarna mellan de två olika revisionerna. Avsluta rapporten med er bedömning gällande ifall ert företag bör ersätta aktuell implementering med protypen vid nästa release.

### Bilaga A - Formler för beräkning av temperatursensor TMP36
Sambandet mellan resultatet `adcValue` från AD-omvandlingen samt den analoga inspänningen `inputVoltage` erhålls från temperatursensor TMP36 kan beräknas med följande formel: 

```math
inputVoltage = adcVal / 1023 * 5
```

Sambandet mellan den omgivande temperaturen `temperature` samt den analoga inspänningen `inputVoltage` kan beräknas med följande formel:

```math
temperature = (inputVoltage - 0.5) * 100,
```

vilket är ekvivalent med

```math
temperature = 100 * inputVoltage - 50
```



