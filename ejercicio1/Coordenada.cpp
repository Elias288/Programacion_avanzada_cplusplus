/*
 * Coordenada.cpp
 *
 *  Created on: 26 mar. 2020
 *      Author: Elias Bianchi
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <malloc.h>
#include "Coordenada.h"

using namespace std;

// Constructor vacío
Coordenada::Coordenada()
{
	x = 0;
	y = 0;
}

// Constructor con parámetros
Coordenada::Coordenada(int primero, int segundo)
{
	x = primero;
	y = segundo;
}

// Función que retorna un puntero char con las coordenadas
char *Coordenada::toString()
{
	// char *co, coo[50];
	// sprintf(coo, "(%d:%d)", this->x, this->y);
	// co = coo;
	// return co;
	char *str = new char[50];
	sprintf(str, "(%d, %d)", this->x, this->y);
	return str;
}

// Función que reasigna los valores de la coordenada
void Coordenada::Mover(int pri, int seg)
{
	x = pri;
	y = seg;
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;
}

// Imprime el valor de la coordenada x
int Coordenada::getX()
{
	return this->x;
}
// Imprime el valor de la coordenada y
int Coordenada::getY()
{
	return this->y;
}

// Destructor de la clase
Coordenada::~Coordenada()
{
}
