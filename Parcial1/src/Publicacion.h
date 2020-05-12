#ifndef PUBLICACION_H_
#define PUBLICACION_H_

#define TEXTO_LEN 64


typedef struct
{
	int id;
	//char nombre[NOMBRE_LEN];
	char texto[TEXTO_LEN];
	int rubro; // Agregado
	int idCliente; // Agregado
	int estado;
	//char cuit[CUIT_LEN];
	int isEmpty;
}Publicacion;

#include "Cliente.h"

int pub_imprimir(Publicacion* auxProducto);
int pub_inicializarArray(Publicacion* array,int limite);
int pub_altaArray(Publicacion* array,int limite,Cliente* arrayClientes,int limiteClientes,int indice, int* id);
int pub_getEmptyIndex(Publicacion* array,int limite);
int pub_imprimirArray(Publicacion* array,int limite);
int pub_imprimirArrayConCuit(Publicacion* array,int limite, Cliente* arrayCliente,int limiteCliente);
int pub_imprimirArrayEnEstado(Publicacion* array,int limite,int estado);
int pub_buscarId(Publicacion array[], int limite, int valorBuscado);
int pub_buscarIdConEstado(Publicacion array[], int limite, int valorBuscado, int estado);
int pub_modificarArray(Publicacion* array,int limite, int indice);
int pub_bajaArray(Publicacion* array,int limite, int indice);
int pub_bajaArrayByIdCliente(Publicacion* array,int limite, int idCliente);
int pub_ordenarPorNombre(Publicacion* array,int limite);
int pub_altaForzadaArray(Publicacion* array,int limite,int indice, int* id, int idCliente, int rubro, char* texto);
int pub_imprimirArrayByIdCliente(Publicacion* array,int limite, int idCliente);
int pub_traducirEstado (char* pResultado,int limite,int valor);
int pub_pausarPublicacion(Publicacion* array,int limite, int indice);
int pub_activarPublicacion(Publicacion* array,int limite, int indice);
int pub_getIdCliente(Publicacion* array,int limite, int indice);

#endif /* PUBLICACION_H_ */
