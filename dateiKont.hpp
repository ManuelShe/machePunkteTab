/*
Programm: machePunkteTab

Projektersteller: Manuel Scheiermann
Das Projekt steht unter der Creative Commons Lizenz 4.0
Siehe dazu: https://creativecommons.org/licenses/by-nc-sa/4.0/deed.de
*/

#ifndef datHeader
#define datHeader

#include <vector>
#include <dirent.h>
#include <stdio.h>
#include "datei.hpp"
#include "blatt.hpp"

class DateiKont {
private:    
    std::vector<Datei*> dateien;
    Datei* deckblatt;
    
public:
    DateiKont();
    void verzeichnisAuslesen(std::string, DIR*);
    void dateienZuweisen(const Blatt&);
    void pruefenAllesAbgegeben(Blatt&);
    void erreichtePunkteErrechnen(Blatt&);
    void alleKommentareAusgeben();
    void deckblattBestimmen(const Blatt&);
    
    std::vector<Datei*> getDateien();
    Datei* getDeckblatt();
};

#endif
