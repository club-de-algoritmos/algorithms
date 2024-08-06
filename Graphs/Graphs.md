## Graph notation
A graph is defined by a set of vertices and edges, mathematically, $G=(V,E)$

## Topological sorting
A topological sort of a directed graph is a linear ordering of its vertices such that for every directed edge from vertex u to vertex v, u comes before v in the ordering.

## Directed Acyclic Graph
A directed acyclic graph (DAG) is a directed graph with no directed cycles. That is, it consists of vertices and edges, with each edge directed from one vertex to another, such that following those directions will never form a closed loop.
As dynamic programming (DP) states are in fact calculated in a topological sorting order, DAGs come very handy at solving DP problems.

## Bipartite graphs
A graph is bipartite if its vertices can be divided into two disjoint independent sets. That is, two non-empty sets such that for each set, every pair of nodes is not connected by an edge.
A bipartite graph and its properties are often very useful, below are some examples of how many problems categorized as NP-Hard for general graphs, are easily solvable in polynomial time for bipartite graphs.

## Clique
A clique $C$ in an undirected graph is a subset of the vertices such that every two distinct vertices in it are adjacent. This is equivalent to the condition that the subgraph including only nodes in $C$ and edges incident to two nodes in $C$, is a complete graph.
A maximal clique is a clique that cannot be extended by including one more adjacent vertex, that is, a clique which does not exist exclusively within the vertex set of a larger clique.
A maximum clique of a graph, G, is a clique, such that there is no clique with more vertices

## Maximum Flow
In the maximum flow problem, our task is to send as much flow as possible from the source to the sink. The weight of each edge is a capacity that restricts the flow that can go through the edge. In each intermediate node, the incoming and outgoing flow has to be equal.
The maximum flow problem can be solved using the Dinitz algorithm which runs in $O(V^2E)$

## Max-flow min-cut Theorem
The max-flow min-cut theorem states that in a flow network, the maximum amount of flow passing from the source to the sink is equal to the total weight of the edges in a minimum cut, i.e., the smallest total weight of the edges which if removed would disconnect the source from the sink. 

## Matching
A matching $M$ is a set of edges without repeated vertices.
A maximum matching is a matching that contains the largest possible number of edges.
A perfect matching is a matching that matches all the vertices of the graph. That is, $|M|=|V|/2$.
A maximum matching in a general graph can be found in $O(VE)$ using the Edmonds-Blossom algorithm and in bipartite graphs we can achieve $O(\sqrt{V}E)$ with the Hopcroft-Karp algorithm.

## Vertex Cover
A vertex cover $VC$ is a set of vertices that includes at least one endpoint of every edge of the graph.
A minimum vertex cover is a Vertex Cover that contains the minimum possible number of vertices.
In general graphs, the problem of finding a minimum vertex cover is NP-Hard.
In bipartite graphs, Konig's theorem demonstrates that the cardinality of its minimum vertex cover and the cardinality of its maximum matching are always equal. That is, given the minimum vertex cover $VC$ and the maximum bipartite matching $M$ of a bipartite graph, $|VC|=|M|$.

## Independent Set
An independent set $I$ is a set of vertices such that no two vertices in $I$ are connected with an edge.
A maximum independent set is an independent set that contains the maximum possible number of vertices.
In general graphs, the problem of finding a maximum independent set is strongly NP-Hard.
In bipartite graphs, Konig's theorem also demonstrates that the cardinality of its maximum independent set is equivalent to the number of nodes left out in its minimum vertex cover. That is, given the minimum vertex cover $VC$ and the maximum independent set of a bipartite graph, $|I|=|V|-|VC|$

## Hall's Theorem
Hall's theorem can be used to find out whether a bipartite graph has a matching that contains all left or right nodes. If the number of left and right nodes is the same, Hall's theorem tells us if it is possible to construct a perfect matching.
For the sake of simplicity let's assume we want to find if there's a matching that contains all left nodes.
Let $X$ be any set of left nodes and let $f(X)$ be the set of their neighbors. According to Hall’s theorem, a matching that contains all left nodes exists exactly when for each $X$ , the condition $|X|<=|f(X)|$ holds.

## Edge Cover
An edge cover $EC$ is a set of edges such that every vertex of the graph is incident to at least one edge of the set.
A minimum edge cover is an edge cover that contains the minimum possible number of edges
A minimum edge cover can be found in polynomial time by finding a maximum matching and extending it greedily so that all vertices are covered. That is, given the minimum edge cover $EC$ and the maximum matching |M| of a graph, $|EC|=|V|-|M|$

## Path Cover
A path cover is a set of paths in a graph such that each node of the graph belongs to at least one path. It turns out that in DAGs we can reduce the problem of finding a minimum path cover to the problem of finding a maximum flow in another graph.
# Node-disjoint
In a node-disjoint path cover, each node belongs to exactly one path.
We can find a minimum node-disjoint path cover by constructing a matching graph where each node of the original graph is represented by two nodes: a left node and a right node. There is an edge from a left node to a right node if there is such an edge in the original graph. In addition, the matching graph contains a source and a sink, and there are edges from the source to all left nodes and from all right nodes to the sink.
A maximum matching in the resulting graph corresponds to a minimum node-disjoint path cover in the original graph.
# General
A general path cover is a path cover where a node can belong to more than one path.
A minimum general path cover can be found almost like a minimum node-disjoint path cover. It suffices to add some new edges to the matching graph so that there is an edge $(u, v)$ always when there is a path from $u$ to $v$ in the original graph.

## Partially Ordered Set (poset)
A poset is a set such that for certain pair of elements, one precedes another. The word partial is used to indicate that not every pair of elements needs to be comparable.
A poset satisfies:
1. Reflexivity: a <= a
2. Antisymmetry: if a <= b and b <= a, then a = b
3. Transitivity: if a <= b and b <= c, then a <= c
A poset, then, can be represented as a DAG, which later will be very useful.
# Chains
A chain poset $C$, is a subset of ordered elements of a poset. That is, the elements are all comparable between them, and then, they can be ordered in a way that, $C_0$ < $C_1$ < ... < $C_k$.
Similarly, an antichain poset $AC$, is subset of non-comparable elements of a poset.
# Dilworth's Theorem
A chain decomposition is a partition of the elements of the poset into disjoint chains.
Dilworth's Theorem states that in any finite poset, the largest antichain has the same size as the smallest chain decomposition.
One can see that the cardinality of the minimum chain decomposition is equivalent to the cardinality of the minimum general path cover of the poset's DAG representation.