# Variablen mit Dateinamen, Compileraufruf und Optionen fuer Compiler und Linker
HDR     = datei.hpp dateiKont.hpp
OBJ     = datei.o dateiKont.o main.o
BIN     = prog
CC      = g++
CCFLAGS = -std=c++11
LDFLAGS = -o $(BIN)

# Defaulttarget
all: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ)

# Uebersetzungsregel mit Hilfe von Patterns
%.o: %.cpp $(HDR)
	$(CC) $(CCFLAGS) -c $<

# Aufraeumen des Verzeichnisses
.PHONY: clean
clean:
	rm -rf *.o $(BIN)
