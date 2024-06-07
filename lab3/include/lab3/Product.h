#ifndef PRODUCT_H_
#define PRODUCT_H_

#include <string>

using namespace std;

class Product
{
private:
	string code;
	string description;
	float price;

public:
	Product();
	Product(Product *product);
	Product(string description, float price);

	string getCode();
	string getDescription();
	float getPrice();
	void print();

	virtual ~Product();
};

#endif /* PRODUCT_H_ */
