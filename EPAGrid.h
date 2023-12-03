#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

// Citation: EPA Grid Data from https://www.epa.gov/egrid/summary-data
class EPAGrid {
public:
    struct State {
        string name;
        float co2;
        float ch4;
        float n2o;
        float co2e;
        float annualNOx;
        float ozoneSznNOx;
        float so2;
        State(); // Constructor
    };

    void Load(string filename);
    State* Access(string state);
    int GetCO2(State* st, int cmbMPG);

private:
    vector<State*> grid;
};

EPAGrid::State::State() {
    this->name = "";
    this->co2 = 0.0;
    this->ch4 = 0.0;
    this->n2o = 0.0;
    this->co2e = 0.0;
    this->annualNOx = 0.0;
    this->ozoneSznNOx = 0.0;
    this->so2 = 0.0;
}

void EPAGrid::Load(string filename) {
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
        State* temp = new State();
        istringstream ss(line);
        string entry;
        vector<string> raw;
        while(getline(ss, entry, ',')) {
            raw.push_back(entry);
        }
        try {
            temp->name = raw.at(0);
            temp->co2 = stof(raw.at(1));
            temp->ch4 = stof(raw.at(2));
            temp->n2o = stof(raw.at(3));
            temp->co2e = stof(raw.at(4));
            temp->annualNOx = stof(raw.at(5));
            temp->ozoneSznNOx = stof(raw.at(6));
            temp->so2 = stof(raw.at(7));
            grid.push_back(temp);
        }
        catch(...) {}
    }
}

EPAGrid::State* EPAGrid::Access(string state) {
    for (int i = 0; i < EPAGrid::grid.size(); i++) {
        if (EPAGrid::grid.at(i)->name == state) {
            return EPAGrid::grid.at(i);
        }
    }
    return nullptr;
}

int EPAGrid::GetCO2(State* st, int cmbMPG) {
    int final = 0;
    float co2 = cmbMPG / 33.7; // Convert miles/gal to miles/kwh
    co2 = co2 * 1000; // convert to miles/mwh
    co2 = 1 / co2; // convert to mwh/mile
    co2 = co2 * st->co2; // convert to lb/mile
    co2 = co2 * 453.6; // convert to g/mile
    final = co2; // convert to int, round
    return final;
}