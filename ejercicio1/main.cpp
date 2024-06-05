#include <stdio.h>
#include <string.h>

#include "Coordenada.h"
#include "Segmento.h"

int main()
{
	int x = 0, y = 0, Op;
	char *C, cad1[30], cad2[30];

	Coordenada *Co[3];
	Co[0] = new Coordenada(0, 0);
	Co[1] = new Coordenada(0, 0);
	Co[2] = new Coordenada(0, 0);

	do
	{
		// Menú
		cout << "1) Mover" << endl;
		cout << "2) Ver" << endl;
		cout << "3) Segmento" << endl;
		cout << "0) Salir" << endl;
		cin >> Op;

		switch (Op)
		{
		case 1:
		{
			// Mover
			cout << "ingrese x" << endl;
			cin >> x;
			cout << "ingrese y" << endl;
			cin >> y;
			Co[0]->Mover(x, y);
			break;
		}
		case 2:
		{
			// Ver
			C = Co[0]->toString();
			while (*C)
			{
				cout << *C++;
			}
			cout << endl;
			break;
		}
		case 3:
		{
			// Segmento
			// primer punto
			cout << "Primer Punto:" << endl;
			cout << "ingrese x" << endl;
			cin >> x;
			cout << "ingrese y" << endl;
			cin >> y;
			Co[1]->Mover(x, y);

			// segundo punto
			cout << "Segundo Punto:" << endl;
			cout << "ingrese x" << endl;
			cin >> x;
			cout << "ingrese y" << endl;
			cin >> y;
			Co[2]->Mover(x, y);

			strcpy(cad1, Co[1]->toString());
			strcpy(cad2, Co[2]->toString());

			cout << "Segmento: " << cad1 << ";" << cad2 << endl;

			Segmento seg(Co[1], Co[2]);
			cout << "longitud: " << seg.Longitud() << endl;

			break;
		}
		}
	} while (Op != 0);

	cout << "Fuera!!!\n";
	return 0;
}
