#include <iostream>
#include <list>

#include "..\include\lab3\ProductController.h"
#include "..\include\lab3\Product.h"

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
        (*product_it)->print();
        cout << endl;
        product_it++;
    }
}

/* POPULATE */
void ProductController::populate()
{
    // Carga de productos de pruebas
}

/* CALCULATE PRICES */
int ProductController::calculatePrices()
{
    int totalAmount;
    list<Product *>::iterator product_it = this->products.begin();
    while (product_it != this->products.end())
    {
        totalAmount += (*product_it)->getPrice();
    }

    cout << "Precio total: " << totalAmount << endl;
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
