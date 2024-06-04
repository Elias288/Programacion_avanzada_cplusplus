#ifndef MENU_H_
#define MENU_H_
#include "Producto.h"
#include <list>

using namespace std;

class Menu :public Producto{
private:
	string codigo;
	string descripcion;
	list<Producto*> Productos;
public:
	Menu();
	Menu(string, string, float);

	void add(Producto*);
	void listarP();

	virtual ~Menu();
};

#endif /* MENU_H_ */
