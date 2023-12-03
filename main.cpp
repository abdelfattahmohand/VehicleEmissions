#include <iostream>
#include "registry.h"
#include "RBTree.h"
#include "Splaytree.h"
#include <string>
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

    vector<RBTree*> rbTrees;
    vector<SplayTree*> splayTrees;

    RBTree* RB2014 = new RBTree();
    rbTrees.push_back(RB2014);
    SplayTree* Splay2014 = new SplayTree();
    splayTrees.push_back(Splay2014);

    RBTree* RB2015 = new RBTree();
    rbTrees.push_back(RB2015);
    SplayTree* Splay2015 = new SplayTree();
    splayTrees.push_back(Splay2015);

    RBTree* RB2016 = new RBTree();
    rbTrees.push_back(RB2016);
    SplayTree* Splay2016 = new SplayTree();
    splayTrees.push_back(Splay2016);

    RBTree* RB2017 = new RBTree();
    rbTrees.push_back(RB2017);
    SplayTree* Splay2017 = new SplayTree();
    splayTrees.push_back(Splay2017);

    RBTree* RB2018 = new RBTree();
    rbTrees.push_back(RB2018);
    SplayTree* Splay2018 = new SplayTree();
    splayTrees.push_back(Splay2018);

    RBTree* RB2019 = new RBTree();
    rbTrees.push_back(RB2019);
    SplayTree* Splay2019 = new SplayTree();
    splayTrees.push_back(Splay2019);

    RBTree* RB2020 = new RBTree();
    rbTrees.push_back(RB2020);
    SplayTree* Splay2020 = new SplayTree();
    splayTrees.push_back(Splay2020);

    RBTree* RB2021 = new RBTree();
    rbTrees.push_back(RB2021);
    SplayTree* Splay2021 = new SplayTree();
    splayTrees.push_back(Splay2021);

    RBTree* RB2022 = new RBTree();
    rbTrees.push_back(RB2022);
    SplayTree* Splay2022 = new SplayTree();
    splayTrees.push_back(Splay2022);

    RBTree* RB2023 = new RBTree();
    rbTrees.push_back(RB2023);
    SplayTree* Splay2023 = new SplayTree();
    splayTrees.push_back(Splay2023);

    RBTree* RB2024 = new RBTree();
    rbTrees.push_back(RB2024);
    SplayTree* Splay2024 = new SplayTree();
    splayTrees.push_back(Splay2024);

    for (int i = 0; i < Registries.size(); i++) {
        for (int j = 0; j < Registries.at(i)->Access().size(); j++) {
            rbTrees.at(i)->insert(Registries.at(i)->Access().at(j));
            splayTrees.at(i)->insert(*Registries.at(i)->Access().at(j));
        }
    }

    cout << "Welcome to the 2024 Vehicle Emmissions Data Base" << endl;
    cout << "Data is availabe from the year 2014 through the year 2024" << endl;
    cout << "Please enter the year you would like to search: " << endl;

    string year;
    getline(cin, year);
    int index = (stoi(year) % 2000) - 14;
    RBTree* RB = rbTrees.at(index);
    SplayTree* Splay = splayTrees.at(index);

    cout << "Enter the make and model of the first car you want to search: " << endl;
    string car1;
    getline(cin, car1);

    cout << "Enter the make and model of the second car you want to search: " << endl;
    string car2;
    getline(cin, car2);

    Registry::Vehicle* Test = RB->search(car1);

    cout << "Car 1: ";
    cout << Test->model << endl;
    cout << "Liters: " << Test->disp << endl;
    cout << "Cylinders: " << Test->cylinders << endl;
    if (Test->fourwd == true) {
        cout << "4WD" << endl;
    } else {
        cout << "2WD" << endl;
    }
    cout << "Fuel Type:" << Test->fuel << endl;
    cout << "Authorized for sale in CA: ";
    if (Test->salesCA == true) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    cout << "Standard: " << Test->standard ;
    cout << " | Description: " << Test->stndDescription << endl;
    cout << "Underhood ID: " << Test->underhoodID << endl;
    cout << "Vehicle Class: " << Test->vehicleClass << endl;

    cout << "All Polution Score: " << Test->allPolutionScore << endl;
    cout << "City MPG: " << Test->cityMPG << endl;
    cout << "HWY MPG: " << Test->hwyMPG << endl;
    cout << "Combined MPG: " << Test->cmbMPG << endl;
    cout << "Greenhouse Gas Score: " << Test->ghgScore << endl;
    cout << "SmartWay Classified: ";
    if (Test->smartWay == true) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    cout << "Combined CO2 Index: " << Test->combCO2 << endl;

    for (int i = 0; i < Test->duplicates.size(); i++) {
        Registry::Vehicle* temp = Test->duplicates.at(i);

        cout << endl;
        cout << "Car " << i + 2 << ": ";

        cout << temp->model << endl;
        cout << "Liters: " << temp->disp << endl;
        cout << "Cylinders: " << temp->cylinders << endl;
        if (temp->fourwd == true) {
            cout << "4WD" << endl;
        } else {
            cout << "2WD" << endl;
        }
        cout << "Fuel Type:" << temp->fuel << endl;
        cout << "Authorized for sale in CA: ";
        if (temp->salesCA == true) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
        cout << "Standard: " << temp->standard ;
        cout << " | Description: " << temp->stndDescription << endl;
        cout << "Underhood ID: " << temp->underhoodID << endl;
        cout << "Vehicle Class: " << temp->vehicleClass << endl;

        cout << "All Polution Score: " << temp->allPolutionScore << endl;
        cout << "City MPG: " << temp->cityMPG << endl;
        cout << "HWY MPG: " << temp->hwyMPG << endl;
        cout << "Combined MPG: " << temp->cmbMPG << endl;
        cout << "Greenhouse Gas Score: " << temp->ghgScore << endl;
        cout << "SmartWay Classified: ";
        if (temp->smartWay == true) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
        cout << "Combined CO2 Index: " << temp->combCO2 << endl;
    }

    cout << "Successful" << endl;
    return 0;
}