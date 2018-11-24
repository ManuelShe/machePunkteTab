#include <iostream>

#ifndef dateiHeader
#define dateiHeader

class Datei{
private:    
    std::string name;       //#(- 5 ) test Kommentar
    std::string aufgabe;
    double punktabzug;
    
public:
    Datei(std::string);
    
    std::string getName();
    std::string getAufgabe();
    double getPunktabzug();
};

#endif
