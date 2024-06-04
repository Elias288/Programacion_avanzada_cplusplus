#include <string>

using namespace std;

#ifndef PRODUCTO_H_
#define PRODUCTO_H_

class Producto {
private:
	string codigo;
	string descripcion;
	float precio;
public:
	Producto();
	Producto(string, string, float);

	string getcodigo();
	string getdescripcion();
	float getPrecio();

	virtual ~Producto();
};

#endif /* PRODUCTO_H_ */
