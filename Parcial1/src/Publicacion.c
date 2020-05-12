#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Publicacion.h"
#include "Cliente.h"

#define STRINGESTADO_LEN 10

/**
 * \brief Imprime los datos de un publicacion
 * \param pElemento Puntero al producto que se busca imprimir
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_imprimir(Publicacion* pElemento)
{
	int retorno=-1;
	char auxiliarStringEstado[STRINGESTADO_LEN];

	if(pElemento != NULL && pElemento->isEmpty == 0)
	{
		retorno=0;
		pub_traducirEstado(auxiliarStringEstado, STRINGESTADO_LEN, pElemento->estado);
		printf("\nPUBLICACION ID: %d - TEXTO: %s - RUBRO: %d - ID CLIENTE: %d - ESTADO: %s",pElemento->id,pElemento->texto,pElemento->rubro,pElemento->idCliente,auxiliarStringEstado);
	}
	return retorno;
}

/**
 * \brief Imprime el array de publicaciones
 * \param array Array de publicaciones a ser actualizado
 * \param limite Limite del array de publicaciones
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_imprimirArray(Publicacion* array,int limite)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		respuesta = 0;
		for(i=0;i<limite;i++)
		{
			pub_imprimir(&array[i]);
		}
		printf ("\n");
	}
	return respuesta;
}

/**
 * \brief Imprime el array de publicaciones
 * \param array Array de publicaciones a ser actualizado
 * \param limite Limite del array de publicaciones
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_imprimirArrayConCuit(Publicacion* array,int limite, Cliente* arrayCliente,int limiteCliente)
{
	int respuesta = -1;
	int i;
	char auxiliarStringEstado[STRINGESTADO_LEN];

	if(array != NULL && limite > 0)
	{
		respuesta = 0;
		for(i=0;i<limite;i++)
		{
			if (array[i].isEmpty == 0)
			{
				pub_traducirEstado(auxiliarStringEstado, STRINGESTADO_LEN, array[i].estado);
				printf("\nPUBLICACION ID: %d - TEXTO: %s - RUBRO: %d - ID CLIENTE: %d - CUIT CLIENTE: %s - ESTADO: %s",array[i].id,array[i].texto,array[i].rubro,array[i].idCliente,arrayCliente[array[i].idCliente].cuit,auxiliarStringEstado);
			}
		}
		printf ("\n");
	}
	return respuesta;
}

/**
 * \brief Imprime el array de publicaciones con un estado especifico
 * \param array Array de publicaciones a ser actualizado
 * \param limite Limite del array de publicaciones
 * \param estado 0 o 1 cual imprimir
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_imprimirArrayEnEstado(Publicacion* array,int limite,int estado)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(array[i].estado == estado && array[i].isEmpty == 0)
			{
				pub_imprimir(&array[i]);
				respuesta = 0;
			}
		}
		printf ("\n");
	}
	return respuesta;
}
/**
 * \brief Inicializa el array
 * \param array Array de publicaciones a ser actualizado
 * \param limite Limite del array de publicaciones
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_inicializarArray(Publicacion* array,int limite)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		respuesta = 0;
		for(i=0;i<limite;i++)
		{
			array[i].isEmpty = 1;
		}
	}
	return respuesta;
}

/**
 * \brief Da de alta un publicacion en una posicion del array
 * \param array Array de publicaciones a ser actualizado
 * \param limite Limite del array de publicaciones
 * \param indice Posicion a ser actualizada
 * \param id Identificador a ser asignado al publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_altaArray(Publicacion* array,int limite,Cliente* arrayClientes,int limiteClientes,int indice, int* id)
{
	int respuesta = -1;
	Publicacion bufferPublicacion;

	if(array != NULL && limite > 0 && indice < limite && indice >= 0 && id != NULL)
	{
		if(	!cli_imprimirArray(arrayClientes, limiteClientes) &&
			!utn_getNumero(&bufferPublicacion.idCliente,"\nIngrese el numero ID Cliente: ","\nERROR\n",0,1000,2) &&
			cli_buscarId(arrayClientes, limiteClientes, bufferPublicacion.idCliente) >= 0 &&
			!utn_getNumero(&bufferPublicacion.rubro,"\nIngrese el numero de Rubro: ","\nERROR\n",1,1000,2) &&
			!utn_getDescripcion(bufferPublicacion.texto,TEXTO_LEN,"\nIngrese el Texto de la Publiacion: ","\nERROR\n",2))
		{
			respuesta = 0;
			bufferPublicacion.id = *id;
			bufferPublicacion.isEmpty = 0;
			bufferPublicacion.estado = 1;
			array[indice] = bufferPublicacion;
			(*id)++;
		}
		else
		{
			printf ("\nEl Cliente no existe!");
		}

	}
	return respuesta;
}
/**
 * \brief Actualiza los datos de un publicacion en una posicion del array
 * \param array Array de publicaciones a ser actualizado
 * \param limite Limite del array de publicaciones
 * \param indice Posicion a ser actualizada
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_modificarArray(Publicacion* array,int limite, int indice)
{
	int respuesta = -1;
	Publicacion bufferPublicacion;

	if(array != NULL && limite > 0 && indice < limite && indice >= 0 && array[indice].isEmpty == 0)
	{
		if(	!utn_getDescripcion(bufferPublicacion.texto,TEXTO_LEN,"\nIngrese el Texto de la Publiacion: ","\nERROR\n",2) &&
			!utn_getNumero(&bufferPublicacion.rubro,"\nIngrese el numero de Rubro: ","\nERROR\n",1000,1,2) &&
			!utn_getNumero(&bufferPublicacion.idCliente,"\nIngrese el numero ID Cliente: ","\nERROR\n",1000,1,2) &&
			!utn_getNumero(&bufferPublicacion.estado,"\nIngrese el nestado: ","\nERROR\n",0,1,2))
		{
			respuesta = 0;
			bufferPublicacion.id = array[indice].id;
			bufferPublicacion.isEmpty = 0;
			array[indice] = bufferPublicacion;
		}
	}
	return respuesta;
}

/**
 * \brief Actualiza una posicion del array
 * \param array Array de publicaciones a ser actualizado
 * \param limite Limite del array de publicaciones
 * \param indice Posicion a ser actualizada
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_bajaArray(Publicacion* array,int limite, int indice)
{
	int respuesta = -1;
	if(array != NULL && limite > 0 && indice < limite && indice >= 0 && array[indice].isEmpty == 0)
	{
		array[indice].isEmpty = 1;
		respuesta = 0;
	}
	return respuesta;
}

/**
 * \brief Da de baja todas las posiciones del array de un ID cliente especifico
 * \param array Array de publicaciones a ser actualizado
 * \param limite Limite del array de publicaciones
 * \param idCliente Posicion a ser actualizada
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_bajaArrayByIdCliente(Publicacion* array,int limite, int idCliente)
{
	int respuesta = -1;
	int i;
	if (array != NULL && limite > 0 && idCliente >= 0)
	{
		for(i=0;i<limite;i++)
		{
			if( array[i].idCliente == idCliente)
			{
				array[i].isEmpty = 1;

			}

		}

	}
	return respuesta;
}

/** \brief Busca un ID en un array y devuelve la posicion en que se encuentra
* \param array publicacion Array de publicacion
* \param limite int Tamaño del array
* \param posicion int* Puntero a la posicion del array donde se encuentra el valor buscado
* \return int Return (-1) si no encuentra el valor buscado o Error [Invalid length or NULL pointer] - (0) si encuentra el valor buscado
*
*/
int pub_buscarId(Publicacion array[], int limite, int valorBuscado)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0 && valorBuscado >= 0)
	{
		for(i=0;i<limite;i++)
		{
			if(array[i].id == valorBuscado && array[i].isEmpty == 0)
			{
				respuesta = i;

				break;
			}
		}
	}
	return respuesta;
}
/** \brief Busca un ID en un array , se fija si corresponde al estado pedido y devuelve la posicion en que se encuentra
* \param array publicacion Array de publicacion
* \param limite int Tamaño del array
* \param valor El valor de ID a buscar
* \param valor El estado a matchear
* \return int Return (-1) si no encuentra el valor buscado o Error [Invalid length or NULL pointer] - (0) si encuentra el valor buscado
*
*/
int pub_buscarIdConEstado(Publicacion array[], int limite, int valorBuscado, int estado)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0 && valorBuscado >= 0)
	{
		for(i=0;i<limite;i++)
		{
			if(array[i].id == valorBuscado && array[i].estado == estado && array[i].isEmpty == 0)
			{
				respuesta = i;

				break;
			}
		}
	}
	return respuesta;
}

/**
 * \brief Buscar primer posicion vacia
 * \param array Array de publicaciones
 * \param limite Limite del array de publicaciones
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 *
 */
int pub_getEmptyIndex(Publicacion* array,int limite)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		respuesta = 0;
		for(i=0;i<limite;i++)
		{
			if(array[i].isEmpty == 1)
			{
				respuesta = i;
				break;
			}
		}
	}
	return respuesta;
}

/**
 * \brief Da de alta FORZADA un publicacion en una posicion del array
 * \param array Array de publicaciones a ser actualizado
 * \param limite Limite del array de publicaciones
 * \param indice Posicion a ser actualizada
 * \param id Identificador a ser asignado al publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_altaForzadaArray(Publicacion* array,int limite,int indice, int* id, int idCliente, int rubro, char* texto)
{
	int respuesta = -1;
	Publicacion bufferPublicacion;

	if(array != NULL && limite > 0 && indice < limite && indice >= 0 && id != NULL && idCliente >= 0 && rubro >= 0 && texto != NULL)
	{
			respuesta = 0;
			bufferPublicacion.idCliente = idCliente;
			bufferPublicacion.rubro = rubro;
			strncpy(bufferPublicacion.texto,texto,TEXTO_LEN);
			bufferPublicacion.id = *id;
			bufferPublicacion.isEmpty = 0;
			bufferPublicacion.estado = 1;
			array[indice] = bufferPublicacion;
			(*id)++;
	}
	return respuesta;
}
/**
 * \brief Imprime el array de publicaciones por IdCliente
 * \param array Array de publicaciones a ser actualizado
 * \param limite Limite del array de publicaciones
 * \param idCliente El id del cliente para imprimir
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_imprimirArrayByIdCliente(Publicacion* array,int limite, int idCliente)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		respuesta = 0;
		for(i=0;i<limite;i++)
		{
			if(array[i].idCliente == idCliente)
			{
				pub_imprimir(&array[i]);
			}
		}
		printf ("\n");
	}
	return respuesta;
}
/**
 * \brief Traduce 0 o 1 al estado en string
 * \param pResultado Array donde se graba la palabra
 * \param limite Limite del array de publicaciones
 * \param valor El valor a evaluar
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_traducirEstado (char* pResultado,int limite,int valor)
{
	int retorno = -1;

	if (pResultado != NULL && limite > 0 && (valor == 0 || valor == 1))
	{
		if (valor == 0)
		{
			strncpy(pResultado,"PAUSADA",limite);
		}
		else
		{
			strncpy(pResultado,"ACTIVA",limite);
		}
	}
	return retorno;
}

/**
 * \brief Cambia Estado de una publicacion de 1 a 0
 * \param array Array de Publicaciones
 * \param limite Limite del array de publicaciones
 * \param indice El indice a cambiar el valor
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_pausarPublicacion(Publicacion* array,int limite, int indice)
{
	int retorno = -1;

	if (array != NULL && limite > 0 && indice >= 0 && array[indice].isEmpty == 0)
	{
		array[indice].estado = 0;

		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Cambia Estado de una publicacion de 0 a 1
 * \param array Array de Publicaciones
 * \param limite Limite del array de publicaciones
 * \param indice El indice a cambiar el valor
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_activarPublicacion(Publicacion* array,int limite, int indice)
{
	int retorno = -1;

	if (array != NULL && limite > 0 && indice >= 0 && array[indice].isEmpty == 0)
	{
		array[indice].estado = 1;

		retorno = 0;
	}
	return retorno;
}

/**
 * \brief retorna el id del cliente de una publicacion
 * \param array Array de las publicaciones
 * \param limite Limite del array de publicaciones
 * \param indice El indice de donde va a traer el ID
 * \return Retorna IdCliente (EXITO) y -1 (ERROR)
 *
 */
int pub_getIdCliente(Publicacion* array,int limite, int indice)
{
	int retorno = -1;

	if (array != NULL && limite >= 0 && indice >= 0)
	{
		retorno = array[indice].idCliente;
	}
	return retorno;
}
