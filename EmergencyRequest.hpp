#pragma once
#include <iostream>
#include <string>
using namespace std;

class EmergencyRequest {
private:
    string location;
    string type;
    int urgency;

public:
    EmergencyRequest(string loc = "", string t = "", int u = 0)
        : location(loc), type(t), urgency(u) {}

    int getUrgency() const { return urgency; }
    string getLocation() const { return location; }
    string getType() const { return type; }

    void display() const {
        cout << "[Urgency: " << urgency
             << "] Location: " << location
             << " | Type: " << type << "\n";
    }
};
