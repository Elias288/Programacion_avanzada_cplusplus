#include "Menu.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

Menu::Menu(string cod, string desc, float cant): Producto(cod, desc, cant){
	this->codigo = cod;
	this->descripcion = desc;
}

void Menu::add(Producto* pro){
	this->Productos.push_front(pro);
}

void Menu::listarP(){
	list<Producto*>::iterator it = this->Productos.begin();

		while (it != this->Productos.end()){
			cout << "Id=" << (*it)->getcodigo() << ", Descripcion:" << (*it)->getdescripcion() << ", Precio=" << (*it)->getPrecio() << ")\n";
			it++;
		}
}

Menu::~Menu() {
}

