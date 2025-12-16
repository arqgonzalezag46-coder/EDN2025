#include <stdio.h>

int main() {
    int numeros[10];  

    printf("=== MEMORIA ESTATICA ===\n");
    printf("Arreglo de 10 enteros (memoria fija):\n");

    for (int i = 0; i < 10; i++) {
        numeros[i] = (i + 1) * 5;
        printf("numeros[%d] = %d\n", i, numeros[i]);
    }

    printf("\n--- Reflexion ---\n");
    printf("1. El tamano del arreglo esta definido en compilacion.\n");
    printf("2. La memoria se almacena en el stack.\n");
    printf("3. Se libera automaticamente al finalizar la funcion.\n");
    printf("4. Es rapida, pero no se puede modificar su tamano.\n");

    return 0;
}