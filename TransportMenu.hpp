// #pragma once
// #include <iostream>
// #include <string>
// #include "TransportUnit.hpp"
// #include "TransportScheduleManager.hpp"

// using namespace std;

// class TransportMenu {
// private:
//     TransportUnitQueue scheduler;

// public:
//     TransportMenu(int size = 10) : scheduler(size) {}

//     void showMenu() {

//         scheduler.loadFromCSV("transports.csv");

//         int choice;
//         do {
//             cout << "\n=== Transport Unit Scheduler Menu ===\n";
//             cout << "1. Register New Vehicle\n";
//             cout << "2. Rotate Vehicle Shift\n";
//             cout << "3. Display Vehicle Schedule\n";
//             cout << "4. Deploy Front Vehicle\n";
//             cout << "5. Save to CSV\n";
//             cout << "6. Load from CSV\n";
//             cout << "0. Exit\n";
//             cout << "Enter choice: ";
//             cin >> choice;
//             cin.ignore();

//             switch (choice) {
//                 case 1:
//                     registerVehicle();
//                     break;
//                 case 2:
//                     scheduler.rotateVehicleShift();
//                     break;
//                 case 3:
//                     scheduler.displaySchedule();
//                     break;
//                 case 4:
//                     deployVehicle();
//                     break;
//                 case 5:
//                     scheduler.saveToCSV("transports.csv");
//                     break;
//                 case 6:
//                     scheduler.loadFromCSV("transports.csv");
//                     break;
//                 case 0:
//                     cout << "Exiting...\n";
//                     break;
//                 default:
//                     cout << "Invalid choice.\n";
//             }
//         } while (choice != 0);
//     }

//     void registerVehicle() {
//         string id, type;
//         int capacity;

//         cout << "Enter Vehicle ID: ";
//         getline(cin, id);

//         cout << "Enter Vehicle Type: ";
//         getline(cin, type);

//         cout << "Enter Capacity: ";
//         cin >> capacity;
//         cin.ignore();

//         auto* newUnit = new TransportUnit(id, type, capacity);
//         scheduler.addVehicle(newUnit);
//     }

//     void deployVehicle() {
//         // simulate deploying the front unit
//         // just mark it in use and increment usage
//         cout << "Deploying front unit...\n";
//         cout << "Emergency vehicle " << scheduler.getFrontUnit() << " deployed. Rotating..."; 

//         scheduler.rotateVehicleShift();
//     }
// };
#pragma once
#include <iostream>
#include <string>
#include "TransportUnit.hpp"
#include "TransportScheduleManager.hpp"

using namespace std;

class TransportMenu {
private:
    TransportScheduleManager manager;

public:
    TransportMenu() {
        // Pre-create queues for known types
        manager.addQueue("Helicopter", 5);
        manager.addQueue("Car", 10);
        manager.addQueue("Truck", 7);
    }

    void showMenu() {
        manager.loadAllFromCSV("schedules");

        int choice;
        do {
            cout << "\n=== Transport Unit Scheduler Menu ===\n";
            cout << "1. Register New Vehicle\n";
            cout << "2. Rotate Vehicle Shift (per type)\n";
            cout << "3. Display All Schedules\n";
            cout << "4. Deploy Front Vehicle (per type)\n";
            cout << "5. Save All to CSV\n";
            cout << "6. Load All from CSV\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1:
                    registerVehicle();
                    break;
                case 2:
                    rotateShift();
                    break;
                case 3:
                    manager.displayAllSchedules();
                    break;
                case 4:
                    deployVehicle();
                    break;
                case 5:
                    manager.saveAllToCSV("schedules");
                    break;
                case 6:
                    manager.loadAllFromCSV("schedules");
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
        int usage;

        cout << "Enter Vehicle ID: ";
        getline(cin, id);

        cout << "Enter Vehicle Type (Helicopter/Car/Truck): ";
        getline(cin, type);

        cout << "Enter Usage Hours: ";
        cin >> usage;
        cin.ignore();

        auto* newUnit = new TransportUnit(id, type, usage);
        manager.addTransportUnit(newUnit);
    }

    void rotateShift() {
        string type;
        cout << "Enter type to rotate (Helicopter/Car/Truck): ";
        getline(cin, type);

        TransportUnitQueue* queue = manager.getQueue(type);
        if (queue) {
            queue->rotateVehicleShift();
        } else {
            cout << "No queue found for type: " << type << "\n";
        }
    }

    void deployVehicle() {
        string type;
        cout << "Enter type to deploy (Helicopter/Car/Truck): ";
        getline(cin, type);

        TransportUnitQueue* queue = manager.getQueue(type);
        if (queue) {
            TransportUnit* unit = queue->getFrontUnit();
            if (unit) {
                cout << "Deploying " << unit->getId() << " (" << unit->getType() << ")\n";
                queue->rotateVehicleShift();
            } else {
                cout << "No vehicles available for deployment.\n";
            }
        } else {
            cout << "No queue found for type: " << type << "\n";
        }
    }
};
