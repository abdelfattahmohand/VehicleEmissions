#include <iostream>
#include "registry.h"
using namespace std;

int main() {

    // Data sourced from: https://www.fueleconomy.gov/feg/download.shtml
    Registry* Data2014 = new Registry();
    Data2014->Load("epa2014.csv");

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
