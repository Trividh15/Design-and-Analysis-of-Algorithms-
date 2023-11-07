//Porblem Statement: Find the Minimum SPanning Tree of a graph using the Kruskal's Algorithm.

#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent, rank;
};

// Function to find the set of an element 'i'
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function that does union of two sets of 'x' and 'y'
void unionSets(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);   //denotes the parent of the element x or the set to which the element x belongs
    int yroot = find(subsets, y);   //denotes the parent of the element y or the set to whihc the element y belongs

    if (xroot == yroot) return;       //if both the values are equal that it means that the elements x and y belong to the same set and hence cannot be operated with "union" as that would result in formation of a loop

    // Make one root point to the other
    subsets[xroot].parent = yroot;    //x would start pointing to the parent of y, i.e., both the elements x and y would point to the same node i.e. they would be roots  of the same parent
}


void kruskalMST(struct Edge* edges, int V, int E) {
    struct Edge result[V]; //This is the array of strutures which holds the information about the edges to be considered in the MST
    int e = 0; //This is the pointer which indicates out position with respect to the tree
   
    struct Subset subsets[V]; // An array to represent subsets for executing the union of the sets and the find function

    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1) {
        // Find the smallest edge
        struct Edge next_edge = edges[e++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e-1] = next_edge;
            unionSets(subsets, x, y);
        }
    }

    printf("Edges in the MST:\n");
    for (int i = 0; i < e; i++)
        printf("(%d, %d) -> %d\n", result[i].src, result[i].dest, result[i].weight);
}


int main() {
    int V = 4; // Number of vertices in the graph
    int E = 5; // Number of edges in the graph

    // Defining the edges with their source, destination, and weight
    struct Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };
     
    //Calling the KruskalMST() function for the array of structures named edges!
    kruskalMST(edges, V, E);
    return 0;
}
