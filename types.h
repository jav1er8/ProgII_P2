/* 
 * File:   types.h
 * Author: Profesores de PROG2
 */

#ifndef TYPES_H
#define	TYPES_H

#define INT_MIN 0x80000000

typedef enum {
    FALSE=0, TRUE=1
} Bool;

typedef enum {
    ERROR=0, OK=1, END=2
} Status;

typedef enum {
    MENOR=-1, IGUAL=0, MAYOR=1
} Comparacion;

#endif	/* TYPES_H */

