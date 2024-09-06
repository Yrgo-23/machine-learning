# 2024-09-06 - Lektion 6

## Dagordning
* Linjär regression i mjukvara (del I) - Skapande av publikt interface för klassen `LinReg`.
* Inlämningsuppgift 3 - Grundläggande maskininlärning.

## Mål med lektionen
* Kunna skapa ett publikt interface för en linjär regressionsmodell innehållande metoder för träning och prediktion.
* Ha lämnat in inlämningsuppgift 3 innan dagen är slut.

## Instruktioner
* Arkitekturen för `LinReg`-klassen sätter vi ihop tillsammans under föreläsningen.
* Se `Arkitektur för linjär regressionsmodell i C++` nedan för lite bakgrund.
* Inlämningsuppgift 3 är tillgänglig på Classroom kl. 10:00.

## Utvärdering
* Några synpunkter på lektionen i sig?
* Katalogen `notes` innehåller det publika interface som sattes ihop under föreläsningen.

## Nästa lektion
* Vidareutveckling av linjär regressionsmodell i C++.

## Arkitektur för linjär regressionsmodell i C++
Vi ska denna under föreläsning påbörja implementeringen av en linjär regressionsmodell. Detta kan göras på många olika sätt. Ni har nog olika idéer på hur denna modell ska fungera, vilka metoder vi ska skapa och så vidare. Detta är helt normalt och är också normalt att diskutera utvecklare sinsemellan (samt ibland chefer) när en ny implementering ska göras. Utvecklarna (samt de potentiella cheferna) kan sedan komma överens om det nya interfacets design och funktion, för att sedan påbörja implementeringen. Notera att det framförallt gäller de publika delarna; implementeringsdetaljer (hur man gör det) finns det ofta mindre synpunkter på, så länge det fungerar korrekt.

Vi ska därmed via diskutioner komma överens om hur regressionsmodellen ska se ut. Vi sätter ihop det publika interfacet live under tiden.

Se exempelkoden i katalogen `lin_reg`, som är ett exempel på ett publikt interface för en linjär regressionsmodell.  
Här ser ni dock enbart mina egna idéer hur det kan se ut; ni har säkert idéer på hur interfacet kan förbättras och dessa får ni gärna framföra.

Några exempel på saker vi kan diskutera:
* Ska man kunna skicka träningsdata efter att modellen har skapats (via en metod) eller ska det bara gå att skicka träningsdata vid skapande av objektet (via konstruktorn)?
* Ska träning genomföras tills precisionen har nått en viss grad, exempelvis 95 %, eller ska vi låta användaren av interfacet få sköta detta själv?
