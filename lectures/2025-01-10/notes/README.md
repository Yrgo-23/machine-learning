# 2025-01-10 - Anteckningar

Implementering av headerfilen [`neural_network.h`](./include/neural_network.h) för att enkelt
kunna skapa och använda neurala nätverk:
* Definition av klassen `NeuralNetwork` med deklarationer av metoder för att prediktera, träna nätverket, lägga till träningsdata och så vidare. 
* Medlemsvariabler bestående av två dense-lager samt vektorer för att lagra träningsdata lades också till.
* Nästa föreläsning ska en källkodsfil döpt `neural_network.cpp` läggas till. I denna fil ska klassens metoder definieras.

I nuläget innehåller `main.cpp` testkod, där två lösa dense-lager tränas till att detektera ett 2-bitars XOR-mönster.  
Denna kod ska senare kunna ersättas med ett objekt av vår klass `NeuralNetwork`.

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
