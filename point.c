

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

/**
* @brief Calculate the euclidean distance betweeen two points.
*
* The euclidean distance is defined as sqrt ((x1-x2)^2 + (y1-y2)^2)
* where (x1, y1) and (x2, y2) are the coordinate of both points
*
* @code
* // Example of use
* const Point *p1, *p2;
* double d;
* p1 = point_new (x1, y1, BARRIER);
* p2 = point_new (x2, y2, SPACE);
* point_euDistance (p1, p2, &d);
* printf ("%lf", d);
* // .... additional code ....
* @endcode
*
* @param p1 pointer to point
* @param p2 pointer to point
* @param distance addresss
*
* @return Returns OK or ERROR in case of invalid parameters
*/
Status point_euDistance (const Point *p1, const Point *p2, double *
distance) {
    int x1, y1, x2, y2, x, y;

    if(!p1 || !p2 || !distance) return ERROR;

    x1=point_getCoordinateX(p1);
    x2=point_getCoordinateX(p2);
    y1=point_getCoordinateY(p1);
    y2=point_getCoordinateY(p2);

    if(x1==__INT_MAX__ || x2==__INT_MAX__ || y1==__INT_MAX__ || y2==__INT_MAX__) return ERROR;

    x=x2-x1;
    y=y2-y1;

    *distance=sqrt(x*x+y*y);

    return OK;

}
/**
* @brief Compares two points using their euclidean distances to the
point (0,0).
*
*
* @param p1,p2 Points to compare.
*
* @return It returns an integer less than, equal to, or greater than
zero if
* the euclidean distance of p1 to the origin of coordinates is found
,
* respectively, to be less than, to match or be greater
* than the euclidean distance of p2. In case of error, returns
INT_MIN.
*/
int point_cmpEuDistance (const void *p1, const void *p2) {
    double eud1, eud2, cmpeud;
    Point *p0=NULL;

    p0=point_new(0, 0, BARRIER);

    if(!p1 || !p2) return INT_MIN;

    if(point_euDistance(p0, p1, &eud1)==ERROR) {
        point_free(p0);
        return INT_MIN;
    }

    if(point_euDistance(p0, p2, &eud2)==ERROR) {
        point_free(p0);
        return INT_MIN;
    }

    point_free(p0);

    /*-1:primero menor que el segundo   0:iguales   1:primero mayor que el segundo*/
    cmpeud=eud2-eud1;
    if(cmpeud==0) {
        return 0;
    }
    else if(cmpeud<0) {
        return 1;
    }
    else {
        return -1;
    }
}