#pragma once
#include <iostream>
#include <string>
#include "TransportUnitQueue.hpp"
#include "Array.hpp"

using namespace std;

enum class UnitType {
    Helicopter,
    Car,
    Truck,
    Unknown
};

class TransportScheduleManager {
private:
    Array<TransportUnitQueue*> queues;
    Array<string> typeNames; // Parallel array to store type names for each queue

public:
    TransportScheduleManager() {}

    ~TransportScheduleManager() {
        for (int i = 0; i < queues.size(); ++i)
            delete queues[i];
    }

    void addQueue(const string& typeName, int capacity = 10) {
        queues.append(new TransportUnitQueue(capacity));
        typeNames.append(typeName);
        cout << "Added queue for " << typeName << "\n";
    }

    void addTransportUnit(TransportUnit* unit) {
        for (int i = 0; i < typeNames.size(); ++i) {
            if (typeNames[i] == unit->getType()) {
                queues[i]->addVehicle(unit);
                return;
            }
        }
        cout << "No queue found for type: " << unit->getType() << "\n";
    }

    void displayAllSchedules() const {
        for (int i = 0; i < queues.size(); ++i) {
            cout << "\n=== " << typeNames[i] << " Schedule ===\n";
            queues[i]->displaySchedule();
        }
    }

    void saveAllToCSV(const string& folderPath) const {
        for (int i = 0; i < queues.size(); ++i) {
            string filename = folderPath + "/" + typeNames[i] + "_schedule.csv";
            queues[i]->saveToCSV(filename);
        }
    }

    void loadAllFromCSV(const string& folderPath) {
        for (int i = 0; i < queues.size(); ++i) {
            string filename = folderPath + "/" + typeNames[i] + "_schedule.csv";
            queues[i]->loadFromCSV(filename);
        }
    }
    
    TransportUnitQueue* getQueue(const string& typeName) {
    for (int i = 0; i < typeNames.size(); ++i) {
        if (typeNames[i] == typeName) {
            return queues[i];
        }
    }
    return nullptr;
}

};
