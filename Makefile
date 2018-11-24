# Variablen mit Dateinamen, Compileraufruf und Optionen fuer Compiler und Linker
HDR     = aufgabe.hpp datei.hpp dateiKont.hpp blatt.hpp
OBJ     = aufgabe.o datei.o dateiKont.o blatt.o main.o
BIN     = machePunkteTab_v1.5
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
