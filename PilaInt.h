#pragma once
// NOTA: Este archivo no debe ser modificado (excepto por los define que eligen la implementacion a usar)

// Elegir la implementacion a usar (solo 1 a la vez):
#define PILA_INT_IMP
//#define PILA_INT_IMP_2

#if defined(PILA_INT_IMP)
#include "PilaIntImp.h"
#elif defined(PILA_INT_IMP_2)
#include "PilaIntImp2.h"
#endif

// PRE: -
// POS: retorna una nueva pila vacia
PilaInt crearPilaInt();

// PRE: -
// POS: inserta un elemento en la cima de la pila
void push(PilaInt& p, int e);

// PRE: !esVacia()
// POS: retorna el elemento de la cima de la pila
int top(PilaInt p);

// PRE: !esVacia()
// POS: elimina el elemento de la cima de la pila
void pop(PilaInt& p);

// PRE: -
// POS: retorna true si y solo si la pila esta vacia
bool esVacia(PilaInt p);

// PRE: -
// POS: retorna la cantidad de elementos presentes en la pila
unsigned int cantidadElementos(PilaInt p);

// PRE: -
// POS: retorna una copia de la pila p sin compartir memoria
PilaInt clon(PilaInt p);

// PRE: -
// POS: libera la memoria de la pila
void destruir(PilaInt& p);
