/*
Programm: machePunkteTab

Projektersteller: Manuel Scheiermann
Das Projekt steht unter der Creative Commons Lizenz 4.0
Siehe dazu: https://creativecommons.org/licenses/by-nc-sa/4.0/deed.de
*/

#include <iostream>
#include <string>
#include "dateiKont.hpp"

DateiKont::DateiKont() : deckblatt(nullptr) {
}

void DateiKont::verzeichnisAuslesen(std::string pfad, DIR *verzeichnis = nullptr){
    const char* pfad_char = pfad.c_str();
    
    DIR *unterverzeichnis;
    struct dirent *datei;
    if(verzeichnis == nullptr)
        verzeichnis = opendir(pfad_char);
    
    while(datei = readdir(verzeichnis)) {
        std::string datei_name = datei->d_name;
        std::string datei_name_mit_pfad = pfad + datei_name;
        const char* datei_name_mit_pfad_char = datei_name_mit_pfad.c_str();
        
        if(!(datei_name == "." || datei_name == "..") &&  (unterverzeichnis = opendir(datei_name_mit_pfad_char))){
            verzeichnisAuslesen(pfad + datei_name + "/", unterverzeichnis);
        }
        else if( datei_name.find(".txt") != std::string::npos ||
            datei_name.find(".c") != std::string::npos ||
            datei_name.find(".h") != std::string::npos ||
            datei_name.find(".cpp") != std::string::npos ||
            datei_name.find(".hpp") != std::string::npos ||
            datei_name.find("Makefile") != std::string::npos ||
            datei_name.find("makefile") != std::string::npos) {
            
            Datei* dat = new Datei(datei->d_name, pfad);
            dateien.push_back(dat);
        }        
    }
    closedir(verzeichnis);
}

void DateiKont::dateienZuweisen(const Blatt& aktuellesBlatt){
    std::cout << std::endl << "Dateien zuweisen ..." << std::endl;
    for(unsigned int i = 0; i < dateien.size(); i++) {
        dateien[i]->zuweisung(aktuellesBlatt);
    }
    std::cout << "Fertig. Dateien zugewiesen." << std::endl;
}

void DateiKont::pruefenAllesAbgegeben(Blatt& aktuellesBlatt){
    bool* aufgabeAbgeben = new bool[aktuellesBlatt.getAufgaben().size()];
    for(unsigned int i = 0; i < aktuellesBlatt.getAufgaben().size(); i++){
        aufgabeAbgeben[i] = false;
    }
    
    for(unsigned int i = 0; i < dateien.size(); i++) {
        for(unsigned int j = 0; j < aktuellesBlatt.getAufgaben().size(); j++){
            if(dateien[i]->getAufgabe() == aktuellesBlatt.getAufgaben()[j]->getAufgabeName()){
                aufgabeAbgeben[j] = true;
                break;
            }
        }
    }
    
    std::cout << std::endl << "Aufgaben abgegeben (1 für ja, 0 für nein):" << std::endl;
    for(unsigned int i = 0; i < aktuellesBlatt.getAufgaben().size(); i++){
        std::cout << "   " << aktuellesBlatt.getAufgaben()[i]->getAufgabeName() << ". Aufgabe:  " << aufgabeAbgeben[i] << std::endl;
        if(aufgabeAbgeben[i] == false){
            aktuellesBlatt.setAufgabenErreichtePunkte(0,i,false);
        }
    }
    std::cout << std::endl;
}

void DateiKont::erreichtePunkteErrechnen(Blatt& aktuellesBlatt){
    pruefenAllesAbgegeben(aktuellesBlatt);
    for(unsigned int i = 0; i < dateien.size(); i++) {
        dateien[i]->punkteZusammenrechnen(aktuellesBlatt);
    }
}

void DateiKont::alleKommentareAusgeben(){
    std::cout << "Kommentare werden in die korrektur.log geschrieben ..." << std::endl;
    if(deckblatt != nullptr){
        Datei* dblatt = new Datei("DECKBLATT" + deckblatt->getName(), deckblatt->getPfad());
        dblatt->kommentareAusgeben();   // Deckblatt Kommentare ausgeben
    }
    
    for(unsigned int i = 0; i < dateien.size(); i++) {      // Kommentare von den anderen Dateien ausgeben
        if(dateien[i] != deckblatt)
            dateien[i]->kommentareAusgeben();
    }
    std::cout << "Fertig. Kommentare in korrektur.log." << std::endl;
}

void DateiKont::deckblattBestimmen(const Blatt& blatt){
    int eingabe_int;
    std::cout << std::endl << "Welcher der Dateien ist das Deckblatt?" << std::endl;
    for(int i = 0; i < dateien.size(); i++)
        std::cout << "     " << i+1 << ": " << dateien[i]->getPfad() + dateien[i]->getName() << std::endl;
    std::cout << "Bitte eine Datei angeben (die Zahl davor): ";
    std::cin >> eingabe_int;
    
    if(eingabe_int < dateien.size() + 1  && eingabe_int > 0)
        deckblatt = dateien[eingabe_int - 1];
}

std::vector<Datei*> DateiKont::getDateien(){
    return dateien;
}

Datei* DateiKont::getDeckblatt(){
    return deckblatt;
}
