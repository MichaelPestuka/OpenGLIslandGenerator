.PHONY: 

all:
	g++ -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -g src/*.cpp src/*.hpp src/glad.c -o island-gen 

run: all
	./island-gen
