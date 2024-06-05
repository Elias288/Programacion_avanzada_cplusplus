/*
 * Segmento.cpp
 *
 *  Created on: 30 mar. 2020
 *      Author: Elias Bianchi
 */

#include <math.h>
#include "Segmento.h"
#include "Coordenada.h"

Segmento::Segmento()
{
	this->pri = NULL;
	this->seg = NULL;
}

Segmento::Segmento(Coordenada *pri, Coordenada *seg)
{
	this->pri = pri;
	this->seg = seg;
}

int Segmento::Longitud()
{
	int cat1, cat2, hip, res, x1, x2, y1, y2;

	// first point
	x1 = this->pri->getX();
	y1 = this->pri->getY();

	// second point
	x2 = this->seg->getX();
	y2 = this->seg->getY();

	cat1 = x1 - x2;
	cat2 = y1 - y2;

	cat1 = cat1 * cat1;
	cat2 = cat2 * cat2;

	hip = cat1 + cat2;
	res = sqrt(hip);

	return res;
}

Segmento::~Segmento()
{
}
