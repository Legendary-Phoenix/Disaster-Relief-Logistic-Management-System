#pragma once
#include <iostream>
#include <string>
#include "TransportUnit.hpp"
#include "TransportUnitScheduler.hpp"

using namespace std;

class TransportMenu {
private:
    TransportUnitScheduler scheduler;

public:
    TransportMenu(int size = 10) : scheduler(size) {}

    void showMenu() {
        int choice;
        do {
            cout << "\n=== Transport Unit Scheduler Menu ===\n";
            cout << "1. Register New Vehicle\n";
            cout << "2. Rotate Vehicle Shift\n";
            cout << "3. Display Vehicle Schedule\n";
            cout << "4. Deploy Front Vehicle\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1:
                    registerVehicle();
                    break;
                case 2:
                    scheduler.rotateVehicleShift();
                    break;
                case 3:
                    scheduler.displaySchedule();
                    break;
                case 4:
                    deployVehicle();
                    break;
                case 0:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    void registerVehicle() {
        string id, type;
        int capacity;

        cout << "Enter Vehicle ID: ";
        getline(cin, id);

        cout << "Enter Vehicle Type: ";
        getline(cin, type);

        cout << "Enter Capacity: ";
        cin >> capacity;
        cin.ignore();

        auto* newUnit = new TransportUnit(id, type, capacity);
        scheduler.addVehicle(newUnit);
    }

    void deployVehicle() {
        // simulate deploying the front unit
        // just mark it in use and increment usage
        cout << "Deploying front unit...\n";
        cout << "Emergency vehicle " << scheduler.getFrontUnit() << " deployed. Rotating..."; 

        scheduler.rotateVehicleShift();
    }
};
