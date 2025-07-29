#pragma once
#include <iostream>
#include <string>
#include "EmergencyRequest.hpp"
#include "PriorityQueue.hpp"

using namespace std;

inline void emergencyMenu() {
    PriorityQueue pq;
    const string FILE_NAME = "emergency_requests.csv";
    pq.loadFromFile(FILE_NAME);

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
            string location, type, description;
            int urgency;
            cin.ignore(); // clear leftover newline

            cout << "Enter location: ";
            getline(cin, location);

            cout << "Enter type (eg: Fire, medical, food): ";
            getline(cin, type);

            while (true) {
                cout << "Enter short description (<= 150 words): ";
                getline(cin, description);
                int wc = EmergencyRequest::countWords(description);
                if (wc <= 150) break;
                cout << "Description has " << wc
                     << " words. Please shorten to 150 words or fewer.\n";
            }

            cout << "Enter urgency (1 = highest): ";
            cin >> urgency;

            pq.enqueue(new EmergencyRequest(location, type, urgency, description));
            pq.saveToFile(FILE_NAME);
            cout << "Request logged.\n";
        }
        else if (choice == 2) {
            EmergencyRequest* req = pq.dequeue();
            if (req) {
                cout << endl << "Processing request:\n";
                req->display();
                delete req;           // free dequeued request
                pq.saveToFile(FILE_NAME);
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
