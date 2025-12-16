#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pedido {
    char nombre_destino[50];
    int cantidad_solicitada;
    struct Pedido* siguiente;
} Pedido;

typedef struct NodoAVL {
    int fecha_vencimiento;      
    char producto[50];
    int stock_total;
    int altura;
    Pedido* cabeza_pedidos;
    struct NodoAVL* izq;
    struct NodoAVL* der;
} NodoAVL;

int altura(NodoAVL* n) {
    return n ? n->altura : 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

NodoAVL* crearNodo(int fecha, char* producto, int stock) {
    NodoAVL* n = (NodoAVL*)malloc(sizeof(NodoAVL));
    n->fecha_vencimiento = fecha;
    strcpy(n->producto, producto);
    n->stock_total = stock;
    n->altura = 1;
    n->cabeza_pedidos = NULL;
    n->izq = n->der = NULL;
    return n;
}

NodoAVL* rotarDerecha(NodoAVL* y) {
    NodoAVL* x = y->izq;
    y->izq = x->der;
    x->der = y;
    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    return x;
}

NodoAVL* rotarIzquierda(NodoAVL* x) {
    NodoAVL* y = x->der;
    x->der = y->izq;
    y->izq = x;
    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    return y;
}

int balance(NodoAVL* n) {
    return n ? altura(n->izq) - altura(n->der) : 0;
}

NodoAVL* insertarAVL(NodoAVL* raiz, int fecha, char* producto, int stock) {
    if (!raiz)
        return crearNodo(fecha, producto, stock);

    if (fecha < raiz->fecha_vencimiento)
        raiz->izq = insertarAVL(raiz->izq, fecha, producto, stock);
    else if (fecha > raiz->fecha_vencimiento)
        raiz->der = insertarAVL(raiz->der, fecha, producto, stock);
    else {
        printf("ERROR: El lote ya existe.\n");
        return raiz;
    }

    raiz->altura = 1 + max(altura(raiz->izq), altura(raiz->der));
    int b = balance(raiz);

    if (b > 1 && fecha < raiz->izq->fecha_vencimiento)
        return rotarDerecha(raiz);
    if (b < -1 && fecha > raiz->der->fecha_vencimiento)
        return rotarIzquierda(raiz);

    return raiz;
}

void encolarPedido(NodoAVL* nodo, char* destino, int cantidad) {
    if (cantidad > nodo->stock_total) {
        printf("Stock insuficiente.\n");
        return;
    }

    Pedido* nuevo = (Pedido*)malloc(sizeof(Pedido));
    strcpy(nuevo->nombre_destino, destino);
    nuevo->cantidad_solicitada = cantidad;
    nuevo->siguiente = NULL;

    if (!nodo->cabeza_pedidos)
        nodo->cabeza_pedidos = nuevo;
    else {
        Pedido* aux = nodo->cabeza_pedidos;
        while (aux->siguiente)
            aux = aux->siguiente;
        aux->siguiente = nuevo;
    }

    nodo->stock_total -= cantidad;
}

void cancelarPedido(NodoAVL* nodo, char* destino, int cantidad) {
    Pedido *act = nodo->cabeza_pedidos, *ant = NULL;

    while (act) {
        if (strcmp(act->nombre_destino, destino) == 0 &&
            act->cantidad_solicitada == cantidad) {

            nodo->stock_total += cantidad;

            if (!ant)
                nodo->cabeza_pedidos = act->siguiente;
            else
                ant->siguiente = act->siguiente;

            free(act);
            printf("Pedido cancelado correctamente.\n");
            return;
        }
        ant = act;
        act = act->siguiente;
    }
    printf("Pedido no encontrado.\n");
}

int contarPedidos(Pedido* cola) {
    int c = 0;
    while (cola) {
        c++;
        cola = cola->siguiente;
    }
    return c;
}

NodoAVL* obtenerMasAntiguo(NodoAVL* raiz) {
    while (raiz && raiz->izq)
        raiz = raiz->izq;
    return raiz;
}

void liberarCola(Pedido* cola) {
    Pedido* aux;
    while (cola) {
        aux = cola;
        cola = cola->siguiente;
        free(aux);
    }
}

NodoAVL* eliminarAVL(NodoAVL* raiz, int fecha) {
    if (!raiz) return NULL;

    if (fecha < raiz->fecha_vencimiento)
        raiz->izq = eliminarAVL(raiz->izq, fecha);
    else if (fecha > raiz->fecha_vencimiento)
        raiz->der = eliminarAVL(raiz->der, fecha);
    else {
        liberarCola(raiz->cabeza_pedidos);

        if (!raiz->izq || !raiz->der) {
            NodoAVL* temp = raiz->izq ? raiz->izq : raiz->der;
            free(raiz);
            return temp;
        }

        NodoAVL* succ = obtenerMasAntiguo(raiz->der);
        raiz->fecha_vencimiento = succ->fecha_vencimiento;
        strcpy(raiz->producto, succ->producto);
        raiz->stock_total = succ->stock_total;
        raiz->cabeza_pedidos = succ->cabeza_pedidos;

        raiz->der = eliminarAVL(raiz->der, succ->fecha_vencimiento);
    }

    raiz->altura = 1 + max(altura(raiz->izq), altura(raiz->der));
    int b = balance(raiz);

    if (b > 1 && balance(raiz->izq) >= 0)
        return rotarDerecha(raiz);
    if (b < -1 && balance(raiz->der) <= 0)
        return rotarIzquierda(raiz);

    return raiz;
}

void reporteInOrden(NodoAVL* raiz) {
    if (!raiz) return;
    reporteInOrden(raiz->izq);
    printf("Fecha: %d | Producto: %s | Stock: %d | Pedidos: %d\n",
           raiz->fecha_vencimiento,
           raiz->producto,
           raiz->stock_total,
           contarPedidos(raiz->cabeza_pedidos));
    reporteInOrden(raiz->der);
}

int main() {
    NodoAVL* raiz = NULL;
    int opcion;

    do {
        printf("\n--- SISTEMA LOGISTICO ---\n");
        printf("1. Recepcion de Mercancia\n");
        printf("2. Registrar Pedido\n");
        printf("3. Cancelar Pedido\n");
        printf("4. Eliminar Lote\n");
        printf("5. Reporte de Estado\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        if (opcion == 1) {
            int fecha, stock;
            char producto[50];
            printf("Fecha (AAAAMMDD): ");
            scanf("%d", &fecha);
            printf("Producto: ");
            scanf("%s", producto);
            printf("Stock: ");
            scanf("%d", &stock);
            raiz = insertarAVL(raiz, fecha, producto, stock);
        }

        if (opcion == 2) {
            NodoAVL* nodo = obtenerMasAntiguo(raiz);
            if (nodo) {
                char destino[50];
                int cantidad;
                printf("Destino: ");
                scanf("%s", destino);
                printf("Cantidad: ");
                scanf("%d", &cantidad);
                encolarPedido(nodo, destino, cantidad);
            }
        }

        if (opcion == 3) {
            int fecha, cantidad;
            char destino[50];
            printf("Fecha del lote: ");
            scanf("%d", &fecha);
            NodoAVL* nodo = raiz;
            while (nodo && nodo->fecha_vencimiento != fecha)
                nodo = (fecha < nodo->fecha_vencimiento) ? nodo->izq : nodo->der;
            if (nodo) {
                printf("Destino: ");
                scanf("%s", destino);
                printf("Cantidad: ");
                scanf("%d", &cantidad);
                cancelarPedido(nodo, destino, cantidad);
            }
        }

        if (opcion == 4) {
            int fecha;
            printf("Fecha del lote a eliminar: ");
            scanf("%d", &fecha);
            raiz = eliminarAVL(raiz, fecha);
        }

        if (opcion == 5)
            reporteInOrden(raiz);

    } while (opcion != 0);

    return 0;
}