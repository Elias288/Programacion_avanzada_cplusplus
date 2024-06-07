#ifndef MENU_H_
#define MENU_H_

#include <string>

#include "DtProduct.h"

using namespace std;

class Menu
{
private:
    string code;
    string description;
    list<DtProduct *> products;

public:
    Menu();
    Menu(string description);

    void add(DtProduct *);
    void listProducts();
    void print();
    float calculatePrice();
    string getDescription();
    string getCode();
    list<DtProduct *> getProducts();
};

#endif /* MENU_H_ */