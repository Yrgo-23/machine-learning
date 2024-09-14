# 2024-09-27 - Lektion 12

## Dagordning
* Neurala nätverk i mjukvara (del I) – Implementering av publikt interface för dense-lager via en klass döpt `DenseLayer`.
* Mer träning av neurala nätverk för hand.

## Mål med lektionen
* Kunna skapa ett publikt interface för ett dense-lager.
* Få mer övning gällande träning av neurala nätverk.

## Instruktioner
* Arkitekturen för `DenseLayer`-klassen sätter vi ihop tillsammans under föreläsningen.
* Se implementering av små neurala nätverk i Python respektive C++ [här](../../code/neural_network/) för inspiration, speciellt filer[`dense_layer.py`](../../code/neural_network/python/dense_layer.py) samt [`dense_layer.h`](../../code/neural_network/cpp/inc/dense_layer.h).
* Skapa ett eget repo på GitLab, döp detta till `neural-network` eller liknande. I detta repo ska ni skapa ett eget neuralt nätverk under nästkommande lektioner.

* Ni har lite startfiler i underkatalogen [`neural_network`](./neural_network/), som ni förslagsvis kan kopiera till ert repo. I denna katalog har ni för närvarande:
    * Filen `utils.h`, som innehåller diverse hjälpfunktioner.
    * Filen `utils_impl.h` som utgör implementationsdetaljer för `utils.h`. Denna fil behöver ni inte tänka på eller inkludera direkt.
    * Makefilen `makefile`, som kan användas för att kompilera projektet.
    * Filen `main.cpp`, som för tillfället enbart används för att testa några av hjälpfunktionerna från `utils.h`.

## Utvärdering
* Några synpunkter på lektionen i sig?

## Nästa lektion
* Implementering av neurala nätverk i mjukvara (del II) – Funktionalitet i dense-lager för träning av nätverket.