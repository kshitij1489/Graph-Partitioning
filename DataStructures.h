#pragma once
#include <vector>
#include "Vertex.h"
#include <climits>

class DataStructures
{

public:
	DataStructures();
	int maxDegree = 0;
	int maxLeftGainIndex = 0;
	int maxRightGainIndex = 0;
	void initializeBuckets(vector<VertexPtr>& buckets);
	void initializeBucketSort(int vertexIndex, int gain, vector<VertexPtr>& buckets, const vector<VertexPtr > vertices, bool side);
	void incrementGain(vector<VertexPtr>& currentBucket, VertexPtr v, bool side);
	void decrementGain(vector<VertexPtr>& complementBucket, VertexPtr v, bool side);

};