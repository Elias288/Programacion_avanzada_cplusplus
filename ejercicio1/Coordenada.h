/*
 * Coordenada.h
 *
 *  Created on: 26 mar. 2020
 *      Author: Elias Bianchi
 */

#ifndef COORDENADA_H_
#define COORDENADA_H_

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Coordenada{
private:
	int x, y;
public:
	Coordenada(int, int);
	Coordenada();
	~Coordenada();
	int getX();
	int getY();
	char* toString();
	void Mover(int,int);
};

#endif /* COORDENADA_H_ */
