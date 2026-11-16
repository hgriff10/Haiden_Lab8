#include "Student.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

// Constructor
Student::Student(string i, string n, int a, double g)
    : id(i), name(n), age(a), gpa(g) {}

// Getters
string Student::getId()   const { return id; }
string Student::getName() const { return name; }
int    Student::getAge()  const { return age; }
double Student::getGpa()  const { return gpa; }

// Grade helper — converts GPA to letter grade
char Student::getGrade() const {
    if (gpa >= 3.7) return 'A';
    if (gpa >= 3.0) return 'B';
    if (gpa >= 2.0) return 'C';
    if (gpa >= 1.0) return 'D';
    return 'F';
}

// Full card-style display
void Student::display() const {
    cout << "ID:    " << id << endl;
    cout << "Name:  " << name << endl;
    cout << "Age:   " << age << endl;
    cout << "GPA:   " << fixed << setprecision(2) << gpa << endl;
    cout << "Grade: " << getGrade() << endl;
}

// One-line row for the summary table
void Student::displayRow() const {
    cout << left
        << setw(9) << id
        << setw(17) << name
        << setw(6) << age
        << setw(7) << fixed << setprecision(2) << gpa
        << setw(5) << getGrade()
        << endl;
}

// CSV line — used when saving to file
string Student::toCSV() const {
    return id + "," + name + "," + to_string(age)
        + "," + to_string(gpa);
}
