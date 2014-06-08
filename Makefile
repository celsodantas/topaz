
SRCDIR = ./src
BINDIR = ./bin
CPP_COMPILER = llvm-g++
CPP_FLAGS	= -Wall -Wextra -pedantic -framework OpenGL -g
HEADERS=-I lib
LDFLAGS=-Llib/assimp/lib -Llib/glfw
LINKFLAGS= -lassimp.3.0.1 -lglfw
CPPFILES=src/Main.cpp src/engine/Engine.cpp src/Game.cpp src/Player.cpp

all: Game.o

Game.o:
	$(CPP_COMPILER) $(CPP_FLAGS) $(HEADERS) $(LDFLAGS) $(LINKFLAGS) $(CPPFILES) -o $(BINDIR)/$@
	chmod +x $(BINDIR)/$@

clean:
	rm -f $(BINDIR)/*.o

build_and_run: clean Game.o
	./$(BINDIR)/Game.o
