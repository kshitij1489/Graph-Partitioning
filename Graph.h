#pragma once
#include <vector>
#include "Vertex.h"
#include "DataStructures.h"
class Graph : public DataStructures
{
public:
	Graph();
	vector<VertexPtr > vertices;
	vector<VertexPtr> leftBuckets;
	vector<VertexPtr> rightBuckets;
	vector<bool> bitvector;
	bool side = false;
	VertexPtr getVertexObj(string name);
	void initializeBuckets();
	vector<int> initializeGain(vector<bool> bitvector);
	void initializeBitVector();
	void randomizeBitVector();
	void calculateMaxDegree();
	void initializeBucketSort(int vertexIndex, int gain, string side);
	bool hasVertex(string u);
	VertexPtr addVertex(string name);
	void addEdge(string a, string b);
	bool isNeighbour(VertexPtr u, VertexPtr v);
};