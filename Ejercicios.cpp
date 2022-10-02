#include "Ejercicios.h"

/*AUXILIARES*/

//PRE: Recibe un árbol y una lista
//POS: agrega los elementos del árbol a la lista, si tiene alguno
void aplanar(NodoABInt* a, ListaOrdInt&l) {
	if (a != NULL) {
		aplanar(a->izq, l);
		agregar(l, a->dato);
		aplanar(a->der, l);
	}
}

ListaOrdInt Enlistar(NodoABInt* a)
{
	ListaOrdInt ret = crearListaOrdInt();
	aplanar(a, ret);
	return ret;
}

ListaOrdInt UnionListaOrd(ListaOrdInt l1, ListaOrdInt l2)
{
	ListaOrdInt ret = crearListaOrdInt();
	ListaOrdInt clon1 = clon(l1);
	ListaOrdInt clon2 = clon(l2);
	while (!esVacia(clon1) && !esVacia(clon2)) {
		int min1 = minimo(clon1);
		int min2 = minimo(clon2);
		int agrego;
		if (min1 > min2) {
			agrego = min1;
			borrar(clon1, min1);
		}
		else {
			agrego = min2;
			borrar(clon2, min2);
		}
		agregar(ret, agrego);
	}

	while (!esVacia(clon1)) {
		int min = minimo(clon1);
		agregar(ret, min);
		borrar(clon1, min);
	}

	while (!esVacia(clon2)) {
		int min = minimo(clon2);
		agregar(ret, min);
		borrar(clon2, min);
	}

	destruir(clon1);
	destruir(clon2);
	return ret;
}

bool EstaContenida(PilaInt p1, PilaInt p2)
{
	PilaInt clon1 = clon(p1);
	PilaInt clon2 = clon(p2);
	ListaOrdInt l1 = crearListaOrdInt();
	ListaOrdInt l2 = crearListaOrdInt();
	bool ret = true;

	while (!esVacia(clon1)) {
		agregar(l1, top(clon1));
		pop(clon1);
	}

	while (!esVacia(clon2)) {
		agregar(l2, top(clon2));
		pop(clon2);
	}
	
	while (!esVacia(l1) && ret) {
		int min = minimo(l1);
		if (!existe(l2, min)) {
			ret = false;
		}
		else {
			borrar(l1, min);
			borrar(l2, min);
		}
	}
	destruir(clon1);
	destruir(clon2);
	destruir(l1);
	destruir(l2);
	return ret;
}


ListaOrdInt ObtenerRepetidos(MultisetInt m) 
{
	ListaOrdInt l = crearListaOrdInt();
	MultisetInt clon1 = clon(m);

	while (!esVacio(clon1)) {
		int agrego = elemento(clon1);
		borrar(clon1, elemento(clon1));
		if (pertenece(clon1, agrego) && !existe(l, agrego)) {
			agregar(l, agrego);
		}
	}
	destruir(clon1);
	return l;
}

MultisetInt Xor(MultisetInt m1, MultisetInt m2)
{
	MultisetInt clon1 = clon(m1);
	MultisetInt clon2 = clon(m2);
	MultisetInt ret = crearMultisetInt();

	while (!esVacio(clon1)) {
		int elem = elemento(clon1);
		if (!pertenece(clon2, elem)) {
			agregar(ret, elem, 1);
		}
		else {
			borrar(clon2, elem);
		}
		borrar(clon1, elem);
	}

	while (!esVacio(clon2)) {
		int elem = elemento(clon2);
		if (!pertenece(clon1, elem)) {
			agregar(ret, elem, 1);
		}
		else {
			borrar(clon1, elem);
		}
		borrar(clon2, elem);
	}
	destruir(clon1);
	destruir(clon2);
	return ret;
}

ColaPrioridadInt MenorPrioridad(ColaPrioridadInt c) {


	ColaPrioridadInt clon1 = clon(c);
	int menorPrioridad = INT_MAX;

	//Encuentro la menor prioridad
	while (!esVacia(clon1)) {
		if (menorPrioridad > principioPrioridad(clon1)) menorPrioridad = principioPrioridad(clon1);
		desencolar(clon1);
	}

	//Desencolo hasta tener los elementos con la menor prioridad
	ColaPrioridadInt clon2 = clon(c);
	while (!esVacia(clon2) && principioPrioridad(clon2) != menorPrioridad) {
		desencolar(clon2);
	}

	int cantidadRet = cantidadElementos(clon2);

	//creo retorno con cota elementos con menor prioridad
	ColaPrioridadInt ret = crearColaPrioridadInt(cantidadRet);
	//los encolo
	while (!esVacia(clon2)) {
		encolar(ret, principio(clon2), principioPrioridad(clon2));
		desencolar(clon2);
	}

	destruir(clon1);
	destruir(clon2);

	return ret;

}

