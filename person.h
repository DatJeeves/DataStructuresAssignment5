#ifndef PERSON_H
#define PERSON_H
#include <string>

// Base class for a person. Classes that may use this are Student and Faculty 

using namespace std;

class Person {
public:
	Person();
	~Person();
	
	void setPerson(int ID, string name, string level);
	int getId();
	void setId(int Id);
	string getName();
	void setName(string name);
	string getLevel();
	void setLevel(string level);

	// Overloading operators
//  - https://www.tutorialspoint.com/cplusplus/relational_operators_overloading.htm
//  - https://www.tutorialspoint.com/cplusplus/cpp_conditional_operator.htm

	bool operator < (Person& p2) { (getId() < p2.getId()) ? true : false; }
	bool operator > (Person& p2) { (getId() > p2.getId()) ? true : false; }
	bool operator == (Person& p2) { (getId() == p2.getId()) ? true : false; }
	bool operator != (Person& p2) { (getId() != p2.getId()) ? true : false; }
	bool operator >= (Person& p2) { (getId() >= p2.getId()) ? true : false; }
	bool operator <= (Person& p2) { (getId() <= p2.getId()) ? true : false; }
	
private:	
	//Person vars
	int PersonID;
	string name;
	string level;


};

#endif
