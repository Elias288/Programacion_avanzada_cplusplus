#include <string>
#include "Producto.h"

using namespace std;

Producto::Producto(string cod, string desc, float precio){
	this->codigo = cod;
	this->descripcion = desc;
	this->precio = precio;
}

Producto::Producto(){
	this->codigo=" ";
	this->descripcion=" ";
	this->precio=0;
}

string Producto::getcodigo(){
	return this->codigo;
}

string Producto::getdescripcion(){
	return this->descripcion;
}

float Producto::getPrecio(){
	return this->precio;
}

Producto::~Producto() {
}

