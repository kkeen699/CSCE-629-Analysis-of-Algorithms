CFLAGS = -O3 -Wall -std=c++11
CFLAGS = -g -Wall -std=c++11

graph: main.o graph.o dijkstra.o dijkstra_heap.o kruskal.o
	g++ -o $@ main.o graph.o dijkstra.o dijkstra_heap.o kruskal.o $(CFLAGS)
#	strip $@

main.o: main.cpp graph.h dijkstra.h dijkstra_heap.h kruskal.h
	g++ -c main.cpp $(CFLAGS)

graph.o: graph.cpp graph.h
	g++ -c graph.cpp $(CFLAGS)

dijkstra.o: dijkstra.cpp dijkstra.h graph.h
	g++ -c dijkstra.cpp $(CFLAGS)

dijkstra_heap.o: dijkstra_heap.cpp dijkstra_heap.h graph.h
	g++ -c dijkstra_heap.cpp $(CFLAGS)

kruskal.o: kruskal.cpp kruskal.h graph.h
	g++ -c kruskal.cpp $(CFLAGS)

clean:
	rm -f graph *.o