#include <iostream>
#include "registry.h"
#include "RBTree.h"
#include "Splaytree.h"
using namespace std;

int main() {

    vector<Registry*> Registries;

    // Data sourced from: https://www.fueleconomy.gov/feg/download.shtml
    Registry* Data2014 = new Registry();
    Data2014->Load("epa2014.csv");
    Registries.push_back(Data2014);
    Registry* Data2015 = new Registry();
    Data2015->Load("epa2015.csv");
    Registries.push_back(Data2015);
    Registry* Data2016 = new Registry();
    Data2016->Load("epa2016.csv");
    Registries.push_back(Data2016);
    Registry* Data2017 = new Registry();
    Data2017->Load("epa2017.csv");
    Registries.push_back(Data2017);
    Registry* Data2018 = new Registry();
    Data2018->Load("epa2018.csv");
    Registries.push_back(Data2018);
    Registry* Data2019 = new Registry();
    Data2019->Load("epa2019.csv");
    Registries.push_back(Data2019);
    Registry* Data2020 = new Registry();
    Data2020->Load("epa2020.csv");
    Registries.push_back(Data2020);
    Registry* Data2021 = new Registry();
    Data2021->Load("epa2021.csv");
    Registries.push_back(Data2021);
    Registry* Data2022 = new Registry();
    Data2022->Load("epa2022.csv");
    Registries.push_back(Data2022);
    Registry* Data2023 = new Registry();
    Data2023->Load("epa2023.csv");
    Registries.push_back(Data2023);
    Registry* Data2024 = new Registry();
    Data2024->Load("epa2024.csv");
    Registries.push_back(Data2024);

    RBTree* TreeRB = new RBTree();
    SplayTree* TreeSplay = new SplayTree();
    for (int i = 0; i < Registries.size(); i++) {
        for (int j = 0; j < Registries.at(i)->Access().size(); j++) {
            TreeRB->insert(*Registries.at(i)->Access().at(j));
            //TreeSplay->insert(*Registries.at(i)->Access().at(j)); // Fix: Exit Code -10737741819
            // Inserts 1, but not multiple
        }
    }

    cout << "Successful" << endl;
    return 0;
}
