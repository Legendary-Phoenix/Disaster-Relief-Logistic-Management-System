#pragma once

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct SupplyBox{
    int id;
    string type;
    int quantity;
};

class SupplyStack {
    private:
        SupplyBox* stack;
        int top;
        int maxSize;
    public:
        SupplyStack(int size = 50){
            maxSize = size;
            top = -1; // Initialize stack as empty
            stack = new SupplyBox[maxSize];
        };

        // DESTRUCTOR
        ~SupplyStack(){
            delete[] stack;
        };

        // CHECKING IF THE STACK IS FULL OR EMPTY
        bool isFull(){
            return top == maxSize - 1;
        }

        // CHECK IF THE STACK IS EMPTY
        bool isEmpty(){
            return top == -1;
        }

        // PACK NEW SUPPLY BOX
        void packSupplyBox(){
            if (isFull()){
                cout << "Stack is full. Cannot pack more supply boxes." << endl;
                return;
            }

            SupplyBox newBox;
            cout << endl << "Enter Supply Box ID: ";
            cin >> newBox.id;
            cin.ignore(); // Clear the newline character from the input buffer
            cout << "Enter Supply Type : ";
            getline(cin, newBox.type);
            cout << "Enter Quantity: ";
            cin >> newBox.quantity;

            stack[++top] = newBox; // Push the new box onto the stack
            cout << "Supply Box packed successfully!" << endl;
        }

        // SEND SUPPLY PACKAGE (LIFO)
        void sendSupplyPackage(){
            if(isEmpty()){
                cout << "No supply box to dispatch!" << endl;
                return;
            }

            // Pop the top box from the stack
            SupplyBox dispatched = stack[top--];
            cout << "\nDispatched Supply Box: " << endl;
            cout << "ID: " << dispatched.id << endl;
            cout << "Type: " << dispatched.type << endl;
            cout << "Quantity: " << dispatched.quantity << endl;
        }

        // VIEW ALL PACKED SUPPLIES
        void viewPackedSupplies(){
            if(isEmpty()){
                cout << "No packed supplies available!" << endl;
                return;
            }

            cout << "\nPacked Supply Boxes: " << endl;
            cout << left << setw(10) << "ID" << setw(20) << "Type" << setw(10) << "Quantity" << endl;
            cout << "----------------------------------------" << endl;
            for (int i = top; i >= 0; i--){
                cout << left << setw(10) << stack[i].id 
                     << setw(20) << stack[i].type 
                     << setw(10) << stack[i].quantity << endl;
            }
        }

};


