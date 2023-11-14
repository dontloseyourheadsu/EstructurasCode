#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Definición de la estructura MinHeap que representa un heap mínimo.
typedef struct {
    int arr[MAX_SIZE]; // Un arreglo de enteros para almacenar los elementos del heap.
    int size; // El tamaño actual del heap.
} MinHeap;

// Función para inicializar un heap mínimo. Establece el tamaño en 0.
void init(MinHeap* h) {
    h->size = 0;
}

// Función para verificar si el heap está vacío.
int isEmpty(MinHeap* h) {
    return h->size == 0;
}

// Función para obtener el tamaño actual del heap.
int getSize(MinHeap* h) {
    return h->size;
}

// Función para realizar la rotación hacia arriba.
void moveUp(MinHeap* h, int index) {
    int parentIndex, tmp;
    if (index != 0) {
        parentIndex = (index - 1) / 2;
        if (h->arr[parentIndex] > h->arr[index]) {
            // Si el valor del padre es mayor que el valor actual, se intercambian.
            tmp = h->arr[parentIndex];
            h->arr[parentIndex] = h->arr[index];
            h->arr[index] = tmp;
            // Luego, se realiza la rotación hacia arriba en el padre recursivamente.
            moveUp(h, parentIndex);
        }
    }
}

// Función para insertar un elemento en el heap.
void insert(MinHeap* h, int value) {
    if (h->size == MAX_SIZE) {
        printf("\nHeap is full\n"); // Si el heap está lleno, muestra un mensaje y no hace nada.
        return;
    }
    h->arr[h->size] = value; // Agrega el valor al final del heap.
    moveUp(h, h->size); // Realiza la rotación hacia arriba para mantener la propiedad del heap mínimo.
    h->size++; // Aumenta el tamaño del heap.
}

// Función para realizar la rotación hacia abajo.
void moveDown(MinHeap* h, int index) {
    int leftChildIndex, rightChildIndex, minIndex, tmp;
    leftChildIndex = 2 * index + 1;
    rightChildIndex = 2 * index + 2;
    if (rightChildIndex >= h->size) {
        if (leftChildIndex >= h->size)
            return;
        else
            minIndex = leftChildIndex;
    } else {
        if (h->arr[leftChildIndex] <= h->arr[rightChildIndex])
            minIndex = leftChildIndex;
        else
            minIndex = rightChildIndex;
    }
    if (h->arr[index] > h->arr[minIndex]) {
        // Si el valor actual es mayor que el valor mínimo de los hijos, se intercambian.
        tmp = h->arr[minIndex];
        h->arr[minIndex] = h->arr[index];
        h->arr[index] = tmp;
        // Luego, se realiza la rotación hacia abajo en el hijo mínimo recursivamente.
        moveDown(h, minIndex);
    }
}

// Función para eliminar y devolver el elemento mínimo del heap.
int removeMin(MinHeap* h) {
    int result;
    if (isEmpty(h)) {
        printf("\nHeap is empty\n"); // Si el heap está vacío, muestra un mensaje y retorna -1.
        return -1;
    }
    result = h->arr[0]; // El valor mínimo está en la raíz del heap.
    h->arr[0] = h->arr[h->size - 1]; // Se reemplaza la raíz con el último elemento del heap.
    h->size--; // Disminuye el tamaño del heap.
    moveDown(h, 0); // Realiza la rotación hacia abajo para mantener la propiedad del heap mínimo.
    return result; // Devuelve el valor mínimo.
}

// Función para imprimir el contenido del heap.
void printHeap(MinHeap* h) {
    int i;
    printf("\n");
    for (i = 0; i < h->size; i++)
        printf("%d ", h->arr[i]);
    printf("\n");
}

int main() {
    MinHeap h;
    init(&h); // Inicializa el heap vacío.
    insert(&h, 9); // Inserta elementos en el heap.
    insert(&h, 8);
    insert(&h, 7);
    insert(&h, 6);
    insert(&h, 5);
    insert(&h, 4);
    insert(&h, 3);
    insert(&h, 2);
    insert(&h, 1);
    printHeap(&h); // Imprime el contenido del heap.
    removeMin(&h); // Elimina el elemento mínimo del heap.
    printHeap(&h); // Imprime el contenido del heap después de la eliminación.
    return 0;
}
