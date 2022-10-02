#include "ColaPrioridadInt.h"
#include "Definiciones.h"

#ifdef COLAPRIORIDAD_INT_IMP

struct _cabezalColaPrioridadInt {
	int cantidadElementos;
	int cota;
	NodoListaIntDobleDato* principioLista;
	NodoListaIntDobleDato* ultimoLista;
};


ColaPrioridadInt crearColaPrioridadInt(unsigned int cota) {
	ColaPrioridadInt cola = new _cabezalColaPrioridadInt;
	cola->cantidadElementos = 0;
	cola->cota = cota;
	cola->principioLista = cola->ultimoLista = NULL;
	return cola;
}

void encolar(ColaPrioridadInt& c, int e, int p) {
	NodoListaIntDobleDato* nuevo = new NodoListaIntDobleDato;
	nuevo->dato1 = e;
	nuevo->dato2 = p;
	nuevo->sig = NULL;

	if (c->principioLista == NULL) {
		nuevo->sig = NULL;
		c->principioLista = c->ultimoLista = nuevo;
		c->cantidadElementos++;

	}else{
		if (c->principioLista->dato2 >= nuevo->dato2) {
			NodoListaIntDobleDato* aux = c->principioLista;
			while (aux != NULL) {
				if (aux->sig == NULL) {
					nuevo->sig = NULL;
					aux->sig = nuevo;
					c->ultimoLista = nuevo;
					break;
				}
				else if (aux->sig->dato2 < nuevo->dato2) {
					nuevo->sig = aux->sig;
					aux->sig = nuevo;
					break;
				}
				aux = aux->sig;
			}
			c->cantidadElementos++;
		}
		else {
			nuevo->sig = c->principioLista;
			c->principioLista = nuevo;
			c->cantidadElementos++;
		}
	}
	
}

int principio(ColaPrioridadInt c) {
	return c->principioLista->dato1;
}

int principioPrioridad(ColaPrioridadInt c) {
	return c->principioLista->dato2;
}

void desencolar(ColaPrioridadInt& c) {
	NodoListaIntDobleDato* borro = c->principioLista;
	c->principioLista = c->principioLista->sig;
	if (c->principioLista == NULL) {
		c->ultimoLista = NULL;
	}
	delete borro;
	c->cantidadElementos--;
}

bool esVacia(ColaPrioridadInt c) {
	return c->principioLista == NULL;

}

bool esLlena(ColaPrioridadInt c) {
	return cantidadElementos(c) == c->cota;
}

unsigned int cantidadElementos(ColaPrioridadInt c) {
	return c->cantidadElementos;
}

ColaPrioridadInt clon(ColaPrioridadInt c) {
	ColaPrioridadInt retorno = crearColaPrioridadInt(c->cota);
	NodoListaIntDobleDato* aux = c->principioLista;
	while (aux != NULL) {
		encolar(retorno, aux->dato1, aux->dato2);
		aux = aux->sig;
	}
	return retorno;
}

void destruir(ColaPrioridadInt& c) {
	while (c->principioLista != NULL) {
		desencolar(c);
	}
	delete c;
}

#endif