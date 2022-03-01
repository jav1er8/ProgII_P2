#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "stack_fDoble.h"
#include "point.h"

#define MAX_RAND 11

Stack *stack_orderPoints(Stack *sin);


int main(int argc, char *argv[]) {
    Stack *p_original, *p_ordenada;
    Point **punto, *origen;
    int n, i, x, y;
    double distancia;

    if(argc < 2) {
        fprintf(stderr, "Introduzca: %s <numero_de_puntos>\n", argv[0]);
        return -1;
    }

    srand(time(NULL));

    n = atoi(argv[1]);

    *punto = (Point**) malloc(n * sizeof(Point*));
    if(!*punto){
        fprintf(stderr, "Error creando array de puntos\n");
        return -1;
    }

    origen = point_new(0, 0, BARRIER);
    if(!origen) {
        fprintf(stderr, "Error creando origen\n");
        free(punto);
        return -1;
    }

    /* Crea n puntos con coordenadas aleatorias entre 0 y MAX_RAND */
    for(i=0; i < n; i++) {
        x = rand() % MAX_RAND;
        y = rand() % MAX_RAND;
        punto[i] = point_new(x, y, BARRIER);
        if(!punto[i]) {
            fprintf(stderr, "Error creando punto %d\n", i+1);

            point_free(origen);
            return -1;
        }
    }

    /* Muestra los puntos y sus distancias */
    for(i=0; i < n; i++) {
        distancia = point_euDistance(origen, punto[i], &distancia);

        fprintf(stdout, "Point p[%d]=");
        point_print(stdout, punto[i]);
        fprintf(stdout, " distance: %lf\n", distancia);
    }

    p_original = stack_init();
    if(!p_original) {
        fprintf(stderr, "Error creando pila\n");
        return -1;
    }

    for(i=0; i < n; i++) {
        if(stack_push(p_original, punto[i]) == ERROR) {
            fprintf(stderr, "Error añadiendo punto a pila\n");
            return -1;
        }
    }

    /* Muestra la pila original */
    fprintf(stdout, "Original stack:\n");
    stack_print(stdout, p_original, point_print);

    p_ordenada = stack_orderPoints(p_original);
    if(!p_ordenada) {
        fprintf(stderr, "Error ordenando pila\n");
    }

    /* Muestra los puntos ordenados de la pila */
    fprintf(stdout, "Ordered stack:");
    stack_print(stdout, p_ordenada, point_print);

    /* Libera los puntos del stack */
    for(i = 0; i < n; i++) {
        point_free(punto[i]);
    }
    free(punto);

    /* Libera el origen */
    point_free(origen);

    /* Libera los stacks */
    stack_free(p_original);
    stack_free(p_ordenada);

    return 0;
}

Stack *stack_orderPoints(Stack *sin) {
    Stack *s_aux;
    Point *p_aux1, *p_aux2;
    int dist;

    s_aux = stack_init();
    if(!s_aux) {
        return NULL;
    }

    while(stack_isEmpty(sin) == FALSE) {
        p_aux1 = (Point*) stack_pop(sin);
        if(!p_aux1) {
            return NULL;
        }

        if(point_euDistance(p_aux1, stack_top(sin), dist) == ERROR) {
            return NULL;
        }
        while(stack_isEmpty(s_aux) == FALSE && dist == MENOR) {
            p_aux2 = (Point*) stack_pop(s_aux);
            if(!p_aux2) {
                return NULL;
            }

            if(stack_push(sin, p_aux2) == ERROR) {
                return NULL;
            }
        }

        if(stack_push(s_aux, p_aux1) == ERROR) {
            return NULL;
        }
    }

    return s_aux;
}