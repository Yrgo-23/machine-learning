# Vektor-funktioner i C++

Kod innefattande funktioner för att tilldela samt skriva ut innehåll ur vektorer innehållande heltal:
* Funktionen *vector::assign* används för att tilldela ett godtyckligt antal heltal till en vektor. Start- och stegvärdet är valbart, men är som default 0 respektive 1.
* Funktionen *vector::print* används för att skriva tal lagrade i en given vektor till en godtycklig utström. Som default sker utskrift i terminalen, men det går också att skriva till filer.

I funktionen *main* tilldelas en vektor 50 heltal [100, 102, 104... 198] via anrop av funktionen *vector::assign*. Talen skrivs både ut i terminalen samt till en fil döpt *numbers.txt* via anrop av funktionen *vector::print.*

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