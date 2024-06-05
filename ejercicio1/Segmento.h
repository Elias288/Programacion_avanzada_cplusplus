/*
 * Segmento.h
 *
 *  Created on: 30 mar. 2020
 *      Author: Elias Bianchi
 */

#include "Coordenada.h"

#ifndef SEGMENTO_H_
#define SEGMENTO_H_

class Segmento
{
private:
	Coordenada *pri;
	Coordenada *seg;

public:
	Segmento();
	Segmento(Coordenada *, Coordenada *);
	int Longitud();
	virtual ~Segmento();
};

#endif /* SEGMENTO_H_ */
