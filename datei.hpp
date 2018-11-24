/*
Programm: machePunkteTab

Projektersteller: Manuel Scheiermann
Das Projekt steht unter der Creative Commons Lizenz 4.0
Siehe dazu: https://creativecommons.org/licenses/by-nc-sa/4.0/deed.de
*/


#ifndef dateiHeader
#define dateiHeader

#include <iostream>
#include "blatt.hpp"

class Blatt;

class Datei{
private:    
    std::string name;
    std::string pfad;
    std::string aufgabe;
    double punktabzug;
    
public:
    Datei(std::string, std::string); //(Name_der_Datei, Pfad_der_Datei)
    void zuweisung(const Blatt&);
    void punkteZusammenrechnen(Blatt&);
    void kommentareAusgeben();
    
    //get und set Methoden
    std::string getName();
    std::string getPfad();
    std::string getAufgabe();
    double getPunktabzug();
    bool getDeckblatt();
    void setAufgabe(std::string);
    void setPunktabzug(double);
    void setDeckblatt(bool);
};

#endif
