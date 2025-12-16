# 🚢 UNIVERSIDAD DEL PACÍFICO  
## 📚 Curso: Estructura de Datos  
## 🧠 Proyecto Final: Sistema Logístico en Lenguaje C  

---

## 👥 Integrantes del Proyecto
- **Wilner Andrés González González**  
- **Karen Lizeth González González**  
- **Yenny Paola Bravo Paredes**  

---

## 🎯 1. Introducción

El presente proyecto desarrolla un **Sistema Logístico en lenguaje C** orientado a la gestión de alimentos perecederos en el **Puerto de Distribución de Alimentos de Buenaventura**.  
El sistema soluciona el problema del **desperdicio de alimentos**, ocasionado por la falta de control sobre los lotes próximos a vencer, mediante el uso de **estructuras de datos avanzadas**.

Se prioriza el despacho de los productos según su **fecha de vencimiento**, garantizando una distribución eficiente hacia poblaciones como **Guapi, Timbiquí, Nuquí y Bahía Solano**.

---

## 🧩 2. Objetivos del Proyecto

### 🎯 Objetivo General
Desarrollar un sistema en C que permita gestionar inventarios perecederos, priorizando su despacho por fecha de vencimiento mediante el uso de árboles AVL y colas FIFO.

### 🎯 Objetivos Específicos
- Implementar un Árbol ABB con balanceo AVL.
- Gestionar pedidos de despacho mediante colas FIFO.
- Garantizar cero fugas de memoria.
- Facilitar la eliminación y cancelación de datos.
- Mostrar reportes ordenados del inventario.

---

## 🏗️ 3. Arquitectura del Sistema

El sistema utiliza una **memoria híbrida**, conformada por:

| Componente | Función |
|----------|--------|
| 🌳 Árbol AVL | Organiza los productos por fecha de vencimiento |
| 📥 Cola FIFO | Gestiona los pedidos de cada lote |
| 🔗 Punteros | Enlazan correctamente las estructuras |
| 🧮 Balanceo | Mantiene eficiencia en las operaciones |

---

## 🌳 4. Árbol ABB con Balanceo AVL

### 📅 Clave del Árbol
- Fecha de vencimiento en formato entero **AAAAMMDD**
- Ejemplo: `20251204`

### 🔁 Lógica de Ordenamiento
- ⬅️ Izquierda: fechas más antiguas (mayor prioridad)
- ➡️ Derecha: fechas futuras (productos más frescos)

### 🧱 Estructura del Nodo AVL
Cada nodo contiene:
- 📅 `fecha_vencimiento`
- 🏷️ `producto`
- 📦 `stock_total`
- 📏 `altura`
- 📥 `cabeza_pedidos`
- 🌲 `izq` y `der`

El árbol se **rebalancea automáticamente** tras cada inserción o eliminación utilizando **rotaciones AVL**.

---

## 📥 5. Cola FIFO de Pedidos

Cada nodo del árbol posee una cola FIFO que gestiona los pedidos asociados a ese lote.

### 📦 Estructura del Pedido
- 🌍 Nombre del destino
- 🔢 Cantidad solicitada
- ➡️ Puntero al siguiente pedido

### 🔄 Principio FIFO
El primer pedido que entra es el primero en ser atendido, asegurando un despacho justo y ordenado.

---

## ⚙️ 6. Funcionalidades del Sistema

### 🟢 6.1 Recepción de Mercancía
- Inserta un nuevo lote en el árbol AVL.
- Valida que la fecha no exista.
- Registra producto y stock.
- Balancea automáticamente el árbol.

---

### 🚚 6.2 Registro de Pedido de Despacho
- Selecciona el lote más próximo a vencer.
- Inserta el pedido en la cola FIFO.
- Descuenta stock.
- Valida disponibilidad.

---

### ❌ 6.3 Cancelación de Pedido
- Busca un pedido específico.
- Elimina el pedido sin afectar el resto.
- Restituye el stock cancelado.

---

### 🗑️ 6.4 Eliminación Completa de un Lote
- Elimina el nodo del árbol AVL.
- Libera toda la cola de pedidos.
- Rebalancea el árbol tras la eliminación.

---

### 📊 6.5 Reporte de Estado
- Recorre el árbol **In-Order**.
- Muestra los lotes desde el más antiguo al más reciente.
- Indica fecha, producto, stock y pedidos pendientes.

---

## 🧠 7. Manejo de Memoria y Punteros

El sistema garantiza **cero fugas de memoria** mediante:
- Liberación previa de colas FIFO.
- Liberación segura de nodos AVL.
- Uso responsable de `malloc` y `free`.
- Correcta manipulación de punteros.

---

## 🧪 8. Resultados Obtenidos

- ✔️ Priorización correcta por fecha.
- ✔️ Pedidos gestionados en orden FIFO.
- ✔️ Árbol siempre balanceado.
- ✔️ Operaciones eficientes.
- ✔️ Sistema estable y funcional.

---

## 🛠️ 9. Compilación y Ejecución

Desde consola o Visual Studio Code:

```bash
gcc Sistema_Logistico.c -o sistema
./sistema