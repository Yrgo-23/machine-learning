# CNN assignment

Skelettkod för inlämningsuppgift i maskininlärning, som innefattar implementering av konvolutionella lager och pooling lager.
* Filen `main.cpp` innehåller testkod, där ett attribut ur en 5 x 5-bild extraheras via ett konvolutionellt lager, följt
av att storleken minskas till 3 x 3 via ett pooling-lager. 
* Filen `conv_layer.h` innehåller skelettkod för klassen `ConvLayer` för implementering av endimensionella konvolutionella lager.
* Filen `pooling_layer.h` innehåller skelettkod för klassen `PoolingLayer` för implementering av endimensionella pooling-lager.

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
