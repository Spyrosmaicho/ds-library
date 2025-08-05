#ifndef GRAPH_H
#define GRAPH_H

typedef struct Graph Graph;

/*Function to initialize the graph*/
Graph* InitializeGraph(int nodes);

/*Function to insert an edge into the graph*/
void InsertEdge(Graph *G,int start,int dest,int weight);

/*Function to print graph using adjacency list representation*/
void ShowGraph(Graph* graph);

/*Find minimum spanning tree using Kruskal's Algorythm*/
void MinimumSpanningTree(Graph* graph);

/*Function to deallocate memory for graph*/
void DestroyGraph(Graph *G);

#endif // GRAPH_H