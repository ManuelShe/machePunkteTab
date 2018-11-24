#include <iostream>
#include "datei.hpp"

Datei::Datei(std::string n) : name(n), aufgabe(""), punktabzug(0){
}


std::string Datei::getName(){
    return name;
}

std::string Datei::getAufgabe(){        //# Kommentar
    return aufgabe;
}

double Datei::getPunktabzug(){          //#(- 1.5 ) Punktabzug von eins-Komma-fünf Punkten
    return punktabzug;
}

