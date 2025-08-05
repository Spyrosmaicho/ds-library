#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "weightedgraph.h"

/*Hidden structs from user*/

typedef struct Edge 
{
    int destination;          //Destination node
    int weight;        //Edge weight
    struct Edge* next; // ext edge in the linked list
} Edge;

typedef struct Graph 
{
    int num_nodes;    
    Edge** adj_list;   // Array of adjacency lists
} Graph;

// struct for Kruskal
typedef struct EDGE 
{
    int u;
    int v;
    int w;
} KruskalEdge;


/*Function that creates a new edge*/
Edge *CreateEdge(int dest,int weight)
{
    Edge *new = malloc(sizeof(Edge));
    assert(new!=NULL);
    new->weight = weight;
    new->destination =dest;
    new->next = NULL;
    return new;
}


/*Function to initialize the graph*/
Graph* InitializeGraph(int nodes) 
{
    Graph* graph = malloc(sizeof(Graph));
    assert(graph!=NULL);
    graph->num_nodes = nodes;
    graph->adj_list = malloc(nodes * sizeof(Edge*));
    assert(graph->adj_list!=NULL);
    for (int i = 0; i < nodes; i++) graph->adj_list[i] = NULL;
    return graph;
}

/*Function to insert an edge into the graph*/
void InsertEdge(Graph *G,int start,int dest,int weight)
{
    //Add edge from start to dest
    Edge* new = CreateEdge(dest, weight);
    new->next = G->adj_list[start];
    G->adj_list[start] = new;

    //Add edge from dest to start
    new = CreateEdge(start, weight);
    new->next = G->adj_list[dest];
    G->adj_list[dest] = new;
}



/*Function to print graph using adjacency list representation*/
void ShowGraph(Graph* graph) 
{
    for (int i = 0; i < graph->num_nodes; i++) 
    {
        Edge* curr = graph->adj_list[i];
        printf("Node %d: ", i);
        while (curr != NULL) 
        {
            printf("(%d, %d) ", curr->destination, curr->weight);
            curr = curr->next;
        }
        printf("\n");
    }
}

//Print the MST edges and total cost
void printMST(KruskalEdge *T, int n) 
{
    int i, cost = 0;
    printf("Selected Edges:\nu  v  w\n");
    for (i = 0; i < n; i++) 
    {
        printf("%d  %d  %d\n", T[i].u, T[i].v, T[i].w);
        cost += T[i].w;
    }
    printf("\nTotal MST Cost = %d\n", cost);
}

/*Helper function to count edges. Useful for memory allocation in MST*/
int count_edges(Graph* graph)
 {
    int count = 0;
    for (int i = 0; i < graph->num_nodes; i++) 
    {
        Edge* current = graph->adj_list[i];
        while (current != NULL) 
        {
            if (i < current->destination) count++;
            current = current->next;
        }
    }
    return count;
}

/*Merges two sorted subarrays into a single sorted array*/
void merge(KruskalEdge* arr, int l, int m, int r) 
{
    //Calculate sizes of left and right subarrays
    int n1 = m - l + 1;  //Size of left subarray
    int n2 = r - m;       //Size of right subarray

    //Create temporary arrays
    KruskalEdge* L = malloc(n1 * sizeof(KruskalEdge));  //Left subarray
    KruskalEdge* R = malloc(n2 * sizeof(KruskalEdge));  //Right subarray

    //Copy data to temporary arrays
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];      //Left copy
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];  //Right copy

    //Merge the temporary arrays back into arr[l..r]
    int i = 0;  //Initial index of left subarray
    int j = 0;  //Initial index of right subarray
    int k = l;  //Initial index of merged subarray

    while (i < n1 && j < n2) 
    {
        // Compare edge weights and merge in ascending order
        if (L[i].w <= R[j].w) 
        {
            arr[k] = L[i];
            i++;
        } 
        else 
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    //Copy remaining elements of L[]
    while (i < n1) arr[k++] = L[i++];

    //Copy remaining elements of R[]
    while (j < n2) arr[k++] = R[j++];

    //Free temporary arrays
    free(L);
    free(R);
}

 /* Recursive Merge Sort function.*/
void mergeSort(KruskalEdge* arr, int l, int r) 
{
    if (l < r) 
    {
        //Find middle point to divide the array
        int m = l + (r - l) / 2;

        //Recursively sort left and right halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        //Merge the sorted halves
        merge(arr, l, m, r);
    }
}

//Find the root of a node with path compression
int find(int* parent,int u) {
    if (parent[u] != u) parent[u] = find(parent, parent[u]);
    return parent[u];
}


//Union two sets using rank (to optimize tree height)
void unionbyrank(int* parent, int* rank,int u, int v) 
{
    int x = find(parent,u);
    int y = find(parent,v);
    if (rank[x] < rank[y]) parent[x] = y;
    else if (rank[y] < rank[x]) parent[y] = x;
    else 
    {
        parent[x] = y;
        rank[y]++;
    }
}


/*Find minimum spanning tree using Kruskal's Algorythm*/
void MinimumSpanningTree(Graph* graph) 
{
    int n = graph->num_nodes;  //Number of nodes
    int e = count_edges(graph);
    KruskalEdge* edges = malloc(e * sizeof(KruskalEdge));  
    assert(edges != NULL);

    // Convert adjacency list to edge array
    int edge_idx = 0;
    for (int u = 0; u < n; u++) 
    {
        Edge* current = graph->adj_list[u];
        while (current != NULL) 
        {
            int v = current->destination;
            if (u < v) 
            {
                edges[edge_idx].u = u;
                edges[edge_idx].v = v;
                edges[edge_idx].w = current->weight;
                edge_idx++;
            }
            current = current->next;
        }
    }

    //Initialize Union-Find structures
    int* parent = malloc(n * sizeof(int));
    int* rank = malloc(n * sizeof(int));
    assert(parent != NULL && rank != NULL);
    
    for (int i = 0; i < n; i++) 
    {
        parent[i] = i;
        rank[i] = 0;
    }

    KruskalEdge* T = malloc((n - 1) * sizeof(KruskalEdge));  //MST
    assert(T != NULL);

    mergeSort(edges, 0, e - 1);  //Sort edges by weight

    int j = 0;  //Counter for MST edges
    for (int i = 0; i < e && j < n - 1; i++) 
    {
        int u = edges[i].u;
        int v = edges[i].v;
        int x = find(parent,u);
        int y = find(parent,v);
        if (x != y) 
        {
            T[j] = edges[i];
            unionbyrank(parent,rank,x, y);
            j++;
        }
    }
    if (j != n - 1) 
    {
        printf("The graph is not connected. MST not possible.\n");
        free(edges); free(parent); free(rank); free(T);
        return;
    }
    printMST(T, n - 1);  //Print MST

     //Free all dynamically allocated memory
    free(edges);
    free(parent);
    free(rank);
    free(T);
}

/*Function to deallocate memory for graph*/
void DestroyGraph(Graph *G) {
    if (G == NULL) return;
    
    //Free each edge in the adjacency lists
    for (int i = 0; i < G->num_nodes; i++) 
    {
        Edge *current = G->adj_list[i];
        while (current != NULL) 
        {
            Edge *temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    //Free the array of adjacency lists
    free(G->adj_list);
    
    //Finally free the graph structure
    free(G);
}