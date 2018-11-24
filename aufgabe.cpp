/*
Programm: machePunkteTab

Projektersteller: Manuel Scheiermann
Das Projekt steht unter der Creative Commons Lizenz 4.0
Siehe dazu: https://creativecommons.org/licenses/by-nc-sa/4.0/deed.de
*/

#include <iostream>
#include "aufgabe.hpp"

Aufgabe::Aufgabe() : aufgabeName("k.A."), maxPunkte(0), erreichtePunkte(0) {
}

Aufgabe::Aufgabe(std::string name) : aufgabeName(name), maxPunkte(0), erreichtePunkte(0) {
}

Aufgabe::Aufgabe(std::string name, int maxP) : aufgabeName(name), maxPunkte(maxP), erreichtePunkte(maxP) {
}

Aufgabe::Aufgabe(std::string name, int maxP, int erreichteP) : aufgabeName(name), maxPunkte(erreichteP), erreichtePunkte(0) {
}

std::string Aufgabe::getAufgabeName(){
    return aufgabeName;
}

double Aufgabe::getMaxPunkte(){
    return maxPunkte;
}

double Aufgabe::getErreichtePunkte(){
    return erreichtePunkte;
}

void Aufgabe::setAufgabeName(std::string name){
    aufgabeName = name;
}

void Aufgabe::setMaxPunkte(double maxP){
    maxPunkte = maxP;
}

void Aufgabe::setErreichtePunkte(double erreichteP){
    erreichtePunkte = erreichteP;
}
