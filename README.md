# Graph-Partitioning
The implementation is based on the Fiduccia-Mattheyses algorithm.

The graph partitioning problem as described by Kernighan and Lin is “given a graph G with costs on its edges, partition the nodes of G into subsets no larger than a given maximum size, so as to minimize the total cost of the edges cut”
To start we will try to solve the problem with two partitions before generalizing the number of partitions. In the 2-partition version of the problem, the task is to assign each vertex to one of two “halves”. The total cost can be visualized by the total weight of the edges between the two halves. This is also called the minimum bisection problem, which is known to be NP-Complete[
