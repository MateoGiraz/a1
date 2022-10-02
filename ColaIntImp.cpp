#include "ColaInt.h"
#include "Definiciones.h"

#ifdef COLA_INT_IMP

struct _cabezalColaInt {
	int cantidadElementos;
	NodoListaInt* principioLista;
	NodoListaInt* ultimoLista;
};

ColaInt crearColaInt() {
	ColaInt cola = new _cabezalColaInt;
	cola->cantidadElementos = 0;
	cola->principioLista = NULL;
	cola->ultimoLista = NULL;
	return cola;
}

void encolar(ColaInt& c, int e) {

	NodoListaInt* nuevo = new NodoListaInt;
	nuevo->dato = e;
	nuevo->sig = NULL;

	if (c->principioLista == NULL) {
		c->principioLista = nuevo;
		c->ultimoLista = nuevo;
		c->cantidadElementos++;
		return;
	}

	c->ultimoLista->sig = nuevo;
	c->ultimoLista = nuevo;
	c->cantidadElementos++;
}

int principio(ColaInt c) {
	return c->principioLista->dato;
}

void desencolar(ColaInt& c) {
	NodoListaInt* borro = c->principioLista;
	c->principioLista = c->principioLista->sig;
	if (c->principioLista == NULL) {
		c->ultimoLista = NULL;
	}
	delete borro;
	c->cantidadElementos--;

}

bool esVacia(ColaInt c) {
	return c->principioLista == NULL;
}

unsigned int cantidadElementos(ColaInt c) {
	return c->cantidadElementos;
}

ColaInt clon(ColaInt c) {
	ColaInt retorno = crearColaInt();
	NodoListaInt* aux = c->principioLista;
	while (aux != NULL) {
		encolar(retorno, aux->dato);
		aux = aux->sig;
	}
	return retorno;
}

void destruir(ColaInt& c) {
	while (c->principioLista != NULL) {
		desencolar(c);
	}
	delete c;
}

#endif