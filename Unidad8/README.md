1️⃣ Simulador Undo/Redo (dos pilas)

- Usa dos pilas dinámicas (UNDO y REDO).

- Permite registrar acciones (cualquier texto) y luego deshacer (undo) o rehacer (redo).

- uestra el contenido actual de las pilas.

# Acciones disponibles:

1. cmd> accion
2. cmd> undo
3. cmd> redo
4. cmd> verundo
5. cmd> verredo
6. cmd> salir

2️⃣ Conversión de expresión infija → postfija (notación polaca inversa)

- Implementa el algoritmo Shunting-yard de Dijkstra.

- Soporta operadores + - * / ^ y paréntesis ().

- Convierte expresiones como:

A+B*(C-D)
a su forma postfija:
A B C D - * +

3️⃣ Evaluación de expresión postfija

- Evalúa expresiones postfijas numéricas (enteros).

- Usa una pila dinámica para almacenar operandos.

# Ejemplo:
Entrada: 2 3 4 * +
Salida: 14

4️⃣ Cola de impresora

- Simula una cola de impresión con ID autoincremental y número de páginas.

# Operaciones:

- Encolar trabajo (con número de páginas)

- Procesar el siguiente trabajo (desencolar)

- Mostrar cola actual

5️⃣ Gestión de turnos en banco (cola circular)

- Simula el sistema de atención de clientes en un banco.

- Cada cliente tiene un ID único.

- La cola se implementa de forma circular para mantener el flujo continuo de atención.

# Menú:

- Ingresar cliente

- Atender cliente

- Ver cola

6️⃣ Cola de prioridad simple

- Implementa una cola con prioridad descendente (mayor prioridad = primero en salir).

- Permite insertar un valor con su prioridad y atender el de prioridad más alta.

# Ejemplo:

Enqueue (valor=10, prioridad=5)
Enqueue (valor=3, prioridad=8)
Dequeue → (valor=3, prioridad=8)

7️⃣ Planificación Round Robin (cola circular)

- Simula la planificación de procesos Round Robin.

Cada proceso tiene:

- ID único

- Tiempo restante de ejecución (burst)

- Se ejecuta usando un quantum fijo y recorre los procesos circularmente.

# Ejemplo:

Proceso 1: burst=8
Proceso 2: burst=4
Quantum=3


# Salida esperada:

Proceso 1 ejecutado por 3, rest=5
Proceso 2 ejecutado por 3, rest=1
Proceso 1 ejecutado por 3, rest=2
...

⚙️ Estructuras dinámicas utilizadas
Módulo	Estructura usada
Undo/Redo	Pilas (LIFO)
Infija → Postfija	Pila de caracteres
Evaluación postfija	Pila numérica
Cola de impresora	Cola (FIFO)
Turnos banco	Cola circular
Cola de prioridad	Cola enlazada con orden
Round Robin	Cola circular de procesos
🧩 Compilación y ejecución
Compilar:
gcc unidad8_ejercicios.c -o unidad8_ejercicios

# Ejecutar:
./unidad8_ejercicios

📜 Menú principal

Al ejecutar el programa, se muestra el menú:

==== MENU PRINCIPAL - EJERCICIOS 8.5 ====
1. Simulador Undo/Redo
2. Infija -> Postfija (RPN)
3. Evaluacion Postfija (numeros)
4. Cola de impresora (jobs)
5. Gestion turnos banco (cola circular)
6. Cola de prioridad simple
7. Planificacion Round Robin
0. Salir

🧼 Liberación de memoria

- Cada módulo libera sus estructuras dinámicas antes de salir del programa:

- Pilas (free)

- Colas (free)

- Listas circulares (free)

- Reasignación de contadores (IDs, procesos, trabajos)