#ifndef PRODUCT_CONTROLLER_H_
#define PRODUCT_CONTROLLER_H_

#include <list>

#include "Product.h"

using namespace std;

class ProductController
{
private:
	list<Product *> products;

public:
	ProductController();

	void addProduct(Product *);
	int getSize();
	void listProducts();
	void populate();
	int calculatePrices();
	Product *find(string);
};

#endif /* PRODUCT_CONTROLLER_H_ */