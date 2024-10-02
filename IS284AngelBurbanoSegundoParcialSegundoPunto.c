/*
- Fecha de publicación: 2/10/2024
- Hora de publicación: 4:05am
- Versión del código: 3
- Autor: Ing(c) Burbano Rodriguez Angel Gabriel
- Nombre del lenguaje utilizado: C
- Versión del lenguaje utilizado: C11
- Versión del compilador utilizado: GCC 6.3.0
- Versión del S.O: Windows 10 Pro Versión 22H2
- Presentado a: Doctor Ricardo Moreno Laverde
- Universidad Tecnológica de Pereira
- Programa de Ingeniería de Sistemas y Computación
- Asignatura IS284 Programación II
- Descripción del programa: Este programa genera una pantalla de caracteres de 60 X 30 (60 de ancho y 30 de alto). Imprime la pantalla 
    de puntos y con circulos generado aleatoriamente.

    Luego se evalua cuales de esos circulos son esquinas de rectangulos imprimiendo de nuevo la pantalla pero con los rectángulos 
    rellenos por "x", sin rellenar los lugares en los que se encuntran otras esquinas, notadas por la letra "o". 
    Finalmente imprime por pantalla cuales son las dimensiones del cuadrado más pequeño y cual es su área.
    Todo el programa se basa en que los puntos de los rectángulos se toman con la siguiente enumeración:
                                                        1 - - - - 2
                                                        |         |
                                                        |         |
                                                        4 - - - - 3

    Se usa el ASCII 46(.) para representar el fondo de la pantalla, el ASCII 111(o) para las esquinas de los rectángulos y
    el ASCII 120(x) para rellenar los rectángulos.
*/

#include <stdio.h>   // Librería estándar de entrada/salida.
#include <stdlib.h>  // Librería estándar de utilidades.
#include <time.h>    // Librería para manejar el tiempo.


/**
 * Rellena la pantalla con puntos (.) y coloca una esquina de rectángulo ('o') aleatoriamente.
 * 
 * row: Fila actual a llenar en la pantalla.
 * col: Columna actual a llenar en la pantalla.
 * screen: Matriz que representa la pantalla de caracteres.
 */
void fill_screen(int row, int col, char screen[30][60]) {
    // Caso base: cuando se ha completado la última fila
    if (row == 30) {
        return;
    }

    // Llena la pantalla con puntos (.) y coloca una 'o' aleatoriamente
    screen[row][col] = '.';
    if (rand() % 22 == 0) {
        screen[row][col] = 'o';
    }
    printf("%c", screen[row][col]);

    // Caso base: cuando se ha completado la última columna de una fila
    if (col == 59) {
        printf("\n");
        fill_screen(row + 1, 0, screen); // Avanzamos a la siguiente fila
    } else {
        fill_screen(row, col + 1, screen); // Avanzamos a la siguiente columna
    }
}

/**
 * Rellena un rectángulo en la pantalla con 'x', sin modificar esquinas 'o'.
 * 
 * x1: Coordenada x de la esquina izquierda del rectángulo.
 * x2: Coordenada x de la esquina derecha del rectángulo.
 * y1: Coordenada y de la esquina superior del rectángulo.
 * y2: Coordenada y de la esquina inferior del rectángulo.
 * screen: Matriz que representa la pantalla de caracteres.
 * i: Fila actual que se está procesando.
 * j: Columna actual que se está procesando.
 */
void make_rectangle(int x1, int x2, int y1, int y2, char screen[30][60], int i, int j) {
    // Caso base: hemos terminado la fila actual
    if (i > y2) {
        return;
    }

    // Cambia los puntos por 'x', si no es una esquina 'o'
    if (j <= x2) {
        if (screen[i][j] == '.') {
            screen[i][j] = 'x';
        }
        make_rectangle(x1, x2, y1, y2, screen, i, j + 1); // Avanzamos a la siguiente columna
    } else {
        make_rectangle(x1, x2, y1, y2, screen, i + 1, x1); // Avanzamos a la siguiente fila
    }
}

/**
 * Busca un rectángulo en la pantalla a partir de una esquina.
 * 
 * screen: Matriz que representa la pantalla de caracteres.
 * x: Coordenada x de la esquina superior izquierda.
 * y: Coordenada y de la esquina superior izquierda.
 * rectangle: Matriz para almacenar las coordenadas de las esquinas del rectángulo encontrado.
 * i: Columna actual que se está procesando.
 * j: Fila actual que se está procesando.
 * 
 * Devuelve 1 si se encontró un rectángulo y 0 en caso contrario.
 */
int find_rectangle(char screen[30][60], int x, int y, int rectangle[3][2], int i, int j) {
    // Caso base: hemos llegado al límite de la pantalla
    if (i >= 60 || j >= 30) {
        return 0;
    }

    // Caso base: encontramos una esquina
    if (screen[y][i] == 'o' && screen[j][i] == 'o' && screen[j][x] == 'o') {
        make_rectangle(x, i, y, j, screen, y, x); // Rellenamos el rectángulo
        // Calcula el área y comprueba si es el rectángulo más pequeño
        if ((i - x) * (j - y) < (rectangle[1][0] - rectangle[0][0]) * (rectangle[2][1] - rectangle[1][1])) {
            rectangle[0][0] = x;
            rectangle[0][1] = y;
            rectangle[1][0] = i;
            rectangle[1][1] = y;
            rectangle[2][0] = i;
            rectangle[2][1] = j;
            return 1;
        }
    }

    // Avanza a la siguiente columna
    if (i < 59) {
        return find_rectangle(screen, x, y, rectangle, i + 1, j);
    }

    // Avanza a la siguiente fila
    return find_rectangle(screen, x, y, rectangle, x + 1, j + 1);
}

/**
 * Revisa la pantalla para buscar rectángulos a partir de las esquinas 'o'.
 * 
 * r: Fila actual a revisar.
 * c: Columna actual a revisar.
 * screen: Matriz que representa la pantalla de caracteres.
 * rectangle: Matriz para almacenar las coordenadas del rectángulo encontrado.
 * area: Puntero a la variable que almacena el área del rectángulo más pequeño encontrado.
 * 
 * Devuelve el área del rectángulo más pequeño encontrado.
 */
int check_screen(int r, int c, char screen[30][60], int rectangle[3][2], int *area) {
    // Caso base: si terminamos de recorrer todas las filas
    if (r == 30) {
        return *area;
    }

    // Si encontramos una esquina 'o', buscamos un rectángulo
    if (screen[r][c] == 'o') {
        if (find_rectangle(screen, c, r, rectangle, c + 1, r + 1)) {
            *area = (rectangle[1][0] - rectangle[0][0] + 1) * (rectangle[2][1] - rectangle[1][1] + 1);
        }
    }

    // Continuar con la siguiente columna
    if (c < 59) {
        return check_screen(r, c + 1, screen, rectangle, area);
    }

    // Avanza a la siguiente fila
    return check_screen(r + 1, 0, screen, rectangle, area);
}

/**
 * Imprime la pantalla de caracteres.
 * 
 * r: Fila actual a imprimir.
 * c: Columna actual a imprimir.
 * screen: Matriz que representa la pantalla de caracteres.
 */
void print_screen(int r, int c, char screen[30][60]) {
    // Caso base: si terminamos de recorrer todas las filas
    if (r == 30) {
        return;
    }

    printf("%c", screen[r][c]); // Imprime el carácter actual

    // Continuar con la siguiente columna
    if (c < 59) {
        print_screen(r, c + 1, screen); // Avanzamos a la siguiente columna
    } else {
        printf("\n");
        print_screen(r + 1, 0, screen); // Avanzamos a la siguiente fila
    }
}

int main() {
    srand(time(NULL)); // Inicializa la semilla para números aleatorios
    char screen[30][60]; // Pantalla de 60 columnas y 30 filas
    int rectangle[3][2] = {{0, 0}, {59, 0}, {59, 29}}; // Coordenadas de las esquinas del rectángulo más pequeño
    int area = 0; // Inicializa el área en 0

    fill_screen(0, 0, screen); // Llenar e imprimir la pantalla con puntos y esquinas 'o'
    printf("\n");

    // Revisa la pantalla para buscar rectángulos
    check_screen(0, 0, screen, rectangle, &area);

    // Si se ha encontrado algún rectángulo, imprime la pantalla actualizada y el área del más pequeño
    if (area) {
        print_screen(0, 0, screen); // Imprimir la pantalla actualizada
        printf("\nEl %crea del m%cs peque%co seria %i x %i %i\n", 160, 160, 164, 
        rectangle[1][0] - rectangle[0][0] + 1, rectangle[2][1] - rectangle[1][1] + 1, area);
    } else {
        printf("No se ha encontrado ningun rectangulo.\n");
    }

    return 0;
}
