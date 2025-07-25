#pragma once

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "VolunteerQueue.h"

class VolunteerQueueArray
{
private:
    string *types;          // array of volunteer type names
    VolunteerQueue *queues; // array of corresponding queues
    int capacity;
    int count;

    void resize()
    {
        int newCapacity = capacity * 2;

        string *newTypes = new string[newCapacity];
        VolunteerQueue *newQueues = new VolunteerQueue[newCapacity];

        for (int i = 0; i < count; ++i)
        {
            newTypes[i] = types[i];
            newQueues[i] = queues[i]; // shallow copy is fine since VolunteerQueue has its own internal handling
        }

        delete[] types;
        delete[] queues;

        types = newTypes;
        queues = newQueues;
        capacity = newCapacity;
    }

    int findTypeIndex(const string &typeName) const
    {
        for (int i = 0; i < count; ++i)
        {
            if (types[i] == typeName)
            {
                return i;
            }
        }
        return -1;
    }

public:
    VolunteerQueueArray()
    {
        capacity = 5;
        count = 0;
        types = new string[capacity];
        queues = new VolunteerQueue[capacity];
    }

    ~VolunteerQueueArray()
    {
        delete[] types;
        delete[] queues;
    }

    void addType(const string &typeName)
    {
        if (findTypeIndex(typeName) != -1)
        {
            return;
        }

        if (count == capacity)
        {
            resize();
        }

        types[count] = typeName;
        // queues[count] already constructed
        count++;
    }

    void enqueue(const string &typeName, const Volunteer &v)
    {
        int idx = findTypeIndex(typeName);
        if (idx == -1)
        {
            addType(typeName);
            idx = count - 1;
        }
        queues[idx].enqueue(v);
    }

    Volunteer dequeue(const string &typeName)
    {
        int idx = findTypeIndex(typeName);
        if (idx == -1 || queues[idx].isEmpty())
        {
            throw runtime_error("Invalid type or no volunteers to deploy.");
        }
        return queues[idx].dequeue();
    }

    void displayByType(const string &typeName) const
    {
        int idx = findTypeIndex(typeName);
        if (idx == -1)
        {
            cout << "Volunteer type not found." << endl;
            return;
        }
        cout << "\n\n---Volunteer Type: " << typeName << "---" << endl;
        queues[idx].display();
    }

    void displayAllTypes() const
    {
        if (count == 0)
        {
            cout << "No volunteer types available." << endl;
            return;
        }
        cout << "\nAvailable volunteer types:" << endl;
        for (int i = 0; i < count; ++i)
        {
            cout << i + 1 << ". " << types[i] << endl;
        }
    }

    string getTypeByIndex(int index) const
    {
        if (index < 0 || index >= count)
        {
            throw out_of_range("Invalid type index");
        }
        return types[index];
    }

    int getTypeCount() const
    {
        return count;
    }

    void saveToCSV(const string &filename)
    {
        cout << "Updating volunteer data in file...\n";
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "Error opening file for writing: " << filename << endl;
            return;
        }

        // Write CSV header
        file << "id,name,contact,type\n";

        // Loop through all volunteer queues
        for (int i = 0; i < count; ++i)
        {
            VolunteerQueue &queue = queues[i];
            int count = queue.getSize();

            for (int j = 0; j < count; ++j)
            {
                try
                {
                    Volunteer &v = queue.getVolunteerAt(j);
                    file << v.getId() << "," << v.getName() << "," << v.getContact() << ","
                         << types[i] << "\n";
                }
                catch (const std::out_of_range &e)
                {
                    cout << "Error accessing volunteer: " << e.what() << endl;
                }
            }
        }

        file.close();
        cout << "Data in file succesfully updated." << endl;
    }
};
