# Implementering av neurala nätverk i C

Två implementeringar av neurala nätverk i C:
* I underkatatalogen [`general`](./general/) finns en generell implementation, där dense-lager och neurala nätverk implementeras
via struktar med associerade funktioner. Denna implementation är relativt enkel, men möjliggör ändå objektorienterat tänk
samt inkapsling av medlemsvariabler.
* I underkatalogen [`vtable`](./vtable/) finns en implementation, dä så kallade virtuella tabeller, även kallat `vtables`, används som designmönster för att möjliggöra polymorfism samt inkapsling.