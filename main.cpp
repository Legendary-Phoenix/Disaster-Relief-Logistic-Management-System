#include <iostream>
#include "SupplyStack.h"
#include <string>
using namespace std;



int main()
{
    int option;
    do
    {
        cout << "Welcome to the Disaster Relief Logistics Management System!" << endl;
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
            cout << "Volunteer Operation Officer functionality not implemented yet." << endl;
            break;
        case 3:
            cout << "Emergency Request Coordinator functionality not implemented yet." << endl;
            break;
        case 4:
            cout << "Transport Unit Scheduler functionality not implemented yet." << endl;
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