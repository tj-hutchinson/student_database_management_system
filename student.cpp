//
// Created by Terrance Hutchinson on 2/11/23.
//

#include "student.h"

// Function to get data for a Student object
void Student::getData() {
// Set flag to false initially
    flag = false;
// Prompt user to enter roll number
    cout << "\nEnter the roll number of the student: ";
// Read roll number from standard input
    cin >> rollNo;
// If the roll number being updated is not the same as the one just entered,
// check for duplication in file
    if (RollNoToBeUpdated != rollNo) {
        checkForDuplicationInFile();
    }
// If a duplicate record was found, print an error message and return from function
    if (flag) {
        cout << "Error: duplicate record" << endl;
        return;
    }
// Prompt user to enter student name
    cout << "\nEnter the name of the student: ";
// Ignore any remaining characters in input buffer and read the name using getline
    cin.ignore();
    cin.getline(studentName, 50);
// Prompt user to enter marks for different subjects and read them from standard input
    cout << "Enter the marks in Social Studies (out of 100): ";
    cin >> socialStudiesMarks;
    cout << "Enter the marks in Statistics (out of 100): ";
    cin >> statisticsMarks;
    cout << "Enter the marks in Math (out of 100): ";
    cin >> mathsMarks;
    cout << "Enter the marks in English (out of 100): ";
    cin >> englishMarks;
    cout << "Enter the marks in Computer Science (out of 100): ";
    cin >> computerMarks;
// Call the calculateGrade function to calculate the grade for this student
    calculateGrade();
}

// Function to check if there is a duplicate record for the current student's roll number in a file
void Student::checkForDuplicationInFile() {
// Initialize currentRollNo to 0 and set flag to false
    int currentRollNo = 0;
    flag = false;
// Open the file for reading
    ifstream infile("DuplicateCheckFile.txt");
// Read roll numbers from the file one by one and compare with the current roll number
    while (infile >> currentRollNo) {
        if (currentRollNo == rollNo) {
// If a duplicate is found, set the flag and break out of the loop
            flag = true;
            break;
        }
    }
// Close the file
    infile.close();
// If no duplicate is found, open the file for writing and append the current roll number to it
    if (!flag) {
        ofstream outfile("DuplicateCheckFile.txt", ios::app);
        outfile << rollNo << "\n";
        outfile.close();
    }
}

// Function to display the data for a Student object
void Student::showData() {
// Print the roll number, name, and marks in different subjects for the student
    cout << "\nRoll number of student: " << rollNo;
    cout << "\nName of student: " << studentName;
    cout << "\nMarks in Social Studies: " << socialStudiesMarks;
    cout << "\nMarks in Statistics: " << statisticsMarks;
    cout << "\nMarks in Math: " << mathsMarks;
    cout << "\nMarks in English: " << englishMarks;
    cout << "\nMarks in Computer Science: " << computerMarks;
// Print the percentage and grade of the student
    cout << "\nPercentage of student: " << studentPercentage;
    cout << "\nGrade of student: " << studentGrade;
}

Student::Student() {
    // Open student data file in binary mode
    ofstream outFile("student.dat", ios::binary | ios::app);
    outFile.close();

    // Open duplicate check file
    ofstream outDFile("DuplicateCheckFile.txt", ios::app);
    outDFile.close();
}

// Function to write the data for a Student object to a binary file
void Student::writeStudentRecordToFile() {
// Open the file for writing in binary mode and append mode
    ofstream outFile("student.dat", ios::binary | ios::app);
// Call the getData function to get input from the user and check for duplicate records
    getData();
// If no duplicate record was found, write the data for this student to the file
    if (!flag) {
        outFile.write(reinterpret_cast<char*>(this), sizeof(Student));
        cout << "\nStudent record created." << endl;
    } else {
// If a duplicate record was found, print an error message
        cout << "Record not created due to duplication." << endl;
    }
// Close the file and wait for user to press Enter to continue
    outFile.close();
    cin.ignore();
    cin.get();
}

// Function to update the record for a student with a given roll number in the binary file
void Student::updateStudentRecord(int rollNo) {
// Set the RollNoToBeUpdated variable to the given roll number
    RollNoToBeUpdated = rollNo;
// Initialize found to false and open the file in binary mode for reading and writing
    bool found = false;
    fstream file("student.dat", ios::binary | ios::in | ios::out);
// If the file could not be opened, print an error message and return from function
    if (!file) {
        cout << "File could not be opened. Press any key to continue." << endl;
        cin.ignore();
        cin.get();
        return;
    }
// Read the data for each student in the file and check if their roll number matches the given roll number
    while (file.read(reinterpret_cast<char*>(this), sizeof(Student))) {
        if (getStudentRollNo() == rollNo) {
// If a matching student is found, display their current data and prompt the user to enter new data
            showData();
            cout << "\n\nPlease enter the new details of the student." << endl;
            getData();
// If no duplicate record is found, update the data for this student in the file
            if (!flag) {
                int pos = (-1) * static_cast<int>(sizeof(this));
                file.seekp(pos, ios::cur);
                file.write(reinterpret_cast<char *>(this), sizeof(Student));
            }
            found = true;
            break;
        }
    }
// Close the file and print appropriate message based on whether a matching record was found and whether a duplicate was found
    file.close();
    if (flag) {
        cout << "Could not update because this roll number already exists." << endl;
    } else if (!found) {
        cout << "\nRecord not found." << endl;
    }
    cin.ignore();
    cin.get();
// If no duplicate was found and a matching record was found and updated, delete the previous record from the duplicate check file
    if (!flag && found && RollNoToBeUpdated != rollNo) {
        deleteFromDuplicateFile(rollNo);
    }
// Reset the RollNoToBeUpdated variable to 0
    RollNoToBeUpdated = 0;
}

// Function to delete the record for a student with a given roll number from the binary file
void Student::deleteStudentRecord(int rollNo) {
// Open the file in binary mode for reading
    ifstream inFile("student.dat", ios::binary);
// If the file could not be opened, print an error message and return from function
    if (!inFile) {
        cout << "\nFile could not be opened. Press any key to continue." << endl;
        cin.ignore();
        cin.get();
        return;
    }
// Open a temporary file for writing
    ofstream outFile("Temp.dat", ios::out);
// Read the data for each student in the file and write their data to the temporary file if their roll number does not match the given roll number
    while (inFile.read(reinterpret_cast<char*>(this), sizeof(Student))) {
        if (getStudentRollNo() != rollNo) {
            outFile.write(reinterpret_cast<char*>(this), sizeof(Student));
        }
    }
// Close the input and output files and delete the original file and rename the temporary file to the original file name
    outFile.close();
    inFile.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
// Print a message to indicate that the record has been deleted and wait for user to press Enter to continue
    cout << "\nRecord deleted. Press any key to continue." << endl;
    cin.ignore();
    cin.get();
// Delete the roll number of the deleted record from the duplicate check file
    deleteFromDuplicateFile(rollNo);
}

// Function to delete a roll number from the duplicate check file
void Student::deleteFromDuplicateFile(int rollNoOfRecord) {
// Initialize currentRollNo to 0 and open the file for reading and a temporary file for writing
    int currentRollNo = 0;
    ifstream inFile("DuplicateCheckFile.txt");
    ofstream outFile("TempFile.txt");
// Read the roll numbers from the input file and write them to the temporary file if they do not match the given roll number
    while (inFile >> currentRollNo) {
        if (currentRollNo != rollNoOfRecord) {
            outFile << "\n" << currentRollNo;
        }
    }
// Close the input and output files, delete the original file, and rename the temporary file to the original file name
    inFile.close();
    outFile.close();
    remove("DuplicateCheckFile.txt");
    rename("TempFile.txt", "DuplicateCheckFile.txt");
// Wait for user to press Enter to continue
    cin.ignore();
    cin.get();
}

// Function to calculate the grade for a Student object based on the percentage of marks
void Student::calculateGrade() {
// Calculate the percentage of marks and assign it to the studentPercentage variable
    studentPercentage = (socialStudiesMarks + statisticsMarks + mathsMarks + englishMarks + computerMarks) / 5.0;
// Assign a grade based on the percentage of marks
    if (studentPercentage >= 80) {
        studentGrade = 'A';
    } else if (studentPercentage >= 70) {
        studentGrade = 'B';
    } else if (studentPercentage >= 60) {
        studentGrade = 'C';
    } else {
        studentGrade = 'F';
    }
}

// Function to display the data for a Student object in a tabular format
void Student::tabularDisplay() {
// Print the roll number, name, marks in different subjects, percentage and grade in a tabular format with appropriate column widths
    cout << left << setw(15) << rollNo << setw(20) << studentName
         << left << setw(20) << socialStudiesMarks
         << left << setw(15) << statisticsMarks
         << left << setw(15) << mathsMarks
         << left << setw(15) << englishMarks
         << left << setw(20) << computerMarks
         << left << setw(15) << fixed << setprecision(2) << studentPercentage
         << left << setw(15) << studentGrade << endl;
}

int Student::getStudentRollNo() {
    return rollNo;
}

// Function to display the data for a Student object with a given roll number
void Student::showStudentRecord(int n) {
// Open the file in binary mode for reading
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
// If the file could not be opened, print an error message and return from function
    if (!inFile) {
        cout << "File could not be opened. Press any key to continue" << endl;
        cin.ignore();
        cin.get();
        return;
    }
// Initialize found to false and read the data for each student in the file and display the data if the roll number matches the given roll number
    bool found = false;
    while (inFile.read(reinterpret_cast<char *>(this), sizeof(Student))) {
        if (getStudentRollNo() == n) {
            showData();
            found = true;
        }
    }
// Close the file and print a message to indicate whether the record was found or not and wait for user to press Enter to continue
    inFile.close();
    if (!found) {
        cout << "\n\nRecord not found" << endl;
        cin.ignore();
        cin.get();
    }
}

// Function to display a menu for showing the class result or the report card for a student
void Student::showResultMenu()
{
    char ch;
    int roll_no;
// Clear the terminal screen
    system("clear");
// Display the menu options for class result, report card, and back to main menu
    cout << "\n\n\n\tRESULT MENU";
    cout << "\n\n\n\t1. Class Result";
    cout << "\n\n\t2. Student Report Card";
    cout << "\n\n\n\t3. Back to Main Menu";
    cout << "\n\n\n\tEnter Choice (1/2/3): ";
    cin >> ch;
// Clear the terminal screen
    system("clear");
// Call the appropriate function based on the user's choice
    switch(ch)
    {
        case '1':
            displayClassResult();
            break;
        case '2':
            cout << "\n\n\tEnter the Roll Number of the Student: ";
            cin >> roll_no;
            showStudentRecord(roll_no);
            break;
        case '3':
            break;
        default:
            cout << "\a";
    }
}

// This function displays the class result of students by reading data from a binary file "student.dat"
void Student::displayClassResult()
{
    // Open the file "student.dat" in binary mode
    ifstream inFile("student.dat", ios::binary);

    // Check if the file was successfully opened
    if (!inFile)
    {
        // If the file could not be opened, display an error message and return
        cout << "File could not be opened.. Press any key to continue..";
        cin.ignore();
        cin.get();
        return;
    }

    // Display the header
    cout << "\n\n\t\tALL CLASS RESULT \n\n";
    cout << left << setw(15) << "Roll Number" << setw(20) << "Name"
         << setw(20) << "Social Studies" << setw(15) << "Statistics"
         << setw(15) << "Math" << setw(15) << "English"
         << setw(20) << "Computer Science" << setw(15) << "Percentage"
         << setw(15) << "Grade" << endl;
    cout << setfill('-') << setw(150) << "" << endl;
    cout << setfill(' ');

    // Read the data from the file and display it
    while (inFile.read(reinterpret_cast<char *>(this), sizeof(Student)))
    {
        // Call the tabularDisplay() function to display the data in tabular form
        tabularDisplay();
    }

    // Close the file
    inFile.close();

    // Wait for the user to press a key
    cin.ignore();
    cin.get();
}