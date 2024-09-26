# Implementering av dense-lager i C

Implementering av ett dense-lager i mjukvara:
* Filen `act_func.h` innehåller tillgängliga aktiveringsfunktioner samt beräkningsfunktioner.
* Filen `dense_layer.h` innehåller en implementering av dense-lager via strukten `dense_layer` samt associerade funktioner.
Dense-lagrets medlemsvariabler hålls privata genom att strukten `dense_layer` endast fördeklareras i denna fil. Denna strukt samt
dess associerade funktioner definieras i filen `dense_layer.c`.
* Filen `main.c` innehåller testkod, där ett dense-lager tränas till att prediktera ett enkelt mönster. Resultatet av träningen skrivs ut i terminalen innan programmet avslutas.

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
