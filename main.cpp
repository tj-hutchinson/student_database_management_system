#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// here we will create Student Class for the system
class student {
private:
    char Student_Name[50];
    int Roll_No;
    int Social_Studies_Marks, Statistics_Marks, Maths_Marks, English_Marks, Computer_Marks;
    double Student_Percentage;
    char Student_Grade;
    bool flag;
    void CalculateGrade();

public:
    student();
    void getdata();
    void CheckForDuplicationInFile();
    void showdata();
    void TabularDisplay();
    int GetStudentRollNo();
    void ShowStudentRecord(int);
};

void intro();
void entry_menu();

int main() {
    system("clear");
//    system("color B1");
    char ch;
    student std_obj;
    cout.setf(ios::fixed | ios::showpoint);
    cout<<setprecision(2);
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
                break;
            case '2':
                // shows Student Database Management System Code
                entry_menu();
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

void entry_menu()
{

}

void student::getdata()
{
    flag = false;
    cout << "\nEnter the roll no of the student = ";
    cin >> Roll_No;
    CheckForDuplicationInFile();
    if(flag==true)
    {
        cout << "Error duplicate record" << endl;
        return;
    }
    cout << "\n\nEnter the name of student: ";
    cin.ignore();
    cin.getline(Student_Name,50);
    cout << "Enter the marks in Social Studies out of 100: ";
    cin >> Social_Studies_Marks;
    cout << "Enter the marks in Statistics out of 100: ";
    cin >> Statistics_Marks;
    cout << "Enter the marks in Math out of 100: ";
    cin >> Maths_Marks;
    cout << "Enter the marks in English out of 100: ";
    cin >> English_Marks;
    cout << "Enter the marks in Computer Science out of 100: ";
    cin >>Computer_Marks;

    CalculateGrade();
}

void student::showdata()
{
    cout << "\nRoll Number of student = " << Roll_No;
    cout << "\nName of student = " << Student_Name;
    cout << "\nMarks in Social Studies = " << Social_Studies_Marks;
    cout << "\nMarks in Statistics = " << Statistics_Marks;
    cout << "\nMarks in Math = " << Maths_Marks;
    cout << "\nMarks in English = " << English_Marks;
    cout << "\nMarks in Computer Science = " << Computer_Marks;
    cout << "\nPercentage of student = " << Student_Percentage;
    cout << "\nGarde Of Student = " << Student_Grade;
}

// Constructor
student::student()
{
    ofstream outFile("student.dat", ios::binary | ios::app);
    outFile.close();
    ofstream outDFile("DuplicatedCheckingFile.txt", ios::app);
    outDFile.close();
}

void student::CheckForDuplicationInFile()
{
    int Current_RollNo = 0;
    flag = false;
    ifstream infile("DuplicateCheckingFile.txt");
    while(!infile.eof())
    {
        infile >> Current_RollNo;
        if(Current_RollNo==Roll_No)
        {
            flag = true;
        }
    }
    infile.close();
    if(flag==false)
    {
        ofstream outfile("DuplicateCheckingFile.txt", ios::app);
        outfile << "\n" << Roll_No;
        outfile.close();
    }
}

void student::CalculateGrade()
{
    Student_Percentage = (Social_Studies_Marks + Statistics_Marks + Maths_Marks + English_Marks + Computer_Marks) / 5.0;
    if(Student_Percentage>=80)
        Student_Grade = 'A';
    if(Student_Percentage >= 70 && Student_Percentage < 80)
        Student_Grade = 'B';
    if(Student_Percentage >= 60 && Student_Percentage < 70)
        Student_Grade = 'C';
    if(Student_Percentage < 60)
        Student_Grade = 'F';
}

void student::TabularDisplay()
{
    cout << Roll_No << setw(4) << Student_Name << setw(20-strlen(Student_Name)) << Social_Studies_Marks << setw(6) << Statistics_Marks << setw(6) << Maths_Marks << setw(6) << English_Marks << setw(8) << Computer_Marks << setw(8) << Student_Percentage << setw(8) << Student_Grade << endl;
}

int student::GetStudentRollNo()
{
    return Roll_No;
}

void student::ShowStudentRecord(int n)
{
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if(!inFile)
    {
        cout << "File could not be opened. Press any key to continue";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while(inFile.read(reinterpret_cast<char *> (this), sizeof(student)))
    {
        if(GetStudentRollNo() == n)
        {
            showdata();
            flag = true;
        }
    }
    inFile.close();
    if(flag==false) {
        cout << "\n\nrecord does not exist";
        cin.ignore();
        cin.get();
    }

}