#pragma once
#include <fstream>
#include "Array.hpp"
#include "EmergencyRequest.hpp"

using namespace std;

class PriorityQueue {
private:
    Array<EmergencyRequest*> queue;

    // Lexicographic priority: urgency first (lower is better), then distance (lower is better)
    static bool higherPriority(const EmergencyRequest* a,
                               const EmergencyRequest* b) {
        if (a->getUrgency() != b->getUrgency())
            return a->getUrgency() < b->getUrgency();
        return a->getDistanceKm() < b->getDistanceKm();
    }

public:
    void enqueue(EmergencyRequest* req) {
        // Insert keeping array sorted by priority (highest at front, index 0)
        int i = queue.size() - 1;
        while (i >= 0 && !higherPriority(queue[i], req)) {
            i--;
        }
        queue.insert(i + 1, req);
    }

    EmergencyRequest* dequeue() {
        if (queue.isEmpty()) return nullptr;
        EmergencyRequest* top = queue[0];
        queue.removeAt(0);
        return top;
    }

    bool isEmpty() const { return queue.isEmpty(); }
    int  size()    const { return queue.size(); }
    EmergencyRequest* at(int idx) { return queue[idx]; }

    void display() {
        if (queue.isEmpty()) {
            cout << "No requests.\n";
            return;
        }
        for (int i = 0; i < queue.size(); ++i) {
            cout << i + 1 << ". ";
            queue[i]->display();
        }
    }

    // --- Persistence ---
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) return;
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            EmergencyRequest* req = EmergencyRequest::fromCSV(line);
            enqueue(req);
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (int i = 0; i < queue.size(); ++i) {
            file << queue[i]->toCSV() << "\n";
        }
    }
};
