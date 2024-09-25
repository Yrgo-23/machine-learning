# Linjär regressionsmodell i C++

Exempel på en linjär regressionsmodell i C++ via en klass döpt `LinReg`:
* Filen `lin_reg.h` utgör det "publika interfacet", alltså det som är av intresse för "användaren", och innehåller därmed metoddeklarationer med tillhörande dokumentation.  
* Filen `lin_reg.cpp` innehåller implementationsdetaljer i form av medlemsfunktioner.

Filen `main.cpp` innehåller testkod, där en regressionsmodell tränas till att detektera mönstret y = 2x + 2.  
Träning genomförs tills modellens precision överstiger 99,9 %, därefter skrivs resultatet ut.

## Kompilering samt körning av programmet
För att kunna kompilera koden, se till att du har GCC-kompilatorn samt `make` installerat. 
Installera därmed paketen `build-essential` samt `make`:

```bash
sudo apt -y update
sudo apt -y install build-essential
sudo apt -y install make
```

Tack vara den bifogade makefilen kan du sedan när som helst kompilera och köra programmet via följande kommando (i denna katalog):

```bash
make
```

Du kan också enbart bygga programmet utan att köra det efteråt via följande kommando:

```bash
make build
```

Du kan köra programmet utan att kompilera innan via följande kommando:

```bash
make run
```

Du kan också ta bort kompilerade filer via följande kommando:

```bash
make clean
```