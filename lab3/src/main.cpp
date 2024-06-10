#include <stdio.h>
#include <iostream>
#include <list>

#include "..\include\lab3\Product.h"
#include "..\include\lab3\Menu.h"
#include "..\include\lab3\ProductController.h"
#include "..\include\lab3\DtProduct.h"
#include "..\include\lab3\MenuController.h"
#include "..\include\lab3\GlobalFunctions.h"

using namespace std;

ProductController *productController = new ProductController();
MenuController *menuController = new MenuController();

void test();
void initialInputMenu();
void administrativeInputMenu();

void registerProduct();
void registerMenu();

int main(int argc, char const *argv[])
{
    // test();
    // system("clear");
    initialInputMenu();

    return 0;
}

void test()
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
}

/* INITIAL MENU */
void initialInputMenu()
{
    int option;

    do
    {
        cout << "1) Administration menu" << endl;
        cout << "0) Exit" << endl;

        cin >> option;

        switch (option)
        {
        case 0:
            cout << "Exiting";
            break;
        case 1:
            administrativeInputMenu();
            break;

        default:
            cout << "option not found" << endl;
            break;
        }
    } while (option != 0);
}

/* ADMINISTRATIVE MENU */
void administrativeInputMenu()
{
    int option;

    do
    {
        cout << "1) Register a product" << endl;
        cout << "2) Register a menu" << endl;
        cout << "3) List products" << endl;
        cout << "4) List menus" << endl;
        cout << "0) Back" << endl;
        cin >> option;

        switch (option)
        {
        case 0:
            break;
        case 1:
            registerProduct();
            break;
        case 2:
            registerMenu();
            break;
        case 3:
            /* LIST PRODUCTS */
            productController->listProducts();
            break;
        case 4:
            /* LIST MENU */
            menuController->listMenus();
            break;
        default:
            cout << "option not found" << endl;
            break;
        }
    } while (option != 0);
}

/* REGISTER PRODUCT */
void registerProduct()
{
    string newDescription, stringPrice;
    float newPrice;
    int option;

    cin.ignore(); // si no se ignora el enter del cin anterior, el getline salta al siguiente

    cout << "Product description: ";
    getline(cin, newDescription);

    cout << "Product price: $";
    getline(cin, stringPrice);
    newPrice = stringToFloat(stringPrice); // se convierte el precio ingresado a float

    Product *newProduct = new Product(newDescription, newPrice);
    productController->addProduct(newProduct);

    cout << "\nProduct correctly added!\n\n";
    cout << newProduct->print() << endl
         << endl;
}

/* REGISTER MENU */
void registerMenu()
{
    string newDescription;
    int option, option2;
    // Out empty products
    if (productController->getSize() == 0)
    {
        cout << "There are no products. Please enter at least 1 in order to create a menu." << endl;
        return;
    }

    cin.ignore();

    cout << "Menu description: ";
    getline(cin, newDescription);

    Menu *menu = new Menu(newDescription);

    do
    {
        string code;
        int cant;
        cout << "Productos:" << endl;
        productController->listProducts();
        cout
            << "Select product (code): ";
        cin >> code;

        cout << "Enter quantity: ";
        cin >> cant;

        try
        {
            menu->add(new DtProduct(productController->find(code), cant));
        }
        catch (exception &e)
        {
            cout << "Error" << endl;
        }

        cout << "Continue adding products?" << endl
             << "1) yes" << endl
             << "0) no" << endl;
        cin >> option;
    } while (option != 0);

    do
    {
        cout << "1) save menu" << endl
             << "2) view menu" << endl
             << "3) cancel" << endl;
        cin >> option2;

        switch (option2)
        {
        case 1:
            menuController->addMenu(menu);
            option2 = 0;
            break;
        case 2:
            cout << menu->print() << endl;
            break;
        case 3:
            option2 = 0;
            break;

        default:
            cout << "option not found" << endl;
            break;
        }
    } while (option2 != 0);
}