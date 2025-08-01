#pragma once
#include <string>
#include <iostream>

class TransportUnit {
private:
    std::string id;         // Unique identifier
    std::string type;       // e.g. "Truck", "Helicopter"
    std::string status;     // e.g. "Available", "In Use", "Maintenance"
    int capacity;           // Carrying capacity
    int usage;              // Tracks how many times it's been used

public:
    TransportUnit(const std::string& id,
                  const std::string& type,
                  int capacity,
                  const std::string& status = "Available")
        : id(id), type(type), capacity(capacity), status(status), usage(0) {}

    // Getters
    std::string getId() const {
        return id;
    }

    std::string getType() const {
        return type;
    }

    std::string getStatus() const {
        return status;
    }

    int getCapacity() const {
        return capacity;
    }

    int getUsage() const {
        return usage;
    }

    // Setters
    void setId(const std::string& newId) {
        id = newId;
    }

    void setType(const std::string& newType) {
        type = newType;
    }

    void setStatus(const std::string& newStatus) {
        status = newStatus;
    }

    void setCapacity(int newCapacity) {
        capacity = newCapacity;
    }

    void setUsage(int newUsage) {
        usage = newUsage;
    }

    void incrementUsage() {
        usage++;
    }

    // Display
    void printInfo() const {
        std::cout << "ID: " << id
                  << ", Type: " << type
                  << ", Capacity: " << capacity
                  << ", Status: " << status
                  << ", Usage: " << usage << std::endl;
    }
};
