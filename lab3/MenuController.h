#ifndef MENU_CONTROLLER_H_
#define MENU_CONTROLLER_H_

#include <list>

#include "Menu.h"
#include "Product.h"
#include "DtProduct.h"

using namespace std;

class MenuController
{
private:
	list<Menu *> menus;

public:
	MenuController();
	void addMenu(Menu *);

	void listMenus();

	virtual ~MenuController();
};

#endif /* MENU_CONTROLLER_H_ */
