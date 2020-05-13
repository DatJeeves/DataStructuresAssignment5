#include "person.h"
#include <string>

using namespace std;

Person::Person() {
	//should I make this able to take user input?
	int PersonID = 0;
	string name = "";
	string level = "";
}

void Person::setPerson(int PersonID, string name, string level)
{
	this->PersonID = PersonID;
	this->name = name;
	this->level = level;
}

Person::~Person() {

}

void Person::setId(int Id) {
	this->PersonID = Id;
}

int Person::getId() {
	return this->PersonID;
}

void Person::setName(string name) {
	this->name = name;
}

string Person::getName() {
	return this->name;
}

string Person::getLevel() {
	return this->level;
}

void Person::setLevel(string level) {
	this->level = level;
}




