#include <stdio.h>
#include <stdlib.h>
#include "weightedgraph.h"

// Helper function for formatted output
void print_line(void)
{
    printf("---------------------\n");
}

int main(void)
{
    int num_nodes;

    // Read number of nodes
    if(scanf("%d", &num_nodes) != 1 || num_nodes <= 0) {
        fprintf(stderr, "Invalid input for number of nodes.\n");
        return 1;
    }

    // Initialize graph
    Graph* G = InitializeGraph(num_nodes);

    int u, v, w;
    // Read edges in format u-v-w (until EOF)
    while (scanf("%d-%d-%d", &u, &v, &w) == 3) 
    {
        if (u < 0 || v < 0 || u >= num_nodes || v >= num_nodes || w < 0) 
        {
            fprintf(stderr, "Invalid edge: %d-%d-%d\n", u, v, w);
            DestroyGraph(G);
            return 1;
        }
        InsertEdge(G, u, v, w);
    }

    printf("Graph Operations\n");
    print_line();
    printf("ShowGraph\n");
    print_line();
    ShowGraph(G);

    printf("\n");
    printf("Minimum Spanning Tree (MST):\n");
    print_line();
    MinimumSpanningTree(G);
    putchar('\n');
    // Clean up
    DestroyGraph(G);
    return 0;
}
