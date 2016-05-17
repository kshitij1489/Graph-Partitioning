#include "DataStructures.h"
#include <algorithm>


DataStructures::DataStructures()
{
}

void DataStructures::initializeBuckets(vector<VertexPtr>& buckets)
{
	int i = 0;

	for (size_t i = 0; i < (2 * maxDegree + 1); i++) {
		buckets.push_back(make_shared<Vertex>());
	}
}

void DataStructures::initializeBucketSort(int vertexIndex, int gain, vector<VertexPtr>& buckets, const vector<VertexPtr > vertices, bool side)
{
	int* maxGainIndex;
	if (side) {
		maxGainIndex = &maxLeftGainIndex;
	}
	else {
		maxGainIndex = &maxRightGainIndex;
	}
	int index;
	if (gain != 0) {
		index = maxDegree + gain;
		*maxGainIndex = max(index, *maxGainIndex);
	}
	else {
		index = maxDegree;
		*maxGainIndex = max(index, *maxGainIndex);
	}
	VertexPtr v = buckets.at(index);
	VertexPtr temp = v->next;
	v->next = vertices.at(vertexIndex);
	v->next->gain = gain;
	v->next->next = temp;
}

void DataStructures::incrementGain(vector<VertexPtr>& currentBucket, VertexPtr v, bool side)
{
	int* maxGainIndex;
	if (side) {
		maxGainIndex = &maxLeftGainIndex;
	}
	else {
		maxGainIndex = &maxRightGainIndex;
	}
	//Remove Vertex from current Linked List
	VertexPtr bucketIndex = currentBucket.at(maxDegree + v->gain);
	while (bucketIndex != NULL) {
		VertexPtr previous = bucketIndex;
		if (bucketIndex->next == v) {
			// Remove Vertex v
			previous->next = v->next;
			v->next = NULL;
			break;
		}
		else {
			previous = bucketIndex->next;
			bucketIndex = bucketIndex->next;
		}
	}
	//Add vertex to new Linked List
	VertexPtr nextBucketIndex = currentBucket.at(maxDegree + v->gain + 2);
	VertexPtr temp = nextBucketIndex->next;
	nextBucketIndex->next = v;
	v->gain += 2;
	int h = v->gain;
	*maxGainIndex = max(*maxGainIndex, maxDegree + v->gain);
	nextBucketIndex->next->next = temp;
}

void DataStructures::decrementGain(vector<VertexPtr>& complementBucket, VertexPtr v, bool side)
{
	int* maxGainIndex;
	if (side) {
		maxGainIndex = &maxLeftGainIndex;
	}
	else {
		maxGainIndex = &maxRightGainIndex;
	}
	//Remove Vertex from current Linked List
	VertexPtr bucketIndex = complementBucket.at(maxDegree + v->gain);
	while (bucketIndex != NULL) {
		VertexPtr previous = bucketIndex;
		if (bucketIndex->next == v) {
			// Remove Vertex v
			previous->next = v->next;
			v->next = NULL;
			break;
		}
		else {
			previous = bucketIndex->next;
			bucketIndex = bucketIndex->next;
		}
	}
	//Add vertex to new Linked List
	VertexPtr previousBucketIndex = complementBucket.at(maxDegree + v->gain - 2);
	VertexPtr temp = previousBucketIndex->next;
	previousBucketIndex->next = v;
	// if the current linkedlist is empty only then check to reduce the maxgainIndex
	if (complementBucket.at(maxDegree + v->gain)->next == NULL && *maxGainIndex == maxDegree + v->gain)
		*maxGainIndex -= 1; // Reduce only if it is equal to the only highest gain vertex
	v->gain -= 2;
	previousBucketIndex->next->next = temp;
}

