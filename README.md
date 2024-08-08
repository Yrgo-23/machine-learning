# Maskininlärning - Ela24

Repo för kursen Maskininlärning med klassen Ela23, vt24 - ht25.

Lektionsplaneringar samt lektionsanteckningar finns i katalogen *lectures*.

Kod för diverse övnings- och inlämningsuppgifter finns i katalogen *code*.

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

### Installera Visual Studio Code

Om du använder en Linux-miljö inuti Windows, såsom WSL eller Git bash, installera Visual Studio Code från Microsoft Store.

Däremot om använder en ren Linux-miljö, skriv följande kommando:

```bash
sudo snap install code --classic
```

