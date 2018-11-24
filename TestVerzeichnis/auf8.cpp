#include <iostream>
#include <dirent.h>
#include <vector>
#include "dateiKont.hpp"
#include "datei.hpp"

DateiKont::DateiKont() {
    std::cout << "DateiKont Konstruktor ..." << std::endl;
    char pfad[] = "./";
    DIR *verzeichnis;
    struct dirent *datei;
    verzeichnis = opendir(pfad);
    
    while(datei = readdir(verzeichnis)) {
        std::string datei_name = datei->d_name;             //#(- 4.5 ) Auch Abzug
        if( datei_name.find(".txt") != std::string::npos ||
            datei_name.find(".c") != std::string::npos ||
            datei_name.find(".h") != std::string::npos ||
            datei_name.find(".cpp") != std::string::npos ||
            datei_name.find(".hpp") != std::string::npos ||
            datei_name.find("Makefile") != std::string::npos) {
            Datei dat(datei->d_name);
            dateien.push_back(dat);
            std::cout << "Datei zu dateien hinzugefuegt: " << datei->d_name << std::endl;
        }
        
    }
    closedir(verzeichnis);
}

Datei DateiKont::getDatei(int i){
    return dateien[i];
}
