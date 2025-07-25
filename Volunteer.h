#pragma once

#include <iostream>
#include <string>
using namespace std;

class Volunteer
{
public:
    string id;
    string name;
    int age;
    string type;

    Volunteer() {}

    Volunteer(string id, string name, int age, string type)
    {
        this->id = id;
        this->name = name;
        this->age = age;
        this->type = type;
    }

    void display() const
    {
        cout << "ID: " << id << ", Name: " << name << ", Age: " << age << ", Type: " << type << endl;
    }

    int Volunteer::nextID = 1;
};
