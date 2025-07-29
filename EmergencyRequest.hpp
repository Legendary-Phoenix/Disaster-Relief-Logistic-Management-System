#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class EmergencyRequest {
private:
    string location;
    string type;
    int urgency;
    string description; //short description (<= 150 words)

    // Replace commas/newlines and collapse newlines to spaces
    static string sanitizeForCSV(const string& s) {
        string out; out.reserve(s.size());
        for (char c : s) {
            if (c == ',' ) out.push_back(';');      // avoid breaking CSV
            else if (c == '\n' || c == '\r') out.push_back(' ');
            else out.push_back(c);
        }
        return out;
    }

public:
    EmergencyRequest(string loc = "", string t = "", int u = 0, string desc = "")
        : location(loc), type(t), urgency(u), description(desc) {}

    int getUrgency() const { return urgency; }
    string getLocation() const { return location; }
    string getType() const { return type; }
    string getDescription() const { return description; }
    void setDescription(const string& desc) { description = desc; }

    void display() const {
        cout << "[Urgency: " << urgency
             << "] Location: " << location
             << " | Type: " << type
             << " | Desc: " << description << "\n";
    }

    string toCSV() const {
        // sanitize description to avoid commas/newlines
        return location + "," + type + "," + to_string(urgency) + "," + sanitizeForCSV(description);
    }

    static EmergencyRequest* fromCSV(const string& line) {
        string fields[4];
        int fi = 0;
        size_t start = 0, pos;
        while (fi < 3 && (pos = line.find(',', start)) != string::npos) {
            fields[fi++] = line.substr(start, pos - start);
            start = pos + 1;
        }
        // last field
        fields[fi++] = (start <= line.size()) ? line.substr(start) : "";
        // If only 3 fields present, set empty description
        string loc   = fields[0];
        string typ   = (fi > 1 ? fields[1] : "");
        int urg      = (fi > 2 ? stoi(fields[2]) : 0);
        string desc  = (fi > 3 ? fields[3] : "");
        return new EmergencyRequest(loc, typ, urg, desc);
    }

    // ---- Word counting utility, words <= 150 ----
    static int countWords(const string& s) {
        int count = 0;
        bool inWord = false;
        for (char c : s) {
            if (!isspace(static_cast<unsigned char>(c))) {
                if (!inWord) { inWord = true; ++count; }
            } else {
                inWord = false;
            }
        }
        return count;
    }
};
