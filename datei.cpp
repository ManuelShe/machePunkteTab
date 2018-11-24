/*
Programm: machePunkteTab

Projektersteller: Manuel Scheiermann
Das Projekt steht unter der Creative Commons Lizenz 4.0
Siehe dazu: https://creativecommons.org/licenses/by-nc-sa/4.0/deed.de
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "datei.hpp"

Datei::Datei(std::string n, std::string p) : name(n), pfad(p), aufgabe(""), punktabzug(0) {
    double abzug = 0;
    std::string tmp;
    std::ifstream in_datei;
    in_datei.open(pfad + name);
    if(!in_datei) {
        std::cout << "Fehler in Konstruktor Datei() (datei.cpp): Datei " << pfad + name << " lässt sich nicht öffnen!" << std::endl;
    }
    else{
        std::cout << "Durchsuche Datei " << pfad + name << " ..." << std::endl;
        while(!in_datei.eof()){
            std::string zeile;
            std::getline(in_datei, zeile);
            std::istringstream iss(zeile);
            while(!iss.eof()){
                iss >> tmp;
                if(tmp == "//#(-"){
                    double a;
                    iss >> a;
                    abzug += a;
                }
            }
        }
        punktabzug = abzug;
    }
    
    std::cout << "In " << pfad + name << ": Punktabzug = " << punktabzug << std::endl;
}

void Datei::zuweisung(const Blatt &aktuellesBlatt){
    bool aufgabeExistiert = false;
    while(!aufgabeExistiert){
        std::string eingabe;
        std::cout << "Weisen Sie der Datei " << pfad + name << " eine Aufgabe zu: ";
        std::cin >> eingabe;
        for(unsigned int i = 0; i < aktuellesBlatt.getAufgaben().size(); i++) {
            if(eingabe == aktuellesBlatt.getAufgaben()[i]->getAufgabeName()){
                aufgabeExistiert = true;
                break;
            }
        }
        if(!aufgabeExistiert)
            std::cout << "  Die Aufgabe ist unbekannt! Bitte geben Sie eine Aufgabe ein, die auf dem Blatt existiert." << std::endl;
        else {
            aufgabe = eingabe;
            std::cout << " Datei wurde der Aufgabe " << eingabe << " zugewiesen." << std::endl;
        }
    }
}

void Datei::punkteZusammenrechnen(Blatt& aktuellesBlatt){
    for(unsigned int i = 0; i < aktuellesBlatt.getAufgaben().size(); i++){
        if(aktuellesBlatt.getAufgaben()[i]->getAufgabeName() == aufgabe)
            aktuellesBlatt.setAufgabenErreichtePunkte(punktabzug,i,true);
    }
}

void Datei::kommentareAusgeben(){
    //stream fuer korrektur.log oeffnen
    std::fstream aus_korrektur_log;
    aus_korrektur_log.open("korrektur.log",std::ios::app);
    aus_korrektur_log << pfad + name << ":" << std::endl;
           
    //Datei oeffnen 
    std::ifstream in_datei;
    in_datei.open(pfad + name);
    if(!in_datei){
        std::cout << "  Fehler in kommentareAusgeben() (datei.cpp): Datei " << pfad + name << " lässt sich nicht öffnen!" << std::endl;
        aus_korrektur_log << "Datei ließ sich nicht öffnen." << std::endl;
    }
    else{
        int zeilennr = 1;
        //Datei durchsuchen
        while(!in_datei.eof()){
            std::string zeile;
            std::getline(in_datei, zeile);
            std::size_t found = zeile.find("//#");
            if(found != std::string::npos){
                //Zeile in korrektur.log schreiben
                aus_korrektur_log << "Zeile " << std::setw(4) << zeilennr << ": " << zeile << std::endl;                
            }
            zeilennr++;
        }
        in_datei.close();
    }
    aus_korrektur_log << std::endl;
    aus_korrektur_log.close();
}

std::string Datei::getName(){
    return name;
}

std::string Datei::getPfad(){
    return pfad;
}

std::string Datei::getAufgabe(){
    return aufgabe;
}

double Datei::getPunktabzug(){
    return punktabzug;
}

void Datei::setAufgabe(std::string auf){
    aufgabe = auf;
}

void Datei::setPunktabzug(double abzug){
    punktabzug = abzug;
}
