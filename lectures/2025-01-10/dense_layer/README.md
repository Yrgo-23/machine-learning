# Implementering av neuralt nätverk via dense-lager i C++

Implementering av ett litet neuralt nätverk bestående av dense-lager i mjukvara:
* Filen `main.cpp` innehåller testkod, där ett neuralt nätverk tränas till att detektera ett 2-bitars XOR-mönster.
* Filen `act_func.h` innehåller information om tillgängliga aktiveringsfunktioner.
* Filen `dense_layer.h` innehåller klassen `DenseLayer` för implementering av dense-lager.
* Filen `utils.h` innehåller ett flertal hjälpfunktioner.
* Filen `utils_impl.h` innehåller implementationsdetaljer för tidigare nämnda hjälpfunktioner.

Träning genomförs under 10 000 epoker med en lärhastighet på 10 %.

## Kompilering samt körning av programmet

Kompilera och kör programmet via följande kommando (i denna katalog):

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
