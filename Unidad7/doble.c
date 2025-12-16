#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Pasajero {
    char genero[20];
    char apellido[30];
    struct Pasajero *sig;
    struct Pasajero *ant;
} Pasajero;

Pasajero *inicio = NULL;
Pasajero *abordados = NULL;
Pasajero *noAbordados = NULL;

int capacidadMax = 0;
int capacidadTotal = 0;
int vendidos = 0;
int abordajeIniciado = 0;

Pasajero* crearPasajero(char *genero, char *apellido) {
    Pasajero *nuevo = (Pasajero*) malloc(sizeof(Pasajero));
    strcpy(nuevo->genero, genero);
    strcpy(nuevo->apellido, apellido);
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    return nuevo;
}

void venderTiquete() {
    if (abordajeIniciado) {
        printf("\nNo se pueden vender tiquetes despues de iniciar el abordaje.\n");
        return;
    }

    if (vendidos >= capacidadTotal) {
        printf("\nNo se pueden vender mas tiquetes (limite de sobreventa alcanzado).\n");
        return;
    }

    char genero[20], apellido[30];
    printf("Ingrese genero (Femenino, Masculino, No_Binario): ");
    scanf("%s", genero);
    printf("Ingrese primer apellido: ");
    scanf("%s", apellido);

    Pasajero *nuevo = crearPasajero(genero, apellido);

    if (inicio == NULL) {
        inicio = nuevo;
    } else {
        Pasajero *temp = inicio;
        while (temp->sig != NULL)
            temp = temp->sig;
        temp->sig = nuevo;
        nuevo->ant = temp;
    }

    vendidos++;
    printf("Tiquete vendido exitosamente a %s %s.\n", genero, apellido);
}

void establecerCapacidad() {
    if (capacidadMax > 0) {
        printf("La capacidad ya fue establecida.\n");
        return;
    }

    printf("Ingrese la capacidad maxima del avion: ");
    scanf("%d", &capacidadMax);
    capacidadTotal = capacidadMax + (int)(capacidadMax * 0.1);
    printf("Capacidad establecida: %d pasajeros (+10%% sobreventa = %d tiquetes maximos)\n",
           capacidadMax, capacidadTotal);
}

void iniciarAbordaje() {
    if (abordajeIniciado) {
        printf("El abordaje ya ha sido iniciado.\n");
        return;
    }

    if (inicio == NULL) {
        printf("No hay pasajeros registrados.\n");
        return;
    }

    abordajeIniciado = 1;
    printf("\n=== PROCESO DE ABORDAJE ===\n");
    int count = 0;
    Pasajero *temp = inicio;

    while (temp != NULL) {
        Pasajero *siguiente = temp->sig;

        if (count < capacidadMax) {
            temp->sig = abordados;
            if (abordados != NULL) abordados->ant = temp;
            abordados = temp;
            temp->ant = NULL;
            count++;
        } else {
            temp->sig = noAbordados;
            if (noAbordados != NULL) noAbordados->ant = temp;
            noAbordados = temp;
            temp->ant = NULL;
        }

        temp = siguiente;
    }

    inicio = NULL;
    printf("Abordaje completado. %d pasajeros abordaron, %d no pudieron.\n",
           count, vendidos - count);
}

void mostrarLista(Pasajero *lista, char *titulo) {
    printf("\n=== %s ===\n", titulo);
    if (lista == NULL) {
        printf("No hay pasajeros.\n");
        return;
    }

    Pasajero *temp = lista;
    int i = 1;
    while (temp != NULL) {
        printf("%d. %s - %s\n", i++, temp->genero, temp->apellido);
        temp = temp->sig;
    }
}

void liberar(Pasajero *lista) {
    Pasajero *temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->sig;
        free(temp);
    }
}

int main() {
    int opcion;
    do {
        printf("\n===== MENU PRINCIPAL (LISTA DOBLE) =====\n");
        printf("1. Establecer capacidad\n");
        printf("2. Vender tiquete\n");
        printf("3. Iniciar abordaje\n");
        printf("4. Ver abordados\n");
        printf("5. Ver no abordados\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: establecerCapacidad(); break;
            case 2: venderTiquete(); break;
            case 3: iniciarAbordaje(); break;
            case 4: mostrarLista(abordados, "PASAJEROS ABORDADOS"); break;
            case 5: mostrarLista(noAbordados, "PASAJEROS NO ABORDADOS"); break;
            case 6:
                printf("Saliendo del programa...\n");
                liberar(inicio);
                liberar(abordados);
                liberar(noAbordados);
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 6);

    return 0;
}