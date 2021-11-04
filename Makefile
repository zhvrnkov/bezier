GL_PKGS=glfw3 glew
CFLAGS=-Wall -Wextra -Ofast
FILES=main.c setup.c

main: main.o
	./main.o

main.o: main.c
	g++ $(CFLAGS) `pkg-config --cflags $(GL_PKGS)` $(FILES) -o main.o `pkg-config --libs $(GL_PKGS)`
