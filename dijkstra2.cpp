
#include <iostream>
#include <cstdio>
#include <cfloat>

#define MAX 6

typedef int POTNODE;

typedef struct CELL *LIST;
struct CELL {
	POTNODE nodeName;
	float nodeLabel;
	LIST next;
};

typedef struct {
	float dist;
	LIST successors;
	POTNODE toPOT;
} GRAPH[MAX];

typedef POTNODE POT[MAX+1];

void swap(POTNODE a, POTNODE b, GRAPH G, POT P)
{
	POTNODE temp;

	temp = P[b];
	P[b] = P[a];
	P[a] = temp;
	G[P[a]].toPOT = a;
	G[P[b]].toPOT = b;
}

float priority(POTNODE a, GRAPH G, POT P)
{
	return G[P[a]].dist;
}

void bubbleUp(POTNODE a, GRAPH G, POT P) {
	if ((a > 1) && (priority(a, G, P) < priority(a/2, G, P))) {
		swap(a, a/2, G, P);
		bubbleUp(a/2, G, P);
	}
}

void bubbleDown(POTNODE a, GRAPH G, POT P, int last)
{
	POTNODE child;

	child = 2 * a;
	if (child < last && priority(child+1, G, P) < priority(child, G, P)) {
		++child;
	}

	if (child <= last && priority(a, G, P) > priority(child, G, P)) {
		swap(a, child, G, P);
		bubbleDown(child, G, P, last);
	}
}

void initialize(GRAPH G, POT P, int *pLast) {
	int i;

	for(i = 0; i < MAX; ++i) {
		G[i].dist = FLT_MAX;
		G[i].toPOT = i + 1;
		P[i+1] = i;
	}

	G[0].dist = 0;
	(*pLast) = MAX;
}

void Dijkstra(GRAPH G, POT P, int *pLast) {
	POTNODE u, v;
	LIST ps;

	initialize(G, P, pLast);
	while ((*pLast) > 1) {
		v = P[1];
		swap(1, *pLast, G, P);
		--(*pLast);
		bubbleDown(1, G, P, *pLast);
		ps = G[v].successors;
		while (ps != NULL) {
			u = ps->nodeName;
			if (G[u].dist > G[v].dist + ps->nodeLabel) {
				G[u].dist = G[v].dist + ps->nodeLabel;
				bubbleUp(G[u].toPOT, G, P);
			}

			ps = ps->next;
		}
	}
}

int main(int argc, char** argv) {
	GRAPH graph;
	POT potNodes;
	POTNODE last;

	// Cell 1
	CELL* c2 = (CELL*) malloc(sizeof(CELL));
	c2->nodeName = 1;
	c2->nodeLabel = 4;
	c2->next = (CELL*) malloc(sizeof(CELL));

	CELL* c3 = c2->next;
	c3->nodeName = 2;
	c3->nodeLabel = 1;
	c3->next = (CELL*) malloc(sizeof(CELL));

	c3 = c3->next;
	c3->nodeName = 3;
	c3->nodeLabel = 5;
	c3->next = (CELL*) malloc(sizeof(CELL));

	c3 = c3->next;
	c3->nodeName = 4;
	c3->nodeLabel = 8;
	c3->next = (CELL*) malloc(sizeof(CELL));

	c3 = c3->next;
	c3->nodeName = 5;
	c3->nodeLabel = 10;
	c3->next = NULL;

	graph[0].successors = c2;
	graph[1].successors = NULL;

	// Cell 3
	c3 = (CELL*) malloc(sizeof(CELL));
	c3->nodeName = 1;
	c3->nodeLabel = 2;
	c3->next = NULL;

	graph[2].successors = c3;

	// Cell 4
	CELL* c4 = (CELL*) malloc(sizeof(CELL));
	c4->nodeName = 4;
	c4->nodeLabel = 2;
	c4->next = NULL;

	graph[3].successors = c4;

	// Cell 5
	CELL* c5 = (CELL*) malloc(sizeof(CELL));
	c5->nodeName = 5;
	c5->nodeLabel = 1;
	c5->next = NULL;

	graph[4].successors = c5;
	graph[5].successors = NULL;

	Dijkstra(graph, potNodes, &last);
	for(int i = 1; i < 6; ++i) {
		printf("1 -> %d: %.0f\n", i+1, graph[i].dist);
	}
}
