#include <iostream>
#include <random>

#include "GlobalFunctions.h"

using namespace std;

int generateRandomId()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 1000);
    int random_id = distrib(gen);

    return random_id;
}
