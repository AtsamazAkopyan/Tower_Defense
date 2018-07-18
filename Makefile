all: compile doc

compile: akopyats

main.o: src/main.cpp src/Tower.h src/Attacker.h src/Map.h src/MapObjects/MapObjects.h \
 src/MapObjects/Wall.h src/MapObjects/MapObjects.h \
 src/MapObjects/../Tower.h src/MapObjects/Path.h src/FileReaderClass.h src/BFS.h
	g++ -std=c++11 -pedantic -Wall -Wno-long-long -O0 -ggdb src/main.cpp -c -o main.o

akopyats: Attacker.o  BFS.o  FileReaderClass.o  main.o  Map.o  Tower.o gameLoop.o  MapObjects.o  Path.o  Wall.o
	g++ Attacker.o  BFS.o  FileReaderClass.o  main.o  Map.o  Tower.o gameLoop.o  MapObjects.o  Path.o  Wall.o -o akopyats

Attacker.o: src/Attacker.cpp src/Attacker.h
	g++ -std=c++11 -pedantic -Wall src/Attacker.cpp -c -o Attacker.o

BFS.o: src/BFS.cpp src/BFS.h src/Map.h src/MapObjects/MapObjects.h src/MapObjects/Wall.h \
 src/MapObjects/MapObjects.h src/MapObjects/../Tower.h \
 src/MapObjects/Path.h src/FileReaderClass.h
	g++ -std=c++11 -pedantic -Wall src/BFS.cpp -c -o BFS.o

FileReaderClass.o: src/FileReaderClass.cpp src/FileReaderClass.h src/Tower.h \
 src/Attacker.h
	g++ -std=c++11 -pedantic -Wall src/FileReaderClass.cpp -c -o FileReaderClass.o
Map.o: src/Map.cpp src/Map.h src/MapObjects/MapObjects.h src/MapObjects/Wall.h \
 src/MapObjects/MapObjects.h src/MapObjects/../Tower.h \
 src/MapObjects/Path.h src/FileReaderClass.h
	g++ -std=c++11 -pedantic -Wall src/Map.cpp -c -o Map.o

Tower.o: src/Tower.cpp src/Tower.h src/FileReaderClass.h
	g++ -std=c++11 -pedantic -Wall src/Tower.cpp -c -o Tower.o

gameLoop.o: src/gameLoop.cpp src/gameLoop.h \
 src/FileReaderClass.h src/Tower.h src/Attacker.h src/BFS.h
	g++ -std=c++11 -pedantic -Wall src/gameLoop.cpp -c -o gameLoop.o

MapObjects.o: src/MapObjects/MapObjects.cpp src/MapObjects/MapObjects.h
	g++ -std=c++11 -pedantic -Wall src/MapObjects/MapObjects.cpp -c -o MapObjects.o

Path.o: src/MapObjects/Path.cpp src/MapObjects/Path.h src/MapObjects/MapObjects.h
	g++ -std=c++11 -pedantic -Wall src/MapObjects/Path.cpp -c -o Path.o

Wall.o: src/MapObjects/Wall.cpp src/MapObjects/Wall.h src/MapObjects/MapObjects.h
	g++ -std=c++11 -pedantic -Wall src/MapObjects/Wall.cpp -c -o Wall.o



run:  compile
	./akopyats

doc: 
	@doxygen
	
	
clean:
	rm -rf akopyats doc *.o
