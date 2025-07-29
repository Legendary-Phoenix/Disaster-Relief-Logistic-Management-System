#pragma once
#include <iostream>
#include <string>
#include "EmergencyRequest.hpp"
#include "PriorityQueue.hpp"

using namespace std;

inline void emergencyMenu() {
    PriorityQueue pq;          // Active pending requests
    PriorityQueue processed;   // Processed history queue

    const string FILE_PENDING   = "emergency_requests.csv";
    const string FILE_PROCESSED = "processed_requests.csv";

    // Load both queues at startup
    pq.loadFromFile(FILE_PENDING);
    processed.loadFromFile(FILE_PROCESSED);

    int choice;
    do {
        cout << "\n--- Emergency Request Coordinator Menu ---\n";
        cout << "1. Log Emergency Request\n";
        cout << "2. View & Process Pending Requests\n";
        cout << "3. View Processed Requests History\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string location, type, description;
            int urgency, distanceKm;

            cin.ignore(); // clear newline
            cout << "Enter location: ";
            getline(cin, location);

            cout << "Enter type (e.g., medical, food): ";
            getline(cin, type);

            // Enforce <= 150 words
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

            cout << "Enter distance from base (km): ";
            cin >> distanceKm;

            pq.enqueue(new EmergencyRequest(location, type, urgency, description, distanceKm));
            pq.saveToFile(FILE_PENDING);
            cout << "Request logged.\n";
        }
        else if (choice == 2) {
            // Sub-loop: keep showing pending list until user enters 0
            while (true) {
                cout << "\n--- Pending Requests (Urgency -> Distance) ---\n";
                pq.display();

                if (pq.isEmpty()) {
                    cout << "\nNo pending requests. Enter 0 to return to menu: ";
                    int back; 
                    cin >> back; 
                    break; // return to main menu
                }
                cout << endl << endl << "--- Options ---" << endl;
                cout << "-1. Process Most Critical Request" << endl;
                cout << " 0. Go back" << endl;
                cout << endl << "Enter request number to process: ";

                int selection;
                cin >> selection;

                if (selection == 0) {
                    break; // return to main menu
                }
                else if (selection == -1) {
                    // Process most critical (front of the queue)
                    EmergencyRequest* req = pq.dequeue();
                    if (req) {
                        cout << "\nProcessing most critical request:\n";
                        req->display();

                        processed.enqueue(req);
                        pq.saveToFile(FILE_PENDING);
                        processed.saveToFile(FILE_PROCESSED);
                    }
                }
                else if (selection >= 1 && selection <= pq.size()) {
                    // Manually process this request by index
                    PriorityQueue temp;

                    for (int i = 0; i < selection - 1; ++i)
                        temp.enqueue(pq.dequeue());

                    EmergencyRequest* selectedReq = pq.dequeue();
                    cout << "\nProcessing selected request:\n";
                    selectedReq->display();
                    processed.enqueue(selectedReq);

                    // Put back temp items
                    while (!temp.isEmpty())
                        pq.enqueue(temp.dequeue());

                    pq.saveToFile(FILE_PENDING);
                    processed.saveToFile(FILE_PROCESSED);
                }
                else {
                    cout << "Invalid selection. Please try again.\n";
                }
            }
        }
        else if (choice == 3) {
            cout << "\n--- Processed Requests (History) ---\n";
            processed.display();
        }
        else if (choice != 0) {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    // Cleanup allocated memory
    while (!pq.isEmpty()) {
        EmergencyRequest* r = pq.dequeue();
        delete r;
    }
    while (!processed.isEmpty()) {
        EmergencyRequest* r = processed.dequeue();
        delete r;
    }
}
