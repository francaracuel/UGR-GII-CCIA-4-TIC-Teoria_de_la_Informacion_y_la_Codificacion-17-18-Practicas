///////////////////////////////////////////////////////////////////////////////
//
// Juan Manuel Fajardo Sarmiento
// Francisco Javier Caracuel Beltrán
//
// TIC - 2017/2018 - 4º - GII - CCIA
//
// arducodif.h
//
// Biblioteca para el manejo de datos con Arduino
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __ARDUCODIF__

#define __ARDUCODIF__

void codificaSimboloMorse(const char corig, char &ccodif, unsigned char &nUtil);

void decodificaSimboloMorse(const char ccodif, const unsigned char nUtils, char &decodif);

void codificador(const char *orig, const int nOrig, char *codif, unsigned char *util);

void decodificador(const char *codif, const unsigned char *utiles,  const  int nCodif, char *decodif);

#endif