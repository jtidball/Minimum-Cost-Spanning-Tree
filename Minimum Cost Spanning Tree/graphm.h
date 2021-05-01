#pragma once
//
//// BASED UPON :
//// From the software distribution accompanying the textbook
//// "A Practical Introduction to Data Structures and Algorithm Analysis,
//// Third Edition (C++)" by Clifford A. Shaffer.
//// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.
//
//// Taken from page 389, 391 both implementations have been taken from 
//
//// Code edited by Jack Tidball
//
//
#include "graph.h"

using namespace std;
class Graphm : public Graph {
private:
	LList<Edge>** vertex; // List headers
	int numVertex, numEdge; // Number of vertices, edges
	int* mark; // Pointer to mark array

public:
	Graphm(int numVert) {
		Init(numVert);
	}

	~Graphm() { // Destructor
		delete[] mark; // Return dynamically allocated memory
		for (int i = 0; i < numVertex; i++) {
			delete[] vertex[i];
		}
		delete[] vertex;
	}

	void Init(int n) {
		int i;
		numVertex = n;
		numEdge = 0;
		mark = new int[n]; // Initialize mark array
		for (i = 0; i < numVertex; i++) {
			mark[i] = false;
		}
		// Create and initialize adjacency lists
		vertex = (LList<Edge>**) new LList<Edge>*[numVertex];
		for (i = 0; i < numVertex; i++)
			vertex[i] = new LList<Edge>();
	}

	int n() { return numVertex; } // Number of vertices
	int e() { return numEdge; }   // Number of edges

	int first(int v) { // Return first neighbor of "v" TAKEN FROM PG 391
		if (vertex[v]->length() == 0)
			return numVertex; // No neighbor
		vertex[v]->moveToStart();
		Edge it = vertex[v]->getValue();
		return it.vertex();
	}

	// Get v’s next neighbor after w
	int next(int v, int w) { //TAKEN FROM PG 391
		Edge it;
		if (isEdge(v, w)) {
			if ((vertex[v]->currPos() + 1) < vertex[v]->length()) {
				vertex[v]->next();
				it = vertex[v]->getValue();
				return it.vertex();
			}
		}
		return n(); // No neighbor
	}

	// Set edge (i, j) to "weight"
	void setEdge(int i, int j, int weight) { // TAKEN FROM PG 392
		Edge currEdge(j, weight);
		if (isEdge(i, j)) { // Edge already exists in graph
			vertex[i]->remove();
			vertex[i]->insert(currEdge);
		}
		else { // Keep neighbors sorted by vertex index
			numEdge++;
			for (vertex[i]->moveToStart();
				vertex[i]->currPos() < vertex[i]->length();
				vertex[i]->next()) {
				Edge temp = vertex[i]->getValue();
				if (temp.vertex() > j)
					break;
			}
			vertex[i]->insert(currEdge);
		}
	}
	
	void delEdge(int i, int j) {  // Delete edge (i, j) TAKEN FROM PG 392
		if (isEdge(i,j)) {
			vertex[i]->remove();
			numEdge--;
		}
	}

	bool isEdge(int i, int j) { // Is (i, j) an edge? CHANGED FROM PG 392
		vertex[i]->moveToStart();
		while (vertex[i]->currPos() < vertex[i]->length()) {
			Edge it = vertex[i]->getValue();
			if (it.vertex() == j) {
				return true;
			}
			vertex[i]->next();
		}
		return false;
	}


	int weight(int i, int j) { // Return weight of (i, j) TAKEN FROM PG 392
		Edge curr;
		if (isEdge(i, j)) {
			curr = vertex[i]->getValue();
			return curr.weight();
		}
		else return 0;
	}

	int getMark(int v) {
		return mark[v];
	}

	void setMark(int v, int val) {
		mark[v] = val;
	}

	void setVisit() {
		bool isVisited = false;
		for (int i = 0; i < numVertex; i++) {
			mark[i] = isVisited;
		}
	}

};
