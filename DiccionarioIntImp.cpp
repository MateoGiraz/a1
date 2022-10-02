#include "DiccionarioInt.h"
#include "Definiciones.h"

#ifdef DICCIONARIO_INT_IMP

/*AUXILIARES*/

//PRE: Recibe una lista y un entero
//POS: Si el entero pertenece a la lista, lo borra
void borrarDeLista(NodoListaInt*& l, int e) {
	NodoListaInt* aux = l;
	if (aux != NULL) {
		if (aux->dato == e) {
			l = l->sig;
			delete aux;
			return;
		}
		while (aux->sig != NULL) {
			if (aux->sig->dato == e) {
				aux->sig = aux->sig->sig;
				return;
			}
			aux = aux->sig;
		}


	}
}

/*FUNCIONES DEL CONTRATO*/

struct _cabezalDiccionarioInt {
	NodoListaInt** tabla;
	int cantidad;
	int cota;
};

//funcion de hash

int fHash(unsigned int i, int esperados) {
	return i % esperados;
}

DiccionarioInt crearDiccionarioInt(unsigned int esperados) {
	DiccionarioInt ret = new _cabezalDiccionarioInt;
	ret->cantidad = 0;
	ret->cota = esperados;
	ret->tabla = new NodoListaInt* [esperados];
	for (int i = 0; i < esperados; i++) {
		ret->tabla[i] = NULL;
	}
	return ret;
}

void agregar(DiccionarioInt& d, int e) {
	if (!pertenece(d, e)) {
		NodoListaInt* agregado = new NodoListaInt;
		agregado->dato = e;
		agregado->sig = d->tabla[fHash(e, d->cota)];
		d->tabla[fHash(e, d->cota)] = agregado;
		d->cantidad++;
	}
}

void borrar(DiccionarioInt& d, int e) {
	if (pertenece(d, e)) {
		borrarDeLista(d->tabla[fHash(e, d->cota)], e);
		d->cantidad--;
	}
}

bool pertenece(DiccionarioInt d, int e) {
	NodoListaInt* aux = d->tabla[fHash(e, d->cota)];
	bool ret = false;
	while (aux != NULL) {
		if (aux->dato == e) ret = true;
		aux = aux->sig;
	}
	return ret;
}

int elemento(DiccionarioInt d) {
	for (int i = 0; i < d->cota; i++) {
		if (d->tabla[i] != NULL) {
			return d->tabla[i]->dato;
		}
	}
}

bool esVacio(DiccionarioInt d) {
	return d->cantidad == 0;
}

unsigned int cantidadElementos(DiccionarioInt d) {
	return d->cantidad;
}

DiccionarioInt clon(DiccionarioInt d) {
	DiccionarioInt ret = crearDiccionarioInt(d->cota);
	for (int i = 0; i < d->cota; i++) {
		NodoListaInt* aux = d->tabla[i];
		while (aux != NULL) {
			agregar(ret, aux->dato);
			aux = aux->sig;
		}
	}
	return ret;
}

void destruir(DiccionarioInt& d) {
	for (int i = 0; i < d->cota; i++) {
		while (d->tabla[i] != NULL) {
			NodoListaInt* borro = d->tabla[i];
			d->tabla[i] = d->tabla[i]->sig;
			delete borro;
		}
	}
	delete[] d->tabla;
	delete d;
}

#endif