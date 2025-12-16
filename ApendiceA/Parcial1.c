#include <stdio.h>
#define MAX 5

typedef struct {
    int codigo;
    float nota;
} Estudiante;

Estudiante estudiantes[MAX] = {
    {2024105, 4.0},
    {2024102, 3.2},
    {2024104, 5.0},
    {2024101, 4.5},
    {2024103, 2.8}
};

void mostrarEstudiantes(Estudiante arr[MAX], int n) {
    for (int i = 0; i < n; i++) {
        printf("Codigo: %d | Nota: %.2f\n", arr[i].codigo, arr[i].nota);
    }
}

float notaMaxima(Estudiante arr[MAX], int i, int n) {
    if (i == n - 1) {
        return arr[i].nota;
    }
    float maxResto = notaMaxima(arr, i + 1, n);
    return (arr[i].nota > maxResto) ? arr[i].nota : maxResto;
}

float sumaNotas(Estudiante arr[MAX], int i, int n) {
    if (i == n) {
        return 0;
    }
    return arr[i].nota + sumaNotas(arr, i + 1, n);
}

float promedio(Estudiante arr[MAX], int n) {
    return sumaNotas(arr, 0, n) / n;
}

void selectionSort(Estudiante arr[MAX], int inicio, int n) {
    if (inicio >= n - 1) {
        return;
    }
    int minIndex = inicio;
    for (int j = inicio + 1; j < n; j++) {
        if (arr[j].codigo < arr[minIndex].codigo) {
            minIndex = j;
        }
    }

    if (minIndex != inicio) {
        Estudiante temp = arr[inicio];
        arr[inicio] = arr[minIndex];
        arr[minIndex] = temp;
    }

    selectionSort(arr, inicio + 1, n);
}

int main() {
    int opc;
    do {
        printf("\n==== MENU ====\n");
        printf("1. Mostrar estudiantes\n");
        printf("2. Buscar la nota maxima (recursivo)\n");
        printf("3. Calcular el promedio (recursivo)\n");
        printf("4. Ordenar estudiantes por codigo (Selection Sort Recursivo)\n");
        printf("5. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                mostrarEstudiantes(estudiantes, MAX);
                break;
            case 2:
                printf("La nota maxima es: %.2f\n", notaMaxima(estudiantes, 0, MAX));
                break;
            case 3:
                printf("El promedio del curso es: %.2f\n", promedio(estudiantes, MAX));
                break;
            case 4:
                selectionSort(estudiantes, 0, MAX);
                printf("Lista ordenada:\n");
                mostrarEstudiantes(estudiantes, MAX);
                break;
            case 5:
                printf("Gracias por usar el programa.\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opc != 5);

    return 0;
}
