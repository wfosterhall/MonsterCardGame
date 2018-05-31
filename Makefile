# default target is all
CC=gcc
all: main

# main is made by linking object files together
main: card.o cardList.o spellCard.o main.o
	g++ spellCard.o card.o cardList.o main.o -o main.exe

# the card.o object file needs recompiled if card.cpp or card.h changes
card.o: card.cpp card.h
	g++ -c card.cpp -o card.o

cardList.o: cardList.cpp cardList.h
	g++ -c cardList.cpp -o cardList.o

spellCard.o: spellCard.cpp spellCard.h
	g++ -c spellCard.cpp -o spellCard.o

# the main.o object file needs recompiled if main.cpp or card.h changes
main.o: main.cpp card.h cardList.h spellCard.h
	g++ -c main.cpp -o main.o

# clean removes all object files and the compiled executable
clean:
	rm -f *.o main
