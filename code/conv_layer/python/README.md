# Konvolutionella lager i Python

Implementering av enkla en- och tvådimensionella konvolutionella lager med tillhörande pooling- och flatten lager, 
vilket kan användas för svartvita bilder (för färgbilder krävs dock tredimensionella lager):
* Filen `main.py` innehåller testkod, där ett tvådimensionellt konvolutionellt lager tränas med en 3x3-bild.
* Filen `conv_layer.py` innehåller klassen `ConvLayer2D` för implementering av tvådimensionella konvolutionella lager.
* Filen `flatten_layer.py` innehåller klassen `FlattenLayer` för implementering av flatten-lager.
* Filen `pooling_layer.py` innehåller klassen `PoolingLayer2D` för implementering av tvådimensionella pooling-lager.

## Körning av programmet

Kör programmet genom att använda `main.py` som startskript:

```bash
python3 main.py
```
