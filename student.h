#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include "person.cpp"

// Contains the student class with the override in the operators
// These will compare the two students for equality

using namespace std;

// Inherits a base class Person
class Student : public Person {
public:
	Student();
	~Student();

	void setStudent(int studentID, int advisorID, double gpa, std::string name, std::string level, std::string major);

	void updateAdvisor(int fid);
	void printDetails();
	string getCSV();

	//student vars
	int advisorID;
	double gpa;
	std::string major;

	// Overloading operators
	//  - https://www.tutorialspoint.com/cplusplus/relational_operators_overloading.htm
	//  - https://www.tutorialspoint.com/cplusplus/cpp_conditional_operator.htm
	
	bool operator < (Student& s2) { (getId() < s2.getId()) ?  true :  false; }
	bool operator > (Student& s2) { (getId() > s2.getId()) ? true : false; }
	bool operator == (Student& s2) { (getId() == s2.getId()) ? true : false; }
	bool operator != (Student& s2) { (getId() != s2.getId()) ? true : false; }
	bool operator >= (Student& s2) { (getId() >= s2.getId()) ? true : false; }
	bool operator <= (Student& s2) { (getId() <= s2.getId()) ? true : false; }
	
	
};

#endif
