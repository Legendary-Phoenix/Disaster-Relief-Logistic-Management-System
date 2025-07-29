#pragma once
#include <iostream>
#include "TransportUnit.hpp"
#include "Array.hpp"

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
            std::cout << "Schedule is full. Cannot add more transport units.\n";
            return;
        }

        // Insert into correct rear position
        rear = (rear + 1) % capacity;
        if (units.size() < capacity)
            units.insert(rear, unit);  // fill empty slots initially
        else
            units[rear] = unit;        // overwrite slot

        count++;
        std::cout << unit->getId() << " added to schedule.\n";
    }

    void rotateVehicleShift() {
        if (count == 0) {
            std::cout << "No transport units to rotate.\n";
            return;
        }

        rear = (rear + 1) % capacity;
        units[rear] = units[front];
        front = (front + 1) % capacity;

        std::cout << "Rotated shift. " << units[rear]->getId() << " moved to rear.\n";
    }

    void displaySchedule() const {
        if (count == 0) {
            std::cout << "No transport units in schedule.\n";
            return;
        }

        std::cout << "Current Transport Unit Schedule:\n";
        for (int i = 0; i < count; ++i) {
            int index = (front + i) % capacity;
            std::cout << "- " << units[index]->getId() << "\n";
        }
    }

    TransportUnit* getFrontUnit() const {
        if (count == 0) return nullptr;
        return units[front];
    }

};
