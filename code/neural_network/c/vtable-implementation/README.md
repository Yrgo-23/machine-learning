# Implementering av neuralt nätverk i C med vtables

Fullständig implementering av ett litet neuralt nätverk i mjukvara:
* Filen `act_func.h` innehåller tillgängliga aktiveringsfunktioner samt beräkningsfunktioner.
* Filen `dense_layer.h` innehåller strukten `dense_layer` för implementering av dense-lager.
* Filen `neural_network.h` innehåller strukten `neural_network` för implementering av neurala nätverk.
* Filen `vector.h` innehåller strukten `vector`, som  möjliggör endimensionella vektorer innehållande heltal, flyttal samt strängar.
* Filen `vector_2d.h` innehåller strukten `vector_2d`, som möjliggör tvådimensionella vektorer innehållande pekare till vektorer
av godtycklig typ. 
* Filen `main.c` innehåller testkod, där ett neuralt nätverk tränas till att detektera ett 2-bitars XOR-mönster.
Träning genomförs tills modellens precision överstiger 99,99 %, därefter skrivs resultatet ut.

Så kallade virtuella tabeller, även kallat `vtables`, används som designmönster för att möjliggöra polymorfism samt inkapsling.
* Polymorfism möjliggör exempelvis att datatypen på en given vektor kan bytas under körtid. Samtidigt kan man lätt lägga till
nya vektortyper efter tid (just nu stöds enbart en- och tvådimensionella vektorer).
* Inkapsling innebär exempelvis att struktarnas medlemsvariabler hålls privata. 

Användning av virtuella tabeller innebär att funktionspekare till samtliga publika associerade funktioner till en given strukt
är lagrade i en tabell, vilket medför att samtliga objekt av strukten har tillgång till dessa.

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
