# 2024-08-21 - Lösningar till övningsuppgifter

Se lösningsförslag i bifogade underkataloger.

## Kompilering samt körning av programmen
För att kunna kompilera respektive program, se till att du har GCC-kompilatorn samt *make* installerat. Installera därmed paketen *build-essential* samt *make:*

```bash
sudo apt -y update
sudo apt -y install build-essential
sudo apt -y install make
```

Dirigera in i katalogen för det program du vill köra. Som exempel, vill du testköra programmet som utgör lösningsförslag för uppgift 1, dirigera in i underkatalogen `exercise1`:

```bash
cd exercise1
```

Kompilera och kör programmet via följande kommando:

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