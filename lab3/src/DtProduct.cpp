#include <iostream>

#include "..\include\lab3\DtProduct.h"

using namespace std;

DtProduct::DtProduct()
{
    this->cant = 1;
}

DtProduct::DtProduct(Product *prod, int _cant) : Product(*prod)
{
    this->cant = _cant;
}

DtProduct::DtProduct(string description, float price, int _cant) : Product(description, price)
{
    this->cant = _cant;
}

int DtProduct::getQuantity()
{
    return this->cant;
}

void DtProduct::print()
{
    cout << "code: " << this->getCode();
    cout << ", description: " << this->getDescription();
    cout << ", price: $" << this->getPrice();
    cout << ", cant: " << this->cant << endl;
}

DtProduct::~DtProduct() {}