#include "ProductoController.h"
#include "Producto.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;

ProductoController::ProductoController() {
}


void ProductoController::create(Producto *pro){
	this->Productos.push_front(pro);
	cout << "Se ha ingresado " << pro->getcodigo() << " al sistema \n";
}

Producto* ProductoController::find(string cod){
	list<Producto*>::iterator it = this->Productos.begin();

	while (it != this->Productos.end()/* && cod <= cant*/){
		if(cod == (*it)->getcodigo())
			return *it;
		it++;
	}
	return *it;
}

void ProductoController::listarP(){
	list<Producto*>::iterator it = this->Productos.begin();

	while (it != this->Productos.end()){
		cout << "Id=" << (*it)->getcodigo() << ", Descripcion:" << (*it)->getdescripcion() << ", Precio=" << (*it)->getPrecio() << "\n";
		it++;
	}
}

int ProductoController::getSize(){
	return this->Productos.size();
}

void ProductoController::populate() {
	for(int i=0; i<5; i++) {
		this->Productos.push_back(new Producto());
	}
}
