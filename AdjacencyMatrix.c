#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 50
#define MAX_NAME_LENGTH 50

typedef struct {
    char names[MAX_VERTICES][MAX_NAME_LENGTH];
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

Graph createGraph() {
    Graph g;
    int i, j;
    for (i = 0; i < MAX_VERTICES; i++) {
        for (j = 0; j < MAX_VERTICES; j++) {
            g.adjacencyMatrix[i][j] = 0;
        }
    }
    g.numVertices = 0;
    return g;
}

int getVertexIndex(Graph *g, char* name) {
    for (int i = 0; i < g->numVertices; i++) {
        if (strcmp(g->names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

void addEdge(Graph *g, char* start, char* end, int weight) {
    int startIndex = getVertexIndex(g, start);
    int endIndex = getVertexIndex(g, end);

    if (startIndex != -1 && endIndex != -1) {
        g->adjacencyMatrix[startIndex][endIndex] = weight;
    }
}

void printTable(Graph *g) {
    printf("%-15s", "Vertices");
    for (int i = 0; i < g->numVertices; i++) {
        printf("%-15s", g->names[i]);
    }
    printf("\n");

    for (int i = 0; i < g->numVertices; i++) {
        printf("%-15s", g->names[i]);
        for (int j = 0; j < g->numVertices; j++) {
            printf("%-15d", g->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Graph g = createGraph();

    // Read vertices from vertices.txt
    FILE* verticesFile = fopen("vertices.txt", "r");
    if (verticesFile == NULL) {
        perror("Error opening vertices.txt");
        return 1;
    }

    while (fscanf(verticesFile, "%s", g.names[g.numVertices]) != EOF) {
        g.numVertices++;
    }
    fclose(verticesFile);

    // Read edges from edges.txt
    FILE* edgesFile = fopen("edges.txt", "r");
    if (edgesFile == NULL) {
        perror("Error opening edges.txt");
        return 1;
    }

    char start[MAX_NAME_LENGTH], end[MAX_NAME_LENGTH];
    int weight;
    while (fscanf(edgesFile, "%s %s %d", start, end, &weight) != EOF) {
        addEdge(&g, start, end, weight);
    }
    fclose(edgesFile);

    // Display graph as a table
    printTable(&g);

    return 0;
}
