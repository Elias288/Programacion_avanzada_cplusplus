#include "Producto.h"
#include <list>

using namespace std;

#ifndef PRODUCTOCONTROLLER_H_
#define PRODUCTOCONTROLLER_H_

class ProductoController {
private:
	list<Producto*> Productos;
public:
	ProductoController();

	int getSize();
	void listarP();
	Producto* find(string);
	void create(Producto*);
	void populate();

};

#endif /* PRODUCTOCONTROLLER_H_ */
