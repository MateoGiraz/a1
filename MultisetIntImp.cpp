#include "MultisetInt.h"
#include "Definiciones.h"

#ifdef MULTISET_INT_IMP

struct _cabezalMultisetInt {
	NodoListaIntDobleDato* lista;
	int cantidadElementos;
};

/*AUXILIARES*/

//PRE: Recibe dos enteros
//POS: Devuelve el máximo
int maximo(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

//PRE: Recibe dos enteros
//POS: Devuelve el mínimo
int minimo(int a, int b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}

//PRE: Recibe un multiset y un entero 
//POS: Devuelve las ocurrencias del entero en el multiset
int ocurrencias(MultisetInt s, int e) {
	NodoListaIntDobleDato* aux = s->lista;
	int ret = 0;
	while (aux != NULL) {
		if (aux->dato1 == e) ret = aux->dato2;
		aux = aux->sig;
	}
	return ret;
}

/*FUNCIONES DEL CONTRATO*/

MultisetInt crearMultisetInt() {
	MultisetInt multiSet = new _cabezalMultisetInt;
	multiSet->cantidadElementos = 0;
	multiSet->lista = NULL;
	return multiSet;
}


void agregar(MultisetInt& s, int e, unsigned int ocurrencias) {

	if (!pertenece(s, e)) {
		NodoListaIntDobleDato* nuevo = new NodoListaIntDobleDato;
		nuevo->dato1 = e;
		nuevo->dato2 = ocurrencias;
		nuevo->sig = s->lista;
		s->lista = nuevo;
		s->cantidadElementos += ocurrencias;
		return;
	}

	NodoListaIntDobleDato* aux = s->lista;
	while (aux->dato1 != e) {
		aux = aux->sig;
	}
	aux->dato2 += ocurrencias;

}

void borrar(MultisetInt& s, int e) {
	if (pertenece(s, e)) {
		NodoListaIntDobleDato* aux = s->lista;
		if (aux->dato1 == e) {
			if (aux->dato2 > 1) {
				aux->dato2--;
				s->cantidadElementos--;
				return;
			}

			s->lista = s->lista->sig;
			delete aux;
			s->cantidadElementos--;
			return;
		}

		while (aux->sig != NULL) {
			if (aux->sig->dato1 == e) {
				if (aux->sig->dato2 > 1) {
					aux->sig->dato2--;
					s->cantidadElementos--;
					return;
				}
				
				NodoListaIntDobleDato* borro = aux->sig;
				aux->sig = aux->sig->sig;
				delete borro;
				s->cantidadElementos--;
				return;
			}
			aux = aux->sig;
		}
	}
}

bool pertenece(MultisetInt s, int e) {
	bool ret = false;
	NodoListaIntDobleDato* aux = s->lista;
	while (aux != NULL) {
		if (aux->dato1 == e) {
			ret = true;
		}
		aux = aux->sig;
	}
	return ret;
}

MultisetInt unionConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt ret = crearMultisetInt();
	NodoListaIntDobleDato* aux = s1->lista;
	NodoListaIntDobleDato* aux2 = s2->lista;
	while (aux != NULL) {
		aux2 = s2->lista;
		while (aux2 != NULL) {
			if (aux->dato1 == aux2->dato1) {
				agregar(ret, aux2->dato1, maximo(aux->dato2, aux2->dato2));
				break;
			}
			aux2 = aux2->sig;
		}
		aux = aux->sig;
	}
	aux2 = s2->lista;
	aux = s1->lista;
	while (aux2 != NULL) {
		if (!pertenece(ret, aux2->dato1)) {
			agregar(ret, aux2->dato1, aux2->dato2);
		}
		aux2 = aux2->sig;
	}
	while (aux != NULL) {
		if (!pertenece(ret, aux->dato1)) {
			agregar(ret, aux->dato1, aux->dato2);
		}
		aux = aux->sig;
	}
	return ret;
}


MultisetInt interseccionConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt ret = crearMultisetInt();
	NodoListaIntDobleDato* aux = s1->lista;
	NodoListaIntDobleDato* aux2 = s2->lista;
	while (aux != NULL) {
		aux2 = s2->lista;
		while (aux2 != NULL) {
			if (aux->dato1 == aux2->dato1) {
				agregar(ret, aux2->dato1, minimo(aux->dato2, aux2->dato2));
				break;
			}
			aux2 = aux2->sig;
		}
		aux = aux->sig;
	}
	return ret;
}


MultisetInt diferenciaConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt ret = crearMultisetInt();
	NodoListaIntDobleDato* aux = s1->lista;
	while (aux != NULL) {
		int diff = aux->dato2 - ocurrencias(s2, aux->dato1);
		if (diff > 0) {
			agregar(ret, aux->dato1, diff);
		}
		aux = aux->sig;
	}

	return ret;
}

bool contenidoEn(MultisetInt s1, MultisetInt s2) {
	NodoListaIntDobleDato* aux = s1->lista;
	bool ret = true;
	while (aux != NULL) {
		int diff = aux->dato2 - ocurrencias(s2, aux->dato1);
		if (diff > 0) {
			ret = false;
		}
		aux = aux->sig;
	}
	return ret;
}

int elemento(MultisetInt s) {
	return s->lista->dato1;

}

bool esVacio(MultisetInt s) {
	return s->lista == NULL;
}

unsigned int cantidadElementos(MultisetInt s) {
	return s->cantidadElementos;
}

void destruir(MultisetInt& s) {
	while (s->lista != NULL) {
		NodoListaIntDobleDato* borro = s->lista;
		s->lista = s->lista->sig;
		delete borro;
	}
	delete s;
}

MultisetInt clon(MultisetInt s) {
	MultisetInt ret = crearMultisetInt();
	NodoListaIntDobleDato* aux = s->lista;
	while (aux != NULL) {
		agregar(ret, aux->dato1, aux->dato2);
		aux = aux->sig;
	}
	return ret;
}

#endif