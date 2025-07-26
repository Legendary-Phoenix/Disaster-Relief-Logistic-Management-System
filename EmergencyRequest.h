#include <string>
#include <iostream>
using namespace std;

class EmergencyRequest {
  private:
    string location;
    string type;
    int urgency;

  public:
    EmergencyRequest(string loc, string t, int u):
      location(loc), type(t), urgency(u) {}

    int getUrgency() const { return urgency; }
    string getLocation() const {return location;}
    string getType() const {return type;}

    void display() const {
      cout << "Location: " << location << " | Type: " << type << " | Urgency: " << urgency << endl;
    }
};