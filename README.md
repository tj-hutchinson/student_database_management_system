# Student Record Management System

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

A program written in C++ to manage student records. The program allows the user to perform various operations such as adding a new student record, displaying the record of a specific student, updating an existing record, deleting a record, and displaying the class result. The program also checks for duplicate records in the file and deletes them if necessary.

## Features

- Add a new student record
- Display the record of a specific student
- Update an existing record
- Delete a record
- Display the class result
- Check for duplicate records in the file and delete them
- Tabular display of student records

## Usage
1. Compile the program using a C++ compiler.
2. Run the executable file.
3. Follow the instructions on the screen to perform the desired operation.

## Class Methods
- Student: Constructor method
- getData: Get data from user
- checkForDuplicationInFile: Check for duplicates in file
- showData: Show data
- tabularDisplay: Tabular display
- getStudentRollNo: Get student roll number
- showStudentRecord: Show student record
- writeStudentRecordToFile: Write student record to file
- updateStudentRecord: Update student record
- deleteStudentRecord: Delete student record
- deleteFromDuplicateFile: Delete from duplicate file
- showResultMenu: Show result menu
- displayClassResult: Display class result

## Private Members
- studentName: Student name
- rollNo: Roll number
- socialStudiesMarks, statisticsMarks, mathsMarks, englishMarks, computerMarks: Marks in various subjects
- studentPercentage: Percentage
- studentGrade: Grade
- flag: Flag
- calculateGrade: Calculate grade

## Note

This program is written in C++ and is meant to be used as a demonstration of basic file handling and data management concepts in C++. It is not meant to be used in a production environment.
