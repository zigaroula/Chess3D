CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lglfw3 -lGLEW -lGL -lGLU -lX11 -lXxf86vm -lXrandr -lXinerama -lXcursor -lpthread -lm 
SOURCES=main.cpp vao.cpp scene.cpp program.cpp shader.cpp application.cpp camera.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f *.o 
