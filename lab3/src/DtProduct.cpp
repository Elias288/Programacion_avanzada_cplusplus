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

float DtProduct::getQuantity()
{
    return this->cant;
}

string DtProduct::printDt()
{
    return this->print() + ", cant: " + to_string(this->cant);
}

DtProduct::~DtProduct() {}