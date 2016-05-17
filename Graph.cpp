#include "vector"
#include "Graph.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>

// Graph class stores the vector of vertices(Vertex object).
// Each Vertex stores the adjacency list of that vertex. Adjacency list is defined as an vector of Vertex object.
Graph::Graph()
{

}

void Graph::initializeBuckets() {
	calculateMaxDegree();
	DataStructures::initializeBuckets(leftBuckets);
	DataStructures::initializeBuckets(rightBuckets);
}

void Graph::initializeBitVector()
{
	// TODO - Currently the vertices are in sorted order in CSV but implement sorting of vertices vector, maybe has an inbuilt function?
	int size = vertices.size();
	int mid = ceil(size / 2);

	for (unsigned int i = 0; i < mid; i++)
		bitvector.push_back(0);
	for (unsigned int i = mid; i < size; i++)
		bitvector.push_back(1);
}

void Graph::randomizeBitVector()
{
	// obtain a time-based seed. Uncomment to get time based seed.
	unsigned seed = 1;//std::chrono::system_clock::now().time_since_epoch().count();
	//Shuffle bitVector. Value 0 and 1 represents two different partitions.
	shuffle(bitvector.begin(), bitvector.end(), std::default_random_engine(seed));
}

void Graph::calculateMaxDegree()
{
	int degree = 0;
	for (VertexPtr u : vertices) {
		int r = u->adjacencyList.size();
		degree = max(degree, r);
	}
	this->maxDegree = degree;
	leftBuckets.reserve(2 * maxDegree + 1);
	rightBuckets.reserve(2 * maxDegree + 1);
}

void Graph::initializeBucketSort(int vertexIndex, int gain, string side) {

	if ("left" == side) {
		DataStructures::initializeBucketSort(vertexIndex, gain, leftBuckets, vertices, false);
	}
	else if ("right" == side) {
		DataStructures::initializeBucketSort(vertexIndex, gain, rightBuckets, vertices, true);
	}
}

VertexPtr Graph::getVertexObj(string name) {
	for (VertexPtr i : vertices)
	{
		if (i->name == name)
			return i;
	}

	return addVertex(name);
}

// Returns true if the graph contains vertex u.
bool Graph::hasVertex(string u) {

	for (VertexPtr i : vertices)
	{
		if (i->name == u)
			return true;
	}
	return false;
}
// This method adds a vertex to the graph. It does nothing if the
// vertex is found in the graph object otherwise
//adds vertex to the graph creating a null adjacency list
VertexPtr Graph::addVertex(string name) {
	VertexPtr u(new Vertex(name));
	//Vertex* u = new Vertex(name);
	//u->name = name;
	vertices.push_back(u);
	return u;
}

// Returns true if v is a neighbour of u(we pass adjacency list of u here)
bool Graph::isNeighbour(VertexPtr u, VertexPtr v) {
	vector<VertexPtr > list = u->adjacencyList;
	for (VertexPtr k : list) {
		if (k->name == v->name)
			return true;
	}
	return false;
}
// This method adds vertices u and v to the graph if they don't exist yet.
// Adds eachother to adjacencylists.
// It checks for duplicate edges to avoid multiple/parallel edges
void Graph::addEdge(string a, string b) {
	VertexPtr u = getVertexObj(a);
	VertexPtr v = getVertexObj(b);

	if (!isNeighbour(u, v)) // to avoid duplicates
		u->adjacencyList.push_back(v);
	if (!isNeighbour(v, u)) // to avoid duplicates
		v->adjacencyList.push_back(u);
}

//initialize gain data structure by calculating the gain for each vertex
vector<int> Graph::initializeGain(vector<bool> bitvector) {
	vector<int> gains;
	for (int i = 0; i < vertices.size(); i++) {
		int gain = 0;
		for (int j = 0; j < vertices.size(); j++) {
			if (isNeighbour(vertices[i], vertices[j])) {
				if (bitvector[i] == bitvector[j])
					gain--;
				else
					gain++;
			}
		}
		if (bitvector.at(i) == false)
			initializeBucketSort(i, gain, "left");
		else
			initializeBucketSort(i, gain, "right");
	}
	return gains;
}