/*
 * Informes.c
 *
 *  Created on: 10 may. 2020
 *      Author: Ariel
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Cliente.h"
#include "Publicacion.h"

/**
 * \brief Graba en un array Todos los clientes de las publicaciones sin repetir
 * \param arrayClientesUnicos Array donde se va a grabar cada cliente
 * \param limiteClientesUnicos Limite del array de clientesunicos
 * \param array El array de publicaciones
 * \param limite El limite del array de publicaciones.
 * \return Retorna LEN en el que me quedo el array de clientes unicos (EXITO) y -1 (ERROR)
 *
 */
int info_getPublicacionClientesUnicos(int* arrayClientesUnicos,int limiteClientesUnicos,Publicacion* array,int limite)
{
	int retorno = -1;
	int i;
	int j;
	int flagExisteCliente;
	int indiceClienteLibre = 0;

	if (arrayClientesUnicos != NULL && limiteClientesUnicos > 0 && array != NULL && limite > 0)
	{
		for (i=0;i<limite;i++)
		{
			flagExisteCliente = 0;
			if(array[i].isEmpty == 0)
			{
				for (j=0;j<limiteClientesUnicos;j++)
				{
					if(array[i].idCliente == arrayClientesUnicos[j])
					{
						flagExisteCliente = 1;
						break;
					}
				}
				if (flagExisteCliente == 0)
				{
					arrayClientesUnicos[indiceClienteLibre] = array[i].idCliente;
					indiceClienteLibre++;
				}
			}
		}
	}
	// DEBUG PARA VER EL ARRAY QUE GENERO
	/*
	for (j=0;j<indiceClienteLibre;j++)
	{

		printf ("\n arrayClientesUnicos[%d]: %d",j,arrayClientesUnicos[j]);

	}
	*/
	retorno = indiceClienteLibre;
	return retorno;
}
/**
 * \brief Inicializa el array de ID de clientes unicos
 * \param array Array de los clientes unicos
 * \param limite Limite del array de clientes unicos
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int info_inicializarArray (int* array,int len)
{
	int i;
	int retorno = -1;
	if(array != NULL && len>0)
	{
		retorno = 0;
		for (i =0;i<len;i++)
		{
			array[i] = 9999999;
		}
	}
	return retorno;
}

/**
 * \brief Devuelve el cliente con mas avisos
 * \param arrayClientesUnicos Array en donde tenga solo los clientes unicos
 * \param len Limite del array de clientes unicos
 * \param arrayPublicaciones Array de todas las publicaciones
 * \param limitePublicaciones Limite del array de publicaciones
 * \return Retorna el ID de cliente con mas avisos (EXITO) y -1 (ERROR)
 *
 */
int info_clienteConMasAvisos (int* arrayClientesUnicos,int len,Publicacion* arrayPublicaciones,int limitePublicaciones)
{
	int retorno = -1;
	int i;
	int j;
	int contadorAvisos = 0;
	int maximo = 0;

	if (arrayClientesUnicos != NULL && len > 0 && arrayPublicaciones != NULL && limitePublicaciones >0)
	{
		for (i=0;i<len;i++)
		{
			contadorAvisos = 0;
			for(j=0;j<limitePublicaciones;j++)
			{
				if (arrayClientesUnicos[i] == arrayPublicaciones[j].idCliente && arrayPublicaciones[j].isEmpty == 0)
				{
					contadorAvisos++;
				}
			}
			if (i == 0 || contadorAvisos >= maximo)
			{
				maximo = contadorAvisos;
				retorno = arrayClientesUnicos[i];
			}
		}
	}
	return retorno;
}

/**
 * \brief Devuelve el cliente con mas avisos pausados o activos
 * \param arrayClientesUnicos Array en donde tenga solo los clientes unicos
 * \param len Limite del array de clientes unicos
 * \param arrayPublicaciones Array de todas las publicaciones
 * \param limitePublicaciones Limite del array de publicaciones
 * \param criterio int 0 para pausados y 1 para activos
 * \return Retorna el ID de cliente con mas avisos (EXITO) y -1 (ERROR)
 *
 */
int info_clienteConMasAvisosConCriterio (int* arrayClientesUnicos,int len,Publicacion* arrayPublicaciones,int limitePublicaciones, int criterio)
{
	int retorno = -1;
	int i;
	int j;
	int contadorAvisos = 0;
	int maximo = 0;

	if (arrayClientesUnicos != NULL && len > 0 && arrayPublicaciones != NULL && limitePublicaciones >0)
	{
		for (i=0;i<len;i++)
		{
			contadorAvisos = 0;
			for(j=0;j<limitePublicaciones;j++)
			{
				if (arrayClientesUnicos[i] == arrayPublicaciones[j].idCliente && arrayPublicaciones[j].isEmpty == 0 && arrayPublicaciones[j].estado == criterio)
				{
					contadorAvisos++;
				}
			}
			if (i == 0 || contadorAvisos>= maximo)
			{
				maximo = contadorAvisos;
				retorno = arrayClientesUnicos[i];
			}
		}
	}
	return retorno;
}

/**
 * \brief Graba en un array los rubros sin repetir
 * \param array Array de las publicaciones
 * \param limite Limite del array de publicaciones
 * \param indice El indice de donde va a traer el ID
 * \return Retorna LEN del nuevo array (EXITO) y -1 (ERROR)
 *
 */
int info_getPublicacionRubrosUnicos(int* arrayRubrosUnicos,int limiteRubrosUnicos,Publicacion* array,int limite)
{
	int retorno = -1;
	int i;
	int j;
	int flagExisteRubro;
	int indiceRubroLibre = 0;

	if (arrayRubrosUnicos != NULL && limiteRubrosUnicos > 0 && array != NULL && limite > 0)
	{
		for (i=0;i<limite;i++)
		{
			flagExisteRubro = 0;
			if(array[i].isEmpty == 0)
			{
				for (j=0;j<limiteRubrosUnicos;j++)
				{
						if(array[i].rubro == arrayRubrosUnicos[j])
					{
						flagExisteRubro = 1;
						break;
					}
				}
				if (flagExisteRubro == 0)
				{
					arrayRubrosUnicos[indiceRubroLibre] = array[i].rubro;
					indiceRubroLibre++;
				}
			}
		}
	}
	// DEBUG
	/*
	for (j=0;j<indiceRubroLibre;j++)
	{

		printf ("\n arrayRubrosUnicos[%d]: %d",j,arrayRubrosUnicos[j]);

	}
	*/
	retorno = indiceRubroLibre;
	return retorno;
}
/**
 * \brief Devuelve el rubro que tiene mas pausados o mas activos
 * \param arrayRubrosUnicos Array en donde tenga solo los rubros unicos
 * \param len Limite del array de rubros
 * \param arrayPublicaciones Array de todas las publicaciones
 * \param limitePublicaciones Limite del array de publicaciones
 * \param criterio int 0 para pausados y 1 para activos
 * \return Retorna el numero de rubro  (EXITO) y -1 (ERROR)
 *
 */
int info_rubroConMasAvisosConCriterio (int* arrayRubrosUnicos,int len,Publicacion* arrayPublicaciones,int limitePublicaciones, int criterio)
{
	int retorno = -1;
	int i;
	int j;
	int contadorRubros = 0;
	int maximo = 0;

	if (arrayRubrosUnicos != NULL && len > 0 && arrayPublicaciones != NULL && limitePublicaciones >0)
	{
		for (i=0;i<len;i++)
		{
			contadorRubros = 0;
			for(j=0;j<limitePublicaciones;j++)
			{
				if (arrayRubrosUnicos[i] == arrayPublicaciones[j].rubro && arrayPublicaciones[j].isEmpty == 0 && arrayPublicaciones[j].estado == criterio)
				{
					contadorRubros++;
				}
			}
			if (contadorRubros > maximo)
			{
				maximo = contadorRubros;
				retorno = arrayRubrosUnicos[i];
			}
		}
	}
	return retorno;
}

/**
 * \brief Devuelve la cantidad de avisos ACTIVOS con un rubro
 * \param arrayPublicaciones Array de todas las publicaciones
 * \param limitePublicaciones Limite del array de publicaciones
 * \param rubro Numero de rubro a buscar.
 * \return Retorna la cantidad de avisos  (EXITO) y -1 (ERROR)
 *
 */
int info_cantidadAvisosPorRubro (Publicacion* arrayPublicaciones,int limitePublicaciones, int rubro)
{
	int retorno = -1;
	int i;
	int contadorRubros=0;

	if (arrayPublicaciones != NULL && limitePublicaciones > 0 && rubro > 0)
	{
		retorno = 0;
		for (i=0; i<limitePublicaciones; i++)
		{
			if (arrayPublicaciones[i].isEmpty == 0 && arrayPublicaciones[i].rubro == rubro && arrayPublicaciones[i].estado == 1)
			{
				contadorRubros++;
			}
		}
		retorno = contadorRubros;
	}
	return retorno;
}
