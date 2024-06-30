#include <iostream>

#include "../include/dataBaseOOP/Table.hpp"
#include "../include/dataBaseOOP/Column.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	Table *table = new Table("Root");
	Column *col1 = new Column("col1", true);
	table->pushColumn(col1);

	cout << table->getTableName() << endl;
	cout << col1->getColumnName() << endl;
	
    return 0;
}

