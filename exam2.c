#include <stdio.h>
#include <stdlib.h>

// Estructura para representar un nodo en la lista de adyacencia
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// Estructura para representar una lista de adyacencia
struct AdjList {
    struct AdjListNode *head;
};

// Estructura para representar un grafo. Un grafo es un array de listas de adyacencia.
struct Graph {
    int V;
    struct AdjList* array;
};

// Estructura para representar un nodo de la cola
struct QueueNode {
    int data;
    struct QueueNode* next;
};

// Estructura para representar una cola
struct Queue {
    struct QueueNode *front, *rear;
};

// Funciones para el grafo
struct AdjListNode* newAdjListNode(int dest);
struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int dest);

// Funciones para la cola
struct QueueNode* newQueueNode(int k);
struct Queue* createQueue();
void enQueue(struct Queue* q, int k);
int deQueue(struct Queue* q);

// Función para el BFS
void BFS(struct Graph* graph, int startVertex);

// Función para imprimir el grafo
void printGraph(struct Graph* graph);

int main() {
    // Se crea un grafo con 6 vértices
    struct Graph* graph = createGraph(6);
    // Se agregan las aristas
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);
    // Se imprime el grafo
    printGraph(graph);
    // Se realiza el BFS
    BFS(graph, 0);
    return 0;
}

// Función para crear un nuevo nodo de lista de adyacencia
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Función para crear un grafo con V vértices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    // Se crea un array de listas de adyacencia. El tamaño del array será V.
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
    // Se inicializan las listas de adyacencia como vacías.
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Función para agregar una arista al grafo no dirigido
void addEdge(struct Graph* graph, int src, int dest) {
    // Se agrega una arista de src a dest. Se agrega un nuevo nodo a la lista de adyacencia de src. El nodo se agrega al principio.
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    // Dado que el grafo es no dirigido, se agrega una arista de dest a src también
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Función para crear un nuevo nodo de cola
struct QueueNode* newQueueNode(int k) {
    struct QueueNode* temp = (struct QueueNode*) malloc(sizeof(struct QueueNode));
    temp->data = k;
    temp->next = NULL;
    return temp;
}

// Función para crear una cola vacía
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*) malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// Función para agregar un elemento a la cola
void enQueue(struct Queue* q, int k) {
    // Se crea un nuevo nodo
    struct QueueNode* temp = newQueueNode(k);
    // Si la cola está vacía, el nodo insertado es el frente y el rear
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    // El nuevo nodo se agrega al final de la cola y se cambia el rear
    q->rear->next = temp;
    q->rear = temp;
}

// Función para eliminar un elemento de la cola
int deQueue(struct Queue* q) {
    // Si la cola está vacía, se retorna -1
    if (q->front == NULL)
        return -1;
    // Se guarda el valor del frente y se cambia el frente
    struct QueueNode* temp = q->front;
    q->front = q->front->next;
    // Si el frente se vuelve NULL, el rear también se vuelve NULL
    if (q->front == NULL)
        q->rear = NULL;
    return temp->data;
}

// Función para realizar el BFS
void BFS(struct Graph* graph, int startVertex) {
    // Se crea una cola para el BFS
    struct Queue* q = createQueue();
    // Se marca el vértice actual como visitado y se encola
    int visited[graph->V];
    int i;
    for (i = 0; i < graph->V; i++)
        visited[i] = 0;
    visited[startVertex] = 1;
    enQueue(q, startVertex);
    // Se itera mientras la cola no esté vacía
    while (q->front != NULL) {
        // Se desencola un vértice de la cola y se imprime
        int currentVertex = deQueue(q);
        printf("%d ", currentVertex);
        // Se obtienen todos los vértices adyacentes al vértice actual. Si un vértice adyacente no ha sido visitado, se marca como visitado y se encola.
        struct AdjListNode* temp = graph->array[currentVertex].head;
        while (temp != NULL) {
            int adjVertex = temp->dest;
            if (visited[adjVertex] == 0) {
                visited[adjVertex] = 1;
                enQueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
}

// Función para imprimir el grafo
void printGraph(struct Graph* graph) {
    int v;
    for (v = 0; v < graph->V; ++v) {
        struct AdjListNode* temp = graph->array[v].head;
        printf("\n Lista de adyacencia del vértice %d\n head ", v);
        while (temp) {
            printf("-> %d", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}