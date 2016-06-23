#Graph-Partitioning

Introduction
---
The graph partitioning problem as described by Kernighan and Lin is “given a graph G with costs on its edges, partition the nodes of G into subsets no larger than a given maximum size, so as to minimize the total cost of the edges cut”
To start we will try to solve the problem with two partitions before generalizing the number of partitions. In the 2-partition version of the problem, the task is to assign each vertex to one of two “halves”. The total cost can be visualized by the total weight of the edges between the two halves. This is also called the minimum bisection problem, which is known to be NP-Complete.

This implementation variant of the Fiduccia-Mattheyses (F-M) algorithm, applied to simple graphs as opposed to hypergraphs, where we experiment and compare solutions using five different termination conditions or walkterms.

Definitions
---
We define a step as moving a vertex from one partition to another. A segment is defined as a sequence of steps, which ends when there are no vertices left to move. A segment here could also be perceived as a pass described in the original Kernighan-Lin paper. A bitvector is a sequence of bits/strings(strings when there are more than 2 partitions), where each bit corresponds to a vertex representing which partition it belongs to. The initial configuration of bitvector of each segment is called the bottom of a segment. Segments are chained together when the lowest value bit vector from one segment becomes the bottom of a new segment. This sequence of segments comprise a walk. A walk is terminated according to the following five criteria, called walkterms:

Walkterm 0 - This is the classic F-M algorithm. A walk is terminated as soon as the most recent segment fails to improve upon the previous one.

Walkterm 1 - The algorithm records the bitvector that have been seen as bottoms of segments. A walk is terminated when the current bottom has already been seen. So it might not terminate even if there is no improvement.

Walkterm 2- Like walkterm 1, but with a subtle difference. When there are multiple bitvectors of lowest value in a segment, care is taken to choose one that has not been seen in the previous walkterms. Under walkterm 1 the bitvector chosen to be the new bottom is typically the first minimum.

Walkterm 3-Like walkterm 2 but the new bottom is the minimum value bitvector among the unseen ones. Hence the walk will terminate only if every partitioning along a segment has been seen. This leads to very long walks.

Walkterm 4- Like walkterm 3 except the definition of seen is changed: here a bitvector is seen if it has arisen anywhere along a segment.


Fiduccia-Mattheyses Algorithm
---
This algorithm extends the concept of cut cost to hypergraphs. Here each vertex is assigned a weight which is used to calculate the gain(i.e the reduction in cut cost). In each pass, only one vertex is moved at a time unlike two in case of the K-L algorithm. Another new introduction is the use of the gain bucket data structure which is used to select a vertex to be moved to the other partition. This data structure computes the weight(gain) of each vertex and sorts them in a list. It takes constant time to find the best vertex from the data structure while updating the data structure after each move is proportional to the degree of the vertex. The vertex with the highest gain is selected and moved. Here, like the K-L algorithm, the vertices are locked once they have been used. This algorithm has a runtime of O(p) where p is the total number of pins or terminals in a graph. Here the best partition encountered during the pass is selected. Additional passes could then be performed until no further improvements are observed. In their algorithm, Fiduccia and Mattheyses, establish balance by allowing certain permissible tolerance which is determined by the fraction of the size of partition, the size of the cutset and the amount by which the partition deviates from the desired fraction.

Though the original paper talks about hypergraphs, our focus here is on simple graphs. The F-M algorithm would also work in polynomial time O(m) on simple graphs, as simple graphs are simply a special case of a hyper graphs where each edge connects only two vertices. The F-M algorithm has a constant time implementation for fetching the best vertex in each step which we discuss in the next section.

Our Modified F-M algorithm for simple graphs and Analysis
---
**Bucket List Structure**
In each step of a segment, we choose the vertex with the maximum gain to be moved. We define a Gain of a vertex as the change in number of edge crossings caused by the vertex when complemented. A gain of a vertex will be positive when number of edge crossings decrease and negative when edge crossings increase upon its shifting. Vertex with the maximum gain is defined as the base vertex. To maintain a sorted list of the vertex gain, we use bucket sort, where the array of buckets range from -pmax to +pmax and where kth bucket in the array will maintain a linked list of vertices having the gain value k. Two separate bucket arrays are maintained, one for each partition. Direct access to each vertex allows us to shift a vertex from one bucket to the head of the list of another bucket quickly. Fetching a vertex having the maximum gain could be done in constant time by maintaining a separate index for the maximum gain vertex. 
Using the proposition stated in the original F-M paper for hypergraphs, we claim that the amount of work needed to maintain each bucket array is O(m) per segment for simple graphs. 

**Initializing Vertex Gain**
At the beginning of each segment, we compute the gains of each vertex in the graph. This process makes as many operations as the sum of the degrees of each vertices. 
The sum of degrees is equal to 2*m. Hence the below algorithm works in O(m) time.
```
Initializing Vertex Gain Algorithm
*	For each free vertex i 
       g(i) ← 0 
*	F ← “From” partition of vertex i 
*	T ← “To” partition of vertex i 
*	For each edge incident on vertex i DO, 
       If F(n) = 1, Then increment gain // F(n) = if both vertices lie on same side of partition
       If T(n) = 0, Then decrement gain // T(n) = if the incident vertices lie on both sides of the partition

```
**Updating Vertex Gains**
After each step, gains of the vertices needs to be recomputed. We note that only the neighboring
vertices of the base cell will have to be worked upon. As per the proposition 4 in the F-M paper [2] for hypergraphs, the total work required to maintain cell gains during a segment is O(n(E)).
```
Updating Vertex Gains Algorithm
• F ← “From” partition of base vertex i
• T ←  “To” partition of base vertex i
• Lock the base vertex and complement its block
• For each edge incident on base vertex i
     Increment the gain of each free neighboring vertex in F.
     Decrement the gain of all free neighboring vertices in T.
```

Credits and Contributers
--------------
```
Matt Stallman, Professor, NCSU
Zach Cleghern
```

References
---
[1] B.W. Kernighan, S. Lin. An efficient heuristic procedure for partitioning graphs. Bell System Tech. J.,
pages 291 - 307, 1970.

[2] C. M. Fiduccia and R. M. Mattheyses. A linear time heuristic for improving network partitions. In
Proceedings of the ACM/IEEE Design Automation Conference, pages 175-181,1982.

[3] Wikipedia Fiduccia-Mattheyses_algorithm.

[4] Matthias Stallmann, Path Splicing Document

