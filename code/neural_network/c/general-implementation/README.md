# Implementering av neuralt nätverk i C

Generell implementering av ett litet neuralt nätverk i mjukvara:
* Filen `act_func.h` innehåller tillgängliga aktiveringsfunktioner samt beräkningsfunktioner.
* Filen `dense_layer.h` innehåller strukten `dense_layer` för implementering av dense-lager.
* Filen `double_vector.h` innehåller funktioner för att enkelt använda en- och tvådimensionella vektorer innehållande flyttal.
* Filen `neural_network.h` innehåller strukten `neural_network` för implementering av neurala nätverk.
* Filen `main.c` innehåller testkod, där ett neuralt nätverk tränas till att detektera ett 2-bitars XOR-mönster.
Träning genomförs tills modellens precision överstiger 99,99 %, därefter skrivs resultatet ut.

I denna implementering implementeras dense-lager och neurala nätverk via struktar med associerade funktioner för att efterlikna
objektorientering till en viss grad. För en given strukt gäller att dess medlemmar hålls privata genom att strukten i fråga
enbart fördefinieras i dess headerfil, tillsammans med deklaration av funktioner för att använda strukten. Den egentliga deklarationen placeras i motsvarande källkodsfil.


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
