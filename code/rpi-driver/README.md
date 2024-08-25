# Raspberry Pi device drivers in C++

Drivrutiner för tryckknappar och lysdioder för Raspberry Pi.

## Kompilering samt körning av programmet
För att kunna kompilera koden, se till att du har GCC-kompilatorn, `make` samt `libgpiod` installerat:

```bash
sudo apt -y update
sudo apt -y install build-essential
sudo apt -y install make
sudo apt -y install libgpiod-dev
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