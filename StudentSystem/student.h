#pragma once                  // Prevent double-inclusion
#include <string>
using namespace std;

class Student {
private:
    string id;           // e.g. "S001"
    string name;
    int    age;
    double gpa;

public:
    // Constructor
    Student(string id, string name, int age, double gpa);

    // Display methods
    void display() const;
    void displayRow() const;   // One-line table row format

    // Getters — used for saving and searching
    string getId()   const;
    string getName() const;
    int    getAge()  const;
    double getGpa()  const;

    // Grade helper
    char   getGrade() const;

    // CSV serialisation
    string toCSV() const;      // Returns "id,name,age,gpa"
};
