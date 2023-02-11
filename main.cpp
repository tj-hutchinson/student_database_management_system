#include "student.h"

void intro();

void displayEntryMenu();

void displayAllRecords();

int main() {
    system("clear");
    char ch;
    Student std_obj;
    cout.setf(ios::fixed | ios::showpoint);
    cout << setprecision(2);
    intro();
    do {
        system("clear");
        intro();
        cout << "\n\n\n\t\t\t\tHOME SCREEN\n\n\n";
        cout << "\n\n\t1. Result Calculation System";
        cout << "\n\n\t2. Student Database Management System";
        cout << "\n\n\t3. Exit";
        cout << "\n\n\n\n\n\tPlease Select Your Option (1-3)";
        cin >> ch;
        switch (ch) {
            case '1':
                //shows Result Calculation System
                std_obj.showResultMenu();
                break;
            case '2':
                // shows Student Database Management System Code
                displayEntryMenu();
                break;
            case '3':
                // User wants to exit the system
                break;
            default:
                cout << "\a";
        }
    } while (ch != '3');

    system("read -p 'Press any key to continue...' var"); // second last statement that stops the output screen till the user presses any key
    return 0; // main ends here
}

void intro() {
    cout << "\n\n\n**** WELCOME TO STUDENT DATABASE MANAGEMENT AND RESULT CALCULATION SYSTEM ****\n\n";
}

void displayEntryMenu() {
    // Input character
    char ch;
    // Input roll number
    int rollNum;
    // Student object
    Student std;

    // Clear the console screen
    system("clear");

    // Display the menu options
    cout << "\n\n\n\t\t\tSTUDENT DATABASE MANAGEMENT SYSTEM MENU";
    cout << "\n\n\t1. CREATE STUDENT RECORD";
    cout << "\n\n\t2. SHOW RECORDS OF ALL STUDENTS";
    cout << "\n\n\t3. SEARCH STUDENT RECORDS";
    cout << "\n\n\t4. UPDATE STUDENT RECORD";
    cout << "\n\n\t5. DELETE STUDENT RECORD";
    cout << "\n\n\t6. BACK TO HOME SCREEN";
    cout << "\n\n\n\n\tPlease Enter Your Choice (1-6) ";

    // Read the user's choice
    cin >> ch;

    // Clear the console screen
    system("clear");

    // Execute the chosen option
    switch (ch) {
        case '1':
            std.writeStudentRecordToFile();
            break;
        case '2':
            displayAllRecords();
            break;
        case '3':
            cout << "\n\n\t Please Enter The Roll Number";
            cin >> rollNum;
            std.showStudentRecord(rollNum);;
            break;
        case '4':
            cout << "\n\n\t Please Enter The Roll Number";
            cin >> rollNum;
            std.updateStudentRecord(rollNum);
            break;
        case '5':
            cout << "\n\n\t Please Enter The Roll Number";
            cin >> rollNum;
            std.deleteStudentRecord(rollNum);
            break;
        case '6':
            break;
        default:
            cout << "\a";
            displayEntryMenu();
    }
}

void displayAllRecords() {
    Student st;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened !! Press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\n\t\tDISPLAY ALL RECORDS !!!\n\n";
    while (inFile.read(reinterpret_cast<char *> (&st), sizeof(Student))) {
        st.showData();
        cout << "\n\n============================================\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}