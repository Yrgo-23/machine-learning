# 2024-10-02 - Lektion 13

## Dagordning
* Implementering av neurala nätverk i mjukvara (del II) – Funktionalitet i dense-lager för träning av nätverket.

## Mål med lektionen
* Kunna implementera implementeringsdetaljer innefattande konstruktorer, get- och set-metoder för ett dense-lager i mjukvara.

## Instruktioner
* Implementationsdetaljerna för `DenseLayer`-klassen har ni tid att sätta ihop under föreläsningen. Vid behov körs genomgång i helklass.  
* Se bifogat skript `dense_layer.cpp`, som utgör testkod för er dense-lager implementering. I detta skript skapas ett litet neuralt nätverk via två sammankopplade dense-lager och tränas till att prediktera ett 2-bitars XOR-mönster. Er egen implementering ska kunna köras med detta skript och ska med framgång kunna prediktera rätt mönster innan ni går ut på LIA.
* Se implementering av små neurala nätverk i Python respektive C++ [här](../../code/neural_network/) för inspiration, speciellt filer [`dense_layer.py`](../../code/neural_network/python/dense_layer.py) samt [`dense_layer.h`](../../code/neural_network/cpp/general/include/dense_layer.h).

## Utvärdering
* Några synpunkter på lektionen i sig?

## Nästa lektion
* Implementering av neurala nätverk i mjukvara (del III) – Fortsatt arbete med implementationsdetaljer.
* **Inlämningsuppgift 5** - Träning av små neurala nätverk.

## Video tutorials - Implementering av neurala nätverk
* För vidare information om implementering av neurala nätverk i C++, se följande video tutorials (särskilt del I):
    * [Del I - Implementering av dense-lager](https://www.youtube.com/watch?v=HmX4KJlK8b8)
    * [Del II - Implementering av litet neuralt nätverk](https://www.youtube.com/watch?v=F424l8VR4ks)