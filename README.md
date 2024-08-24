# Maskininlärning - Ela24

Repo för kursen Maskininlärning med klassen Ela23, vt24 - ht25.

Lektionsplaneringar samt lektionsanteckningar finns i katalogen *lectures*.

Kod för diverse övnings- och inlämningsuppgifter finns i katalogen *code*.

### Installera Visual Studio Code

Om du använder en Linux-miljö inuti Windows, såsom WSL eller Git bash, installera Visual Studio Code från Microsoft Store.

Däremot om använder en ren Linux-miljö, skriv följande kommando:

```bash
sudo snap install code --classic
```

### Ladda ned och installera WSL

WSL *(Windows Subsystem For Linux)* möjliggör att vi kan köra en Linux-distribution i terminalmiljö på en Windows-dator. Använd med fördel WSL för att:
* Klona repot lokalt och skapa egna revisioner av koden.
* Bygga, lagra samt köra kodexempel samt egna revisioner i detta repo.
* Bygga, lagra samt köra diverse C- och C++-program.

För att ladda ned WSL, börja med att öppna Windows Powershell som administratör. Skriv sedan följande kommandon:

```bash
wsl --install
wsl --set-default-version 2
```

När installationen är klar, öppna Microsoft Store och ladda ned den senaste versionen av Linux-distributionen `Ubuntu`. Sök därmed på `Ubuntu` i Microsoft Store. Ett flertal alternativ kommer dyka upp:
* Notera att befintliga distributioner är daterade efter släppdatum, så exempelvis `Ubuntu 22.04` släpptes i april 2022.
* Välj den senaste befintliga distributionen (som för tillfället är `Ubuntu 24.04 LTS`, som släpptes i år).

Efter att installationen är slutförd, skriv `Ubuntu` i Windows Search (sökrutan i det nedra vänsta hörnet). Klicka på din Ubuntu-distribution. En svart ruta kommer öppnas, vilket är din Linux-terminal i din Windows-miljö.

Först gången kommer du ombeds att lägga till användarnamn och lösenord, vilket enbart kommer användas i terminalen:
* Välj ett kort och användarnamn, så som ditt förnamn.
* Välj ett lämpligt lösenord och se till att spara detta på lämpligt sätt.

Ladda ned nödvändiga paket för att kompilera kod, använda Git med mera:

```bash
sudo apt -y update
sudo apt -y install build-essential
sudo apt -y install make
sudo apt -y install git
```

### Klona repot lokalt

Klona repot med följande kommando i en Linux-terminal, Git Bash eller dylikt:

```bash
git clone https://github.com/Yrgo-23/machine-learning.git
```

Dirigera in i repot och lista eventuella filer via följande kommandon:

```bash
cd machine-learning/
ls
```

Öppna repot med Visual Studio Code. 

Se instruktioner nedan för att installera Visual Studio Code längst ned i detta dokument:

```bash
code .
```

### Synka repot lokalt

Synka repot kontinuerligt genom att använda följande kommandon varje gång du använder repot:

```bash
git fetch origin main
git checkout main
git reset --hard FETCH_HEAD
```

Det som görs ovan är att du:
* Hämtar ändringarna från remote branch *main* på GitHub.
* Ser till att du är på den lokala main-branchen innan du genomför din synkroniseringen.
* Uppdaterar lokalt branch *main* med remote branch *main*. Eventuella lokala kodändringar raderas.

*Notera att remote branch *main* är den enda branchen tillgänglig på GitHub. När fler brancher används brukar main (eller master) utgöra "huvud-branchen", medan övriga branches är alternativa revisioner av koden som slutligen brukar sammansättas med main-branchen.*

### Skapa en egen branch
Om du vill skapa en egen branch för att göra egna ändringar eller test, använd nedanstående kommando.
Ersätt &lt;BRANCH_NAME&gt; med ditt val av namn på branchen, exempelvis *my-branch*.

```bash
git checkout -b <BRANCH_NAME>
```

Du kan lista samtliga lokala branches via följande kommando:

```bash
git branch
```

Du kan dirigera mellan dina lokala branches via nedanstående kommando.
Ersätt &lt;TARGET_BRANCH&gt; med den branch du vill dirigera till, exempelvis *main*.

```bash
git checkout <TARGET_BRANCH>
```

Synkronisera din egna branch med main-branchen på GitHub utan att skriva över denna kodändringar såhär:

```bash
git fetch origin main
git checkout <BRANCH_NAME>
git rebase origin/main
```

Det som görs ovan är att du:
* Hämtar ändringarna från ordinarie branch *main* på GitHub.
* Ser till att du är på den din egna branch innan du gör några uppdateringar.
* Placerar dina egna ändringar ovanpå samtliga ändringar i main-branchen på GitHub.

Även om du använder en egen branch är det rekommenderat att du synkroniserar den lokala main-branchen
med remote main-branch såsom visades ovan.

### Kompilering samt körning av kod

#### Alternativ 1 - Online-kompilator
Du kan använda denna [online-kompilator](https://www.onlinegdb.com/online_c_compiler) för att enkelt kompilera och köra program. 

**OBS! Byt språk till C++17 innan du trycker *Run*!**

#### Alternativ 2 - GCC-kompilatorn i Linux
Om du använder en Linux-miljö kan du använda *make* för att kompilera och köra koden.

Se först till att du har GCC-kompilatorn samt *make* installerat.   
Installera därmed paketet *build-essential* samt *make:*

```bash
sudo apt -y update
sudo apt -y install build-essential
sudo apt -y install make
```

För varje program, skapa en ny katalog, exempelvis *example-dir:*:

```bash
mkdir example-dir
cd example-dir
```

I denna katalog, skapa en fil döpt *makefile:*

```bash
touch makefile
```

I denna makefil, lägg till följande innehåll:

```bash
################################################################################
# @brief Builds the project and runs the program as default.
################################################################################
default: build run

################################################################################
# @brief Builds the project and creates an executable called main.
# 
# @note Add all your source files (.cpp extension) between "g++" and "-o".
################################################################################
build:
	@g++ main.cpp -o main -Wall -Werror

################################################################################
# @brief Runs the program (by running the main executable)
################################################################################
run:
	@./main

################################################################################
# @brief Removes compiled files (by deleting the main executable).
################################################################################
clean:
	@rm -f main
```

För att kompileringen ska fungera:
* Placera samtliga header- och källkodsfiler (.h- samt .cpp-filer) direkt i denna katalog. Om ni vill använda underkataloger, säg till mig, så hjälper jag er.
* Se till att lägga till samtliga källkodsfiler (.cpp-filer) mellan *g++" samt *-o" under vårt build-target.

Tack vara denna makefil kan du sedan kompilera och köra ditt program via följande kommando (i denna katalog):

```bash
make
```

Du kan också enbart bygga ditt program utan att köra det efteråt via följande kommando:

```bash
make build
```

Du kan köra ditt program utan att kompilera innan via följande kommando:

```bash
make run
```

Du kan också ta bort kompilerade filer via följande kommando:

```bash
make clean
```
