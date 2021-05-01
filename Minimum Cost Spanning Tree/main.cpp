#include <fstream>
#include "llist.h"
#include "Edge.h"
#include "graphm.h"
#include <iostream>
#include <string>


using namespace std;

int minVertex(Graphm* G, int* D);
Graphm* Prim(Graphm* G, int* D, int s, int numVert);
void printf(Graphm* G);
void print(Graphm* G, string file, int numVert);
// Main
int main() {

	cout << "Jack Tidball Lab 5 Minimum Cost Spanning Tree\n\n";

	fstream input("test.txt");

	if (!input.is_open()) {
		cout << "File did not open correctly";
		system("pause");
	}

	int numVert;
	input >> numVert;

	int* arr = new int[numVert];
	Graphm* graph = new Graphm(numVert);

	int temp;
	int j = 0;
	int i = 0;

	while (i < numVert) {
		input >> temp;
		if (!input >> temp) {
			break;
		}
		if (i >= j) {
			if (temp != 0) {
				graph->setEdge(j, i, temp);
				graph->setEdge(i, j, temp);
			}
		}
		if (i == numVert - 1) {
			i = -1;
			j++;
		}
		i++;
	}

	cout << "Number of Vertices: " << graph->n() << "\n";
	cout << "Number of Edges: " << graph->e() << "\n";
	cout << "Matrix is: \n";
	printf(graph);


	Graphm* g;

	cout << "Begin MST 1 starting at Vertex 0\n";
	g = Prim(graph, arr, 0, numVert);
	print(g, "MST - 1", numVert);
	cout << "End of MST 1" << "\n\n";

	g = graph;
	cout << "Begin MST 2 starting at Vertex 4\n";
	g = Prim(graph, arr, 4, numVert);
	print(g, "MST - 2", numVert);
	cout << "End of MST 2" << "\n\n";

	g = graph;
	cout << "Begin MST 3 starting at Vertex 2\n";
	g = Prim(graph, arr, 2, numVert);
	print(g, "MST - 3", numVert);
	cout << "End of MST 3" << "\n\n";



	system("pause");
	return 0;
}


int minVertex(Graphm* G, int* D) { // PG 401 Min vertex Function / Find Min cost Vertex 
	int i, v = -1;
	// Initialize v to some unvisited vertex 
	for (i = 0; i < G->n(); i++) {
		if (G->getMark(i) == 0) {
			v = i;
			break;
		}
	}
	for (i++; i < G->n(); i++) // Now find smallest D value
		if ((G->getMark(i) == 0) && (D[i] < D[v]))
			v = i;
	return v;
}

Graphm* Prim(Graphm* G, int* D, int s, const int numVert) { // Prim’s algorithm based upon textbook PG 405 
	G->setVisit();
	Graphm* graph = new Graphm(numVert);
	int V[6]; // Has to be a constant because must be known at compile time / store closest vertex 
	int i, w;
	for (int i = 0; i < G->n(); i++) { // Initialize
		D[i] = INFINITY;
	}
	D[s] = 0; //D[0] = 0 
	for (i = 0; i < G->n(); i++) { // Process Vertices 
		int v = minVertex(G, D);
		G->setMark(v, true); // Set to visited 

		if (v != s) {
			int wt = G->weight(V[v], v);
			graph->setEdge(V[v], v, wt);
			graph->setEdge(v, V[v], wt);

			cout << "Add edge " << V[v] << " to " << v << endl; // Print edge 

		}
		if (D[v] == INFINITY) { // Unreachable Vertices
			return graph; //return the graph 
		}
		for (w = G->first(v); w < G->n(); w = G->next(v, w)) // Kept this section from text book 
		{
			if (D[w] > G->weight(v, w))
			{
				D[w] = G->weight(v, w); // Update distance 
				V[w] = v; // where it came from
			}
		}
	}
	cout << "\n";
	return graph;
}

void printf(Graphm* G) { //special print without output
	for (int i = 0; i < G->n(); i++) {
		for (int j = 0; j < G->n(); j++) {
			if (G->isEdge(i, j)) {
				cout << G->weight(i, j);
			}
			else {
				cout << "0";
			}
			cout << " ";
		}
		cout << "\n";
	}
	cout << "\n\n";
}


void print(Graphm* G, string file = "", int numVert = 6) { // print with output
	ofstream output;
	output.open(file + ".txt");
	if (!output.is_open()) {
		std::cout << "Unable to open file";
	}
	output << numVert << "\n";

	for (int i = 0; i < G->n(); i++) {
		for (int j = 0; j < G->n(); j++) {
			if (G->isEdge(i, j)) {
				cout << G->weight(i, j);
				output << G->weight(i, j);
			} else {
				cout << "0";
				output << "0";
			}
		cout << " ";
		output << " ";
		}

	cout << "\n";
	output << "\n";
	}
	cout << "\n\n";
	output << "\n\n";
	output.close();
}