//To apply the Prim's algorithm to find the minimum spanning tree of a graph

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int N = 5;
// N being the number of nodes

// defining a structure Edge to store the edges included in the MST in the form of (source,destination)
struct Edge
{
  int src, dest, weight;
};

// This is to defiine a node in the adjacency list
// destination and weight is specified and adjlistnode *next points to the next node of the adjacency list
struct adjlistnode
{
  int dest, weight;
  struct adjlistnode *next;
};

// This is to represent the linked list assigned with each vertex in the graph
// adjlist *head points to the first node of the corresponding linked list of each vertex
struct adjlist
{
  int weight;
  struct adjlist *head;
};

// This is to store the complete information of the graph
struct Graph
{
  int numofvertices;     // Holds the value of number of vertices in graph
  struct adjlist *array; // Points to an array, each element of which, represents a vertex and its corresponding linked list to represent the vertices connected to that particular vertex
};

// Function to create a new node with given destination and weight
struct adjlistnode *createnewnode(int dest, int weight)
{
  struct adjlistnode *newnode = (struct adjlistnode *)malloc(sizeof(struct adjlistnode *));
  newnode->dest = dest;
  newnode->weight = weight;
  newnode->next = NULL;
  return newnode;
}

// Function to create a graph with given number of vertices
struct Graph *createGraph(int numofvertices)
{
  struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
  graph->numofvertices = numofvertices;

  graph->array = (struct AdjList *)malloc(numofvertices * sizeof(struct adjlist));

  for (int i = 0; i < numofvertices; ++i)
  {
    graph->array[i].head = NULL;
  }

  return graph;
}

// Function to add an edge to the graph
void addedge(struct Graph *graph, int src, int dest, int weight)
{

  struct adjlistnode *newnode = createnewnode(dest, weight);
  newnode->next = graph->array[src].head;
  newnode->dest = dest;

  newnode = createnewnode(src, weight);
  newnode->next = graph->array[dest].head;
  graph->array[dest].head = newnode;
}

// To apply prim's algorithm to make the MST
void primMST(struct Graph *graph, int numofvertices, int N)
{
  struct Edge *mstedge = (struct Edge *)malloc((graph->numofvertices - 1) * sizeof(struct Edge *));
  int mstedgecount = 0;

  bool *visitedarr = (bool *)malloc(numofvertices * sizeof(bool *));
  for (int i = 0; i < numofvertices; i++)
  {
    visitedarr[i] = false;
  }

  // Defining an array to keep track of the minimum costs of adding edges to the MST
  int *key = (int *)malloc(numofvertices * sizeof(int *));
  // The distance of the first node is set to be 0 as it is included in the MST straight away
  key[0] = 0;

  // Initializing all the elements of the key array to a large value except the one at the zeroth index
  for (int i = 1; i < numofvertices; i++)
  {
    key[i] = __INT_MAX__;
  }

  for (int count = 0; count < numofvertices - 1; count++)
  {
    int u = -1;
    int v = 0;

    while (v < numofvertices)
    {
      if (!visitedarr[v] && (u == -1 || key[v] < key[u]))
      {
        u = v;
      }
      v++;
    }

    // Marking the edges included in the MST
    visitedarr[u] = true;

    if (count > 0)
    {
      mstedge[mstedgecount].src = u;          //Assigns u to the value of the source node 
      mstedge[mstedgecount].dest = v;         //ASsigns v as the destination node of the selected edge 

      mstedge[mstedgecount].weight = graph->array[u].head->weight;  //weight of the head node of the adjacency list of the selected vertex u is being assigned to the selected edge
      mstedgecount++;
    }

    struct adjlistnode *iterator = graph->array[u].head;
    // Above is the initialization of an iterator "iterator" to the head element of the adjacency list of the selected vertex "u"
    while (iterator != NULL)
    {
      
      int v = iterator->dest;
      int w = iterator->weight;
      if (!visitedarr[v] && w < key[v])
      { // This condition basically checks if adding the edge from vertex u to v would provide a shorted path to v than the current known path in the MST
        key[v] = w;
      }
      iterator = iterator->next;
    }
  }

  //Printing the edges in the MST
  printf("The edges in the MST are:\n");
  for(int i = 0; i<mstedgecount; ++i)
  {
    printf("%d - %d\tWeight:%d\n", mstedge[i].src, mstedge[i].dest, mstedge[i].weight);
  }

  free(mstedge);
  free(visitedarr);
  free(key);
}

int main()
{
  int numofvertices = 5;
  struct Graph* graph = createGraph(numofvertices);
  
  addedge(graph, 0, 1, 2);
  addedge(graph, 0, 3, 1);
  addedge(graph, 1, 2, 3);
  addedge(graph, 1, 3, 2);
  addedge(graph, 1, 4, 4);
  addedge(graph, 2, 4, 5);
  addedge(graph, 3, 4, 3);

  //calling the primMST to start applying Prim's Algorithm
  primMST(graph, numofvertices, N);

  //Free up the space (optional hai, but its a good practice!!)
  free(graph->array);
  free(graph);

  return 0;

}
