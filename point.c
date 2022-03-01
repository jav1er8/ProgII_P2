

#include "point.h"

struct _Point {
    int x, y;
    char symbol;
    Bool visited; // for DFS
};

/**
 * @brief Constructor. Initialize a point.
 * 
 * This function allocates memory for a point and sets its fields acoording 
 * its input parameter values.
 *
 * @code
 * // Example of use
 * Point * v;
 * v = point_new (0, 0, BARRIER);
 * @endcode
 *
 * @param x Point x coordinate 
 * @param y Point y coordinate 
 * @param symbol Point symbol 
 * 
 * @return Return the initialized point if it was done correctly, 
 * otherwise return NULL.
*/
Point * point_new (int x, int y, char symbol) {
    Point *new_point;

    new_point = (Point*) malloc(sizeof(Point));
    if(!new_point)
        return NULL;

    if(point_setCoordinateX(new_point, x)==ERROR || point_setCoordinateY(new_point, y)==ERROR || point_setSymbol(new_point, symbol)==ERROR) {
        point_free(new_point);
        return NULL;
    }    

    return new_point;
}

/**
 * @brief Destructor. Free the dynamic memory reserved for a point .
 *
 * @param p Point to free
 */
void point_free (Point *p) {
    if(!p) {
        return;
    }

    free(p);
    return;
}


/**
 * @brief Gets the x coordinate of a given point.
 *
 * @param Point pointer
 *
 * @return Returns the x coordinate of a given point, or INT_MAX in 
 * case of error.
 */
int point_getCoordinateX (const Point *p) {
    if(!p) {
        return __INT_MAX__;
    }
    
    return p->x;
}


/**
 * @brief Gets the y coordinate of a given point.
 *
 * @param Point pointer
 *
 * @return Returns the y coordinate of a given point, or INT_MAX in 
 * case of error.
 */
int point_getCoordinateY (const Point *p) {
    if(!p) {
        return __INT_MAX__;
    }
    return p->y;
}


/**
 * @brief Gets the symbol of a given point.
 *
 * @param Point pointer
 *
 * @return Returns the symbol of a given point, or INT_MAX in 
 * case of error.
 */
char point_getSymbol (const Point *p) {
    if(!p) {
        return ERRORCHAR;
    }
    return p->symbol;
}


/**
 * @brief Modifies the x coordinate  of a given point.
 *
 * @param p Point pointer
 * @param x New x coordinate, must be equal or greater than 0
 *
 * @return Returns OK or ERROR in case of error 
 */
Status point_setCoordinateX (Point *p, int x) {
    if(!p || x<0) {
        return ERROR;
    }
    p->x = x;
    
    return OK;
}


/**
 * @brief Modifies the y coordinate  of a given point.
 *
 * @param p Point pointer
 * @param y New y coordinate, must be equal or greater than 0
 *
 * @return Returns OK or ERROR in case of error 
 */
Status point_setCoordinateY (Point *p, int y) {
    if(!p || y<0) {
        return ERROR;
    }
    p->y = y;
    
    return OK;
}


/**
 * @brief Modifies the symbol of a given point.
 *
 * @param p Point pointer
 * @param c New symbol, must be a valid symbol
 *
 * @return Returns OK or ERROR in case of error 
 */
Status point_setSymbol (Point *p, char c) {
    if(!p || c == ERRORCHAR) {
        return ERROR;
    }
    p->symbol=c;
    
    return OK;
}

Bool point_getVisited (const Point *p); // DFS (P2)
Status point_setVisited (Point *p, Bool bol);    // DFS (P2)


/**
 * @brief Reserves memory for a point where it copies the data from
 * the point src.
 * 
 * @code
 * // Example of use
 * Point *trg, *src;
 * src = point_new();
 * trg = point_hardcpy(src);
 * // .... aditional code ...
 * // free points
 * point_free(src);
 * point_free(trg);
 * @endcode
 * 
 * @param src Original Point pointer
 *
 * @return Returns the pointer of the copied Point if everything 
 * went well, or NULL otherwise.
 */
Point *point_hardcpy (const Point *src) {
    Point *trg;

    if(!src)
        return NULL;
    
    trg = point_new(src->x, src->y, src->symbol);
    
    if(!trg)
        return NULL;

    return trg;
}


/**
 * @brief Compares two points.
 * 
 * @param p1,p2 Points to compare.
 *
 * @return Returns True or False. 
 * In case of error, returns FALSE. 
 */
Bool point_equal (const void *p1, const void *p2) {
    Point* _p1 = (Point*)p1;
    Point* _p2 = (Point*)p2;

    /*Error control*/
    if(!_p1 || !_p2) {
        return FALSE;
    }
    
    if(_p1->x != _p2->x || _p1->y != _p2->y || _p1->symbol != _p2->symbol /*comprobacion visited*/) {
        return FALSE;
    }

    return TRUE;
}


/** 
 * @brief Prints in pf the data of a point.
 * 
 * The format will be: [(x, y): symbol], without line break at the 
 * end.
 *
 * @code
 * Point * v;
 * v = point_new ();
 * point_print (stdout, v);
 * @endcode
 *
 * @param pf File descriptor
 * @param p Point to be printed
 *
 * @return Returns the number of characters that have been written 
 * successfully. If there have been errors returns -1.
 */
int point_print (FILE *pf, const void *p) {
    if(!pf)
        return -1;
    
    Point* _p = (Point*) p;

    //print info
    return fprintf(pf, "[(%d, %d): %c]", _p->x, _p->y, _p->symbol /*visited*/);
}
