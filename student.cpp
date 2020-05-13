#include "student.h"
#include <string>

using namespace std;

Student::Student() {
	//should I make this able to take user input?
	int advisorID = 0;
	double gpa = 0.0;	
	string major = "";
	this->setPerson(0, "", "");
	
}

void Student:: setStudent (int studentID, int advisorID, double gpa, string name, string level, string major)
{
	setPerson(studentID, name, level);
	this->major = major;
	this->gpa = gpa;
	this->advisorID = advisorID;
}

Student::~Student() {

}

void Student::updateAdvisor(int fid) {
	advisorID = fid;
}

void Student::printDetails() {
	cout << endl;
	cout << "Student ID: " << getId() << endl;
	cout << "Student:    " << getName() << endl;
	cout << "GPA:        " << gpa << endl;
	cout << "Level:      " << getLevel() << endl;
	cout << "Major:      " << major << endl;
	cout << "Advisor ID: " << advisorID << endl;
	cout << endl;
}

string Student::getCSV() {
	string csvRec;

	csvRec = (to_string(getId()) + "," +
		getName() + "," +
		to_string(gpa) + "," +
		getLevel() + "," +
		major + "," +
		to_string(advisorID) + ",");

	return csvRec;
}


