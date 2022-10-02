#include "PilaInt.h"
#include "Definiciones.h"

#ifdef PILA_INT_IMP

struct _cabezalPilaInt {
	NodoListaInt* primeroLista;
	int largo;
};


PilaInt crearPilaInt() {
	PilaInt pila = new _cabezalPilaInt;
	pila->largo = 0;
	pila->primeroLista = NULL;
	return pila;
}

void push(PilaInt& p, int e) {
	NodoListaInt* nuevo = new NodoListaInt;
	nuevo->dato = e;
	nuevo->sig = p->primeroLista;
	p->primeroLista = nuevo;
	p->largo++;
}

int top(PilaInt p) {
	return p->primeroLista->dato;
}

void pop(PilaInt& p) {
	NodoListaInt* borrar = p->primeroLista;
	p->primeroLista = p->primeroLista->sig;
	p->largo--;
	delete borrar;
}

unsigned int cantidadElementos(PilaInt p) {
	return p->largo;
}

bool esVacia(PilaInt p) {
	return p != NULL && p->primeroLista == NULL;
}

NodoListaInt* clonarLista(NodoListaInt* l) {
	if (l == NULL) {
		return NULL;
	}
	NodoListaInt* nuevo = new NodoListaInt;
	nuevo->dato = l->dato;
	nuevo->sig = clonarLista(l->sig);
	return nuevo;
}


PilaInt clon(PilaInt p) {
	PilaInt retorno = crearPilaInt();
	retorno->largo = p->largo;
	retorno->primeroLista = clonarLista(p->primeroLista);
	return retorno;
}

void destruir(PilaInt& p) {

	while (!esVacia(p)) {
		pop(p);
	}
	delete p;
}


#endif