# Konvolutionella lager i mjukvara

Mjukvaruimplementeringar av konvolutionella lager, både för inspiration samt test:
* I underkatalogen [`cpp`](./cpp/) finns en implementering skriven i C++.
* I underkatalogen [`python`](./python/) finns en implementering skriven i Python.

* **Konvolutionella lager** lämpar sig utmärkt för att extrahera attribut ur bilder, exempelvis kanter och cirklar. 
Den extraherade datan brukar matas in i ett klassiskt neuralt nätverk för att göra prediktioner. 
Ett antal konvolutionella lager används för att kraftigt minska storleken på det efterföljande klassiska neurala nätverket.  

* **Pooling-lager** används för att nedsampla extraherade attribut från bilden i syfte att minska antalet beräkningar  
vid prediktion (färre pixlar medför färre ingångsnoder i efterföljande neurala nätverk). 
Vanligtvis sker pooling genom att de mest signifikanta attributen bibehålles, medan övriga förkastas. 
Detta kan liknas vid att en bild skalas ned.  

* **Flatten-lager** används för att omvandla extraherade attribut från 2D (eller 3D vid färgbilder) till 1D, 
för att sedan mata dessa attribut till ingången på ett klassiskt neuralt nätverk för prediktion.  