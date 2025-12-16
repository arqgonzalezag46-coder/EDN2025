#include <stdio.h>
#include <stdlib.h>
typedef struct Nodo {
    int dato;
    struct Nodo *sig;
} Nodo;

Nodo* insertarInicio(Nodo *inicio, int valor) {
    Nodo *nuevo = (Nodo*) malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error al asignar memoria para el nodo.\n");
        exit(1);
    }
    nuevo->dato = valor;
    nuevo->sig = inicio;
    return nuevo;
}


void liberarLista(Nodo *inicio) {
    Nodo *temp;
    while (inicio != NULL) {
        temp = inicio;
        inicio = inicio->sig;
        free(temp);
    }
}

int main() {
    
    printf("=== 1. MEMORIA DINAMICA (malloc) ===\n");
    int n;
    printf("Ingrese el tamano del arreglo: ");
    scanf("%d", &n);

    int *numeros = (int*) malloc(n * sizeof(int));
    if (numeros == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
        numeros[i] = (i + 1) * 10;

    printf("Arreglo creado con malloc:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", numeros[i]);
    printf("\n\n");

    printf("=== 2. USO DE calloc ===\n");
    int *copia = (int*) calloc(n, sizeof(int));
    if (copia == NULL) {
        printf("Error al usar calloc.\n");
        free(numeros);
        return 1;
    }

    printf("Arreglo con calloc (inicializado en 0):\n");
    for (int i = 0; i < n; i++)
        printf("%d ", copia[i]);
    printf("\n\n");

    printf("=== 3. REDIMENSIONAMIENTO (realloc) ===\n");
    int nuevoTam = n + 3;
    numeros = (int*) realloc(numeros, nuevoTam * sizeof(int));
    if (numeros == NULL) {
        printf("Error al redimensionar memoria.\n");
        free(copia);
        return 1;
    }

    for (int i = n; i < nuevoTam; i++)
        numeros[i] = (i + 1) * 100;

    printf("Arreglo redimensionado:\n");
    for (int i = 0; i < nuevoTam; i++)
        printf("%d ", numeros[i]);
    printf("\n\n");

    printf("=== 4. LIBERACION DE MEMORIA ===\n");
    free(copia);
    printf("Memoria de 'copia' liberada correctamente.\n\n");

    printf("=== 5. PUNTEROS Y ARITMETICA DE PUNTEROS ===\n");
    int arr[] = {5, 10, 15, 20, 25};
    int *p = arr;

    for (int i = 0; i < 5; i++)
        printf("Valor: %d - Direccion: %p\n", *(p + i), (p + i));

    int *p1 = &arr[0];
    int *p2 = &arr[4];
    printf("Diferencia entre p2 y p1: %ld posiciones\n\n", p2 - p1);

    printf("=== 6. LISTA ENLAZADA SIMPLE ===\n");
    Nodo *inicio = NULL;
    for (int i = 0; i < 3; i++) {
        int valor;
        printf("Ingrese el valor del nodo %d: ", i + 1);
        scanf("%d", &valor);
        inicio = insertarInicio(inicio, valor);
    }

    printf("\nLista enlazada creada:\n");
    Nodo *temp = inicio;
    while (temp != NULL) {
        printf("%d -> ", temp->dato);
        temp = temp->sig;
    }
    printf("NULL\n\n");

    printf("=== 7. EXTENSION: Insertar y liberar lista ===\n");
    inicio = insertarInicio(inicio, 99);
    printf("Nodo 99 insertado al inicio.\n");

    printf("Lista actualizada:\n");
    for (Nodo *p = inicio; p != NULL; p = p->sig)
        printf("%d -> ", p->dato);
    printf("NULL\n");

    liberarLista(inicio);
    printf("\nMemoria de la lista liberada correctamente.\n");

    free(numeros);
    printf("\n=== FIN DEL PROGRAMA ===\n");
    return 0;
}