#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

class Registry {
public:
    struct Vehicle {
        string model;
        float disp;
        int cylinders;
        string transmission;
        bool fourwd;
        string fuel;
        bool salesCA;
        string standard;
        string stndDescription;
        string underhoodID;
        string vehicleClass;

        int allPolutionScore;
        int cityMPG;
        int hwyMPG;
        int cmbMPG;
        int ghgScore;
        bool smartWay;
        int combCO2;

        Vehicle();
    };

    void Load(string filename);

private:
    vector<Vehicle*> storage;
};

Registry::Vehicle::Vehicle() {
    this->disp = 0.0;
    this->cylinders = 0;
    this->fourwd = false;
    this->salesCA = false;
    this->allPolutionScore = 0;
    this->cityMPG = 0;
    this->hwyMPG = 0;
    this->cmbMPG = 0;
    this->ghgScore = 0;
    this->smartWay = false;
    this->combCO2 = 0;
}

void Registry::Load(string filename) {
    ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        cout << "Could not open file :" << filename << endl;
        return;
    }

    string header;
    getline(file, header);

    while(!file.eof()) {
        string line;
        getline(file, line);
        Vehicle* temp = new Vehicle();
        istringstream ss(line);
        string entry;
        vector<string> raw;
        while(getline(ss, entry, ',')) {
            raw.push_back(entry);
        }
        try {
            temp->model = raw.at(0);
            temp->disp = stof(raw.at(1));
            temp->cylinders = stoi(raw.at(2));
            temp->transmission = raw.at(3);
            if (raw.at(4) == "4WD")
                temp->fourwd = true;
            temp->fuel = raw.at(5);
            if (raw.at(6) == "CA")
                temp->salesCA = true;
            temp->standard = raw.at(7);
            temp->stndDescription = raw.at(8);
            temp->underhoodID = raw.at(9);
            temp->vehicleClass = raw.at(10);

            temp->allPolutionScore = stoi(raw.at(11));
            temp->cityMPG = stoi(raw.at(12));
            temp->hwyMPG = stoi(raw.at(13));
            temp->cmbMPG = stoi(raw.at(14));
            temp->ghgScore = stoi(raw.at(15));
            if (raw.at(16) == "Yes")
                temp->smartWay = true;
            temp->combCO2 = stoi(raw.at(17));
        }
        catch(...) {}
    }
}