CPP = g++
CPPFLAGS = -g -Wall -Werror -pedantic -ansi #-DMAP std=c++11 has to be put in last
OPTIMIZATION = -O3
BIN = bin/
EXE = $(BIN)/atmo
INT = $(wildcard src/*.h)
REAL = $(INT:.h=.cpp)
ECHO = @echo
.PHONY: clean tests

help:
	$(ECHO) "- help    : Display this message"
	$(ECHO) "- debug   : Build debug version of <Atmo>"
	$(ECHO) "- release : Build optimized version of <Atmo>"
	$(ECHO) "- run	   : Run program"
	$(ECHO) "- clean   : Delete binary files"

debug:
	@ mkdir -p bin
	$(ECHO) "Building debug version of <Atmo> ..."
	@ $(CPP) $(CPPFLAGS) -std=c++11 -o $(EXE) $(REAL)

release:
	@ mkdir -p bin
	$(ECHO) "Building release version of <Atmo> ..."
	@ $(CPP) $(OPTIMIZATION) -std=c++11 -o $(EXE) $(REAL)

run:
	$(ECHO) "Running <Atmo>"
	@ ./$(EXE)

clean:
	@ rm -r $(BIN)/*
	$(ECHO) "$(BIN) directory is now clean"
