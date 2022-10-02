#include "ListaOrdInt.h"
#include "Definiciones.h"

#ifdef LISTA_ORD_INT_IMP_2

struct _cabezalListaOrdInt {
	NodoABIntDobleDato* A;
	int cantidadElementos;
};

/*AUXILIARES*/

//PRE: -
//POS: agrega una ocurrencia del entero e al árbol binario A
void agregarRec(NodoABIntDobleDato*& A, int e) {

	if (!A) {
		NodoABIntDobleDato* nuevo = new NodoABIntDobleDato;
		nuevo->dato1 = e;
		nuevo->dato2 = 1;
		A = nuevo;
	}
	else {
		if (A->dato1 == e) {
			A->dato2++;
		}
		else if (A->dato1 < e) {
			agregarRec(A->der, e);
		}
		else {
			agregarRec(A->izq, e);
		}
	}

}

//PRE: -
//POS: Devuelve true sii el entero e pertenece al árbol A
bool existeRec(NodoABIntDobleDato* A, int e) {
	if (!A) {
		return false;
	}
	else {
		if (A->dato1 == e) {
			return true;
		}
		else if (A->dato1 > e) {
			return existeRec(A->izq, e);
		}
		else {
			return existeRec(A->der, e);
		}

	}
}

//PRE: -
//POS: Devuelve un clon del árbol parámetro sin compartir memoria
NodoABIntDobleDato* clonarArbol(NodoABIntDobleDato* A)
{
	if (A == NULL) {
		return NULL;
	}

	NodoABIntDobleDato* nuevo = new NodoABIntDobleDato;
	nuevo->dato1 = A->dato1;
	nuevo->dato2 = A->dato2;

	nuevo->izq = clonarArbol(A->izq);
	nuevo->der = clonarArbol(A->der);

	return nuevo;
}


//PRE: - 
//POS: Destruye el árbol borrando todos los nodos
void destruirRec(NodoABIntDobleDato*& A) {
	if (A && A->izq && A->der) {
		destruirRec(A->izq);
		destruirRec(A->der);
	}
	else if (A && A->izq) {
		destruirRec(A->izq);
	}
	else if (A && A->der) {
		destruirRec(A->der);
	}
	delete A;
}

//PRE: Recibe un ábol binario no vacío
//POS: Retorna el menor entero perteneciente al árbol
int minimoAux(NodoABIntDobleDato* A) {
	while (A->izq != NULL) {
		A = A->izq;
	}
	return A->dato1;
}

//PRE: Recibe un ábol binario no vacío
//POS: Retorna las ocurrencias del menor entero perteneciente al arbol
int ocurrenciasMinAux(NodoABIntDobleDato* A) {
	while (A->izq != NULL) {
		A = A->izq;
	}
	return A->dato2;
}



//PRE: -
//POS: Elimina una ocurrencia del árbol binario de búsqueda
void eliminar(int borro, NodoABIntDobleDato*& A);

//PRE: El elemento pertenece al arbol, y es el minimo (a->izq == NULL)
//POS: Elimina una ocurrencia del árbol binario de búsqueda
void eliminarTodasLasOcurrencias(NodoABIntDobleDato*& A, int e) {
	if (A) {
		if (e > A->dato1) {
			eliminar(e, A->der);
		}
		else if (e < A->dato1) {
			eliminar(e, A->izq);
		}
		else if (e == A->dato1) {	
			NodoABIntDobleDato* borro = A;
			A = A->der;
			delete borro;
				
		}
	}
}


//PRE: Recibe un árbol binario no vacío, con A->der, A->izq != NULL
//POS: Elimina el nodo raiz del árbol
void borrarNodoRaiz(NodoABIntDobleDato*& A) {

	int elemNuevaRaiz = minimoAux(A->der);
	int ocurrencias = ocurrenciasMinAux(A->der);
	eliminarTodasLasOcurrencias(A->der, elemNuevaRaiz);
	A->dato1 = elemNuevaRaiz;
	A->dato2 = ocurrencias;

}

void eliminar(int borro, NodoABIntDobleDato*& A) {
	if (A) {
		if (borro > A->dato1) {
			eliminar(borro, A->der);
		}
		else if (borro < A->dato1) {
			eliminar(borro, A->izq);
		}
		else if (borro == A->dato1) {
			if (A->dato2 > 1) {
				A->dato2--;
			}
			else {
				if (A->der == NULL) {
					NodoABIntDobleDato* borro = A;
					A = NULL;
					delete borro;
				}
				else if (A->izq == NULL) {
					NodoABIntDobleDato* borro = A;
					A = A->der;
					delete borro;
				}
				else {
					borrarNodoRaiz(A);
				}
			}
		}
	}
}

/*FUNCIONES DEL CONTRATO*/

ListaOrdInt crearListaOrdInt() {
	_cabezalListaOrdInt* lista = new _cabezalListaOrdInt;
	lista->A = NULL;
	lista->cantidadElementos = 0;
	return lista;
}

void agregar(ListaOrdInt& l, int e) {
	agregarRec(l->A, e);
	l->cantidadElementos++;
}

void borrarMinimo(ListaOrdInt& l) {
	if (l && l->A) {
		int min = minimo(l);
		borrar(l, min);
	}
}

void borrarMaximo(ListaOrdInt& l) {
	if (l && l->A) {
		int max = maximo(l);
		borrar(l, max);
	}
}

void borrar(ListaOrdInt& l, int e) {
	if (l && l->A) {
		if (existe(l, e)) {
			eliminar(e, l->A);
			l->cantidadElementos--;
		}
	}
}

int minimo(ListaOrdInt l) {
	if (l) {
		NodoABIntDobleDato* aux = l->A;
		while (aux != NULL && aux->izq != NULL) {
			aux = aux->izq;
		}
		return aux->dato1;
	}
}

int maximo(ListaOrdInt l) {
	NodoABIntDobleDato* aux = l->A;
	while (aux != NULL && aux->der != NULL) {
		aux = aux->der;
	}
	return aux->dato1;
}

bool existe(ListaOrdInt l, int e) {
	if (l == NULL) {
		return false;
	}
	return existeRec(l->A, e);
}

bool esVacia(ListaOrdInt l) {
	return l->A == NULL;
}

unsigned int cantidadElementos(ListaOrdInt l) {
	return l->cantidadElementos;
}

ListaOrdInt clon(ListaOrdInt l) {
	ListaOrdInt ret = new _cabezalListaOrdInt;
	ret->cantidadElementos = l->cantidadElementos;
	ret->A = clonarArbol(l->A);
	return ret;
}

void destruir(ListaOrdInt& l) {
	destruirRec(l->A);
	delete l;
}


#endif