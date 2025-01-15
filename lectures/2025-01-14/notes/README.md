# 2025-01-14 - Anteckningar

Implementering av implementationsdetaljer för klassen `NeuralNetwork` i källkodsfilen [`neural_network.cpp`](./source/neural_network.cpp).

Filen `main.cpp` innehåller testkod, där ett neuralt nätverk tränas till att detektera ett 2-bitars XOR-mönster.

Resterande moduler kan kortfattat beskrivas enligt nedan:
* [`act_func.h`](./include/act_func.h) innehåller tillgängliga aktiveringsfunktioner via enumerationen `ActFunc`
samt associerade funktioner.
* [`dense_layer.h`](./include/dense_layer.h) innehåller klassen `DenseLayer` för implementering av dense-lager.
* [`neural_network.h`](./include/neural_network.h) innehåller klassen `NeuralNetwork` för implementering av neurala nätverk.
* [`utils.h`](./include/utils.h) innehåller ett flertal hjälpfunktioner, exempelvis för matematiska beräkningar
samt utskrift av innehåll i vektorer.

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
