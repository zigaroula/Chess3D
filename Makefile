CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-L/usr/local/lib -lGLEW -lGLU -lglfw3 -lrt -lXrandr -lXinerama -lXi -lXcursor -lGL -lm -ldl -lXrender -ldrm -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lxcb-dri3 -lxcb-present -lxcb-sync -lxshmfence -lXxf86vm -lXfixes -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp 
SOURCES=main.cpp vao.cpp scene.cpp program.cpp shader.cpp application.cpp camera.cpp game.cpp board.cpp player.cpp piece.cpp pawn.cpp rook.cpp knight.cpp bishop.cpp queen.cpp king.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f *.o 
