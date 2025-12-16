#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

char *leerLinea(const char *prompt) {
    printf("%s", prompt);
    char buf[512];
    if (fgets(buf, sizeof(buf), stdin) == NULL) return NULL;
    size_t len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';
    char *res = (char*) malloc(strlen(buf)+1);
    strcpy(res, buf);
    return res;
}

typedef struct NodoStr {
    char *dato;
    struct NodoStr *sig;
} NodoStr;

NodoStr* pushStr(NodoStr *tope, const char *txt) {
    NodoStr *nuevo = (NodoStr*) malloc(sizeof(NodoStr));
    nuevo->dato = (char*) malloc(strlen(txt)+1);
    strcpy(nuevo->dato, txt);
    nuevo->sig = tope;
    return nuevo;
}

NodoStr* popStr(NodoStr *tope, char **out) {
    if (tope == NULL) { *out = NULL; return NULL; }
    NodoStr *temp = tope;
    *out = tope->dato;
    tope = tope->sig;
    free(temp);
    return tope;
}

void mostrarPilaStr(NodoStr *tope) {
    NodoStr *t = tope;
    int i = 1;
    if (t == NULL) { printf("  (vacia)\n"); return; }
    while (t) {
        printf("  %d) %s\n", i++, t->dato);
        t = t->sig;
    }
}

void liberarPilaStr(NodoStr *tope) {
    while (tope) {
        NodoStr *tmp = tope;
        tope = tope->sig;
        free(tmp->dato);
        free(tmp);
    }
}

void moduloUndoRedo() {
    NodoStr *undo = NULL;
    NodoStr *redo = NULL;
    char opcion[8];

    printf("\n--- SIMULADOR UNDO/REDO ---\n");
    printf("Comandos: 'accion' para registrar, 'undo', 'redo', 'verundo', 'verredo', 'salir'\n");

    while (1) {
        char *linea = leerLinea("cmd> ");
        if (!linea) break;

        if (strcmp(linea, "salir") == 0) {
            free(linea);
            break;
        } else if (strcmp(linea, "undo") == 0) {
            char *acc = NULL;
            undo = popStr(undo, &acc);
            if (acc == NULL) {
                printf("No hay acciones para deshacer.\n");
            } else {
                redo = pushStr(redo, acc);
                printf("Deshecho: %s\n", acc);
                free(acc); 
            }
        } else if (strcmp(linea, "redo") == 0) {
            char *acc = NULL;
            redo = popStr(redo, &acc);
            if (acc == NULL) {
                printf("No hay acciones para rehacer.\n");
            } else {
                undo = pushStr(undo, acc);
                printf("Rehecho: %s\n", acc);
                free(acc);
            }
        } else if (strcmp(linea, "verundo") == 0) {
            printf("Pila UNDO:\n"); mostrarPilaStr(undo);
        } else if (strcmp(linea, "verredo") == 0) {
            printf("Pila REDO:\n"); mostrarPilaStr(redo);
        } else {
            
            if (strlen(linea) > 0) {
                undo = pushStr(undo, linea);
               
                liberarPilaStr(redo);
                redo = NULL;
                printf("Accion registrada: %s\n", linea);
            }
        }
        free(linea);
    }

    liberarPilaStr(undo);
    liberarPilaStr(redo);
    printf("--- Fin modulo Undo/Redo ---\n");
}


int prioridadOp(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int esOperador(char c) {
    return c=='+' || c=='-' || c=='*' || c=='/' || c=='^';
}

typedef struct NodoCh {
    char c;
    struct NodoCh *sig;
} NodoCh;

NodoCh* pushCh(NodoCh *top, char c) {
    NodoCh *n = (NodoCh*) malloc(sizeof(NodoCh));
    n->c = c; n->sig = top; return n;
}

NodoCh* popCh(NodoCh *top, char *out) {
    if (!top) { *out = 0; return NULL; }
    NodoCh *t = top; *out = t->c; top = t->sig; free(t); return top;
}


void infijaToPostfija() {
    char *expr = leerLinea("Ingresa expresion infija (ej: A+B*(C-D)) : ");
    if (!expr) return;
    NodoCh *ops = NULL;
    char salida[2048] = {0};
    int pos = 0;

    for (int i = 0; expr[i] != '\0'; ++i) {
        char c = expr[i];
        if (isspace((unsigned char)c)) continue;
        if (isalnum((unsigned char)c)) {
            salida[pos++] = c;
            salida[pos++] = ' ';
        } else if (c == '(') {
            ops = pushCh(ops, c);
        } else if (c == ')') {
            char topc;
            while (ops) {
                ops = popCh(ops, &topc);
                if (topc == '(') break;
                salida[pos++] = topc; salida[pos++] = ' ';
            }
        } else if (esOperador(c)) {
            char topc = 0;
            while (ops) {
                topc = ops->c;
                if (esOperador(topc) && ((prioridadOp(topc) > prioridadOp(c)) || (prioridadOp(topc) == prioridadOp(c) && c != '^'))) {
                    ops = popCh(ops, &topc);
                    salida[pos++] = topc; salida[pos++] = ' ';
                } else break;
            }
            ops = pushCh(ops, c);
        } else {
           
        }
    }

    char topc;
    while (ops) { ops = popCh(ops, &topc); if (topc!='(') { salida[pos++] = topc; salida[pos++] = ' '; } }

    salida[pos] = '\0';
    printf("Postfija: %s\n", salida);
    free(expr);
}



typedef struct NodoNum {
    long val;
    struct NodoNum *sig;
} NodoNum;

NodoNum* pushNum(NodoNum *top, long v) {
    NodoNum *n = (NodoNum*) malloc(sizeof(NodoNum));
    n->val = v; n->sig = top; return n;
}

NodoNum* popNum(NodoNum *top, long *out) {
    if (!top) { *out = 0; return NULL; }
    NodoNum *t = top; *out = t->val; top = t->sig; free(t); return top;
}

void evalPostfija() {
    char *expr = leerLinea("Ingresa expresion postfija (numeros enteros separados por espacio, ej: '2 3 4 * +'):\n> ");
    if (!expr) return;
    NodoNum *stk = NULL;
    char *token = strtok(expr, " ");
    while (token) {
        if (isdigit((unsigned char)token[0]) || (token[0]=='-' && isdigit((unsigned char)token[1]))) {
            long num = atol(token);
            stk = pushNum(stk, num);
        } else if (strlen(token) == 1 && strchr("+-*/^", token[0])) {
            long b, a;
            stk = popNum(stk, &b);
            stk = popNum(stk, &a);
            long r = 0;
            char op = token[0];
            if (op == '+') r = a + b;
            else if (op == '-') r = a - b;
            else if (op == '*') r = a * b;
            else if (op == '/') r = (b != 0) ? a / b : 0;
            else if (op == '^') {
                r = 1;
                for (int i = 0; i < b; ++i) r *= a;
            }
            stk = pushNum(stk, r);
        } else {
            printf("Token ignorado: %s\n", token);
        }
        token = strtok(NULL, " ");
    }
    long resultado = 0;
    stk = popNum(stk, &resultado);
    printf("Resultado: %ld\n", resultado);
   
    while (stk) { long tmp; stk = popNum(stk, &tmp); }
    free(expr);
}


typedef struct Job {
    int id;
    int paginas;
    struct Job *sig;
} Job;

Job *cabPrinter = NULL;
Job *ultPrinter = NULL;
int nextJobID = 1;

void enqueuePrinter(int paginas) {
    Job *j = (Job*) malloc(sizeof(Job));
    j->id = nextJobID++;
    j->paginas = paginas;
    j->sig = NULL;
    if (cabPrinter == NULL) {
        cabPrinter = ultPrinter = j;
    } else {
        ultPrinter->sig = j;
        ultPrinter = j;
    }
    printf("Trabajo agregado: ID=%d, paginas=%d\n", j->id, j->paginas);
}

void processPrinter() {
    if (cabPrinter == NULL) { printf("No hay trabajos.\n"); return; }
    Job *t = cabPrinter;
    cabPrinter = cabPrinter->sig;
    if (cabPrinter == NULL) ultPrinter = NULL;
    printf("Procesando ID=%d, paginas=%d ... (simulado)\n", t->id, t->paginas);
    free(t);
}

void showPrinterQueue() {
    if (cabPrinter == NULL) { printf("Cola vacia.\n"); return; }
    Job *t = cabPrinter;
    printf("Cola de impresora:\n");
    while (t) { printf("  ID=%d paginas=%d\n", t->id, t->paginas); t = t->sig; }
}

void clearPrinter() {
    while (cabPrinter) { Job *t = cabPrinter; cabPrinter = cabPrinter->sig; free(t); }
    ultPrinter = NULL;
    nextJobID = 1;
}


typedef struct Cliente {
    int id;
    struct Cliente *sig;
} Cliente;

Cliente *frenteBanco = NULL;
Cliente *finalBanco = NULL;
int nextClienteID = 1;

void ingresarCliente() {
    Cliente *n = (Cliente*) malloc(sizeof(Cliente));
    n->id = nextClienteID++;
    if (frenteBanco == NULL) {
        n->sig = n;
        frenteBanco = finalBanco = n;
    } else {
        n->sig = frenteBanco;
        finalBanco->sig = n;
        finalBanco = n;
    }
    printf("Cliente ingresado ID=%d\n", n->id);
}

void atenderCliente() {
    if (frenteBanco == NULL) { printf("No hay clientes.\n"); return; }
    Cliente *t = frenteBanco;
    printf("Atendiendo cliente ID=%d\n", t->id);
    if (frenteBanco == finalBanco) {
        free(t); frenteBanco = finalBanco = NULL;
    } else {
        frenteBanco = frenteBanco->sig;
        finalBanco->sig = frenteBanco;
        free(t);
    }
}

void mostrarBanco() {
    if (frenteBanco == NULL) { printf("No hay clientes.\n"); return; }
    Cliente *t = frenteBanco;
    printf("Cola circular (banco): ");
    do {
        printf("%d -> ", t->id);
        t = t->sig;
    } while (t != frenteBanco);
    printf("(inicio)\n");
}

void clearBanco() {
    while (frenteBanco) {
        if (frenteBanco == finalBanco) { free(frenteBanco); frenteBanco = finalBanco = NULL; break; }
        Cliente *tmp = frenteBanco->sig;
        free(frenteBanco);
        frenteBanco = tmp;
        finalBanco->sig = frenteBanco;
    }
    nextClienteID = 1;
}


typedef struct NodoPrio {
    int valor;     
    int prioridad;  
    struct NodoPrio *sig;
} NodoPrio;

NodoPrio *cabPrio = NULL;

void enqueuePrio(int val, int pr) {
    NodoPrio *nuevo = (NodoPrio*) malloc(sizeof(NodoPrio));
    nuevo->valor = val; nuevo->prioridad = pr; nuevo->sig = NULL;
    if (!cabPrio || pr > cabPrio->prioridad) {
        nuevo->sig = cabPrio;
        cabPrio = nuevo;
        return;
    }
    NodoPrio *t = cabPrio;
    while (t->sig && t->sig->prioridad >= pr) t = t->sig;
    nuevo->sig = t->sig;
    t->sig = nuevo;
}

void dequeuePrio() {
    if (!cabPrio) { printf("Cola de prioridad vacia.\n"); return; }
    NodoPrio *t = cabPrio;
    cabPrio = cabPrio->sig;
    printf("Retirado valor=%d prioridad=%d\n", t->valor, t->prioridad);
    free(t);
}

void mostrarPrio() {
    if (!cabPrio) { printf("Cola de prioridad vacia.\n"); return; }
    NodoPrio *t = cabPrio;
    printf("Cola prioridad:\n");
    while (t) { printf("  valor=%d prio=%d\n", t->valor, t->prioridad); t = t->sig; }
}

void clearPrio() {
    while (cabPrio) { NodoPrio *t = cabPrio; cabPrio = cabPrio->sig; free(t); }
}



typedef struct Proc {
    int id;
    int tiempo_rest;
    struct Proc *sig;
} Proc;

Proc *frenteRR = NULL;
Proc *finalRR = NULL;
int nextProcID = 1;

void enqueueRR(int burst) {
    Proc *p = (Proc*) malloc(sizeof(Proc));
    p->id = nextProcID++;
    p->tiempo_rest = burst;
    if (!frenteRR) { p->sig = p; frenteRR = finalRR = p; }
    else { p->sig = frenteRR; finalRR->sig = p; finalRR = p; }
    printf("Proceso agregado ID=%d burst=%d\n", p->id, burst);
}

void ejecutarRoundRobin() {
    if (!frenteRR) { printf("No hay procesos.\n"); return; }
    int quantum;
    printf("Ingrese quantum: ");
    if (scanf("%d", &quantum) != 1) { limpiarBuffer(); printf("Entrada invalida.\n"); return; }
    limpiarBuffer();
    printf("--- Ejecucion Round Robin (quantum=%d) ---\n", quantum);

    while (frenteRR) {
        Proc *p = frenteRR;
        
        if (p->tiempo_rest <= quantum) {
            printf("Proceso %d finaliza (restante=%d <= q).\n", p->id, p->tiempo_rest);
            
            if (frenteRR == finalRR) { free(p); frenteRR = finalRR = NULL; }
            else {
                Proc *tmp = frenteRR;
                frenteRR = frenteRR->sig;
                finalRR->sig = frenteRR;
                free(tmp);
            }
        } else {
            p->tiempo_rest -= quantum;
            printf("Proceso %d ejecutado por %d. restante=%d. se mueve al final.\n", p->id, quantum, p->tiempo_rest);
            
            frenteRR = frenteRR->sig;
            finalRR = finalRR->sig;
        }
    }
    nextProcID = 1;
    printf("--- Fin Round Robin ---\n");
}

void mostrarRR() {
    if (!frenteRR) { printf("No hay procesos.\n"); return; }
    Proc *t = frenteRR;
    printf("Cola procesos (id:restante): ");
    do {
        printf("%d:%d -> ", t->id, t->tiempo_rest);
        t = t->sig;
    } while (t != frenteRR);
    printf("(inicio)\n");
}

void clearRR() {
    if (!frenteRR) return;
    while (frenteRR) {
        if (frenteRR == finalRR) { free(frenteRR); frenteRR = finalRR = NULL; break; }
        Proc *tmp = frenteRR->sig;
        free(frenteRR);
        frenteRR = tmp;
        finalRR->sig = frenteRR;
    }
    nextProcID = 1;
}



void menuUndoRedo() {
    moduloUndoRedo();
}

void menuInfijaPostfija() {
    infijaToPostfija();
}

void menuEvalPostfija() {
    evalPostfija();
}

void menuPrinter() {
    int op;
    do {
        printf("\n--- Cola de impresora ---\n");
        printf("1. Enviar trabajo\n2. Procesar trabajo\n3. Ver cola\n4. Volver\nElige: ");
        if (scanf("%d", &op) != 1) { limpiarBuffer(); break; }
        limpiarBuffer();
        if (op == 1) {
            int pag;
            printf("Paginas: ");
            if (scanf("%d", &pag) != 1) { limpiarBuffer(); printf("Entrada invalida.\n"); continue; }
            limpiarBuffer();
            enqueuePrinter(pag);
        } else if (op == 2) {
            processPrinter();
        } else if (op == 3) {
            showPrinterQueue();
        }
    } while (op != 4);
}

void menuBanco() {
    int op;
    do {
        printf("\n--- Gestion turnos banco (cola circular) ---\n");
        printf("1. Ingresar cliente\n2. Atender cliente\n3. Ver cola\n4. Volver\nElige: ");
        if (scanf("%d", &op) != 1) { limpiarBuffer(); break; }
        limpiarBuffer();
        if (op == 1) ingresarCliente();
        else if (op == 2) atenderCliente();
        else if (op == 3) mostrarBanco();
    } while (op != 4);
}

void menuPrio() {
    int op;
    do {
        printf("\n--- Cola de prioridad simple ---\n");
        printf("1. Enqueue (valor, prioridad)\n2. Dequeue (retirar mayor prioridad)\n3. Ver cola\n4. Volver\nElige: ");
        if (scanf("%d", &op) != 1) { limpiarBuffer(); break; }
        limpiarBuffer();
        if (op == 1) {
            int v,p; printf("Valor: "); if (scanf("%d",&v)!=1){ limpiarBuffer(); continue;} printf("Prioridad: "); if (scanf("%d",&p)!=1){ limpiarBuffer(); continue;}
            limpiarBuffer();
            enqueuePrio(v,p);
        } else if (op == 2) {
            dequeuePrio();
        } else if (op == 3) {
            mostrarPrio();
        }
    } while (op != 4);
}

void menuRR() {
    int op;
    do {
        printf("\n--- Round Robin ---\n");
        printf("1. Agregar proceso (burst)\n2. Ejecutar Round Robin\n3. Ver cola procesos\n4. Volver\nElige: ");
        if (scanf("%d",&op)!=1){ limpiarBuffer(); break; }
        limpiarBuffer();
        if (op == 1) {
            int b; printf("Burst (tiempo): "); if (scanf("%d",&b)!=1){ limpiarBuffer(); continue; } limpiarBuffer();
            enqueueRR(b);
        } else if (op == 2) {
            ejecutarRoundRobin();
        } else if (op == 3) {
            mostrarRR();
        }
    } while (op != 4);
}

int main() {
    int opcion = -1;
    while (1) {
        printf("\n==== MENU PRINCIPAL - EJERCICIOS 8.5 ====\n");
        printf("1. Simulador Undo/Redo\n");
        printf("2. Infija -> Postfija (RPN)\n");
        printf("3. Evaluacion Postfija (numeros)\n");
        printf("4. Cola de impresora (jobs)\n");
        printf("5. Gestion turnos banco (cola circular)\n");
        printf("6. Cola de prioridad simple\n");
        printf("7. Planificacion Round Robin\n");
        printf("0. Salir\n");
        printf("Elige una opcion: ");
        if (scanf("%d", &opcion) != 1) { limpiarBuffer(); break; }
        limpiarBuffer();
        if (opcion == 0) break;
        switch (opcion) {
            case 1: menuUndoRedo(); break;
            case 2: menuInfijaPostfija(); break;
            case 3: menuEvalPostfija(); break;
            case 4: menuPrinter(); break;
            case 5: menuBanco(); break;
            case 6: menuPrio(); break;
            case 7: menuRR(); break;
            default: printf("Opcion invalida.\n");
        }
    }

    liberarPilaStr(NULL);
    clearPrinter();
    clearBanco();
    clearPrio();
    clearRR();
    printf("Saliendo. Recursos liberados.\n");
    return 0;
}