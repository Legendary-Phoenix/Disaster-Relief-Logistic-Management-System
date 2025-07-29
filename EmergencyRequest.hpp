#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

class EmergencyRequest {
private:
    string location;
    string type;
    int    urgency;       // lower number = higher priority (1 = highest)
    string description;   // short description <= 150 words
    int    distanceKm;    // secondary key: lower distance => higher priority

    // Replace commas/newlines to keep CSV parsing simple
    static string sanitizeForCSV(const string& s) {
        string out; out.reserve(s.size());
        for (char c : s) {
            if (c == ',') out.push_back(';');         // avoid breaking CSV fields
            else if (c == '\n' || c == '\r') out.push_back(' ');
            else out.push_back(c);
        }
        return out;
    }

public:
    EmergencyRequest(string loc = "", string t = "", int u = 0,
                     string desc = "", int dist = 0)
        : location(loc), type(t), urgency(u),
          description(desc), distanceKm(dist) {}

    int    getUrgency()     const { return urgency; }
    string getLocation()    const { return location; }
    string getType()        const { return type; }
    string getDescription() const { return description; }
    int    getDistanceKm()  const { return distanceKm; }

    void setDescription(const string& desc) { description = desc; }
    void setDistanceKm(int d) { distanceKm = d; }

    void display() const {
        cout << "[Urgency: " << urgency
             << " | Dist: " << distanceKm << " km]"
             << " Location: " << location
             << " | Type: " << type
             << " | Desc: " << description << "\n";
    }

    // Count words for the 150-word limit
    static int countWords(const string& s) {
        int count = 0; bool inWord = false;
        for (char c : s) {
            if (!isspace(static_cast<unsigned char>(c))) {
                if (!inWord) { inWord = true; ++count; }
            } else {
                inWord = false;
            }
        }
        return count;
    }

    // --- CSV I/O (simple CSV: no quotes; commas sanitized in description) ---
    // Format: location,type,urgency,description,distanceKm
    string toCSV() const {
        return location + "," + type + "," + to_string(urgency) + ","
             + sanitizeForCSV(description) + "," + to_string(distanceKm);
    }

    // Parse a CSV line into an EmergencyRequest.
    // Handling of when desc and distance are empty
    static EmergencyRequest* fromCSV(const string& line) {
        // Collect up to 5 parts by doing at most 4 splits on commas.
        string parts[5];
        int    count = 0;

        size_t start = 0, pos;
        while (count < 4 && (pos = line.find(',', start)) != string::npos) {
            parts[count++] = line.substr(start, pos - start);
            start = pos + 1;
        }
        parts[count++] = (start <= line.size() ? line.substr(start) : "");

        // Mapping
        string loc  = (count > 0 ? parts[0] : "");
        string typ  = (count > 1 ? parts[1] : "");
        int urg     = (count > 2 && !parts[2].empty() ? stoi(parts[2]) : 0);
        string desc = (count > 3 ? parts[3] : "");
        int dist    = (count > 4 && !parts[4].empty() ? stoi(parts[4]) : 0);

        return new EmergencyRequest(loc, typ, urg, desc, dist);
    }
};
