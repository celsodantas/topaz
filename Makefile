
SRCDIR = ./src
BINDIR = ./bin
CPP_COMPILER = llvm-g++
CPP_FLAGS	= -Wall -Wextra -pedantic -framework OpenGL -framework SDL2 -framework SDL2_ttf -g
HEADERS=-I lib
LDFLAGS=-Llib/assimp/lib
LINKFLAGS= -lassimp.3.0.1
CPPFILES=src/Main.cpp src/Engine.cpp src/Game.cpp

all: Game.o

Game.o:
	$(CPP_COMPILER) $(CPP_FLAGS) $(HEADERS) $(LDFLAGS) $(LINKFLAGS) $(CPPFILES) -o $(BINDIR)/$@
	chmod +x $(BINDIR)/$@

clean: 
	rm -f $(BINDIR)/*.o