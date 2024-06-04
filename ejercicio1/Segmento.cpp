/*
 * Segmento.cpp
 *
 *  Created on: 30 mar. 2020
 *      Author: Elias Bianchi
 */

#include "Segmento.h"
#include "Coordenada.h"
#include <math.h>

Segmento::Segmento(){
	this->pri = NULL;
	this->seg = NULL;
}

Segmento::Segmento(Coordenada *pri, Coordenada *seg){
	this->pri = pri;
	this->seg = seg;

}

int Segmento::Longitud(){
	int cat1, cat2, hip, res, x1, x2, y1, y2;
	x1 = this->pri->getX();
	x2 = this->seg->getX();
	y1 = this->pri->getY();
	y2 = this->seg->getY();

	cat1 = x1 - x2;
	cat2 = y1 - y2;

	cat1 = cat1 * cat1;
	cat2 = cat2 * cat2;

	hip = cat1 + cat2;
	res = sqrt(hip);
	return res;
}

Segmento::~Segmento() {
	// TODO Auto-generated destructor stub
}

