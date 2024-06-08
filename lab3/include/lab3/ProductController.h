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

	int getSize();
	float calculatePrices();
	void addProduct(Product *);
	void listProducts();
	void populate();
	Product *find(string);
};

#endif /* PRODUCT_CONTROLLER_H_ */