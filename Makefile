all: bin rshell

bin:
	mkdir bin

rshell:
	g++ -Wall -Werror -ansi -pedantic src/main.cpp -o bin/rshell
