/*
 * Coordenada.cpp
 *
 *  Created on: 26 mar. 2020
 *      Author: Elias Bianchi
 */
#include "Coordenada.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <malloc.h>

using namespace std;

Coordenada::Coordenada(){
	x=0;
	y=0;
}

Coordenada::Coordenada(int primero, int segundo){
	x= primero;
	y= segundo;
}

char* Coordenada::toString(){
	char *co, coo[50];
	sprintf(coo, "(%d:%d)", this->x, this->y);
	co = coo;
	return co;
}

void Coordenada::Mover(int pri, int seg){
	x= pri;
	y= seg;
}

int Coordenada::getX(){
	return this->x;
}
int Coordenada::getY(){
	return this->y;
}

Coordenada::~Coordenada(){

}

