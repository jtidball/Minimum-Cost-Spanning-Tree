#pragma once

// Edge class for Adjacency List graph representation pg 388
class Edge {
	int vert, wt;
public:
	Edge() { vert = -1; wt = -1; }
	Edge(int v, int w) { vert = v; wt = w; }
	int vertex() { return vert; }
	int weight() { return wt; }

};