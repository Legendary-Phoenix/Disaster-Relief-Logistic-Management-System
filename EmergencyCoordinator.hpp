#pragma once
#include <iostream>
#include <string>
#include "EmergencyRequest.hpp"
#include "PriorityQueue.hpp"

using namespace std;

inline void emergencyMenu() {
    PriorityQueue pq;
    int choice;

    do {
        cout << "\n--- Emergency Request Coordinator Menu ---\n";
        cout << "1. Log Emergency Request\n";
        cout << "2. Process Most Critical Request\n";
        cout << "3. View Pending Requests\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string location, type;
            int urgency;
            cin.ignore();
            cout << "Enter location: ";
            getline(cin, location);
            cout << "Enter type (e.g., medical, food): ";
            getline(cin, type);
            cout << "Enter urgency (1 = highest): ";
            cin >> urgency;

            pq.enqueue(new EmergencyRequest(location, type, urgency));
            cout << "Request logged.\n";
        }
        else if (choice == 2) {
            EmergencyRequest* req = pq.dequeue();
            if (req) {
                cout << "Processing request:\n";
                req->display();
                delete req;
            } else {
                cout << "No requests to process.\n";
            }
        }
        else if (choice == 3) {
            cout << "\n--- Pending Requests ---\n";
            pq.display();
        }
        else if (choice != 0) {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);
}
