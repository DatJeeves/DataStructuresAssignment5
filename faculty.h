#ifndef FACULTY_H
#define FACULTY_H
#include <string>
#include "person.h"
#include "list.h"

using namespace std;

// Inherits a base class Person
class Faculty : public Person {
public:
	Faculty();
	void setFaculty(int FacultyID,std::string name, std::string level, std::string dept);
	void printDetails();
	string getCSV();
	~Faculty();

	//Faculty vars
	string dept;

	// list of students ;
	List<int> advisees;
	
	// Overloading operators
	//  - https://www.tutorialspoint.com/cplusplus/relational_operators_overloading.htm
	//  - https://www.tutorialspoint.com/cplusplus/cpp_conditional_operator.htm

	bool operator < (Faculty& f2) { (getId() < f2.getId()) ? true : false; }
	bool operator > (Faculty& f2) { (getId() > f2.getId()) ? true : false; }
	bool operator == (Faculty& f2) { (getId() == f2.getId()) ? true : false; }
	bool operator != (Faculty& f2) { (getId() != f2.getId()) ? true : false; }
	bool operator >= (Faculty& f2) { (getId() >= f2.getId()) ? true : false; }
	bool operator <= (Faculty& f2) { (getId() <= f2.getId()) ? true : false; }

};

#endif
