#include <iostream>
#include <list>

#include "..\include\lab3\MenuController.h"
#include "..\include\lab3\Menu.h"

using namespace std;

MenuController::MenuController() {}

void MenuController::addMenu(Menu *menu)
{
    this->menus.push_front(menu);
}

void MenuController::listMenus()
{
    list<Menu *>::iterator menu_it = this->menus.begin();
    while (menu_it != this->menus.end())
    {
        (*menu_it)->print();
        cout << endl;
        menu_it++;
    }
}

MenuController::~MenuController() {}