#include "TablaIntString.h"
#include "Definiciones.h"

#ifdef TABLA_INT_STRING_IMP

struct NodoIntString {
	int d;
	const char* string;
	NodoIntString* sig;
};

struct _cabezalTablaIntString {
	NodoIntString** tabla;
	int esperados;
	int elementos;
};

//funcion de hash

int fHashString(unsigned int i, int esperados) {
	return i % esperados;
}

/*AUXILIARES*/

//PRE: -
//POS: Si el elemento pertenece a la lista, lo borra
void borrarDeLista(NodoIntString*& l, int e) {
	NodoIntString* aux = l;
	if (aux != NULL) {
		if (aux->d == e) {
			l = l->sig;
			delete aux;
			return;
		}
		while (aux->sig != NULL) {
			if (aux->sig->d == e) {
				aux->sig = aux->sig->sig;
				return;
			}
			aux = aux->sig;
		}


	}
}

//PRE: -
//POS: Devuelve true sii el elemento pertenece a la tablaIntString
bool pertenece(TablaIntString s, int e) {
	bool ret = false;
	NodoIntString* aux = s->tabla[fHashString(e, s->esperados)];
	while (aux != NULL && !ret) {
		if (aux->d == e) {
			ret = true;
		}
		aux = aux->sig;
	}
	return ret;
}

//PRE: - 
//POS: Borra la lista
void borrarLista(NodoIntString*& l) {
	if (l != NULL) {
		borrarLista(l->sig);
		delete l;
	}
}

//PRE: - 
//POS: Devuelve una lista clon de la lista parámetro, sin compartir memoria
NodoIntString* clonarLista(NodoIntString* l) {
	if (l != NULL) {
		NodoIntString* ret = new NodoIntString;
		ret->d = l->d;
		ret->string = l->string;
		ret->sig = clonarLista(l->sig);
		return ret;
	}
	else {
		return NULL;
	}
}

//PRE: - 
//POS: Devuelve el largo del string parámetro
int length(const char* string) {
	int largo = 0;
	int i = 0;

	while (string[i] != '\0') {
		largo++;
		i++;
	}
	return(largo);
}


/*FUNCIONES DEL CONTRATO*/

TablaIntString crearTablaIntString(unsigned int esperados) {
	TablaIntString tabla = new _cabezalTablaIntString;
	tabla->elementos = 0;
	tabla->esperados = esperados;
	tabla->tabla = new NodoIntString * [esperados];
	for (int i = 0; i < esperados; i++) {
		tabla->tabla[i] = NULL;
	}
	return tabla;
}

void agregarPrincipioIntString(NodoIntString*& n, int d, const char* r) {
	NodoIntString* nuevo = new NodoIntString;
	nuevo->d = d;
	nuevo->string = r;
	nuevo->sig = n;
	n = nuevo;
}

void agregar(TablaIntString& t, int d, const char* r) {

	if (t->tabla[fHashString(d, t->esperados)] == NULL) {
		agregarPrincipioIntString(t->tabla[fHashString(d, t->esperados)], d, r);
		t->elementos++;
		return;
	}

	NodoIntString* aux = t->tabla[fHashString(d, t->esperados)];
	while (aux != NULL) {
		if (aux->d == d) {
			aux->string = r;
			return;
		}
		aux = aux->sig;
	}

	agregarPrincipioIntString(t->tabla[fHashString(d, t->esperados)], d, r);
	t->elementos++;
}

bool estaDefinida(TablaIntString t, int d) {
	NodoIntString* aux = t->tabla[fHashString(d, t->esperados)];

	while (aux != NULL) {
		if (aux->d == d) {
			return aux->string != NULL;
		}
		aux = aux->sig;
	}
	return false;
}

char* recuperar(TablaIntString t, int d) {

	NodoIntString* aux = t->tabla[fHashString(d, t->esperados)];

	char* vacio = new char[1];
	vacio[0] = '\0';

	while (aux != NULL) {
		if (aux->d == d) {
			int largo = length(aux->string) + 1;
			char* ret = new char[largo];
			for (int i = 0; aux->string[i] != '\0'; i++) {
				ret[i] = aux->string[i];
			}
			ret[largo-1] = '\0';
			delete[] vacio;
			return ret;
		}
		aux = aux->sig;
	}
	
	return vacio;

	
}

void borrar(TablaIntString& t, int d) {
	if (pertenece(t, d)) {
		borrarDeLista(t->tabla[fHashString(d, t->esperados)], d);
		t->elementos--;
	}
}

int elemento(TablaIntString t) {
	for (int i = 0; i < t->esperados; i++) {
		if (t->tabla[i] != NULL) {
			return t->tabla[i]->d;
		}
	}
}

bool esVacia(TablaIntString t) {
	bool ret = true;
	for (int i = 0; i < t->esperados; i++) {
		if (t->tabla[i] != NULL) ret = false;
	}
	return ret;
}

unsigned int cantidadElementos(TablaIntString t) {
	return t->elementos;
}

void destruir(TablaIntString& t) {
	for (int i = 0; i < t->esperados; i++) {
		borrarLista(t->tabla[i]);
	}
	delete t;
}

TablaIntString clon(TablaIntString t) {
	TablaIntString clon = crearTablaIntString(t->esperados);
	clon->elementos = t->elementos;
	for (int i = 0; i < clon->esperados; i++) {
		clon->tabla[i] = clonarLista(t->tabla[i]);
	}
	return clon;
}

#endif