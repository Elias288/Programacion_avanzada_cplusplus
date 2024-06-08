#include <iostream>
#include <list>

#include "..\include\lab3\ProductController.h"
#include "..\include\lab3\Product.h"
#include "..\include\lab3\GlobalFunctions.h"

using namespace std;

ProductController::ProductController() {}

/* ADD PRODUCT */
void ProductController::addProduct(Product *pro)
{
    this->products.push_front(pro);
}

/* LIST PRODUCTS */
void ProductController::listProducts()
{
    list<Product *>::iterator product_it = this->products.begin();
    while (product_it != this->products.end())
    {
        cout << (*product_it)->print() << endl;
        product_it++;
    }
    cout << endl;
}

/* POPULATE */
void ProductController::populate()
{
    // Carga de productos de pruebas
}

int ProductController::getSize()
{
    int cant = 0;
    list<Product *>::iterator product_it = this->products.begin();
    while (product_it != this->products.end())
    {
        cant++;
        product_it++;
    }

    return cant;
}

/* CALCULATE PRICES */
float ProductController::calculatePrices()
{
    float totalAmount;
    list<Product *>::iterator product_it = this->products.begin();
    while (product_it != this->products.end())
    {
        totalAmount += (*product_it)->getPrice();
    }

    cout << "Precio total: " << floatToString(totalAmount) << endl;
    return totalAmount;
}

/* FIND */
Product *ProductController::find(string cod)
{
    list<Product *>::iterator product_it = this->products.begin();
    while (product_it != this->products.end())
    {
        if (cod == (*product_it)->getCode())
        {
            return *product_it;
        }
        product_it++;
    }
    return *product_it;
}
