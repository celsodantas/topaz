
SRCDIR = ./src
BINDIR = ./bin
CPP_COMPILER = llvm-g++
NO_FLAGS  = -Wno-unused-variable -Wno-unused-private-field -Wno-sign-compare
CPP_FLAGS	= -Wall -Wextra -std=c++11 -pedantic -framework OpenGL -g $(NO_FLAGS)
HEADERS=-I$(shell brew --prefix)/include -Ilib -Isrc
LDFLAGS=-L$(shell brew --prefix)/lib
LINKFLAGS= -lassimp -lglfw3
CPPFILES=src/Main.cpp src/engine/EventGrandCentral.cpp src/engine/Core.cpp src/Game.cpp src/Player.cpp src/engine/Importer.cpp src/engine/GameObject.cpp

all: Game.o

Game.o:
	$(CPP_COMPILER) $(CPP_FLAGS) $(HEADERS) $(LDFLAGS) $(LINKFLAGS) $(CPPFILES) -o $(BINDIR)/$@
	chmod +x $(BINDIR)/$@

clean:
	rm -fr $(BINDIR)/*.o*

build_and_run: clean Game.o
	./$(BINDIR)/Game.o
