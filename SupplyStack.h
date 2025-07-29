/*
NAME : MUHAMMAD RIDWAN BIN JESMARNEL
TP NUMBER : TP078616
ROLE: ROLE 1
*/

#pragma once

#include <iostream>
#include <string>
#include <iomanip> // TO BEUTIFY THE OUPUT
#include <fstream> // TO READ AND WRITE FILES
#include <ctime> // FOR TIME STAMPS
#include <sstream>
using namespace std;

struct SupplyBox{
    string id;
    string type;
    int quantity;
    string status;
    string timestamp;
};

class SupplyStack {
    private:
        SupplyBox* stack; // POINTER TO DYNAMIC ARRAY OF SUPPLYBOX
        int top;
        int maxSize;

    public:
        SupplyStack(int size = 50){
            maxSize = size;
            top = -1; // Initialize stack as empty
            stack = new SupplyBox[maxSize];


            //LOAD EXISTING DATA FROM CSV
            loadFromCSV("packed_supplies.csv");

            // CLEARING OR CREATING PACKED CSV AT START
            // ofstream ofs("packed_supplies.csv", ios::trunc);
            // ofs << "ID,Type,Quantity\n";
            // ofs.close();
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

        /*
            *** LOAD THE CSV FILE START ***
        */
        
        void loadFromCSV(const string& filename){
            ifstream fin(filename);
            if(!fin.is_open()){
                cout << "CSV file not found. A new one will be created on first packing the supply." << endl;
                return;
            }

            string line;
            //getline(fin, line);

            while(getline(fin, line)) {
                if(isFull()) break;

                stringstream ss(line);
                string id, type, quantityStr, status, timestamp;
                getline(ss, id, ',');
                getline(ss, type, ',');
                getline(ss, quantityStr, ',');
                getline(ss, status, ',');
                getline(ss, timestamp, ',');

                SupplyBox box;
                box.id = id;
                box.type = type;
                box.status = status;
                box.quantity = stoi(quantityStr);
                box.timestamp = timestamp;
                stack[++top] = box; // Push the box onto the stack
            }
            fin.close();
        }
        /*
            *** LOAD THE CSV FILE END ***
        */


        /*
            ** DATE AND TIME FUNCTION START **
        */
        string getTime(){
            time_t now = time(0);
            tm* localtm = localtime(&now);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtm);
            return string(buffer);
        }
        /*
            ** DATE AND TIME FUNCTION END **
        */

        /*
            *** EXPORT FUNCTION START ***
        */
        void exportToCSV(SupplyBox& box, const string& filename) {
            box.timestamp = getTime(); // Set the timestamp for the box
            ofstream fout(filename, ios::app);
            if(fout.is_open()){
                fout << "BX0" << box.id << "," << box.type << "," << box.quantity << "," << box.status << "," << box.timestamp << "\n";
                fout.close();
            }
        }
        /*
            *** EXPORT FUNCTION END ***
        */

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
            newBox.status = "Packed";

            stack[++top] = newBox; // Push the new box onto the stack
            exportToCSV(newBox, "packed_supplies.csv"); // Export to CSV file
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
            dispatched.status = "Dispatched"; // Update status to dispatched
            exportToCSV(dispatched, "dispatched_supplies.csv"); // Export dispatched box to CSV file
            
            // REWRITE THE CSV FILE
            ofstream fout("packed_supplies.csv");
            //fout << "ID,Type,Quantity,Status,Timestamp\n";
            for(int i = 0; i <= top; i++){
                fout << stack[i].id << ","
                << stack[i].type << ","
                << stack[i].quantity << ","
                << stack[i].status << ","
                << stack[i].timestamp << "\n";
            }

            fout.close();

            //OUTPUT CONFIRMATION
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
            cout << left << setw(10) << "ID" << setw(20) 
                << "Type" << setw(10) << "Quantity" 
                << setw(15) << "Status" 
                << setw(20) << "Time" << endl;
            cout << "-----------------------------------------------------------------------------" << endl;
            for (int i = top; i >= 0; i--){
                cout << left << setw(10) << stack[i].id 
                     << setw(20) << stack[i].type 
                     << setw(10) << stack[i].quantity 
                     << setw(15) << stack[i].status
                     << setw(20) << stack[i].timestamp << endl;
            }
        }

        // VIEW DISPATCHED SUPPLIES
        void viewDispatchedSupplies() {
            ifstream fin("dispatched_supplies.csv");
            if(!fin.is_open()){
                cout << "\nNo dispatched_supplies.csv found." << endl;
                return;
            }

            string line;

            cout << "\nDispatched Supply Boxes: " << endl;
            cout << left << setw(10) << "ID" 
            << setw(20) << "Type" 
            << setw(10) << "Quantity" 
            << setw(15) << "Status" 
            << setw(20)<< "Time" << endl;
            cout << "-----------------------------------------------------------------------------" << endl;
            
            while(getline(fin, line)){
                stringstream ss(line);
                string id, type, quantity, status, timestamp;
                getline(ss, id, ',');
                getline(ss, type, ',');
                getline(ss, quantity, ',');
                getline(ss, status, ',');
                getline(ss, timestamp, ',');
                cout << left << setw(10) << id 
                     << setw(20) << type 
                     << setw(10) << quantity 
                     << setw(15) << status 
                     << setw(20) << timestamp << endl;
            }

            fin.close();
        }

};
