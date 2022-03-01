#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "point.h"
#include "map.h"

#define MAX_RAND 101

void memory_free(Point **p, int contador);

int main(int argc, char *argv[]) {

    Point **p, *origen;
    int i, j, n, contador=0, cmp;
    double distance;

    n=atoi(argv[1]);
    if(n<=0) return 1;

    srand(time(NULL));


    origen=point_new(0, 0, BARRIER);
    if(!origen) return 1;

    p=(Point**) malloc(n*sizeof(Point*));
    for(i=0; i<n; i++) {
        p[i]=NULL;
    }

    if(!p) return 1;

    for(i=0; i<n; i++) {
        p[i]=point_new(rand()%MAX_RAND, rand()%MAX_RAND, BARRIER);
        if(!p[i]) {
            memory_free(p, contador);
            return 1;
        }
        contador++;
    }

    for(i=0; i<n; i++) {
        if(point_euDistance(p[i], origen, &distance)==ERROR) {
            memory_free(p, contador);
            return 1;
        }

        fprintf(stdout,  "Point p[%d]=", i);
        point_print(stdout, p[i]);
        fprintf(stdout, " distance: %.6lf\n", distance);
    }


    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            cmp=point_cmpEuDistance(p[i], p[j]);
            if(cmp==INT_MIN) {
                memory_free(p, contador);
                return 1;
            }

            fprintf(stdout, "p[%d] < p[%d]: ", i, j);
            
            if(cmp==0 || cmp==1) {
                fprintf(stdout, "False\n");
            }
            else if(cmp==-1) {
                fprintf(stdout, "True\n");
            }
        }
    }

    memory_free(p, contador);
    point_free(origen);

    return 0;
}

void memory_free(Point **p, int contador) {
    int i;
    for(i=0; i<contador; i++) {
        point_free(p[i]);
    }
    free(p);
    return;
}