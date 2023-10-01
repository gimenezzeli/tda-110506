#include "./src/lista.h"
#include "pa2m.h"
#include <stdlib.h>

void crear_lista()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Una lista creada es != NULL");
	pa2m_afirmar(lista_tamanio(lista) == 0, "La lista creada esta vacia");
	lista_destruir(lista);
}

void insertar_agranda_la_lista()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)0xbebecafe;
	lista_insertar(lista, e1);
	pa2m_afirmar(lista_tamanio(lista) == 1, "Puedo insertar un elemento.");
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "El tamaño de la lista es el correcto.");
	void *e2 = (void *)0xbebecaff;
	lista_insertar(lista, e2);
	void *e3 = (void *)0xbebecafa;
	lista_insertar(lista, e3);
	void *e4 = (void *)0xbebecafb;
	lista_insertar(lista, e4);
	void *e5 = (void *)0xbebecafc;
	lista_insertar(lista, e5);
	pa2m_afirmar(lista_tamanio(lista) == 5,
		     "Puedo insertar mas elementos.");
	pa2m_afirmar(lista_tamanio(lista) == 5,
		     "El tamaño de la lista es el correcto.");
	lista_destruir(lista);
}

void comprobar_posiciones()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)0xbebecafe;
	lista_insertar(lista, e1);
	void *e2 = (void *)0xbebecaff;
	lista_insertar(lista, e2);
	void *e3 = (void *)0xbebecafa;
	lista_insertar(lista, e3);
	void *e4 = (void *)0xbebecafb;
	lista_insertar(lista, e4);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 0) == e1,
		"La posicion del primer elemento de la lista es el correcto.");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == e2,
		     "La posicion del 2° elemento de la lista es el correcto.");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == e3,
		     "La posicion del 3° elemento de la lista es el correcto.");
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 3) == e4,
		"El ultimo elemento insertado esta en la posicion correcta.");
	lista_destruir(lista);
}

void insertar_en_lista_nula()
{
	lista_t *lista_nula = NULL;
	void *e1 = (void *)0xbeaecafe;
	lista_t *lista_nueva = lista_insertar(lista_nula, e1);
	pa2m_afirmar(lista_nueva == NULL,
		     "No inserta al final en una lista nula.");
	lista_t *lista_nueva2 = lista_insertar_en_posicion(lista_nula, e1, 10);
	pa2m_afirmar(lista_nueva2 == NULL,
		     "No inserta en ninguna posicion si es una lista nula.");
	lista_destruir(lista_nula);
}

void insertar_al_final()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)0xbebecafe;
	lista_insertar(lista, e1);
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == e1,
		     "El elemento insertado esta en la posicion correcta.");
	void *e2 = NULL;
	lista_insertar(lista, e2);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 1) == e2,
		"El elemento NULL insertado esta en la posicion correcta.");
	lista_insertar(lista, e1);
	pa2m_afirmar(lista_elemento_en_posicion(lista, 2) ==
			     lista_elemento_en_posicion(lista, 0),
		     "Puedo insertar un elemento repetido.");
	lista_destruir(lista);
}

void insertar_en_posicion()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)0xbebecafe;
	lista_insertar_en_posicion(lista, e1, 100);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 0) == e1,
		"El elemento insertado en la posicion 100 esta en la posicion correcta (al principio).");
	void *e2 = (void *)0xbebecafa;
	lista_insertar(lista, e2);
	void *e3 = (void *)0xbebecafb;
	lista_insertar(lista, e3);
	void *e4 = (void *)0xbebecafc;
	lista_insertar_en_posicion(lista, e4, 15);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 3) == e4,
		"El elemento insertado en la posicion 15 esta en la posicion correcta (al final).");
	lista_destruir(lista);
}

void eliminar_achica_la_lista()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)0xbebecafe;
	lista_insertar(lista, e1);
	void *e2 = (void *)0xbebecaff;
	lista_insertar(lista, e2);
	void *e3 = (void *)0xbebecafd;
	lista_insertar(lista, e3);
	void *e4 = (void *)0xbebecaef;
	lista_insertar(lista, e4);
	lista_quitar(lista);
	pa2m_afirmar(lista_tamanio(lista) == 3,
		     "Puedo eliminar un elemento de la lista.");
	pa2m_afirmar(lista_tamanio(lista) == 3,
		     "El tamaño de la lista se achica.");
	lista_quitar(lista);
	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "Puedo eliminar otro elemento de la lista.");
	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "El tamaño de la lista se achica.");
	lista_destruir(lista);
}

void eliminar_elementos()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)0xbebecafe;
	lista_insertar(lista, e1);
	void *e2 = (void *)0xbebecaff;
	lista_insertar(lista, e2);
	void *e3 = (void *)0xbebecafd;
	lista_insertar(lista, e3);
	void *e4 = (void *)0xbebecaef;
	lista_insertar(lista, e4);
	void *elemento_borrado1 = lista_quitar_de_posicion(lista, 1);
	pa2m_afirmar(elemento_borrado1 == e2,
		     "El elemento borrado de la posicion 1 es el correcto.");
	void *elemento_borrado2 = lista_quitar(lista);
	pa2m_afirmar(elemento_borrado2 == e4,
		     "El ultimo elemento borrado es el correcto.");
	lista_destruir(lista);
}

void quitar_elementos_de_lista_nula()
{
	lista_t *lista = NULL;
	void *elemento_borrado1 = lista_quitar(lista);
	void *elemento_borrado2 = lista_quitar_de_posicion(lista, 12);
	pa2m_afirmar(elemento_borrado1 == NULL,
		     "No puedo borrar el ultimo elemento de una lista nula.");
	pa2m_afirmar(
		elemento_borrado2 == NULL,
		"No puedo borrar un elemento de una posicion arbitraria de una lista nula.");
	lista_destruir(lista);
}

void quitar_elementos_de_lista_vacia()
{
	lista_t *lista = lista_crear();
	void *elemento_borrado1 = lista_quitar(lista);
	void *elemento_borrado2 = lista_quitar_de_posicion(lista, 12);
	pa2m_afirmar(elemento_borrado1 == NULL,
		     "No puedo borrar el ultimo elemento de una lista vacia.");
	pa2m_afirmar(
		elemento_borrado2 == NULL,
		"No puedo borrar un elemento de una posicion arbitraria de una lista vacia.");
	lista_destruir(lista);
}

void multiple_eliminacion()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)0xbebecafe;
	lista_insertar(lista, e1);
	void *e2 = (void *)0xbebecaff;
	lista_insertar(lista, e2);
	void *e3 = (void *)0xbebecafa;
	lista_insertar(lista, e3);
	void *e4 = (void *)0xbebecafb;
	lista_insertar(lista, e4);
	void *e5 = (void *)0xbebecafc;
	lista_insertar(lista, e5);
	lista_quitar(lista);
	lista_quitar(lista);
	lista_quitar(lista);
	lista_quitar(lista);
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "Se eliminaron varios elementos de la lista.");
	void *e6 = (void *)0xbebecaac;
	lista_insertar(lista, e6);
	void *elemento_borrado1 = lista_quitar_de_posicion(lista, 100);
	pa2m_afirmar(
		elemento_borrado1 == e6,
		"Se elimino el ultimo elemento de la lista cuando se le pasa una posicion inexistente.");
	void *e7 = NULL;
	lista_insertar(lista, e7);
	void *elemento_borrado2 = lista_quitar(lista);
	pa2m_afirmar(elemento_borrado2 == e7,
		     "Se elimino el elemento NULL de la lista.");
	lista_destruir(lista);
}

void obtener_elementos_lista_nula()
{
	lista_t *lista_nula = NULL;
	void *elemento1 = lista_elemento_en_posicion(lista_nula, 5);
	pa2m_afirmar(elemento1 == NULL,
		     "No se puede obtener un elemento de una lista nula.");
	lista_destruir(lista_nula);
}

void obtener_elementos_lista_vacia()
{
	lista_t *lista_vacia = lista_crear();
	void *elemento2 = lista_elemento_en_posicion(lista_vacia, 3);
	pa2m_afirmar(elemento2 == NULL,
		     "No se puede obtener un elemento de una lista vacia.");
	lista_destruir(lista_vacia);
}

void obtener_elementos()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)0xbebecaff;
	lista_insertar(lista, e1);
	void *e2 = (void *)0xbebecafa;
	lista_insertar(lista, e2);
	void *e3 = (void *)0xbebecafb;
	lista_insertar(lista, e3);
	void *e4 = (void *)0xbebecafc;
	lista_insertar(lista, e4);
	void *elemento1 = lista_elemento_en_posicion(lista, 10);
	pa2m_afirmar(
		elemento1 == NULL,
		"No se puede obtener un elemento de posicion inexistente.");
	void *elemento2 = lista_elemento_en_posicion(lista, 2);
	pa2m_afirmar(elemento2 == e3,
		     "El elemento en posicion 2 es el correcto.");
	lista_destruir(lista);
}

void conteo_lista_nula()
{
	lista_t *lista_nula = NULL;
	pa2m_afirmar(lista_tamanio(lista_nula) == 0,
		     "La cantidad de elementos de la lista nula es 0.");
	pa2m_afirmar(lista_vacia(lista_nula), "La lista nula esta vacia.");
	lista_destruir(lista_nula);
}

void conteo_lista_vacia()
{
	lista_t *lista = NULL;
	pa2m_afirmar(lista_tamanio(lista) == 0,
		     "La cantidad de elementos de la lista vacia es 0.");
	pa2m_afirmar(lista_vacia(lista), "La lista vacia esta vacia.");
	lista_destruir(lista);
}

void conteo_lista()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)0xbebecafe;
	lista_insertar(lista, e1);
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "El tamaño de la lista es el correcto.");
	void *e2 = (void *)0xbebecaff;
	lista_insertar(lista, e2);
	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "El tamaño de la lista es el correcto.");
	void *e3 = (void *)0xbebecafa;
	lista_insertar(lista, e3);
	pa2m_afirmar(lista_tamanio(lista) == 3,
		     "El tamaño de la lista es el correcto.");
	void *e4 = (void *)0xbebecafb;
	lista_insertar(lista, e4);
	pa2m_afirmar(lista_tamanio(lista) == 4,
		     "El tamaño de la lista es el correcto.");
	void *e5 = (void *)0xbebecafc;
	lista_insertar(lista, e5);
	pa2m_afirmar(lista_tamanio(lista) == 5,
		     "El tamaño de la lista es el correcto.");
	pa2m_afirmar(!lista_vacia(lista),
		     "Una lista con elementos no esta vacia");
	lista_destruir(lista);
}

int elemento_es_igual_a(void *_a, void *_b)
{
	void *a = _a;
	void *b = _b;

	if (a && b && a == b)
		return 0;

	return -1;
}

void buscar_en_lista_nula()
{
	lista_t *lista_nula = NULL;
	void *e1 = (void *)0xbebecafc;
	void *elemento2 =
		lista_buscar_elemento(lista_nula, elemento_es_igual_a, e1);
	pa2m_afirmar(elemento2 == NULL,
		     "No se puede buscar en una lista nula.");
	lista_destruir(lista_nula);
}

void buscar_en_lista_vacia()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)0xbebecafc;
	void *elemento1 = lista_buscar_elemento(lista, elemento_es_igual_a, e1);
	pa2m_afirmar(elemento1 == NULL,
		     "No se puede buscar en una lista vacia.");
	lista_destruir(lista);
}

void buscar_lista_comparador_nulo()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)0xbebecafc;
	lista_insertar(lista, e1);
	void *e2 = (void *)0xbebecaec;
	lista_insertar(lista, e2);
	void *e3 = (void *)0xbebecabc;
	lista_insertar(lista, e3);
	void *elemento1 = lista_buscar_elemento(lista, NULL, e1);
	pa2m_afirmar(elemento1 == NULL, "No puedo buscar con comparador nulo.");
	lista_destruir(lista);
}

void buscar_lista_contexto_nulo()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)0xbebecafc;
	lista_insertar(lista, e1);
	void *e2 = (void *)0xbebecaec;
	lista_insertar(lista, e2);
	void *e3 = (void *)0xbebecabc;
	lista_insertar(lista, e3);
	void *elemento1 =
		lista_buscar_elemento(lista, elemento_es_igual_a, NULL);
	pa2m_afirmar(elemento1 == NULL, "No puedo buscar con contexto nulo.");
	lista_destruir(lista);
}

void buscar_lista_elemento_no_existente()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)0xbebecafc;
	lista_insertar(lista, e1);
	void *e2 = (void *)0xbebecaec;
	lista_insertar(lista, e2);
	void *e3 = (void *)0xbebecabc;
	lista_insertar(lista, e3);
	void *e4 = (void *)0xbebecebc;
	void *elemento1 = lista_buscar_elemento(lista, elemento_es_igual_a, e4);
	pa2m_afirmar(elemento1 == NULL,
		     "No se puede buscar un elemento inexistente.");
	lista_destruir(lista);
}

void buscar_lista_elemento()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)'A';
	lista_insertar(lista, e1);
	void *e2 = (void *)'B';
	lista_insertar(lista, e2);
	void *e3 = (void *)'C';
	lista_insertar(lista, e3);
	void *elemento1 = lista_buscar_elemento(lista, elemento_es_igual_a, e3);
	pa2m_afirmar(elemento1 == e3, "El elemento buscado es el correcto.");
	lista_destruir(lista);
}

void buscar_lista_elemento_duplicado()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)'A';
	lista_insertar(lista, e1);
	lista_insertar(lista, e1);
	void *e2 = (void *)'B';
	lista_insertar(lista, e2);
	void *elemento1 = lista_buscar_elemento(lista, elemento_es_igual_a, e1);
	pa2m_afirmar(elemento1 == e1, "Se puede buscar un elemento repetido.");
	lista_destruir(lista);
}

void buscar_primer_elemento_en_lista_nula()
{
	lista_t *lista_nula = NULL;
	void *elemento = lista_primero(lista_nula);
	pa2m_afirmar(
		elemento == NULL,
		"No se puede obtener el primer elemento de una lista nula.");
	lista_destruir(lista_nula);
}

void buscar_ultimo_elemento_en_lista_nula()
{
	lista_t *lista_nula = NULL;
	void *elemento = lista_elemento_en_posicion(
		lista_nula, lista_tamanio(lista_nula) - 1);
	pa2m_afirmar(
		elemento == NULL,
		"No se puede obtener el ultimo elemento de una lista nula.");
	lista_destruir(lista_nula);
}

void buscar_primer_elemento_en_lista_vacia()
{
	lista_t *lista = lista_crear();
	void *elemento = lista_primero(lista);
	pa2m_afirmar(
		elemento == NULL,
		"No se puede obtener el primer elemento de una lista vacia.");
	lista_destruir(lista);
}

void buscar_ultimo_elemento_en_lista_vacia()
{
	lista_t *lista = lista_crear();
	void *elemento =
		lista_elemento_en_posicion(lista, lista_tamanio(lista) - 1);
	pa2m_afirmar(
		elemento == NULL,
		"No se puede obtener el ultimo elemento de una lista vacia.");
	lista_destruir(lista);
}

void buscar_primer_elemento()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)'A';
	lista_insertar(lista, e1);
	void *e2 = (void *)'B';
	lista_insertar(lista, e2);
	void *e3 = (void *)'C';
	lista_insertar(lista, e3);
	void *elemento = lista_primero(lista);
	pa2m_afirmar(elemento == e1,
		     "El elemento de la primer posicion es el correcto.");
	lista_destruir(lista);
}

void buscar_ultimo_elemento()
{
	lista_t *lista = lista_crear();
	void *e1 = (void *)'A';
	lista_insertar(lista, e1);
	void *e2 = (void *)'B';
	lista_insertar(lista, e2);
	void *e3 = (void *)'C';
	lista_insertar(lista, e3);
	void *elemento =
		lista_elemento_en_posicion(lista, lista_tamanio(lista) - 1);
	pa2m_afirmar(elemento == e3,
		     "El elemento de la ultima posicion es el correcto.");
	lista_destruir(lista);
}

void pruebas_de_primero_y_ultimo()
{
	buscar_primer_elemento_en_lista_nula();
	buscar_ultimo_elemento_en_lista_nula();
	buscar_primer_elemento_en_lista_vacia();
	buscar_ultimo_elemento();
	buscar_primer_elemento();
	buscar_ultimo_elemento();
}

void iteradores()
{
	lista_iterador_t *it = NULL;
	pa2m_afirmar(it == NULL, "Se puede crear un iterador nulo.");
	lista_iterador_destruir(it);
}

void pruebas_de_insertar()
{
	insertar_agranda_la_lista();
	printf("\n");
	insertar_al_final();
	printf("\n");
	comprobar_posiciones();
	printf("\n");
	insertar_en_lista_nula();
	printf("\n");
	insertar_en_posicion();
}

void pruebas_de_eliminar()
{
	eliminar_achica_la_lista();
	printf("\n");
	eliminar_elementos();
	printf("\n");
	quitar_elementos_de_lista_nula();
	printf("\n");
	quitar_elementos_de_lista_vacia();
	printf("\n");
	multiple_eliminacion();
}

void pruebas_de_obtencion()
{
	obtener_elementos_lista_nula();
	printf("\n");
	obtener_elementos_lista_vacia();
	printf("\n");
	obtener_elementos();
}

void pruebas_de_cantidad()
{
	conteo_lista_nula();
	conteo_lista_vacia();
	printf("\n");
	conteo_lista();
}

void pruebas_de_buscar()
{
	buscar_en_lista_nula();
	buscar_en_lista_vacia();
	buscar_lista_comparador_nulo();
	buscar_lista_contexto_nulo();
	buscar_lista_elemento_no_existente();
	buscar_lista_elemento();
	buscar_lista_elemento_duplicado();
	printf("\n");
	pruebas_de_primero_y_ultimo();
}

void destruir_lista()
{
	lista_t *lista = lista_crear();

	lista_insertar(lista, malloc(sizeof(int)));
	lista_insertar(lista, malloc(sizeof(int)));
	lista_insertar(lista, malloc(sizeof(int)));
	lista_insertar(lista, malloc(sizeof(int)));
	lista_insertar(lista, malloc(sizeof(int)));

	lista_destruir_todo(lista, free);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== MIS PRUEBAS ========================");

	pa2m_nuevo_grupo("\nPruebas de crear");
	crear_lista();
	pa2m_nuevo_grupo("\nPruebas de insertar");
	pruebas_de_insertar();
	pa2m_nuevo_grupo("\nPruebas de eliminar");
	pruebas_de_eliminar();
	pa2m_nuevo_grupo("\nPruebas de obtencion");
	pruebas_de_obtencion();
	pa2m_nuevo_grupo("\nPruebas de cantidad");
	pruebas_de_cantidad();
	pa2m_nuevo_grupo("\nPruebas de buscar");
	pruebas_de_buscar();
	destruir_lista();

	return pa2m_mostrar_reporte();
}
