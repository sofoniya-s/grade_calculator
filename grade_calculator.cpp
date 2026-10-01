

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct Course {
    string name;
    double creditHours;
    double mark;
    string letter;
    double gradePoint;
};

// Convert a mark (0-100) to a letter grade and grade point.
// Edit these ranges if your university uses a different scale.
void convertMark(double mark, string &letter, double &gp) {
    if (mark >= 90)      { letter = "A+"; gp = 4.00; }
    else if (mark >= 85) { letter = "A";  gp = 4.00; }
    else if (mark >= 80) { letter = "A-"; gp = 3.75; }
    else if (mark >= 75) { letter = "B+"; gp = 3.50; }
    else if (mark >= 70) { letter = "B";  gp = 3.00; }
    else if (mark >= 65) { letter = "B-"; gp = 2.75; }
    else if (mark >= 60) { letter = "C+"; gp = 2.50; }
    else if (mark >= 50) { letter = "C";  gp = 2.00; }
    else if (mark >= 45) { letter = "C-"; gp = 1.75; }
    else if (mark >= 40) { letter = "D";  gp = 1.00; }
    else                 { letter = "F";  gp = 0.00; }
}

// Read a number between lo and hi, repeating until the input is valid.
double readNumber(const string &prompt, double lo, double hi) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= lo && value <= hi) {
            return value;
        }
        cout << "  Invalid input. Enter a number from " << lo << " to " << hi << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    cout << "====================================\n";
    cout << "     UNIVERSITY GRADE CALCULATOR    \n";
    cout << "====================================\n\n";

    int n = static_cast<int>(readNumber("How many courses this semester? ", 1, 20));
    vector<Course> courses;

    for (int i = 0; i < n; i++) {
        Course c;
        cout << "\n--- Course " << (i + 1) << " ---\n";
        cout << "Course name: ";
        cin >> ws;
        getline(cin, c.name);
        c.creditHours = readNumber("Credit hours (1-10): ", 1, 10);
        c.mark = readNumber("Total mark (0-100): ", 0, 100);
        convertMark(c.mark, c.letter, c.gradePoint);
        courses.push_back(c);
    }

    double totalCredits = 0, totalPoints = 0, totalMarks = 0;

    cout << "\n" << left << setw(24) << "Course"
         << right << setw(8) << "Credit"
         << setw(8) << "Mark"
         << setw(8) << "Grade"
         << setw(8) << "Point" << "\n";
    cout << string(56, '-') << "\n";

    cout << fixed << setprecision(2);
    for (const Course &c : courses) {
        cout << left << setw(24) << c.name.substr(0, 22)
             << right << setw(8) << c.creditHours
             << setw(8) << c.mark
             << setw(8) << c.letter
             << setw(8) << c.gradePoint << "\n";
        totalCredits += c.creditHours;
        totalPoints += c.gradePoint * c.creditHours;
        totalMarks += c.mark;
    }
    cout << string(56, '-') << "\n";

    double semesterGPA = totalPoints / totalCredits;
    double average = totalMarks / courses.size();

    cout << "Total credit hours : " << totalCredits << "\n";
    cout << "Average mark       : " << average << "\n";
    cout << "Semester GPA       : " << semesterGPA << "\n";

    // Optional: cumulative GPA
    char choice;
    cout << "\nCalculate cumulative GPA (CGPA)? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        double prevGPA = readNumber("Previous CGPA (0-4): ", 0, 4);
        double prevCredits = readNumber("Previous total credit hours: ", 0, 1000);
        double cgpa = (prevGPA * prevCredits + totalPoints) / (prevCredits + totalCredits);
        cout << "New CGPA           : " << cgpa << "\n";
    }

    
    cout << "\n";
    if (semesterGPA >= 3.75)      cout << "Standing: Great Distinction\n";
    else if (semesterGPA >= 3.25) cout << "Standing: Very Good\n";
    else if (semesterGPA >= 2.75) cout << "Standing: Good\n";
    else if (semesterGPA >= 2.00) cout << "Standing: Satisfactory\n";
    else                          cout << "Standing: Below 2.00 - academic warning range\n";

    return 0;
}
