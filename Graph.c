#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

Node* createNode(char* v) {
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Failed to allocate memory for new node.\n");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = strdup(v);
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices, char* names[]) {
    Graph* graph = malloc(sizeof(Graph));
    if (graph == NULL) {
        fprintf(stderr, "Failed to allocate memory for graph.\n");
        exit(EXIT_FAILURE);
    }

    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(int));
    graph->vertexNames = malloc(vertices * sizeof(char*));

    if (graph->adjLists == NULL || graph->visited == NULL || graph->vertexNames == NULL) {
        fprintf(stderr, "Failed to allocate memory for graph components.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
        graph->vertexNames[i] = strdup(names[i]);
    }

    return graph;
}

void addEdge(Graph* graph, char* src, char* dest) {
    int srcIndex = getVertexIndex(graph, src);
    int destIndex = getVertexIndex(graph, dest);

    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[srcIndex];
    graph->adjLists[srcIndex] = newNode;

    // Add edge from dest to src for undirected graph
    newNode = createNode(src);
    newNode->next = graph->adjLists[destIndex];
    graph->adjLists[destIndex] = newNode;
}
/*
added visited and getVertexIndex in case you found it useful
*/
void visitVertex(Graph* graph, char* vertex) {
    int vertexIndex = getVertexIndex(graph, vertex);
    if (vertexIndex != -1) {
        graph->visited[vertexIndex] = 1;
        printf("Visited %s\n", vertex);
    } else {
        printf("Vertex %s not found.\n", vertex);
    }
}

int getVertexIndex(Graph* graph, const char* name) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (strcmp(graph->vertexNames[i], name) == 0) {
            return i;
        }
    }
    return -1; // Vertex name not found
}

void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %s\n ", graph->vertexNames[v]);
        while (temp) {
            printf("%s -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    char* vertexNames[] = {"A", "B", "C", "D", "E"};

    Graph* graph = createGraph(5, vertexNames);

    addEdge(graph, "A", "B");
    addEdge(graph, "A", "C");
    addEdge(graph, "B", "C");
    addEdge(graph, "B", "D");
    addEdge(graph, "C", "D");
    addEdge(graph, "D", "E");
    visitVertex(graph, "C");
    printGraph(graph);
    return 0;
}
