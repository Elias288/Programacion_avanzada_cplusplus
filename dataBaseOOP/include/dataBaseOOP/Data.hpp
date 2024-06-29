#ifndef DATA_H_
#define DATA_H_

#include <string>

using namespace std;

class Data
{
private:
    string value;
    Data *nextData;
    Data *foreignKey;

public:
    Data(const string _value);
    Data(Data *_data);

    string getValue();
    Data *getNextData();
    Data *getForeignKey();

    void setNextData(Data *_nextData);
    void setForeignKey(Data *_foreignKey);

    virtual ~Data();
};

#endif // DATA_H_
