# Implementering av neuralt nätverk i C++

Fullständig implementering av ett litet neuralt nätverk i mjukvara:
* Filen `main.cpp` innehåller testkod, där ett neuralt nätverk tränas till att detektera ett 2-bitars XOR-mönster.
* Filen `act_func.h` innehåller information om tillgängliga aktiveringsfunktioner.
* Filen `dense_layer.h` innehåller klassen `DenseLayer` för implementering av dense-lager.
* Filen `neural_network.h` innehåller klassen `NeuralNetwork` för implementering av neurala nätverk.
* Filen `utils.h` innehåller ett flertal hjälpfunktioner.
* Filen `utils_impl.h` innehåller implementationsdetaljer för tidigare nämnda hjälpfunktioner.

Träning genomförs tills modellens precision överstiger 99,99 %, därefter skrivs resultatet ut.

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
