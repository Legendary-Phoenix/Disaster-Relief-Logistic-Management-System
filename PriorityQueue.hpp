#pragma once
#include "Array.hpp"
#include "EmergencyRequest.hpp"
using namespace std;

class PriorityQueue {
private:
    Array<EmergencyRequest*> queue;

public:
    void enqueue(EmergencyRequest* req) {
        int i = queue.size() - 1;
        while (i >= 0 && queue[i]->getUrgency() > req->getUrgency()) {
            i--;
        }
        queue.insert(i + 1, req); // insert in sorted position
    }

    EmergencyRequest* dequeue() {
        if (queue.isEmpty()) return nullptr;

        EmergencyRequest* top = queue[0];
        queue.removeAt(0);
        return top;
    }

    void display() {
        if (queue.isEmpty()) {
            cout << "No pending requests.\n";
            return;
        }

        for (int i = 0; i < queue.size(); ++i) {
            cout << i + 1 << ". ";
            queue[i]->display();
        }
    }

    bool isEmpty() {
        return queue.isEmpty();
    }
};
