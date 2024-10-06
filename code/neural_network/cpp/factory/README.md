# Implementering av neuralt nätverk i C++

Fullständig implementering av ett litet neuralt nätverk i mjukvara implementerat med
designmönstret `factory`. Därmed används interfaces i kombination med factory-metoder för
att skapa objekt såsom neurala nätverk och dense-lager. Man låter samtliga implementationer av exempelvis
ett dense-lager ärva ett så kallat interface. Därefter använder man detta interface i implementationen.
Endast när man skapar ett objekt måste man ange vilken subklass man syftar till att använda. Därmed är
det väldigt smidigt att byta implementation till en annan vid behov.

[Här](https://www.geeksforgeeks.org/factory-method-pattern-c-design-patterns/) finns mer information om designmönstret `factory`.

* Filen `main.cpp` innehåller testkod, där ett neuralt nätverk tränas till att detektera ett 2-bitars XOR-mönster.
Träning genomförs tills modellens precision överstiger 99,99 %, därefter skrivs resultatet ut.
* Filen `act_func.h` innehåller information om tillgängliga aktiveringsfunktioner.
* Filen `act_func_calc.h` innehåller klassen `ActFuncCalc` för implementering av aktiveringsfunktionsberäknare.
* Filen `dense_layer.h` innehåller klassen `DenseLayer` för implementering av dense-lager.
* Filen `dense_layer_interface.h` innehåller ett interface för dense-lager. Detta interface
utgör basklass för samtliga implementeringar av dense-lager när denna design pattern används och medför därmed att man enkelt kan skifta vilket dense-lager som används.
* Filen `factory.h` innehåller fabriksmetoder för att konstruera neurala nätverk, dense-lager, aktiveringsfunktionsberäknare, vektorer med mera.
* Filen `neural_network.h` innehåller klassen `NeuralNetwork` för implementering av neurala nätverk.
* Filen `neural_network_interface.h` innehåller ett interface för neurala nätverk. Detta interface
utgör basklass för samtliga implementeringar av neurala nätverk när denna design pattern används och medför därmed att man enkelt kan skifta vilket neuralt nätverk som används.
* Filen `utils.h` innehåller ett flertal hjälpfunktioner.
* Filen `utils_impl.h` innehåller implementationsdetaljer för tidigare nämnda hjälpfunktioner.

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
