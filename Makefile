.PHONY: 

all:
	g++ -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl src/*.cpp src/*.hpp src/glad.c -o test 

run: all
	./test