#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "TransportUnit.hpp"
#include "Array.hpp"

using namespace std;

class TransportUnitQueue {
private:
    Array<TransportUnit*> units;
    int front;
    int rear;
    int count;
    int capacity;

public:
    TransportUnitQueue(int size = 10)
        : units(size), front(0), rear(-1), count(0), capacity(size) {}

    int getCount() const { return count; }
    int getFrontIndex() const { return front; }
    int getCapacity() const { return capacity; }
    TransportUnit* getUnitAtIndex(int index) const { return units.get(index); }

    void addVehicle(TransportUnit* unit) {
        if (count == capacity) {
            cout << "Schedule is full. Cannot add more transport units.\n";
            return;
        }

        rear = (rear + 1) % capacity;

        if (rear >= units.size()) {
            // Add new element if this position hasn't been used yet
            units.append(unit);
        } else {
            // Overwrite existing position
            units[rear] = unit;
        }

        count++;
        cout << unit->getId() << " added to schedule.\n";
    }

    void rotateVehicleShift() {
        if (count == 0) {
            cout << "No transport units to rotate.\n";
            return;
        }

        // Move the front vehicle to the rear
        TransportUnit* movedUnit = units.get(front);
        front = (front + 1) % capacity;
        rear = (rear + 1) % capacity;

        if (rear >= units.size()) {
            units.append(movedUnit); // new slot
        } else {
            units[rear] = movedUnit; // overwrite
        }

        cout << "Rotated shift. " << movedUnit->getId() << " moved to rear.\n";
    }

    void displaySchedule() const {
        if (count == 0) {
            cout << "No transport units in schedule.\n";
            return;
        }

        cout << "Current Transport Unit Schedule:\n";
        for (int i = 0; i < count; ++i) {
            int index = (front + i) % capacity;
            if (index >= units.size()) {
                cerr << "[Error] Accessing uninitialized slot at index " << index << "\n";
                continue;
            }
            cout << "- " << units.get(index)->getId() << "\n";
        }
    }

    TransportUnit* getFrontUnit() const {
        if (count == 0) return nullptr;
        return units.get(front);
    }

    void saveToCSV(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Failed to open file for writing.\n";
            return;
        }

        for (int i = 0; i < count; ++i) {
            int index = (front + i) % capacity;
            TransportUnit* unit = units.get(index);
            outFile << unit->getId() << "," << unit->getType() << "," << unit->getUsage() << "\n";
        }

        outFile.close();
        cout << "Schedule saved to " << filename << "\n";
    }

    void loadFromCSV(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "Failed to open file for reading.\n";
            return;
        }

        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string id, type, usageStr;

            if (getline(ss, id, ',') &&
                getline(ss, type, ',') &&
                getline(ss, usageStr)) {
                int usage = stoi(usageStr);
                TransportUnit* unit = new TransportUnit(id, type, usage);
                addVehicle(unit);
            }
        }

        inFile.close();
        cout << "Schedule loaded from " << filename << "\n";
    }
};
