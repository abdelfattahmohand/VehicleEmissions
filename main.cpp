#include <iostream>
#include "registry.h"
#include "RBTree.h"
#include "Splaytree.h"
#include "EPAGrid.h"
#include <string>
#include <chrono>
using namespace std;

int main() {

    EPAGrid* Grid = new EPAGrid();
    Grid->Load("eGRID2021_summary_tables.csv");

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
            splayTrees.at(i)->insert(Registries.at(i)->Access().at(j));
        }
    }

    cout << "Welcome to the 2024 Vehicle Emmissions Data Base!" << endl;
    cout << "Data is availabe from the year 2014 through the year 2024" << endl;
    cout << endl << "Please enter the year you would like to search : " << endl;

    string year;
    getline(cin, year);
    int index = (stoi(year) % 2000) - 14;
    RBTree* RB = rbTrees.at(index);
    SplayTree* Splay = splayTrees.at(index);

    cout << "What state do you live in? Input the 2 letter code in all caps: " << endl;
    string st;
    getline(cin, st);
    EPAGrid::State* state = Grid->Access(st);
    bool exit = false;
    while (!exit){
        cout << "How many cars would you like to search for? (1 or 2 cars, 0 to exit program): " << endl;
        string numCars;
        getline(cin, numCars);

        if (numCars == "0"){
            break;
        }
            // USER INTERFACE FOR 1 CAR SEARCH
        else if (numCars == "1"){
            cout << "Enter the make and model of the car you want to search for: " << endl;
            string car1;
            getline(cin, car1);

            // Same search in R/B and Splay
            auto RBStart = chrono::high_resolution_clock::now();
            Registry::Vehicle* RBTest1 = RB->search(car1);
            auto RBStop = chrono::high_resolution_clock::now();
            auto RBDur = chrono::duration_cast<chrono::nanoseconds>(RBStop - RBStart);

            auto SplayStart = chrono::high_resolution_clock::now();
            Registry::Vehicle* SplayTest1 = Splay->search(car1);
            auto SplayStop = chrono::high_resolution_clock::now();
            auto SplayDur = chrono::duration_cast<chrono::nanoseconds>(SplayStop - SplayStart);

            // Print out search results
            if(RBTest1!= nullptr){
                cout << endl << "------ Car: ";
                cout << RBTest1->model << " ------" << endl;
                cout << "Liters: " << RBTest1->disp << endl;
                cout << "Cylinders: " << RBTest1->cylinders << endl;
                if (RBTest1->fourwd == true) {
                    cout << "4WD" << endl;
                } else {
                    cout << "2WD" << endl;
                }
                cout << "Fuel Type:" << RBTest1->fuel << endl;
                cout << "Authorized for sale in CA: ";
                if (RBTest1->salesCA == true) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
                cout << "Standard: " << RBTest1->standard ;
                cout << " | Description: " << RBTest1->stndDescription << endl;
                cout << "Underhood ID: " << RBTest1->underhoodID << endl;
                cout << "Vehicle Class: " << RBTest1->vehicleClass << endl;

                cout << "All Polution Score: " << RBTest1->allPolutionScore << endl;
                cout << "City MPG: " << RBTest1->cityMPG << endl;
                cout << "HWY MPG: " << RBTest1->hwyMPG << endl;
                cout << "Combined MPG: " << RBTest1->cmbMPG << endl;
                cout << "Greenhouse Gas Score: " << RBTest1->ghgScore << endl;
                cout << "SmartWay Classified: ";
                if (RBTest1->smartWay == true) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
                if (RBTest1->fuel == "Electricity") {
                    cout << "Combined CO2 Index: " << Grid->GetCO2(state, RBTest1->cmbMPG) << endl;
                } else {
                    cout << "Combined CO2 Index: " << RBTest1->combCO2 << endl;
                }

                for (int i = 0; i < RBTest1->duplicates.size(); i++) {
                    Registry::Vehicle* temp = RBTest1->duplicates.at(i);

                    cout << endl;
                    cout << "-- Other car with the same Model " << i + 1 << ": ";

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
                    if (temp->fuel == "Electricity") {
                        cout << "Combined CO2 Index: " << Grid->GetCO2(state, temp->cmbMPG) << endl;
                    } else {
                        cout << "Combined CO2 Index: " << temp->combCO2 << endl;
                    }
                }

                cout << endl << "Time it took to search for car (R/B tree): " << RBDur.count() << " nanoseconds" << endl;
                cout << "Time it took to search for car (Splay tree): " << SplayDur.count() << " nanoseconds" << endl;

                // Calculate speedups
                if (RBDur.count() > SplayDur.count()){
                    double improvement = ((double)RBDur.count() - SplayDur.count()) / RBDur.count() * 100.0;
                    cout << "Splay Tree search was " << fixed << setprecision(2) << improvement << "% faster than Red-Black Tree search!" << endl;
                } else if (RBDur.count() < SplayDur.count()){
                    double improvement = ((double)SplayDur.count() - RBDur.count()) / SplayDur.count() * 100.0;
                    cout << "Red-Black Tree search was " << fixed << setprecision(2) << improvement << "% faster than Splay Tree search!" << endl;
                } else{
                    cout << "Both searches took the exact same time! Wow!" << endl;
                }
            }

            // If car is not found
            else{
                cout << "Sorry, that car is not in our database, try again" << endl << endl;
            }
        }

            // USER INTERFACE FOR 2 CAR SEARCH
        else if (numCars == "2"){

            cout << "Enter the make and model of the first car you want to search for: " << endl;
            string car1;
            getline(cin, car1);

            cout << "Enter the make and model of the second car you want to search for: " << endl;
            string car2;
            getline(cin, car2);

            // Same search in R/B and Splay - Car 1
            auto RBStart = chrono::high_resolution_clock::now();
            Registry::Vehicle* RBTest1 = RB->search(car1);
            auto RBStop = chrono::high_resolution_clock::now();
            auto RBDur1 = chrono::duration_cast<chrono::nanoseconds>(RBStop - RBStart);

            auto SplayStart = chrono::high_resolution_clock::now();
            Registry::Vehicle* SplayTest1 = Splay->search(car1);
            auto SplayStop = chrono::high_resolution_clock::now();
            auto SplayDur1 = chrono::duration_cast<chrono::nanoseconds>(SplayStop - SplayStart);

            if(RBTest1 != nullptr){
                cout << endl << "------ Car 1: ";
                cout << RBTest1->model << " ------" << endl;
                cout << "Liters: " << RBTest1->disp << endl;
                cout << "Cylinders: " << RBTest1->cylinders << endl;
                if (RBTest1->fourwd == true) {
                    cout << "4WD" << endl;
                } else {
                    cout << "2WD" << endl;
                }
                cout << "Fuel Type:" << RBTest1->fuel << endl;
                cout << "Authorized for sale in CA: ";
                if (RBTest1->salesCA == true) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
                cout << "Standard: " << RBTest1->standard ;
                cout << " | Description: " << RBTest1->stndDescription << endl;
                cout << "Underhood ID: " << RBTest1->underhoodID << endl;
                cout << "Vehicle Class: " << RBTest1->vehicleClass << endl;

                cout << "All Polution Score: " << RBTest1->allPolutionScore << endl;
                cout << "City MPG: " << RBTest1->cityMPG << endl;
                cout << "HWY MPG: " << RBTest1->hwyMPG << endl;
                cout << "Combined MPG: " << RBTest1->cmbMPG << endl;
                cout << "Greenhouse Gas Score: " << RBTest1->ghgScore << endl;
                cout << "SmartWay Classified: ";
                if (RBTest1->smartWay == true) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
                cout << "Combined CO2 Index: " << RBTest1->combCO2 << endl;

                for (int i = 0; i < RBTest1->duplicates.size(); i++) {
                    Registry::Vehicle* temp = RBTest1->duplicates.at(i);

                    cout << endl;
                    cout << "-- Other car with the same Model " << i + 1 << ": ";

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
                    if (temp->fuel == "Electricity") {
                        cout << "Combined CO2 Index: " << Grid->GetCO2(state, temp->cmbMPG) << endl;
                    } else {
                        cout << "Combined CO2 Index: " << temp->combCO2 << endl;
                    }
                }
            }
            else{
                cout << endl << "Sorry, car 1 is not in our database, try again" << endl;
            }

            // Same search in R/B and Splay - Car 2
            auto RBStart2 = chrono::high_resolution_clock::now();
            Registry::Vehicle* RBTest2 = RB->search(car1);
            auto RBStop2 = chrono::high_resolution_clock::now();
            auto RBDur2 = chrono::duration_cast<chrono::nanoseconds>(RBStop2 - RBStart2);

            auto SplayStart2 = chrono::high_resolution_clock::now();
            Registry::Vehicle* SplayTest2 = Splay->search(car1);
            auto SplayStop2 = chrono::high_resolution_clock::now();
            auto SplayDur2 = chrono::duration_cast<chrono::nanoseconds>(SplayStop2 - SplayStart2);

            if(RBTest2 != nullptr){
                cout << endl << endl << "------ Car 2: ";
                cout << RBTest2->model << " ------" << endl;
                cout << "Liters: " << RBTest2->disp << endl;
                cout << "Cylinders: " << RBTest2->cylinders << endl;
                if (RBTest2->fourwd == true) {
                    cout << "4WD" << endl;
                } else {
                    cout << "2WD" << endl;
                }
                cout << "Fuel Type:" << RBTest2->fuel << endl;
                cout << "Authorized for sale in CA: ";
                if (RBTest2->salesCA == true) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
                cout << "Standard: " << RBTest2->standard ;
                cout << " | Description: " << RBTest2->stndDescription << endl;
                cout << "Underhood ID: " << RBTest2->underhoodID << endl;
                cout << "Vehicle Class: " << RBTest2->vehicleClass << endl;

                cout << "All Polution Score: " << RBTest2->allPolutionScore << endl;
                cout << "City MPG: " << RBTest2->cityMPG << endl;
                cout << "HWY MPG: " << RBTest2->hwyMPG << endl;
                cout << "Combined MPG: " << RBTest2->cmbMPG << endl;
                cout << "Greenhouse Gas Score: " << RBTest2->ghgScore << endl;
                cout << "SmartWay Classified: ";
                if (RBTest2->smartWay == true) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
                if (RBTest2->fuel == "Electricity") {
                    cout << "Combined CO2 Index: " << Grid->GetCO2(state, RBTest2->cmbMPG) << endl;
                } else {
                    cout << "Combined CO2 Index: " << RBTest2->combCO2 << endl;
                }

                for (int i = 0; i < RBTest2->duplicates.size(); i++) {
                    Registry::Vehicle* temp = RBTest2->duplicates.at(i);

                    cout << endl;
                    cout << "-- Other car with the same Model " << i + 1 << ": ";

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
                    if (RBTest2->fuel == "Electricity") {
                        cout << "Combined CO2 Index: " << Grid->GetCO2(state, RBTest2->cmbMPG) << endl;
                    } else {
                        cout << "Combined CO2 Index: " << RBTest2->combCO2 << endl;
                    }
                }
            }
            else{
                cout << "Sorry, car 2 is not in our database, try again" << endl;
            }

            if (RBTest1 != nullptr and RBTest2 != nullptr){
                cout << endl << "Time it took to search for car 1 (R/B tree): " << RBDur1.count() << " nanoseconds" << endl;
                cout << "Time it took to search for car 1 (Splay tree): " << SplayDur1.count() << " nanoseconds" << endl;

                // Calculate speedups
                if (RBDur1.count() > SplayDur1.count()){
                    double improvement = ((double)RBDur1.count() - SplayDur1.count()) / RBDur1.count() * 100.0;
                    cout << "Splay Tree search was " << fixed << setprecision(2) << improvement << "% faster than Red-Black Tree search for Car 1!" << endl;
                } else if (RBDur1.count() < SplayDur1.count()){
                    double improvement = ((double)SplayDur1.count() - RBDur1.count()) / SplayDur1.count() * 100.0;
                    cout << "Red-Black Tree search was " << fixed << setprecision(2) << improvement << "% faster than Splay Tree search for Car 1!" << endl;
                } else{
                    cout << "Both searches took the exact same time! Wow!" << endl;
                }

                cout << endl << "Time it took to search for car 2 (R/B tree): " << RBDur2.count() << " nanoseconds" << endl;
                cout << "Time it took to search for car 2 (Splay tree): " << SplayDur2.count() << " nanoseconds" << endl;

                if (RBDur2.count() > SplayDur2.count()){
                    double improvement = ((double)RBDur2.count() - SplayDur2.count()) / RBDur2.count() * 100.0;
                    cout << "Splay Tree search was " << fixed << setprecision(2) << improvement << "% faster than Red-Black Tree search for Car 2!" << endl;
                } else if (RBDur2.count() < SplayDur2.count()){
                    double improvement = ((double)SplayDur2.count() - RBDur2.count()) / SplayDur2.count() * 100.0;
                    cout << "Red-Black Tree search was " << fixed << setprecision(2) << improvement << "% faster than Splay Tree search for Car 2!" << endl;
                } else{
                    cout << "Both searches took the exact same time! Wow!" << endl;
                }
            }
            cout << endl << endl;
            }

    }

    cout << endl << endl << "Thank you for using the 2024 Vehicle Emissions Database, have a great day!" << endl;
    return 0;
}
