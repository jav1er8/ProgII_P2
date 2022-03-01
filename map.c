#include <stdio.h>
#include "map.h"

#define MAX_NCOLS 64 // Maximum map cols
#define MAX_NROWS 64 // Maximum map rows
#define MAX_BUFFER 64 // Maximum file line size
struct _Map {
    unsigned int nrows, ncols;
    Point *array[MAX_NROWS][MAX_NCOLS]; // array with the Map points
    Point *input, *output; // points input/output
};

Map * map_new (unsigned int nrows, unsigned int ncols) {
    Map *new_map = NULL;
    int i, j;

    new_map = (Map*) malloc(sizeof(Map));
    if(!new_map || nrows >= MAX_NROWS || ncols >= MAX_NCOLS) {
        return NULL;
    }

    new_map->nrows = nrows;
    new_map->ncols = ncols;
    new_map->input = NULL;
    new_map->output = NULL;
    for(i=0; i < MAX_NROWS; i++) {
        for(j=0; j < MAX_NCOLS; j++) {
            new_map->array[i][j] = NULL;
        }
    }

    return new_map;
}

void map_free (Map *g) {
    int i, j;

    if(!g){
        return;
    }

    for(i=0; i < MAX_NROWS; i++) {
        for(j=0; j < MAX_NCOLS; j++) {
            point_free(g->array[i][j]);
            g->array[i][j]=NULL;
        }
    }



    free(g);
}

Point *map_insertPoint (Map *mp, Point *p) {
    int x, y;
    
    if(!mp || !p) {
        return NULL;
    }

    x = point_getCoordinateX(p);
    y = point_getCoordinateY(p);
    if(x == __INT_MAX__ || y == __INT_MAX__) {
        return NULL;
    }

    //introducir el punto
    mp->array[y][x] = p;
    if(!mp->array) {
        return NULL;
    }

    return mp->array[y][x];
}

int map_getNcols (const Map *mp) {
    if(!mp) {
        return -1;
    }

    return mp->ncols;
}

int map_getNrows (const Map *mp) {
    if(!mp) {
        return -1;
    }

    return mp->nrows;
}

//Get input / Get output

Point *map_getInput (const Map *mp) {
    if(!mp) {
        return NULL;
    }

    return mp->input;
}

Point *map_getOutput (const Map *mp) {
    if(!mp) {
        return NULL;
    }

    return mp->output;                                                                                                                                                                                                                               
}

Point *map_getPoint (const Map *mp, const Point *p) {
    int x, y;
    
    if(!mp || !p) {
        return NULL;
    }

    x = point_getCoordinateX(p);
    y = point_getCoordinateY(p);
    if(x == __INT_MAX__ || y == __INT_MAX__) {
        return NULL;
    }

    return mp->array[y][x];
}

Point *map_getNeighboor (const Map *mp, const Point *p, Position pos) {
    int x, y;
    
    if(!mp || !p || (pos != RIGHT && pos != LEFT && pos != UP && pos != DOWN && pos != STAY)) {
        return NULL;
    }

    x = point_getCoordinateX(p);
    y = point_getCoordinateY(p);
    if(x == __INT_MAX__ || y == __INT_MAX__) {
        return NULL;
    }

    switch(pos) {
        case RIGHT:
            x ++;
            break;
        case LEFT:
            x --;
            break;
        case UP:
            y --;
            break;
        case DOWN:
            y ++;
            break;
        default:
            break;
    }

    if(y > map_getNrows(mp) || x > map_getNcols(mp)) {
        return NULL;
    }

    return mp->array[y][x];
}

Status map_setInput (Map *mp, Point *p) {
    if(!mp || !p) {
        return ERROR;
    }

    mp->input = p;

    return OK;
}

Status map_setOutput (Map *mp, Point *p) {
    if(!mp || !p) {
        return ERROR;
    }

    mp->output = p;

    return OK;
}

//Read form file

Bool map_equal (const void *_mp1, const void *_mp2) {
    Map *m1, *m2;
    int i, j;

    if(!_mp1 || !_mp2) {
        return FALSE;
    }

    m1 = (Map*)_mp1;
    m2 = (Map*)_mp2;

    if(m1->ncols != m2->ncols) {
        return FALSE;
    }

    if(m1->nrows != m2->nrows) {
        return FALSE;
    }

    for(i=0; i<m1->nrows; i++) {
        for(j=0; j<m1->ncols; j++) {
            if(point_equal(m1->array[i][j], m2->array[i][j]) == FALSE) {
                return FALSE;
            }
        }
    }

    if(m1->input != m2->input) {
        return FALSE;
    }

    if(m1->output != m2->output) {
        return FALSE;
    }

    return TRUE;
}

int map_print (FILE *pf, Map *mp) {
    int i, j, nchars=0, aux;

    if(!pf || !mp) {
        return -1;
    }

    //print the number of rows and columns
    fprintf(pf, "%d, %d\n", mp->nrows, mp->ncols);

    //print the points
    for(i=0; i<mp->nrows; i++) {
        for(j=0; j<mp->ncols; j++){
            if((aux = point_print(pf, mp->array[i][j]) )== -1) {
                return -1;
            }
            nchars += aux;
        }
    }
    fprintf(pf, "\n");
    return nchars;
}

Map * map_readFromFile (FILE *pf) {
    int nrows, ncols, x, y;
    char c;
    Map *new_map = NULL;

    if(!pf) {
        return NULL;
    }

    if(fscanf(pf, "%d %d", &nrows, &ncols)!=2) {
        return NULL;
    }


    //crear mapa
    new_map = map_new(nrows, ncols);
    if(!new_map) {
        return NULL;
    }
    
    //leer de fichero e introducir nuevos puntos
    for(y=0; y<nrows; y++ ) {
        for(x=0; x<ncols; x++) {
            c=fgetc(pf);
            if(!c) {
                map_free(new_map);
                return NULL;
            }

            if(c == '\n') {
                x--;
            }
            else {
                if(!map_insertPoint(new_map, point_new(x, y, c))) {
                    map_free(new_map);
                    return NULL;
                }

                if(c==INPUT) {
                    if(map_setInput(new_map, new_map->array[y][x])==ERROR || map_getInput(new_map)==NULL){
                        map_free(new_map);
                        return NULL;
                    }
                }

                if(c==OUTPUT) {
                    if(map_setOutput(new_map, new_map->array[y][x])==ERROR || map_getOutput(new_map)==NULL){
                        map_free(new_map);
                        return NULL;
                    }
                }
            }
        }
    }

    return new_map;
}
