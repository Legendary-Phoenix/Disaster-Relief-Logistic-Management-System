#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "TransportUnit.hpp"
#include "Array.hpp"

using namespace std;

class TransportUnitScheduler {

private:
    Array<TransportUnit*> units;
    int front;
    int rear;
    int count;
    int capacity;

public:
    TransportUnitScheduler(int size = 10)
        : units(size), front(0), rear(-1), count(0), capacity(size) {}

    void addVehicle(TransportUnit* unit) {
        if (count == capacity) {
            cout << "Schedule is full. Cannot add more transport units.\n";
            return;
        }

        rear = (rear + 1) % capacity;
        if (units.size() < capacity)
            units.insert(rear, unit);
        else
            units[rear] = unit;

        count++;
        cout << unit->getId() << " added to schedule.\n";
    }

    void rotateVehicleShift() {
        if (count == 0) {
            cout << "No transport units to rotate.\n";
            return;
        }

        rear = (rear + 1) % capacity;
        units[rear] = units[front];
        front = (front + 1) % capacity;

        cout << "Rotated shift. " << units[rear]->getId() << " moved to rear.\n";
    }

    void displaySchedule() const {
        if (count == 0) {
            cout << "No transport units in schedule.\n";
            return;
        }

        cout << "Current Transport Unit Schedule:\n";
        for (int i = 0; i < count; ++i) {
            int index = (front + i) % capacity;
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
