//
// Created by Terrance Hutchinson on 2/11/23.
//

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

static int RollNoToBeUpdated = 0;

class Student {
public:
    // Constructor
    Student();

    // Get data from user
    void getData();

    // Check for duplicates in file
    void checkForDuplicationInFile();

    // Show data
    void showData();

    // Tabular display
    void tabularDisplay();

    // Get student roll number
    int getStudentRollNo();

    // Show student record
    void showStudentRecord(int);

    // Write student record to file
    void writeStudentRecordToFile();

    // Update student record
    void updateStudentRecord(int);

    // Delete student record
    void deleteStudentRecord(int);

    // Delete from duplicate file
    void deleteFromDuplicateFile(int);

    // Show result menu
    void showResultMenu();

    // Display class result
    void displayClassResult();

private:
    // Student name
    char studentName[50];

    // Roll number
    int rollNo;

    // Marks in various subjects
    int socialStudiesMarks, statisticsMarks, mathsMarks, englishMarks, computerMarks;

    // Percentage
    double studentPercentage;

    // Grade
    char studentGrade;

    // Flag
    bool flag;

    // Calculate grade
    void calculateGrade();
};

#endif // STUDENT_H
