/*
Programm: machePunkteTab

Projektersteller: Manuel Scheiermann
Das Projekt steht unter der Creative Commons Lizenz 4.0
Siehe dazu: https://creativecommons.org/licenses/by-nc-sa/4.0/deed.de
*/

#ifndef blattHeader
#define blattHeader

#include <iostream>
#include <vector>
#include "aufgabe.hpp"
#include "datei.hpp"

class Datei;

class Blatt {
private:
    int blattnummer;
    double bonuspunkte;
    double gesamtpunktzahl;
    std::vector<Aufgabe*> aufgaben;
    bool eingelesen;        //bei true existiert die Datei korrektur.log
    
    std::string authoren;
    double erreichtePunkte;
    
public:
    Blatt();
    void errechneErreichtePunkte();
    void punkteAnzeigen();
    void ausgabe(Datei*); //Ausgabe in die Datei korrektur.log und ggf. in das Deckblatt
    
    int getBlattnummer() const;
    double getGesamtpunktzahl() const;
    std::vector<Aufgabe*> getAufgaben() const;
    bool getEingelesen() const;
    
    void setAufgabenErreichtePunkte(double,unsigned int,bool); //(double Punkte, int Position, bool Punkte_Abziehen)
};

#endif
