#include <stdio.h>
#include <iostream>
#include <list>

#include "..\include\lab3\Product.h"
#include "..\include\lab3\Menu.h"
#include "..\include\lab3\ProductController.h"
#include "..\include\lab3\DtProduct.h"
#include "..\include\lab3\MenuController.h"

using namespace std;

ProductController *productController = new ProductController();
MenuController *menuController = new MenuController();

int main(int argc, char const *argv[])
{

    Product *producto1 = new Product("panchos", 50);
    productController->addProduct(producto1);
    Product *producto2 = new Product("hamburguesa", 100);
    productController->addProduct(producto2);
    Product *producto3 = new Product("pizza", 15);
    productController->addProduct(producto3);
    Product *producto4 = new Product("coca cola", 10);
    productController->addProduct(producto4);
    Product *producto5 = new Product("Pepsi", 14);
    productController->addProduct(producto5);

    Menu *menu1 = new Menu("Menu 1");
    menu1->add(new DtProduct(producto1, 1));
    menu1->add(new DtProduct(producto4, 4));

    Menu *menu2 = new Menu("Menu 2");
    menu2->add(new DtProduct(producto3, 1));
    menu2->add(new DtProduct(producto2, 2));

    menuController->addMenu(menu1);
    menuController->addMenu(menu2);

    productController->listProducts();
    cout << endl;
    menuController->listMenus();

    return 0;
}
