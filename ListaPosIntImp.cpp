#include "ListaPosInt.h"
#include "Definiciones.h"

#ifdef LISTA_POS_INT_IMP

struct _cabezalListaPosInt {
	int largoarreglo;
	int* arreglo;
};


//funciones del contrato

ListaPosInt crearListaPosInt()
{
	ListaPosInt lista = new _cabezalListaPosInt;
	lista->largoarreglo = 0;
	lista->arreglo = new int[lista->largoarreglo];
	return lista;
}

void agregar(ListaPosInt& l, int e, unsigned int pos)
{
	int* resizeado = new int[l->largoarreglo + 1];

	for (int i = 0; i < l->largoarreglo; i++) {
		resizeado[i] = l->arreglo[i];
	}

	if (pos >= l->largoarreglo) {
		resizeado[l->largoarreglo] = e;
	}
	else {
		for (int i = l->largoarreglo - 1; i >= pos; i--) {
			resizeado[i + 1] = resizeado[i];
		}
		resizeado[pos] = e;
	}

	l->arreglo = resizeado;
	l->largoarreglo++;
}

void borrar(ListaPosInt& l, unsigned int pos)
{
	if (pos < l->largoarreglo) {

		for (int i = pos; i < l->largoarreglo - 1; i++) {
			l->arreglo[i] = l->arreglo[i + 1];
		}

		int* resizeado = new int[l->largoarreglo - 1];
		for (int i = 0; i < l->largoarreglo - 1; i++) {
			resizeado[i] = l->arreglo[i];
		}

		l->arreglo = resizeado;
		l->largoarreglo--;
	}
}

int elemento(ListaPosInt l, unsigned int pos)
{
	return l->arreglo[pos];
}

bool esVacia(ListaPosInt l)
{
	return cantidadElementos(l) == 0;
}

unsigned int cantidadElementos(ListaPosInt l)
{
	return l->largoarreglo;
}

ListaPosInt clon(ListaPosInt l)
{
	ListaPosInt ret = new _cabezalListaPosInt;
	ret->largoarreglo = l->largoarreglo;
	ret->arreglo = new int[ret->largoarreglo];
	for (int i = 0; i < ret->largoarreglo; i++) {
		ret->arreglo[i] = l->arreglo[i];
	}
	return ret;
}

void destruir(ListaPosInt& l)
{
	delete[] l->arreglo;
	delete l;
}


#endif