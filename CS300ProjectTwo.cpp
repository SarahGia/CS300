// CS300ProjectTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Sarah Giannini
//2/23/2025

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

string toUpperCase(string str) {  //convert a string to uppercase
    for (char& c : str) {
        c = toupper(c);
    }
    return str;
}

void loadCourses(map<string, Course>& courses) {  //load courses from file
    string filename;
    cout << "Enter the file name: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Error: Unable to open file.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle, prereq;

        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.courseTitle = courseTitle;

        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courses[courseNumber] = course;
    }

    file.close();
    cout << "Courses loaded successfully.\n";
}

void displayCourses(const map<string, Course>& courses) {  //display all courses alphanumeric
    cout << "\nHere is a sample schedule:\n";

    vector<string> sortedCourses;
    for (const auto& pair : courses) {
        sortedCourses.push_back(pair.first);
    }
    sort(sortedCourses.begin(), sortedCourses.end());

    for (const string& courseNum : sortedCourses) {
        cout << courseNum << ", " << courses.at(courseNum).courseTitle << endl;
    }
}

void searchCourse(const map<string, Course>& courses) {  //search and display a course with prerequisites
    string courseNumber;
    cout << "What course do you want to know about? ";
    cin >> courseNumber;

    courseNumber = toUpperCase(courseNumber);

    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        cout << it->second.courseNumber << ", " << it->second.courseTitle << endl;

        if (!it->second.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < it->second.prerequisites.size(); i++) {
                cout << it->second.prerequisites[i];
                if (i < it->second.prerequisites.size() - 1) {
                    cout << ", ";  //comma formatting
                }
            }
            cout << endl;
        }
        else {
            cout << "No prerequisites.\n";
        }
    }
    else {
        cout << "Course not found.\n";
    }
}

//display the menu
void displayMenu() {
    cout << "\n1. Load Data Structure.\n";
    cout << "2. Print Course List.\n";
    cout << "3. Print Course.\n";
    cout << "9. Exit\n";
}

int main() {
    map<string, Course> courses; //store data
    int choice;

    cout << "Welcome to the course planner.\n";
    do {
        displayMenu();
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            loadCourses(courses);
            break;
        case 2:
            displayCourses(courses);
            break;
        case 3:
            searchCourse(courses);
            break;
        case 9:
            cout << "Thank you for using the course planner!\n";
            break;
        default:
            cout << choice << " is not a valid option.\n";
        }
    } while (choice != 9);

    return 0;
}
