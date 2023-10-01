#include "lista.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
const int CERO = 0;
const size_t UNO = 1;

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio; //apunta al primer nodo
	nodo_t *nodo_fin; //apunta al ultimo nodo
	int cantidad;
};

struct lista_iterador {
	lista_t *lista;
	nodo_t *nodo_actual;
};

lista_t *lista_crear()
{
	lista_t *nueva_lista = malloc(sizeof(lista_t));
	if (!nueva_lista) {
		free(nueva_lista);
		return NULL;
	}
	nueva_lista->cantidad = 0;
	nueva_lista->nodo_inicio = NULL;

	return nueva_lista;
}

nodo_t *crear_nodo(void *elemento)
{
	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));

	if (!nuevo_nodo) {
		free(nuevo_nodo);
		return NULL;
	}

	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = NULL;

	return nuevo_nodo;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista)
		return NULL;

	nodo_t *nodo_nuevo = crear_nodo(elemento);
	if (!nodo_nuevo)
		return NULL;

	if (lista_vacia(lista)) {
		lista->nodo_inicio = nodo_nuevo;
		lista->nodo_fin = nodo_nuevo;
		lista->cantidad++;
		return lista;
	} else {
		lista->nodo_fin->siguiente = nodo_nuevo;
		lista->nodo_fin = nodo_nuevo;
	}

	lista->cantidad++;

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (!lista)
		return NULL;

	if (lista_tamanio(lista) == CERO || posicion >= lista_tamanio(lista))
		return lista_insertar(lista, elemento);

	nodo_t *nodo_nuevo = crear_nodo(elemento);
	nodo_t *nodo_actual = lista->nodo_inicio;
	int contador = 0;

	if (posicion == CERO) {
		nodo_nuevo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_nuevo;
		lista->cantidad++;
		return lista;
	}

	while (nodo_actual->siguiente != NULL) {
		if (contador == posicion - UNO) {
			nodo_nuevo->siguiente = nodo_actual->siguiente;
			nodo_actual->siguiente = nodo_nuevo;
		}
		nodo_actual = nodo_actual->siguiente;
		contador++;
	}

	lista->cantidad++;
	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (!lista || lista_tamanio(lista) == CERO)
		return NULL;

	nodo_t *nodo_actual = lista->nodo_inicio;
	nodo_t *nodo_viejo = NULL;
	void *elemento = nodo_actual->elemento;

	//Caso especial: eliminar el unico elemento
	if (lista_tamanio(lista) == UNO) {
		free(nodo_actual);
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
		lista->cantidad--;
		free(nodo_viejo);

		return elemento;
	}
	// Recorre la lista hasta llegar al penúltimo nodo
	while (nodo_actual->siguiente != NULL) {
		nodo_viejo = nodo_actual;
		nodo_actual = nodo_actual->siguiente;
	}
	// Desconecta el último nodo de la lista y me guardo el elemento antes de eliminarlo
	elemento = nodo_actual->elemento;
	nodo_viejo->siguiente = NULL;
	lista->nodo_fin = nodo_viejo;

	//Libero el nodo y reduzco el tamaño de la lista
	free(nodo_actual);
	lista->cantidad--;

	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_tamanio(lista) == CERO)
		return NULL;

	nodo_t *nodo_actual = lista->nodo_inicio;
	void *elemento = nodo_actual->elemento;
	nodo_t *nodo_viejo = NULL;
	int contador = CERO;

	//Caso especial: eliminar el primer nodo
	if (posicion == CERO) {
		lista->nodo_inicio = nodo_actual->siguiente;
		free(nodo_actual);
		free(nodo_viejo);
		lista->cantidad--;
		return elemento;
	}
	//Caso especial: la posicion es mayor al tamaño de la lista, debo eliminar el ultimo
	if (posicion >= lista_tamanio(lista)) {
		elemento = lista_quitar(lista);
		return elemento;
	}

	//Recorrer la lista hasta el nodo anterior al que se va a eliminar
	while (nodo_actual->siguiente != NULL && contador < posicion) {
		nodo_viejo = nodo_actual;
		nodo_actual = nodo_actual->siguiente;
		contador++;
	}
	//Me guardo el elemento antes de borrarlo
	elemento = nodo_actual->elemento;

	//Actualizar el puntero del nodo anterior
	nodo_viejo->siguiente = nodo_actual->siguiente;
	nodo_actual->siguiente = NULL;

	//Libero el nodo y reduzco el tamaño de la lista
	free(nodo_actual);
	lista->cantidad--;

	return elemento;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_tamanio(lista) <= posicion)
		return NULL;

	nodo_t *nodo_actual = lista->nodo_inicio;
	int contador = 0;

	while (contador < posicion) {
		nodo_actual = nodo_actual->siguiente;
		contador++;
	}
	return nodo_actual->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (!lista || !comparador || lista_tamanio(lista) == CERO)
		return NULL;

	nodo_t *nodo_actual = lista->nodo_inicio;

	while (nodo_actual != NULL) {
		if (comparador(nodo_actual->elemento, contexto) == CERO) {
			return nodo_actual->elemento;
		} else {
			nodo_actual = nodo_actual->siguiente;
		}
	}

	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if (lista == NULL || lista_tamanio(lista) == CERO)
		return NULL;

	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if (!lista || lista_tamanio(lista) == CERO)
		return NULL;

	return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista)
{
	return !lista || lista_tamanio(lista) == CERO;
}

size_t lista_tamanio(lista_t *lista)
{
	if (!lista)
		return 0;

	return (size_t)lista->cantidad;
}

void lista_destruir(lista_t *lista)
{
	lista_destruir_todo(lista, NULL);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (!lista)
		return;

	nodo_t *actual = lista->nodo_inicio;

	while (actual != NULL) {
		nodo_t *proximo = actual->siguiente;
		if (funcion != NULL)
			funcion(actual->elemento);
		free(actual);
		actual = proximo;
	}
	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista)
		return NULL;

	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if (!iterador)
		return NULL;

	iterador->lista = lista;
	iterador->nodo_actual = lista->nodo_inicio;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if (!iterador)
		return false;

	return iterador->nodo_actual != NULL;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->nodo_actual)
		return false;

	iterador->nodo_actual = iterador->nodo_actual->siguiente;

	return lista_iterador_tiene_siguiente(iterador);
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->nodo_actual)
		return NULL;

	return iterador->nodo_actual->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (!lista || !funcion)
		return 0;

	size_t contador = 0;
	nodo_t *nodo_actual = lista->nodo_inicio;

	while (nodo_actual != NULL) {
		contador++;
		if (funcion(nodo_actual->elemento, contexto) == false)
			return contador;
		nodo_actual = nodo_actual->siguiente;
	}
	return contador;
}
