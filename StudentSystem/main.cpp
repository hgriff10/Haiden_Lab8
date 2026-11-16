#include "Student.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;


void saveToFile(const vector<Student>& students) {
    ofstream file("data.csv");
    if (!file) {
        cout << "Error: Cannot save to data.csv" << endl;
        return;
    }

    file << "ID,Name,Age,GPA" << endl;

    for (const Student& s : students) {
        file << s.toCSV() << endl;
    }

    file.close();
    cout << students.size() << " record(s) saved to data.csv" << endl;
}


void loadFromFile(vector<Student>& students) {
    ifstream file("data.csv");
    if (!file) {
        cout << "No saved data found. Starting fresh." << endl;
        return;
    }

    students.clear();    // Remove any existing data first
    string line;
    getline(file, line); // Skip the header row

    while (getline(file, line)) {
        string id, name, ageStr, gpaStr;
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, ageStr, ',');
        getline(ss, gpaStr, ',');

        if (id.empty()) continue; // Skip blank lines

        int    age = stoi(ageStr);
        double gpa = stod(gpaStr);
        students.push_back(Student(id, name, age, gpa));
    }

    file.close();
    cout << students.size() << " record(s) loaded from data.csv" << endl;
}


void importFromCSV(vector<Student>& students) {
    string filename;
    cout << "Enter CSV filename to import: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Error: Cannot open " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header
    int imported = 0;

    while (getline(file, line)) {
        string id, name, ageStr, gpaStr;
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, ageStr, ',');
        getline(ss, gpaStr, ',');

        if (id.empty()) continue;

        try {
            students.push_back(Student(id, name, stoi(ageStr), stod(gpaStr)));
            imported++;
        }
        catch (...) {
            cout << "Skipped invalid row: " << line << endl;
        }
    }

    file.close();
    cout << imported << " student(s) imported from " << filename << endl;
}


void addStudent(vector<Student>& students) {
    string id, name; int age; double gpa;
    cout << "Student ID:  "; cin >> id;
    cin.ignore();
    cout << "Name:        "; getline(cin, name);
    cout << "Age:         "; cin >> age;
    cout << "GPA (0-4.0): "; cin >> gpa;
    students.push_back(Student(id, name, age, gpa));
    cout << "Student added successfully!" << endl;
}


void displayAll(const vector<Student>& students) {
    if (students.empty()) { cout << "No records found." << endl; return; }

    cout << endl << "=== All Students ==" << endl;
    cout << left << setw(9) << "ID" << setw(17) << "Name"
        << setw(6) << "Age" << setw(7) << "GPA" << "Grade" << endl;
    cout << string(46, '-') << endl;

    double totalGpa = 0;
    for (const Student& s : students) {
        s.displayRow();
        totalGpa += s.getGpa();
    }

    cout << string(46, '-') << endl;
    cout << "Total: " << students.size()
        << "  |  Avg GPA: " << fixed << setprecision(2)
        << totalGpa / students.size() << endl;
}


void showStats(const vector<Student>& students) {
    if (students.empty()) { cout << "No data." << endl; return; }
    double total = 0, hi = 0, lo = 4.0;
    string hiName, loName;
    for (const Student& s : students) {
        double g = s.getGpa();
        total += g;
        if (g > hi) { hi = g; hiName = s.getName(); }
        if (g < lo) { lo = g; loName = s.getName(); }
    }
    cout << fixed << setprecision(2);
    cout << "Total students:  " << students.size() << endl;
    cout << "Average GPA:     " << total / students.size() << endl;
    cout << "Highest GPA:     " << hi << " (" << hiName << ")" << endl;
    cout << "Lowest GPA:      " << lo << " (" << loName << ")" << endl;
}


int main() {
    vector<Student> students;

    loadFromFile(students);

    int choice;
    do {
        cout << "\n============================================" << endl;
        cout << "  STUDENT RECORD MANAGEMENT SYSTEM         " << endl;
        cout << "============================================" << endl;
        cout << " 1. Add new student" << endl;
        cout << " 2. Display all students" << endl;
        cout << " 3. Save records to file" << endl;
        cout << " 4. Load records from file" << endl;
        cout << " 5. Import from CSV" << endl;
        cout << " 6. Show statistics" << endl;
        cout << " 7. Exit" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(students);     break;
        case 2: displayAll(students);     break;
        case 3: saveToFile(students);     break;
        case 4: loadFromFile(students);   break;
        case 5: importFromCSV(students);  break;
        case 6: showStats(students);      break;
        case 7: cout << "Goodbye!" << endl; break;
        default: cout << "Invalid option." << endl;
        }
    } while (choice != 7);

    return 0;
}