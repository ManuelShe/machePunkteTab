/*
Programm: machePunkteTab

Projektersteller: Manuel Scheiermann
Das Projekt steht unter der Creative Commons Lizenz 4.0
Siehe dazu: https://creativecommons.org/licenses/by-nc-sa/4.0/deed.de
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "blatt.hpp"

Blatt::Blatt() : blattnummer(0), bonuspunkte(0), gesamtpunktzahl(0), eingelesen(false), authoren("k.A."), erreichtePunkte(0) {
    
    // Einlesen der Daten fuer das Blatt
    std::string tmp;
    double tmp_d;
    std::ifstream in_datei;
    in_datei.open("korrektur.log");
    if(!in_datei) {
        std::cout << "Erstelle korrektur.log ..." << std::endl;
        std::cout << "Bitte die Blattnummer eingeben: ";
        std::cin >> blattnummer;
        std::cout << "Wie viele Bonuspunkte können erreicht werden?: ";
        std::cin >> bonuspunkte;
        std::cout << "Wie hoch ist die Gesamtpunktzahl (ohne Bonusaufgaben): ";
        std::cin >> gesamtpunktzahl;
        std::cout << "Die Aufgaben. Geben Sie Bezeichnungen für die Aufgaben ein (z.B. 9 oder 9* für eine Bonusaufgabe). Ein - beendet die Aufnahme von weiteren Aufgaben." << std::endl;
        
        bool fertigEingelesen = false;
        std::string eingabe;
        double eingabe_double;
        int i = 1;
        do{
            std::cout << "     Bezeichnung der " << i << ". Aufgabe des Blattes: ";
            std::cin >> eingabe;
            if(eingabe != "-")
            {
                Aufgabe* aufg = new Aufgabe(eingabe);
                aufgaben.push_back(aufg);
                i++;
            }
            else{
                fertigEingelesen = true;
            }
        }while(!fertigEingelesen);
        
        std::cout << std::endl << "maximalen Punkte. Geben Sie die maximalen Punkte ein, die in der jeweiligen Aufgabe erreicht werden können." << std::endl;
        
        for(int i = 0; i < aufgaben.size(); i++){
            std::cout << "     Maximale Punkte der Aufgabe " << aufgaben[i]->getAufgabeName() << ": ";
            std::cin >> eingabe_double;
            aufgaben[i]->setMaxPunkte(eingabe_double);
        }
        
        std::cout << std::endl << "Datei korrektur.log wird erstellt ..." << std::endl;
        
        //Ausgabe in korrektur.log
        std::string file = "korrektur.log";
        std::fstream myfile;
        myfile.open(file, std::ios::out);
        
        myfile << "korrektur Log" << std::endl;
        myfile << "Uebungsblatt " << blattnummer << "   Bonuspunkte " << bonuspunkte << "   Gesamtpunktzahl " << gesamtpunktzahl << std::endl;
        myfile << "------------------------------------------------------" << std::endl;
        myfile << "Aufgaben:" << std::endl;
        
        for(int i = 0; i < aufgaben.size(); i++)
            myfile << aufgaben[i]->getAufgabeName() << " ";
        
        myfile << "-" << std::endl << std::endl << "maximale_Punkte:" << std::endl;
        
        for(int i = 0; i<aufgaben.size(); i++)
            myfile << aufgaben[i]->getMaxPunkte() << " ";
        
        myfile << "-" << std::endl << std::endl;
        myfile.close();
        std::cout << "Datei korrektur.log ist erstellt." << std::endl << "Programm Ende." << std::endl;
        
    }
    else{
        std::string zeile;
        std::getline(in_datei, zeile); // Ueberschrift
        std::getline(in_datei, zeile);
        std::istringstream iss(zeile);
        
        iss >> tmp;
        iss >> blattnummer;
        iss >> tmp;
        iss >> bonuspunkte;
        iss >> tmp;
        iss >> gesamtpunktzahl;
        
        std::getline(in_datei, zeile); // "------------------------------------"
        std::getline(in_datei, zeile); // "Aufgaben:"
        std::getline(in_datei, zeile);
        std::istringstream iss2(zeile);
        
        iss2 >> tmp; // Aufgaben Name
        
        do{
            Aufgabe* aufg = new Aufgabe(tmp);
            aufgaben.push_back(aufg);
            iss2 >> tmp;
        }while(tmp != "-");
        
        std::getline(in_datei, zeile); // Leere Zeile
        std::getline(in_datei, zeile); // "Punkte:"
        std::getline(in_datei, zeile);
        std::istringstream iss3(zeile);
        
        iss3 >> tmp; // Eingelesene Punkte
        int pos = 0;
        do{
            tmp_d = std::stod(tmp); // Konvertierung in double
            aufgaben[pos]->setMaxPunkte(tmp_d);
            aufgaben[pos]->setErreichtePunkte(tmp_d);
            iss3 >> tmp;
            pos++;
        }while(tmp != "-");
        
        std::cout << std::endl << "Übersicht" << std::endl << "------------------------" << std::endl;
        std::cout << "Eingelesen Übungsblatt: " << blattnummer << std::endl;
        std::cout << "Eingelesen Gesamtpunktzahl: " << gesamtpunktzahl << std::endl;
        std::cout << "Eingelesene Aufgaben:" << std::endl;
        
        for(unsigned int i=0; i<aufgaben.size(); i++){
            std::cout << "   Aufgabe: " << std::setw(5) << aufgaben[i]->getAufgabeName() << "      Maximale Punkte: " << aufgaben[i]->getMaxPunkte() << std::endl;
        }
        
        errechneErreichtePunkte();
        
        std::cout << std::endl << "Geben Sie die Authoren der Abgabe ein: ";
        std::getline (std::cin,authoren);
        eingelesen = true;
    }
        
}

void Blatt::errechneErreichtePunkte(){
    erreichtePunkte = 0;
    for(unsigned int i = 0; i < aufgaben.size(); i++){
        erreichtePunkte += aufgaben[i]->getErreichtePunkte();
    }
}


void Blatt::punkteAnzeigen(){
    
    std::string tmp;
    std::getline(std::cin, tmp);  // Eingebepuffer leeren
    
    if(erreichtePunkte < gesamtpunktzahl/2){
        std::cout << "!WARNUNG!: Die Gesamtpunktzahl liegt bei " << erreichtePunkte << " und damit unter den benötigten " << gesamtpunktzahl/2 << " Punkten für den Bonus.";
        std::getline(std::cin, tmp);  // Auf Eingabe warten
    }
    
    if(erreichtePunkte >= gesamtpunktzahl/2 - 1 && erreichtePunkte < gesamtpunktzahl/2){
        std::cout << "!WARNUNG!: Es fehlen nur " << gesamtpunktzahl/2 - erreichtePunkte << " um die/den Bonuspunkt(e) zu erlangen!";
        std::getline(std::cin, tmp);  // Auf Eingabe warten
    }
    
    std::cout << std::endl << "Das Übungsblatt wird wie folgt bewertet:" << std::endl;
    
    for(int i = 0; i < aufgaben.size(); i++){
        std::string eingabe;
        std::cout << "Aufgabe " << std::setw(3) << aufgaben[i]->getAufgabeName() << " -> " << std::setw(3) << aufgaben[i]->getErreichtePunkte() << " von " <<  aufgaben[i]->getMaxPunkte() << " Punkt(en) (Enter bestätigen oder andere Punktzahl eingeben): ";
        std::getline(std::cin, eingabe);
        
        if(eingabe != ""){
            aufgaben[i]->setErreichtePunkte(atof(eingabe.c_str()));
            std::cout << "      Geändert: Aufgabe " << std::setw(3) << aufgaben[i]->getAufgabeName() << " -> " << std::setw(3) << aufgaben[i]->getErreichtePunkte() << " von " << aufgaben[i]->getMaxPunkte() << " Punkt(en)" << std::endl;
        }
    }
    errechneErreichtePunkte();
    double erreichteBonuspunkte = 0;
    if(erreichtePunkte >= gesamtpunktzahl/2)
        erreichteBonuspunkte = bonuspunkte;
    
    std::cout << std::endl << "Gesamtpunktzahl: " << erreichtePunkte << "/" << gesamtpunktzahl << "   Bonuspunkt(e): " << erreichteBonuspunkte << std::endl << "---------------------------------------------" << std::endl;
    std::getline(std::cin, tmp);  // Auf Eingabe warten
}
    
void Blatt::ausgabe(Datei* deckblatt){
        std::cout << "Zusammenfassender Kopf wird erstellt ..." << std::endl;
        for(int i = 0; i < 2; i++){
            std::ofstream myfile;
            if(i==0){
                std::string file = "korrektur.log";
                myfile.open(file, std::ios::app);
                myfile << std::endl << "Zusammenfassender_Kopf:" << std::endl;
            }
            else if(i==1){
                if(deckblatt == nullptr)
                    break;
                
                std::string file = deckblatt->getPfad() + "DECKBLATT" + deckblatt->getName();
                myfile.open(file);
                std::cout << "Zusammenfassender Kopf wird in die Datei " << file << " geschrieben ..." << std::endl;
            }
            myfile << "/*" << std::endl;
            myfile << " *   Uebungsblatt " << blattnummer << std::endl;
            myfile << " *   Name(n): " << authoren << std::endl;
            myfile << " *" << std::endl;
            
            myfile << " *         |";
            for(int i=0; i < aufgaben.size(); i++){
                myfile << "         |";
            }
            myfile << std::endl;
            
            myfile << " * Aufgabe |";
            for(int i=0; i < aufgaben.size(); i++){
                myfile << "  " << std::setw(5) << aufgaben[i]->getAufgabeName() << "  |";
            }
            myfile << " Summe";
            myfile << std::endl;
            
            myfile << " * --------+";
            for(int i=0; i < aufgaben.size(); i++){
                myfile << "---------+";
            }
            
            myfile << "----------";
            myfile << std::endl;
            
            myfile << " * Punkte  |";
            for(int i=0; i < aufgaben.size(); i++){
                myfile << "  " << std::setw(5) << aufgaben[i]->getErreichtePunkte() << "  |";
            }
            myfile << std::endl;
            
            myfile << " *         |";
            for(int i=0; i < aufgaben.size(); i++){
                myfile << "         |";
            }
            myfile << "  " << std::setw(5) << erreichtePunkte << " / " << gesamtpunktzahl;
            myfile << std::endl;
        
            myfile << " *";
            
            if(erreichtePunkte >= gesamtpunktzahl/2) {
                myfile << " => " << bonuspunkte << " Bonuspunkt(e)" << std::endl;
            }
            else{            
                myfile << " => 0 Bonuspunkte" << std::endl;
            }
            
            myfile << " *" << std::endl;
            myfile << " * (* sind Bonusaufgaben)" << std::endl;
            myfile << " *" << std::endl;
            myfile << " */" << std::endl;
            myfile << std::endl;
            
            if(i==1){
                std::ifstream inStream;
                std::string inFile = deckblatt->getPfad() + deckblatt->getName();
                inStream.open(inFile);
                while(!inStream.eof()){
                    std::string zeile;
                    std::getline(inStream, zeile);
                    myfile << zeile << std::endl;
                }                
                inStream.close();
            }
            
            myfile.close();
            
        }
        std::cout << "Fertig. Zusammenfassender_Kopf erstellt." << std::endl;
}
    
int Blatt::getBlattnummer() const{
    return blattnummer;
}

double Blatt::getGesamtpunktzahl() const{
    return gesamtpunktzahl;
}

std::vector<Aufgabe*> Blatt::getAufgaben() const{
    return aufgaben;
}

bool Blatt::getEingelesen() const{
    return eingelesen;
}

void Blatt::setAufgabenErreichtePunkte(double p,unsigned int pos, bool abzug){
    if(abzug == true){
        aufgaben[pos]->setErreichtePunkte(aufgaben[pos]->getErreichtePunkte() - p);
    }
    else{        
        aufgaben[pos]->setErreichtePunkte(p);
    }
    errechneErreichtePunkte();
}
