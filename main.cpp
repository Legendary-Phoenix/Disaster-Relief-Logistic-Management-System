#include <iostream>
#include "SupplyStack.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "VolunteerQueueArray.h"
#include "EmergencyCoordinator.hpp"
#include "TransportMenu.hpp"

using namespace std;


// === GLOBAL ID GENERATOR ===
int volunteerIDCounter = 1;
string generateVolunteerID()
{
    ostringstream oss;
    oss << "V" << setw(3) << setfill('0') << volunteerIDCounter++;
    return oss.str();
}

// === LOAD JSON FUNCTION ===
void loadVolunteersFromJSON(const string &filename, VolunteerQueueArray &vqa)
{
    cout << "Loading volunteer data from file...\n";
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Warning: Could not open file " << filename << ". Skipping CSV load.\n";
        return;
    }

    string line;
    getline(file, line); // skip header
    int maxID = 0;

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, contact, type;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, contact, ',');
        getline(ss, type, ',');

        // Extract numeric part of ID and update maxID
        if (id.length() > 1 && id[0] == 'V')
        {
            try
            {
                int numericID = stoi(id.substr(1));
                if (numericID > maxID)
                    maxID = numericID;
            }
            catch (...)
            {
            }
        }

        Volunteer v(id, name, contact, type);
        vqa.enqueue(type, v);
    }
    volunteerIDCounter = maxID + 1;
    file.close();
    cout << "CSV loaded successfully.\n";
}

// === TYPE SELECTION ===
string promptVolunteerType(VolunteerQueueArray &vqa)
{
    vqa.displayAllTypes();
    cout << vqa.getTypeCount() + 1 << ". Create new type" << endl;
    cout << "Choose a type: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == vqa.getTypeCount() + 1)
    {
        cout << "\nEnter new volunteer type name: ";
        string newType;
        getline(cin, newType);
        vqa.addType(newType);
        cout << "\nNew volunteer type successfully added.";
        return newType;
    }
    else if (choice >= 1 && choice <= vqa.getTypeCount())
    {
        return vqa.getTypeByIndex(choice - 1);
    }
    else
    {
        cout << "Invalid choice. Try again.\n";
        return promptVolunteerType(vqa);
    }
}

// === MENU ===
void volunteerMenu(VolunteerQueueArray &vqa)
{
    while (true)
    {
        cout << "\n=== Volunteer Operations ===\n";
        cout << "1. Register Volunteer\n";
        cout << "2. Deploy Volunteer to Field\n";
        cout << "3. View Registered Volunteers\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            // Register
            string name, contact, skill;

            cout << "\nEnter name: ";
            getline(cin, name);
            cout << "Enter contact: ";
            getline(cin, contact);
            cout << "\n--Assign volunteer to type--";
            string type = promptVolunteerType(vqa);
            string id = generateVolunteerID();

            Volunteer v(id, name, contact, type);
            vqa.enqueue(type, v);

            cout << "\nVolunteer registered successfully.\n";
            vqa.saveToCSV("volunteers.csv");
        }
        else if (choice == 2)
        {
            // Deploy
            if (vqa.getTypeCount() == 0)
            {
                cout << "No volunteer types available.\n";
                continue;
            }
            cout << "\n--Choose volunteer type to deploy--";
            string type = promptVolunteerType(vqa);
            try
            {
                Volunteer deployed = vqa.dequeue(type);
                cout << "\nVolunteer deployed to relief site.\n";
                cout << "\nDeployed volunteer:\n";
                deployed.display();
                cout << "\n";
            }
            catch (const exception &e)
            {
                cout << "Error: " << e.what() << endl;
            }
            vqa.saveToCSV("volunteers.csv");
        }
        else if (choice == 3)
        {
            // View
            if (vqa.getTypeCount() == 0)
            {
                cout << "No volunteer types available.\n";
                continue;
            }

            string type = promptVolunteerType(vqa);
            vqa.displayByType(type);
        }
        else if (choice == 4)
        {
            cout << "Exiting system. Goodbye!\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Try again.\n";
        }
    }
}

int main()
{
    int option;
    VolunteerQueueArray vqa;
    TransportMenu menu;
    
    do
    {
        cout << "\nWelcome to the Disaster Relief Logistics Management System!" << endl;
        cout << "Which operation would you like to perform?" << endl;
        cout << "1. Supply Base Manager" << endl;
        cout << "2. Volunteer Operation Officer" << endl;
        cout << "3. Emergency Request Coordinator" << endl;
        cout << "4. Transport Unit Scheduler" << endl;
        cout << "5. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> option;

        switch (option)
        {
        case 1:
        {
            SupplyStack supplyStack;
            int subOption;
            do
            {
                cout << "\nSupply Base Manager Options:" << endl;
                cout << "1. Pack Supply Box" << endl;
                cout << "2. Send Supply Package" << endl;
                cout << "3. View Packed Supplies" << endl;
                cout << "4. View Dispatched Supplies" << endl;
                cout << "5. Check if Stack is Full" << endl;
                cout << "6. Check if Stack is Empty" << endl;
                cout << "7. Exit to Main Menu" << endl;
                cout << "\nEnter your choice: ";
                cin >> subOption;

                switch (subOption)
                {
                case 1:
                    supplyStack.packSupplyBox();
                    break;
                case 2:
                    supplyStack.sendSupplyPackage();
                    break;
                case 3:
                    supplyStack.viewPackedSupplies();
                    break;
                case 4:
                    supplyStack.viewDispatchedSupplies();
                    break;
                case 5:
                    cout << (supplyStack.isFull() ? "Stack is full." : "Stack is not full.") << endl;
                    break;
                case 6:
                    cout << (supplyStack.isEmpty() ? "Stack is empty." : "Stack is not empty.") << endl;
                    break;
                case 7:
                    cout << "\nReturning to main menu...\n" << endl;
                    break;
                default:
                    cout << "Invalid option. Please try again." << endl;
                }
            } while (subOption != 7);
            break;
        }
        case 2:
            loadVolunteersFromJSON("volunteers.csv", vqa);
            volunteerMenu(vqa);

            break;
        case 3:
            emergencyMenu();
            break;
        case 4:
            menu.showMenu();

            break;
        case 5:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    } while (option != 5);
    return 0;
}
