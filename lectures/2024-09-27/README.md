# 2024-09-27 - Lektion 12

## Dagordning
* Neurala nätverk i mjukvara (del I) – Implementering av publikt interface för dense-lager via en klass döpt `DenseLayer`.
* Mer träning av neurala nätverk för hand.

## Mål med lektionen
* Kunna skapa ett publikt interface för ett dense-lager.
* Få mer övning gällande träning av neurala nätverk.

## Instruktioner
* Arkitekturen för `DenseLayer`-klassen sätter vi ihop under föreläsningen (via en kombination av eget arbete samt genomgång).
* Se implementering av dense-lager i C i underkatalogen [dense_layer_c](./dense_layer_c/), speciellt filer [`dense_layer.h`](./dense_layer_c/include/dense_layer.h) samt [`dense_layer.c`](./dense_layer_c/source/dense_layer.c).
* Se implementering av små neurala nätverk i C++, C och Python [här](../../code/neural_network/) för inspiration, speciellt filer[`dense_layer.py`](../../code/neural_network/python/dense_layer.py) samt [`dense_layer.h`](../../code/neural_network/cpp/general/include/dense_layer.h).
* Skapa en katalog utanför klassrepot. I denna katalog ska ni skapa ett eget neuralt nätverk (och ni ska kunna pusha till GitHub).
* Ert neurala nätverk, som vi kommer utveckla under många lektioner, ska också lagras via repo på GitHub. Detta repo bör döpas till `neural-network` eller liknande. 
* Jag kommer hjälpa er med att skapa ett Git-repo under föreläsningen. Instruktioner finns längst
ned i detta dokument.

* Ni har lite startfiler i underkatalogen [`neural_network`](./neural_network/), som ni förslagsvis kan kopiera till ert repo. I denna katalog har ni för närvarande:
    * Filen `utils.h`, som innehåller diverse hjälpfunktioner.
    * Filen `utils_impl.h` som utgör implementationsdetaljer för `utils.h`. Denna fil behöver ni inte tänka på eller inkludera direkt.
    * Makefilen `makefile`, som kan användas för att kompilera projektet.
    * Filen `main.cpp`, som för tillfället enbart används för att testa några av hjälpfunktionerna från `utils.h`.

## Utvärdering
* Några synpunkter på lektionen i sig?

## Nästa lektion
* Implementering av neurala nätverk i mjukvara (del II) – Funktionalitet i dense-lager för träning av nätverket.

## Skapa ett eget Git-repo

* Skapa en katalog att lägga ditt nya repo till. Döp denna katalog till exempelvis `neural-network`:

```bash
mkdir neural-network
cd neural-network
```

### 1. Initiera Git lokalt

* Initiera Git med branchen `main` som huvudbranch:

```bash
git init --initial-branch=main
```

### 2. Skapa ett Git-repo remote

* Skapa ett repo på GitHub, se instruktioner [här](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-new-repository).

* Om ni inte har gjort det tidigare, skapa en SSH-nyckel i er terminal:

### 3. Skapa en SSH-nyckel

```bash
ssh-keygen
```

* Spara denna SSH-nyckel på default filsökväg utan passphrase (dvs. klicka ENTER tills processen är klar).

* Kopiera sedan denna nyckel till GitHub, se instruktioner [här](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account).

### 4. Lägg till en fil för commit

* Kopiera [`.gitignore`](../../.gitignore) från detta repo, placera denna på roten i ditt repo. Lägg sedan till denna i nästa commit:

```bash
git add .gitignore
```

### 5. Lägg till användaruppgifter

* Om ni inte har gjort det tidigare, lägg till dina användaruppgifter såsom visas nedan, men med er mailadress samt ert namn:

```bash
git config --global user.email "erik.axel.pihl@gmail.com"
git config --global user.name "Erik Pihl"
```

### 6. Skapa en första commit

* Skapa en ny commit med meddelandet *"Add .gitignore"*:

```bash
git commit -m "Add .gitignore`
```

### 7. Pusha din commit till GitHub

* Pusha koden till din main-branch på GitHub:

```bash
git push -u origin main
```