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

    Volunteer(string id, string name, string contact, string skill)
        : id(id), name(name), contact(contact), type(type) {}

    // string getId() const { return id; }
    // string getName() const { return name; }
    // string getContact() const { return contact; }
    // string getSkill() const { return skill; }

    // void setId(string id) { this->id = id; }
    // void setName(string name) { this->name = name; }
    // void setContact(string contact) { this->contact = contact; }
    // void setSkill(string skill) { this->skill = skill; }

    void display() const
    {
        cout << "ID: " << id << "\nName: " << name
             << "\nContact: " << contact << "\nType: " << type << endl;
    }
};
