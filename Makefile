
dijkstra : build_dijk
	./test.o

build_dijk : dijkstra.cpp
	g++ -std=c++11 -o test.o dijkstra.cpp
