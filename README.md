# Graph-Partitioning

The graph partitioning problem as described by Kernighan and Lin is “given a graph G with costs on its edges, partition the nodes of G into subsets no larger than a given maximum size, so as to minimize the total cost of the edges cut”
To start we will try to solve the problem with two partitions before generalizing the number of partitions. In the 2-partition version of the problem, the task is to assign each vertex to one of two “halves”. The total cost can be visualized by the total weight of the edges between the two halves. This is also called the minimum bisection problem, which is known to be NP-Complete.

This implementation variant of the Fiduccia-Mattheyses (F-M) algorithm, applied to simple graphs as opposed to hypergraphs, where we experiment and compare solutions using five different termination conditions or walkterms.

Definitions:
We define a step as moving a vertex from one partition to another. A segment is defined as a sequence of steps, which ends when there are no vertices left to move. A segment here could also be perceived as a pass described in the original Kernighan-Lin paper. A bitvector is a sequence of bits/strings(strings when there are more than 2 partitions), where each bit corresponds to a vertex representing which partition it belongs to. The initial configuration of bitvector of each segment is called the bottom of a segment. Segments are chained together when the lowest value bit vector from one segment becomes the bottom of a new segment. This sequence of segments comprise a walk. A walk is terminated according to the following five criteria, called walkterms:

Walkterm 0 - This is the classic F-M algorithm. A walk is terminated as soon as the most recent segment fails to improve upon the previous one.

Walkterm 1 - The algorithm records the bitvector that have been seen as bottoms of segments. A walk is terminated when the current bottom has already been seen. So it might not terminate even if there is no improvement.

Walkterm 2- Like walkterm 1, but with a subtle difference. When there are multiple bitvectors of lowest value in a segment, care is taken to choose one that has not been seen in the previous walkterms. Under walkterm 1 the bitvector chosen to be the new bottom is typically the first minimum.

Walkterm 3-Like walkterm 2 but the new bottom is the minimum value bitvector among the unseen ones. Hence the walk will terminate only if every partitioning along a segment has been seen. This leads to very long walks.

Walkterm 4- Like walkterm 3 except the definition of seen is changed: here a bitvector is seen if it has arisen anywhere along a segment.
