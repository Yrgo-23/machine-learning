# Konvolutionella lager i C++

Implementering av enkla en- och tvådimensionella konvolutionella lager med tillhörande pooling- och flatten lager, 
vilket kan användas för svartvita bilder (för färgbilder krävs dock tredimensionella lager):
* Filen `main.cpp` innehåller testkod, där ett tvådimensionellt konvolutionellt lager tränas med en 3x3-bild.
* Filen `conv_layer_1d.h` innehåller klassen `ConvLayer1D` för implementering av endimensionella konvolutionella lager.
* Filen `conv_layer_2d.h` innehåller klassen `ConvLayer2D` för implementering av tvådimensionella konvolutionella lager.
* Filen `conv_utils.h` innehåller ett flertal hjälpfunktioner för konvolutionella lager.
* Filen `conv_utils_impl.h` innehåller implementationsdetaljer för tidigare nämnda hjälpfunktioner.
* Filen `flatten_layer.h` innehåller klassen `FlattenLayer` för implementering av flatten-lager.
* Filen `pooling_layer_2d.h` innehåller klassen `PoolingLayer2D` för implementering av tvådimensionella pooling-lager.

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
