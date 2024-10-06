# Implementering av neurala nätverk i C++

Två implementeringar av neurala nätverk i C++:
* I underkatatalogen [`general`](./general/) finns en generell implementation, där dense-lager och neurala nätverk implementeras
via klasser. 
* I underkatalogen [`factory`](./factory/) finns en implementation, där designmönstret `factory` används för att skapa neurala nätverk,
dense-lager med mera, där man enkelt kan byta ut vilken implementation man använder (om flera finns) genom att låta samtliga implementation
av exempelvis ett dense-lager ärver ett så kallat interface 