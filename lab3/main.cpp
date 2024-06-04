#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <list>

#include "Producto.h"
#include "Menu.h"
#include "ProductoController.h"

void altaProducto();
void MenuGeneral();
void MenuAdmin();
void MenuMozo();

using namespace std;

ProductoController* pc = new ProductoController();
Producto *P;
Menu *M;

int main(){
	int op = 0;

	do{
		MenuGeneral();
		cin >> op;

		switch(op){
		case 1:
			op = 0;
			do{
				MenuAdmin();
				cin >> op;
				switch(op){
				case 1:

					altaProducto();
					/*ProductoController PC;
					Producto *P1, *P2, *P3;

					int a=1;
					string b="pepe";
					float c= 100;

					P1 = new Producto(a,b,c);
					P2 = new Producto(2,"lola",100);
					P3 = new Producto(3,"carlos",421);


					PC.create(P1);
					PC.create(P2);
					PC.create(P3);

					cout << "cantidad:" << PC.getSize() << "\n";
					PC.listarP();*/
					break;
				case 2:
					break;
				/*case 3:
					break;
				case 4:
					break;
				case 5:
					break;*/
				}
			}while(op!=6);
			break;
		case 2:
			op = 0;
			do{
				MenuMozo();
				cin >> op;
				switch(op){
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				}
			}while(op!=5);
			break;
		case 3:
			op = 0;
			do{
				cout << "1) Agregar Empleados."<<endl;
				cout << "2) Agregar Productos."<<endl;
				cout << "3) Agregar Mesas."<<endl;
				cout << "4) Volver."<<endl;
				cin >> op;
				switch(op){
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				}
			}while(op!=3);
			break;
		}
	}while(op!=4);
	return 0;
}

void MenuGeneral(){
	cout << "1) Administrador" <<endl;
	cout << "2) Mozo"<<endl;
	cout << "3) Datos de Prueba"<<endl;
	cout << "4) Salir"<<endl;
}

void MenuAdmin(){
	cout << "1) Alta producto."<<endl;
	cout << "2) Informacion de producto."<<endl;// que le pida el id del producto?
	cout << "3) Baja producto."<<endl;
	cout << "4) Alta Empleado."<<endl;
	cout << "5) Asignar mozos a mesas."<<endl;
	cout << "6) Volver."<<endl;
}

void MenuMozo(){
	cout << "1) Iniciar venta en mesa."<<endl;
	cout << "2) Agregar producto a una mesa."<<endl;
	cout << "3) Quitar producto de una venta."<<endl;
	cout << "4) Facturación de una venta."<<endl;
	cout << "5) Volver."<<endl;
}

void altaProducto(){
	string desc, cod;
	int pro, opt, opt2, opt3, opt4, cant ;
	float pre;

	do{
		if(pc->getSize() > 0){
			cout << "1) producto \n";
			cout << "2) Menu \n";
			cin >> opt;

			switch(opt){
			case 1:
				cout << "Ingrese codigo \n";
				cin >> cod;
				cout << "ingrese descripcion \n";
				cin >> desc;
				cout << "Ingrese Precio \n";
				cin >> pre;

				P = new Producto(cod, desc, pre);

				pc->create(P);
				break;

			case 2:
				//MENU
				cout << "Ingrese codigo \n";
				cin >> cod;
				cout << "ingrese descripcion \n";
				cin >> desc;

				M = new Menu(cod, desc, 0);

				do{
					cout << "LISTA DE PRODUCTOS\n";
					pc->listarP();
					cout << "Seleccionar Producto: \n";
					cin >> cod;
					cout << "Ingrese cantidad\n";
					cin >> cant;

					try{

						M->add(pc->find(cod));
					}catch (exception& e){
						cout << "Ocurrio un error " << e.what() << "\n" ;
					}

					cout << "seguir ingresando 1=yes 0=no \n";
					cin >> opt2;
				}while(opt2 != 0);

				cout << "Desea confirmar yes:1 or no:0 \n";
				cin >> opt3;
				if(opt3 == 1){
					pc->create(M);
				}

				break;
			}
		}else{
			cout << "Ingrese codigo \n";
			cin >> cod;
			cout << "ingrese descripcion \n";
			cin >> desc;
			cout << "Ingrese Precio \n";
			cin >> pre;

			P = new Producto(cod, desc, pre);

			pc->create(P);

		}

		cout << "seguir ingresando productos? 1=yes 0=no \n";
		cin >> opt4;
	}while(opt4 != 0);

}


