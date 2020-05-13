#include "faculty.h"
#include <string>

using namespace std;

Faculty::Faculty() {
	int advisorID = 0;
	double gpa = 0.0;	
	string major = "";
	this->setPerson(0, "", "");
	
}

void Faculty::setFaculty(int FacultyID, string name, string level, string dept)
{
	this->setPerson(FacultyID, name, level);
	this->dept = dept;
}

Faculty::~Faculty() {

}

void Faculty::printDetails() {
	cout << endl;
	cout << "Faculty ID: " << getId() << endl;
	cout << "Name      : " << getName() << endl;
	cout << "Level     : " << getLevel() << endl;
	cout << "Dept      : " << dept << endl;
	cout << "Advisees  : " << endl;
	
	int listSize = advisees.GetListSize();
	int tempAdvisee = 0;
	cout << " Faculty has " << listSize << " advisees: " << endl;
	for (int i = 0; i < listSize; ++i) {
		if (advisees.head != NULL) {
			tempAdvisee = advisees.popHead();
			cout << "     Advisee " << i << ": " << tempAdvisee << endl;
			advisees.AddToTail(tempAdvisee);
		}
	}
	cout << endl;
}

string Faculty::getCSV() {
	string csvRec = "";
	csvRec = (to_string(getId()) + "," +
		getName() + "," +
		getLevel() + "," +
		dept + ",");

	int listSize = advisees.GetListSize();
	int tempAdvisee = 0;
	for (int i = 0; i < listSize; ++i) {
		tempAdvisee = advisees.popHead();
		csvRec = csvRec + to_string(tempAdvisee) + ",";
		advisees.AddToTail(tempAdvisee);
	}
	return csvRec;
}




