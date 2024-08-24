# 2024-09-04 - Lektion 5

## Dagordning
* Vad är maskininlärning?
* Linjär regression – träning för hand, prediktion, epoker, lärhastighet med mera.
* Om tid finns, påbörjade av regressionsmodell i C++.

## Mål med lektionen
* Känna till varför ett traditionellt program inte lämpar sig väl för att efterlikna mänsklig intelligens.
* Känna till hur en maskininlärningsalgoritm skiljer sig mot ett traditionellt program sett till indata, utdata samt regler.
* Kunna träna linjära regressionsmodeller för hand.

## Instruktioner
* Läs introduktionstexten om maskininlärning i detta dokument.
* Läs bifogad fil `Linjär regression.pdf` för information om linjär regression.

## Utvärdering
* Några synpunkter på lektionen i sig?

## Nästa lektion
* Linjär regression i mjukvara (del I).
* Inlämningsuppgift 3 - Grundläggande maskininlärning.

## Introduktion till maskininlärning

### Traditionell programmering vs. maskininlärning

#### Traditionell programmering
I traditionell programmering används någon typ av **indata** i kombination med uppsatta **regler** för att generera **utdata**:

* **Indata** kan exempelvis utgöras av insignaler en sensorer, en tryckknapp, en terminal eller en fil.
* **Regler** utgörs av villkor implementerade i programmet, exempelvis via vilkorssatser.
* **Utdata** kan exempelvis utgöras av signaler som skrivs till en aktuator, exempelvis för att styra en lysdiod, en motor eller en fläkt.

Som exempel på ett traditionellt program inom ett inbyggt system kan temperaturen läsas in som indata via en temperatursensor, där regler är implementerade via en villkorssats för att styra ett ventilationssystem utefter aktuell rumstemperatur. Nedan visas ett exempel på hur en metod för att implementera detta hade kunnat se ut i C++ för en metod `runVentilation` i en fiktiv klass döpt `HardwareController`:

```cpp
/*******************************************************************************
 * @brief Runs the PWM controlled ventilation system. 
 *******************************************************************************/
void HardwareController::runVentilation()
{
    const auto temperature{tempSensor::read()};
    if (temperature < 10) 
    { 
        ventilation.run(0.0);
    }
    else if (temperature >= 10 && temperature <= 25) 
    { 
        ventilation.run(0.5); 
    }
    else
    {
        ventilation.run(1.0);
    }
}
```

Gällande ovanstående program kan vi enkelt urskilja **indata**, **regler** samt **utdata**:
* **Indatan** utgörs av insignaler från en temperatursensor implementerad via ett objekt döpt `tempSensor`.
* **Reglerna** utgörs av en if else-sats för att styra ventilationssystemet utefter aktuell temperatur. Dessa regler har satts av en programmerare.
* **Utdatan** sätts antingen till `0.0`, `0.5` eller `1.0` utefter reglerna i vilkorssatsen. Denna utdata används att styra hastigheten på ventilationssystemet, så att detta antingen avstängt eller går på hel- eller halvfart.

Ovanstående program utgör ett traditionellt program i den mån att en människa har satt reglerna. Utdatan utgör därmed en funktion av aktuell indata samt de satta reglerna:

```
Traditionell programmering: indata + regler => utdata
```

#### Maskininlärning
I maskininlärning används i stället **indata** i kombination med **utdata** för att träna maskinen i syfte att denna ska upptäcka **regler/mönster** själv i form av sambandet mellan in- och utdatan. Vi behöver då använda träningsuppsättningar med indata samt utdata, som maskinen utsätts för många gånger.

När maskinen på detta sätt upptäcker reglerna själv sägs den bli tränad och datan den tränas på kallas träningsdata. Träningsdatan består av en eller flera träningsuppsättningar, där en given träningsuppsättning innehar en insignal samt motsvarande utsignal.

Gällande det tidigare exemplet med styrning av ett ventilationssystem hade vi kunnat skapa träningsuppsättningar i form av olika temperaturer som indata samt värden `0.0`, `0.5` samt `1.0` som utdata:

| Indata | Utdata |
|--------|--------|
|  -10   |  0.0   |
|  -5    |  0.0   |
|   0    |  0.0   |
|   5    |  0.0   |
|   10   |  0.5   |
|   15   |  0.5   |
|   20   |  0.5   |
|   25   |  0.5   |
|   30   |  1.0   |
|   35   |  1.0   |
|   40   |  1.0   |


Vi hade sedan kunnat träna maskinen genom att utsätta denna får ovanstående träningsuppsättningar under ett visst antalet **epoker** (omgångar). Under en epok utsätts modellen för samtliga träningsuppsättningar. Träning med en uppsättning sker enligt nedan:

* Vi låter maskinen **prediktera** vad utdatan ska bli vid en viss temperatur. Som exempel, vi ger maskinen indatan 15 och den gissar till en början (innan den har blivit tränad ordentligt) att rätt svar är 0.2.
* Vi **utvärderar** sedan maskinens svar genom att jämföra detta med referensdatan, alltså rätt svar, vilket vi från från vår utdata. Som exempel gissade vår maskin på 0.2 när vi gav den indatan 15, men rätt svar är 0.5. Aktuellt fel är därmed 0.3.
* Vi **optimerar** sedan maskinen så att den gissar bättre nästa gång. Detta gör vi genom att justera dess så kallade parametrar (mer om detta nedan). Eftersom maskinen gissade lite för lågt bör vi öka dess parametrar något. Vid nästa gissning bör maskinens gissning vara närmare 0.5 än nu. 

Efter många små förändringar bör maskinen prediktera mycket nära träningsdatan. Vår maskin kan då anses vara tränad. Detta kan ta allt från ett tiotal upp till tusentals epoker beroende på hur komplext mönster maskinen ska lära sig. 

```
Maskininlärning: indata + utdata => regler
```

För att realisera en välfungerande maskininlärningsalgoritm krävs tre faktorer:

* Indata, exempelvis bilder på objekt, data från sensorer eller dylikt.
* Förväntad utdata, så att maskinen kan lära sig vilken utdata som förväntas för given indata.
* En metod för att mäta ifall algoritmen fungerar väl, alltså ifall aktuell utdata matchar förväntad utdata. Vid behov måste algoritmen justeras, vilket kallas lärande.

### Varför maskininlärning?
Låt oss anta att vi ska försöka efterlikna mänsklig intelligens på en maskin via ett traditionellt program. Denna maskin ska sedan kunna fungera som en vanlig människa. Vi kan försöka täcka en vanlig vardag för var och en av oss:
* Indatan utgörs av allt vi ställs inför under en dag och alla beslut vi tar. Ta som exempel att vi vaknar sent en vardag vi ska till jobbet.
* Reglerna försöker vi implementera med villkorssatser för att erhålla önskat resultat/utdata. Exempelvis kan vi implementera en if-sats för att kunna styra vad vi ska göra om vi vaknar sent en dag vi ska till jobbet.
* Utdatan består av vad vi utför/resultatet, vilket vi placerar i tidigare nämnd if-sats. Exempelvis kan vi skriva att vi skippar frukosten och i stället direkt borstar tänderna och lämnar bostaden för att komma fortare till jobbet.

Ovanstående beteende hade kunnat implementeras via en if-sats i en metod döpt `controlBehaviour` för en klass döpt `IntelligentMachine`:

```cpp
/*******************************************************************************
 * @brief Controls the behaviour of the intelligent machine.
 *******************************************************************************/
void IntelligentMachine:controlBehaviour()
{
    if (actualWakeupTime() > supposedWakeupTime() && isWorkday())
    {
        getDressed();
        brushTeeth();
        goToWork();
    }
}
```

Problemet med att vi kör med strategin ovan är att det hade krävts ett ofantligt månste villkorssatser för att täcka alla beslut vi tar
en given dag, särskilt om vi tar i åtanke alla kombinationer av villkor som kan uppstå. Det kanske är så att vi vaknade för sent på en arbetsdag, men vi börjar två timmar senare idag, eller så vaknar vi sent men känner oss sjuka med mera. När vi sedan tänker oss att detta program ska täcka alla beslut vi tar över lång tid är det lätt att inse att programmet hade blivit så ofantligt stort och komplext att:
* Det hade tagit evigheter att implementera programmet.
* Programmet hade tagit en ofantlig mängd minne.
* Programmet måste uppdateras när vi lära oss nya saker, vilket hade krävs enorma resurser sett till arbetstimmar.

Därmed är det inte görbart att efterlikna mänsklig intelligens med ett traditionellt program. Dock trodde man fram till sena 1980-talet att detta skulle fungera. Faktum är att det som presenterades ovan är ett exempel på vad som numera är känt som *symbolisk AI*, vilket var den dominanta paradigmen inom artificiell intelligens innan maskininlärning blev utbrett. Symbolisk AI är alltså i praktiken traditionell programmering, där en maskin förses med en mycket stor mängd med regler för ett enormt antal olika scenarion.

Symbolisk AI verkade lovande, då det medförde att maskiner kunde lösa komplexa, men mycket väldefinierade uppgifter, exempelvis att spela schack. Dock visade sig det vara inadekvat för mindre väldefinierade uppgifter, såsom datorseende, taligenkänning och språköversättning, där indata (bilder, ord, fraser) kan variera stort gällande olika ljus, vinklar, vem som säger något, dialekt och dylikt.

Därmed uppstod i stället maskininlärning, där maskinen själv får hitta reglerna genom att bli tränad via stora mängder indata samt motsvarande förväntad utdata. Ifall ett nytt scenario dyker upp får maskinen helt enkelt prediktera vad som ska göras utifrån vad den redan vet (har blivit tränad till), vilket påminner om hur vi människor fungerar. 