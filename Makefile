
dijkstra2 : build_dijk2
	./test.o

dijkstra : build_dijk
	./test.o

build_dijk2 : dijkstra2.cpp
	g++ -std=c++11 -o test.o dijkstra2.cpp

build_dijk : dijkstra.cpp
	g++ -std=c++11 -o test.o dijkstra.cpp
