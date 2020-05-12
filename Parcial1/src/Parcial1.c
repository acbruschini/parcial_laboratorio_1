/*
 ============================================================================
 Name        : Parcial1.c
 Author      : Ariel Bruschini
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Cliente.h"
#include "Publicacion.h"
#include "Informes.h"

#define MENUPRINCIPAL_LEN 12
#define ARRAYCLIENTES_LEN 100
#define ARRAYPUBLICACIONES_LEN 1000
#define ARRAYCLIENTESUNICOS_LEN 100
#define ARRAYRUBROSUNICOS_LEN 100


int main(void) {

	setbuf(stdout, NULL);
	Cliente arrayClientes[ARRAYCLIENTES_LEN];
	Publicacion arrayPublicaciones[ARRAYPUBLICACIONES_LEN];
	int idCliente = 0;
	int idPublicacion = 0;

	int auxiliarIndiceCliente;
	int auxiliarIdCliente;
	int auxiliarIndicePublicacion;
	int auxiliarIdPublicacion;
	int auxiliarRubro;
	int auxiliarCantidadRubros;

	int arrayClientesUnicos[ARRAYCLIENTESUNICOS_LEN];
	int arrayRubrosUnicos[ARRAYRUBROSUNICOS_LEN];

	int opcionMenuPrincipal;

	// DEFINO ARRAY PARA FUNC MENU
	char menuPrincipal[MENUPRINCIPAL_LEN][300] = {
			"ABM PARA MANEJO DE PUBLICIDAD EN SITIOS WEB",
			"Alta de Cliente",
			"Modificar datos de Clientes",
			"Baja de Clientes",
			"Publicar",
			"Pausar Publicacion",
			"Reanudar Publicacion",
			"Imprimir Clientes",
			"Imprimir Publicaciones",
			"Informar Clientes",
			"Informar Publicaciones",
			"SALIR"
	};

	if (!cli_inicializarArray(arrayClientes,ARRAYCLIENTES_LEN) && !pub_inicializarArray(arrayPublicaciones, ARRAYPUBLICACIONES_LEN))
	{
		// DEBUG ALTA FORZADA
		cli_altaForzadaArray(arrayClientes, ARRAYCLIENTES_LEN, 0, &idCliente, "Ariel", "Bruschini", "20-28986231-6");
		cli_altaForzadaArray(arrayClientes, ARRAYCLIENTES_LEN, 1, &idCliente, "Leticia", "Leoz", "20-32576985-6");
		cli_altaForzadaArray(arrayClientes, ARRAYCLIENTES_LEN, 2, &idCliente, "Pablo", "Stanley", "20-12345678-6");
		cli_altaForzadaArray(arrayClientes, ARRAYCLIENTES_LEN, 6, &idCliente, "Eugenio", "Simmons", "20-87654321-6");
		cli_altaForzadaArray(arrayClientes, ARRAYCLIENTES_LEN, 4, &idCliente, "Pedro", "Criss", "20-11111111-6");
		pub_altaForzadaArray(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, 0, &idPublicacion, 1, 11, "Texto del aviso con rubro 11");
		pub_altaForzadaArray(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, 1, &idPublicacion, 1, 11, "Texto del aviso con rubro 11");
		pub_altaForzadaArray(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, 2, &idPublicacion, 2, 33, "Texto del aviso con rubro 22");
		pub_altaForzadaArray(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, 10, &idPublicacion, 4, 33, "Texto del aviso con rubro 33");
		pub_altaForzadaArray(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, 4, &idPublicacion, 4, 55, "Texto del aviso con rubro 1");
		pub_altaForzadaArray(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, 6, &idPublicacion, 4, 55, "Texto del aviso con rubro 1");
		pub_altaForzadaArray(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, 8, &idPublicacion, 6, 55, "Texto del aviso con rubro 1");

		// MENU
		do
		{
			opcionMenuPrincipal = menu(menuPrincipal,MENUPRINCIPAL_LEN);
			switch (opcionMenuPrincipal)
			{
			case 1:
				// ALTA DE CLIENTE
				auxiliarIndiceCliente = cli_getEmptyIndex(arrayClientes,ARRAYCLIENTES_LEN);
				if ( auxiliarIndiceCliente >= 0 &&
					!cli_altaArray(arrayClientes,ARRAYCLIENTES_LEN,auxiliarIndiceCliente,&idCliente))
				{
				}
				break;

			case 2:
				// MODIFICAR DATOS DE CLIENTES
				if(cli_imprimirArray(arrayClientes,ARRAYCLIENTES_LEN) == -1)
				{
					printf ("\nNo existen Clientes para modificar");
					break;
				}
				if(!utn_getNumero(&auxiliarIdCliente, "\nIngrese el ID del Cliente que quiere modificar: ", "\nERROR\n", 0, 99999, 2) &&
									(auxiliarIndiceCliente = cli_buscarId(arrayClientes, ARRAYCLIENTES_LEN, auxiliarIdCliente)) >= 0 &&
									!cli_modificarArray(arrayClientes, ARRAYCLIENTES_LEN, auxiliarIndiceCliente))
				{
					printf ("\nEl cliente %d se ha modificado con exito",auxiliarIndiceCliente);
				}
				else
				{
					printf ("\nIngreso datos erroneos, No se modifico ningun cliente");
				}
				break;

			case 3:
				//BAJA DE CLIENTES
				if(cli_imprimirArray(arrayClientes,ARRAYCLIENTES_LEN) == -1)
				{
					printf ("\nNo existen Clientes para dar de bajas");
					break;
				}
				if(!utn_getNumero(&auxiliarIdCliente, "\nIngrese el ID del Cliente que quiere dar de baja: ", "\nERROR\n", 0, 99999, 2) &&
					(auxiliarIndiceCliente = cli_buscarId(arrayClientes, ARRAYCLIENTES_LEN, auxiliarIdCliente)) >= 0 &&
					!pub_imprimirArrayByIdCliente(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, auxiliarIdCliente) &&
					utn_isConfirmacion("\nEsta seguro que quiere dar de baja al cliente y todas sus publicaciones? (S o N): ", "\nERROR\n", "S", "N", 2))
				{
					cli_bajaArray(arrayClientes, ARRAYCLIENTES_LEN, auxiliarIndiceCliente);
					pub_bajaArrayByIdCliente(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, auxiliarIdCliente);
					printf ("\nEl cliente %d se ha dado de baja",auxiliarIndiceCliente);
				}
				else
				{
					printf ("\nNo se elimino ningun cliente");
				}
				break;

			case 4:
				//PUBLICAR
				auxiliarIndicePublicacion = pub_getEmptyIndex(arrayPublicaciones,ARRAYPUBLICACIONES_LEN);
				if ( auxiliarIndicePublicacion >= 0 &&
					!pub_altaArray(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, arrayClientes, ARRAYCLIENTES_LEN, auxiliarIndicePublicacion, &idPublicacion))
				{
					printf ("\nSe ingreso una nueva publicacion con el ID: %d",idPublicacion);
				}
				break;

			case 5:
				// PAUSAR PUBLICACION
				if(pub_imprimirArrayEnEstado(arrayPublicaciones, ARRAYPUBLICACIONES_LEN,1) == -1){
					printf ("No existen Publicaciones Activas para Pausar");
					break;
				}
				if(!utn_getNumero(&auxiliarIdPublicacion, "\nIngrese el ID de la publicacion a Pausar: ", "\nERROR\n", 0, 99999, 2) &&
				   (auxiliarIndicePublicacion = pub_buscarIdConEstado(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, auxiliarIdPublicacion, 1)) >= 0 &&
				   (auxiliarIdCliente = pub_getIdCliente(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, auxiliarIndicePublicacion)) >= 0 &&
				   (auxiliarIndiceCliente = cli_buscarId(arrayClientes, ARRAYCLIENTES_LEN, auxiliarIdCliente)) >= 0 &&
				   !cli_imprimir(&arrayClientes[auxiliarIndiceCliente]) &&
				   utn_isConfirmacion("\nEsta seguro que quiere Pausar la publicacion del cliente? (S o N): ", "\nERROR\n", "S", "N", 2)
				   )
				{
					pub_pausarPublicacion(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, auxiliarIndicePublicacion);
				}
				else
				{
					printf ("\nNo se pauso ninguna publicacion");
				}
				break;

			case 6:
				// REANUDAR PUBLICACION
				if(pub_imprimirArrayEnEstado(arrayPublicaciones, ARRAYPUBLICACIONES_LEN,0) == -1){
					printf ("No existen Publicaciones Pausadas para Activar");
					break;
				}
				if(!utn_getNumero(&auxiliarIdPublicacion, "\nIngrese el ID de la publicacion a Activar: ", "\nERROR\n", 0, 99999, 2) &&
				   (auxiliarIndicePublicacion = pub_buscarIdConEstado(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, auxiliarIdPublicacion, 0)) >= 0 &&
				   (auxiliarIdCliente = pub_getIdCliente(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, auxiliarIndicePublicacion)) >= 0 &&
				   (auxiliarIndiceCliente = cli_buscarId(arrayClientes, ARRAYCLIENTES_LEN, auxiliarIdCliente)) >= 0 &&
				   !cli_imprimir(&arrayClientes[auxiliarIndiceCliente]) &&
				   utn_isConfirmacion("\nEsta seguro que quiere Activar la publicacion del cliente? (S o N): ", "\nERROR\n", "S", "N", 2)
				   )
				{
					pub_activarPublicacion(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, auxiliarIndicePublicacion);
				}
				else
				{
					printf ("\nNo se activo ninguna publicacion");
				}

				break;

			case 7:
				// IMPRIMIR CLIENTES
				cli_imprimirArrayClientesConAvisos(arrayClientes, ARRAYCLIENTES_LEN, arrayPublicaciones, ARRAYPUBLICACIONES_LEN);
				break;

			case 8:
				// IMPRIMIR PUBLICACIONES
				pub_imprimirArrayConCuit(arrayPublicaciones, ARRAYPUBLICACIONES_LEN,arrayClientes, ARRAYCLIENTES_LEN);
				break;

			case 9:
				// INFORMAR CLIENTES
				// CLIENTE CON MAS AVISOS PAUSADOS
				if (!info_inicializarArray(arrayClientesUnicos, ARRAYCLIENTESUNICOS_LEN) &&
					(auxiliarIdCliente = info_clienteConMasAvisosConCriterio(arrayClientesUnicos, info_getPublicacionClientesUnicos(arrayClientesUnicos, ARRAYCLIENTESUNICOS_LEN, arrayPublicaciones, ARRAYPUBLICACIONES_LEN), arrayPublicaciones, ARRAYPUBLICACIONES_LEN,0)) >= 0 &&
					(auxiliarIndiceCliente = cli_buscarId(arrayClientes, ARRAYCLIENTES_LEN, auxiliarIdCliente)) >= 0)
				{
					printf ("\nEl ID del cliente con mas anuncios PAUSADOS es:");
					cli_imprimir(&arrayClientes[auxiliarIndiceCliente]);
				}
				else
				{
					printf ("\nNo existen Clientes con anuncios PAUSADOS");
				}

				// CLIENTE CON MAS AVISOS ACTIVOS
				if (!info_inicializarArray(arrayClientesUnicos, ARRAYCLIENTESUNICOS_LEN) &&
					(auxiliarIdCliente = info_clienteConMasAvisosConCriterio(arrayClientesUnicos, info_getPublicacionClientesUnicos(arrayClientesUnicos, ARRAYCLIENTESUNICOS_LEN, arrayPublicaciones, ARRAYPUBLICACIONES_LEN), arrayPublicaciones, ARRAYPUBLICACIONES_LEN,1)) >= 1 &&
					(auxiliarIndiceCliente = cli_buscarId(arrayClientes, ARRAYCLIENTES_LEN, auxiliarIdCliente)) >= 0)
				{
					printf ("\nEl ID del cliente con mas anuncios ACTIVOS es:");
					cli_imprimir(&arrayClientes[auxiliarIndiceCliente]);
				}
				else
				{
					printf ("\nNo existen Clientes con anuncios ACTIVOS");
				}

				// CLIENTE CON MAS AVISOS
				if (!info_inicializarArray(arrayClientesUnicos, ARRAYCLIENTESUNICOS_LEN) &&
					(auxiliarIdCliente = info_clienteConMasAvisos(arrayClientesUnicos, info_getPublicacionClientesUnicos(arrayClientesUnicos, ARRAYCLIENTESUNICOS_LEN, arrayPublicaciones, ARRAYPUBLICACIONES_LEN), arrayPublicaciones, ARRAYPUBLICACIONES_LEN)) >= 0 &&
					(auxiliarIndiceCliente = cli_buscarId(arrayClientes, ARRAYCLIENTES_LEN, auxiliarIdCliente)) >= 0)
				{
					printf ("\nEl ID del cliente con mas anuncios es:");
					cli_imprimir(&arrayClientes[auxiliarIndiceCliente]);
				}
				else
				{
					printf ("\nNo existen Clientes con anuncios");
				}

				break;

			case 10:
				// INFORMAR PUBLICACIONES

				// RUBRO CON MAS PUBLICACIONES ACTIVAS
				if (!info_inicializarArray(arrayRubrosUnicos, ARRAYRUBROSUNICOS_LEN) &&
					(auxiliarIdPublicacion = info_rubroConMasAvisosConCriterio(arrayRubrosUnicos, info_getPublicacionRubrosUnicos(arrayRubrosUnicos, ARRAYRUBROSUNICOS_LEN, arrayPublicaciones, ARRAYPUBLICACIONES_LEN), arrayPublicaciones, ARRAYPUBLICACIONES_LEN,1)) >= 0)
				{
					printf ("\nEl Rubro con mas publicaciones ACTIVAS es: %d",auxiliarIdPublicacion);
				}
				else
				{
					printf ("\nNo existen publicaciones con RUBROS ACTIVOS");
				}

				// RUBRO CON MAS PUBLICACIONES PAUSADAS
				if (!info_inicializarArray(arrayRubrosUnicos, ARRAYRUBROSUNICOS_LEN) &&
					(auxiliarIdPublicacion = info_rubroConMasAvisosConCriterio(arrayRubrosUnicos, info_getPublicacionRubrosUnicos(arrayRubrosUnicos, ARRAYRUBROSUNICOS_LEN, arrayPublicaciones, ARRAYPUBLICACIONES_LEN), arrayPublicaciones, ARRAYPUBLICACIONES_LEN,0)) >= 0)
				{
					printf ("\nEl Rubro con mas publicaciones PAUSADAS es: %d",auxiliarIdPublicacion);
				}
				else
				{
					printf ("\nNo existen publicaciones con RUBROS PAUSADOS");
				}

				// CANTIDAD DE PUBLICACIONES DE UN RUBRO
				if (!utn_getNumero(&auxiliarRubro, "\nIngrese el numero de Rubro que quiere contar: ", "\nERROR\n", 0, 99999, 2) &&
					(auxiliarCantidadRubros = info_cantidadAvisosPorRubro(arrayPublicaciones, ARRAYPUBLICACIONES_LEN, auxiliarRubro)) >= 0)
				{
					printf ("\nEl rubro %d existe en %d avisos ACTIVOS.",auxiliarRubro,auxiliarCantidadRubros);
				}
				else
				{
					printf ("\nNo existen publicaciones ese rubro.");
				}
				break;
			}
		} while (opcionMenuPrincipal != MENUPRINCIPAL_LEN - 1);
	}
	return EXIT_SUCCESS;
}
