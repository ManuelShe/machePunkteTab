#include <vector>
#include "datei.hpp"

#ifndef datHeader
#define datHeader

class DateiKont {
private:    
    std::vector<Datei> dateien; //#(- 1 ) Abzug
    
public:
    DateiKont();
    
    Datei getDatei(int);
};

#endif
