#ifndef DT_PRODUCT_H_
#define DT_PRODUCT_H_

#include <list>

#include "Product.h"

class DtProduct : public Product
{
private:
	int cant;

public:
	DtProduct();
	DtProduct(string, float, int);
	DtProduct(Product *, int);

	int getQuantity();
	void print();

	virtual ~DtProduct();
};

#endif /* DT_PRODUCT_H_ */
