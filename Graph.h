#ifndef GRAPH_H
#define GRAPH_H

typedef struct Node {
    char* vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    char** vertexNames; // Add this line
    int* visited;
    Node** adjLists;
} Graph;

Graph* createGraph(int vertices, char* names[]); // Correct the declaration
void addEdge(Graph* graph, char* src, char* dest);
void visitVertex(Graph* graph, char* vertex);
int getVertexIndex(Graph* graph, const char* name);
void printGraph(Graph* graph);
#endif // GRAPH_H

