#include <iostream>
#include <list>

#include "GlobalFunctions.h"
#include "Menu.h"

using namespace std;

Menu::Menu()
{
    string random_id = to_string(generateRandomId());
    this->code = random_id;
    this->description = "Menu: " + random_id;
}

Menu::Menu(string _description)
{
    string random_id = to_string(generateRandomId());
    this->code = random_id;
    this->description = _description;
}

void Menu::add(DtProduct *pro)
{
    this->products.push_front(pro);
}

void Menu::listProducts()
{
    list<DtProduct *>::iterator dtProduct_it = this->products.begin();
    while (dtProduct_it != this->products.end())
    {
        (*dtProduct_it)->print();
        dtProduct_it++;
    }
}

float Menu::calculatePrice()
{
    float totalAmount;

    list<DtProduct *>::iterator dtProduct_it = this->products.begin();
    while (dtProduct_it != this->products.end())
    {
        totalAmount += (*dtProduct_it)->getPrice() * (*dtProduct_it)->getQuantity();
        dtProduct_it++;
    }

    return totalAmount;
}

void Menu::print()
{
    cout << "Menu: " << this->getCode() << ", Description: " << this->getDescription() << endl;
    cout << "Products:" << endl;
    this->listProducts();
    cout << "Total amount: $" << this->calculatePrice() << endl;
}

string Menu::getCode()
{
    return this->code;
}

string Menu::getDescription()
{
    return this->description;
}

list<DtProduct *> Menu::getProducts()
{
    return this->products;
}