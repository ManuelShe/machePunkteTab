/*
Programm: machePunkteTab

Projektersteller: Manuel Scheiermann
Das Projekt steht unter der Creative Commons Lizenz 4.0
Siehe dazu: https://creativecommons.org/licenses/by-nc-sa/4.0/deed.de
*/

#ifndef aufgabeHeader
#define aufgabeHeader

class Aufgabe {
private:
    std::string aufgabeName;
    double maxPunkte;
    double erreichtePunkte;
    
public:
    Aufgabe();
    Aufgabe(std::string); // (std::string Name_der_Aufgabe) Alles andere wird gleich 0 gesetzt
    Aufgabe(std::string, int); // (std::string Name_der_Aufgabe, int maximale_Punkte) Die erreichen Punkte werden gleich der maximalen Punkte gesetzt
    Aufgabe(std::string, int, int); // (std::string Name_der_Aufgabe, int maximale_Punkte, int erreichte_Punkte)
    
    //get und set Methoden
    std::string getAufgabeName();
    double getMaxPunkte();
    double getErreichtePunkte();
    
    void setAufgabeName(std::string);
    void setMaxPunkte(double);
    void setErreichtePunkte(double);
};

#endif
