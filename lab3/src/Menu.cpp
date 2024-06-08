#include <iostream>
#include <list>

#include "..\include\lab3\GlobalFunctions.h"
#include "..\include\lab3\Menu.h"

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

string Menu::listProducts()
{
    string products;

    list<DtProduct *>::iterator dtProduct_it = this->products.begin();
    while (dtProduct_it != this->products.end())
    {
        products += (*dtProduct_it)->printDt() + "\n";
        dtProduct_it++;
    }

    return products;
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

string Menu::print()
{
    return "Menu: " + this->getCode() +
           ", description: " + this->getDescription() + "\n" +
           "Products: \n" + this->listProducts() +
           "Total amount: $" + floatToString(this->calculatePrice()) +
           "\n";
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