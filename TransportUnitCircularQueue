#include <iostream>
#include <string>
using namespace std;

class TransportUnitCircularQueue {
private:
    string* vehicles;
    int capacity;
    int front;
    int rear;
    int count;

public:
    TransportUnitCircularQueue(int size) {
        capacity = size;
        vehicles = new string[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~TransportUnitCircularQueue() {
        delete[] vehicles;
    }

    bool isFull() const {
        return count == capacity;
    }

    bool isEmpty() const {
        return count == 0;
    }

    void addVehicle(const string& vehicleName) {
        if (isFull()) {
            cout << "Schedule is full. Cannot add more vehicles.\n";
            return;
        }
        rear = (rear + 1) % capacity;
        vehicles[rear] = vehicleName;
        count++;
        cout << "Added vehicle: " << vehicleName << endl;
    }

    void rotateVehicleShift() {
        if (isEmpty()) {
            cout << "No vehicles to rotate.\n";
            return;
        }
        // Move the front vehicle to the rear
        string frontVehicle = vehicles[front];
        front = (front + 1) % capacity;
        rear = (rear + 1) % capacity;
        vehicles[rear] = frontVehicle;

        // No change to count, just rotated
        cout << "Rotated vehicle shift. " << frontVehicle << " moved to rear.\n";
    }

    void displaySchedule() const {
        if (isEmpty()) {
            cout << "No vehicles in schedule.\n";
            return;
        }

        cout << "Current Transport Unit Schedule:\n";
        for (int i = 0; i < count; ++i) {
            int idx = (front + i) % capacity;
            cout << i + 1 << ". " << vehicles[idx] << endl;
        }
    }
};
