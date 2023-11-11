#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

Node *createNode(char *v)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for new node.\n");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = strdup(v);
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int vertices, char *names[])
{
    Graph *graph = malloc(sizeof(Graph));
    if (graph == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for graph.\n");
        exit(EXIT_FAILURE);
    }

    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(vertices * sizeof(int));
    graph->vertexNames = malloc(vertices * sizeof(char *));

    if (graph->adjLists == NULL || graph->visited == NULL || graph->vertexNames == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for graph components.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
        graph->vertexNames[i] = strdup(names[i]);
    }

    return graph;
}

void addDirectedEdge(Graph *graph, char *src, char *dest)
{
    int srcIndex = getVertexIndex(graph, src);
    int destIndex = getVertexIndex(graph, dest);

    if (src[strlen(src) - 1] == dest[0])
    {
        Node *newNode = createNode(dest);
        newNode->next = graph->adjLists[srcIndex];
        graph->adjLists[srcIndex] = newNode;
    }
    else
    {
        printf("Error: Spell %s cannot be casted after spell %s\n", dest, src);
    }
}

void addEdges(Graph *graph, char **spellList, int numSpells)
{
    for (int i = 0; i < numSpells; i++)
    {
        for (int j = 0; j < numSpells; j++)
        {
            if (i != j && spellList[i][strlen(spellList[i]) - 1] == spellList[j][0])
                addDirectedEdge(graph, spellList[i], spellList[j]);
        }
    }
}
/*
added visited and getVertexIndex in case you found it useful
*/
void visitVertex(Graph *graph, char *vertex)
{
    int vertexIndex = getVertexIndex(graph, vertex);
    if (vertexIndex != -1)
    {
        graph->visited[vertexIndex] = 1;
        printf("Visited %s\n", vertex);
    }
    else
    {
        printf("Vertex %s not found.\n", vertex);
    }
}

int getVertexIndex(Graph *graph, const char *name)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        if (strcmp(graph->vertexNames[i], name) == 0)
        {
            return i;
        }
    }
    return -1; // Vertex name not found
}

void printGraph(Graph *graph)
{
    for (int v = 0; v < graph->numVertices; v++)
    {
        Node *temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %s\n ", graph->vertexNames[v]);
        while (temp)
        {
            printf("%s -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
