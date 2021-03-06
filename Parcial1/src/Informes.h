/*
 * Informes.h
 *
 *  Created on: 10 may. 2020
 *      Author: Ariel
 */

#ifndef INFORMES_H_
#define INFORMES_H_

int info_getPublicacionClientesUnicos(int* arrayClientesUnicos,int limiteClientesUnicos,Publicacion* array,int limite);
int info_inicializarArray (int* array,int len);
int info_clienteConMasAvisos (int* arrayClientesUnicos,int len,Publicacion* arrayPublicaciones,int limitePublicaciones);
int info_clienteConMasAvisosConCriterio (int* arrayClientesUnicos,int len,Publicacion* arrayPublicaciones,int limitePublicaciones, int criterio);
int info_getPublicacionRubrosUnicos(int* arrayRubrosUnicos,int limiteRubrosUnicos,Publicacion* array,int limite);
int info_rubroConMasAvisosConCriterio (int* arrayRubrosUnicos,int len,Publicacion* arrayPublicaciones,int limitePublicaciones, int criterio);
int info_cantidadAvisosPorRubro (Publicacion* arrayPublicaciones,int limitePublicaciones, int rubro);

#endif /* INFORMES_H_ */
