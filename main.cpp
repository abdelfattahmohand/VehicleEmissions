#include <iostream>
#include "registry.h"
#include "RBTree.h"
#include "Splaytree.h"
using namespace std;

int main() {

    // Data sourced from: https://www.fueleconomy.gov/feg/download.shtml
    Registry* Data2014 = new Registry();
    Data2014->Load("epa2014.csv");
    Registry::Vehicle* testVehicle = Data2014->Access(0);
    cout << testVehicle->combCO2;

    RBTree* TreeRB = new RBTree();
    TreeRB->insert(*Data2014->Access(0));

    SplayTree* TreeSplay = new SplayTree();
    TreeSplay->insert(Data2014->Access(0));


    cout << "Hello, World!" << endl;
    return 0;
}
