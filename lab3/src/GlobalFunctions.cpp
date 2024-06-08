#include <iostream>
#include <random>
#include <iomanip>
#include <sstream>

#include "..\include\lab3\GlobalFunctions.h"

using namespace std;

int generateRandomId()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 1000);
    int random_id = distrib(gen);

    return random_id;
}

float stringToFloat(string number)
{
    try
    {
        return stof(number);
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: invalid argument, String cannot be converted to float";
    }
    catch (const out_of_range &e)
    {
        cerr << "Error: Out of range. The number is too large for a float.";
    }
    return 0;
}

string floatToString(float amount)
{
    stringstream stream;
    stream << fixed << setprecision(2) << amount;
    return stream.str();
}
