#pragma once
using namespace std;
#include "string"
#include "vector"
#include <limits>
#include <memory>
class Vertex;
typedef shared_ptr<Vertex> VertexPtr;

class Vertex
{
public:
	Vertex();
	Vertex(string name);
	string name;
	int gain;
	string color = "";
	int distance = numeric_limits<int>::max();
	VertexPtr parent;
	VertexPtr next = NULL;
	vector<VertexPtr > adjacencyList;
	
};