all: hello

hello: HelloWorld.o
	g++ HelloWorld.o -o hello

HelloWorld.o: HelloWorld.cpp
	g++ -c HelloWorld.cpp

clean:
	rm -rf *o hello
