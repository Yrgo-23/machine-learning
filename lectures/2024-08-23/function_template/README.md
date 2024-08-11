# Funktionstemplates och *type traits*

Kod innehållande ett funktionstemplate för utskrift av tal och text lagrade i vektorer:
* Denna funktion klarar att skriva ut alla typer av tal samt strängar.
* Via constraints med *type traits,* både från C++ standardbibliotek samt ett eget *type trait,* kan dock inte övriga datatyper
användas i samband med denna funktion. I stället genereras då ett kompileringsfel med ett specifikt felmeddelande.

## Kompilering samt körning av programmet
För att kunna kompilera koden, se till att du har GCC-kompilatorn samt *make* installerat. Installera därmed paketen *build-essential* samt *make:*

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