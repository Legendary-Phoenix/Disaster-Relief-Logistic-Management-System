#pragma once

#include <string>
#include <iostream>
using namespace std;

class Volunteer
{
private:
    string id;
    string name;
    string contact;
    string type;

public:
    Volunteer() {}

    Volunteer(string id, string name, string contact, string type)
        : id(id), name(name), contact(contact), type(type) {}

    string getId() const { return id; }
    string getName() const { return name; }
    string getContact() const { return contact; }
    string getType() const { return type; }

    void setId(string id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setContact(string contact) { this->contact = contact; }
    void setType(string skill) { this->type = type; }

    void display() const
    {
        cout << "ID: " << id << "\nName: " << name
             << "\nContact: " << contact << "\nType: " << type << endl;
    }
};
