#include "..\include\dataBaseOOP\Data.hpp"

using namespace std;

Data::Data(const string _value)
{
    this->value = _value;
    this->nextData = NULL;
    this->foreignKey = NULL;
}

Data::Data(Data *_data)
{
    this->value = _data->getValue();
    this->nextData = _data->getNextData();
    this->foreignKey = _data->getForeignKey();
}

string Data::getValue()
{
    return this->value;
}

Data *Data::getNextData()
{
    return this->nextData;
}

Data *Data::getForeignKey()
{
	return this->foreignKey;
}

void Data::setNextData(Data *_nextData)
{
    this->nextData = _nextData;
}

void Data::setForeignKey(Data *_foreignKey)
{
    this->foreignKey = _foreignKey;
}

Data::~Data() {}
