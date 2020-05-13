#include "treeNode.cpp"
#include "student.cpp"
#include "faculty.cpp"
#include "Input.cpp"
#include "bst.cpp"
#include "sim.h"
#include <fstream>
#include <iostream>

using namespace std;

Sim::Sim() {

}

void Sim::SetUpSim() {
	try {
			List<string>* mylist = new List<string>;

			string student;
			string sid;
			string fid;
			string name;
			string level;
			string dept;

			ifstream myFile;
			string line, colname;
			// Check if we will have an error with the files, if so report it and use empty trees
			myFile.open("studentTable.csv");
			if (!myFile.is_open()) throw std::runtime_error("Could not open file studentTable.csv");
			myFile.close();

			myFile.open("facultyTable.csv");
			if (!myFile.is_open()) throw std::runtime_error("Could not open file facultyTable.csv");
			while (getline(myFile, line)) {
				stringstream ss(line);
				getline(ss, fid, ',');
				getline(ss, name, ',');
				getline(ss, level, ',');
				getline(ss, dept, ',');
				//AddFaculty(mylist, stoi(fid), name, level, dept);
				AddFaculty(mylist, stoi(fid), name, level, dept);

			}
			// Close file
			myFile.close();

			// Open an existing file
			myFile.open("studentTable.csv");
			if (!myFile.is_open()) throw std::runtime_error("Could not open file studentTable.csv" );

			// Helper vars
			while (getline(myFile, line)) {
				// Read the column names				
				stringstream ss(line);
				getline(ss, sid, ',');
				getline(ss, name, ',');
				string gpa;
				getline(ss, gpa, ',');
				getline(ss, level, ',');
				string major;
				getline(ss, major, ',');
				getline(ss, fid, ',');
				//AddStudent(mylist, stoi(sid), name, stoi(fid), stod(gpa), level, major);
				AddStudent(mylist, stoi(sid), name, stoi(fid), 4.0, level, major);
			}
			// Close file
			myFile.close();
			delete(mylist);
	}
	catch (exception& e) {
		cout << "Using an empty Student and / or Faculty issue is - " << e.what() << endl;
	}
}

string Sim::GetString(string prompt) {
	cout << prompt << endl;
	string answer;
	cin >> ws;
	getline(std::cin, answer);

	return answer;
}

int Sim::GetId(string type) {
	cout << "Please enter the id for your " << type << endl;
	int answer;
	cin >> answer;

	while (std::cin.fail()) {
		std::cout << "ERROR: please enter a number" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> answer;
	}

	cout << "Using " << type << "ID: " << answer << endl;
	return answer;
}

double Sim::GetDouble(string prompt) {
	cout << prompt << endl;
	double answer;
	cin >> answer;

	while (std::cin.fail()) {
		std::cout << "ERROR: please enter a number" << std::endl;
		std::cin.clear();
		std::cin >> answer;
	}

	cout << "Using : " << answer << endl;
	return answer;
}

void Sim::DisplayStudents() {
	masterStudent.printTree();
}

void Sim::DisplayFaculty() {
	masterFaculty.printTree();
}

void Sim::FindStudent() {
	int id = GetId("student");

	FindStudent(id);
}

void Sim::FindStudent(int id) {
	if (masterStudent.search(id)) {
		masterStudent.returnNode(id)->data->printDetails();
	}
	else {
		cout << "Could not find student with Id: " << id << endl;
	}
}

void Sim::FindFaculty() {
	int id = GetId("faculty");

	if (masterFaculty.search(id)) {
		masterFaculty.returnNode(id)->data->printDetails();
	}
	else {
		cout << "ERROR: Could not find faculty with Id: " << id << endl;
	}
}

void Sim::ShowFacultyForStudent() {
	int id = GetId("student");
	int fId;
	TreeNode<Student>* s = new TreeNode<Student>;

	if (masterStudent.search(id)) {
		s = masterStudent.returnNode(id);
		fId = s->data->advisorID;
	}
	else {
		cout << "ERROR: Could not find student with Id: " << id << endl;
		return;
	}
	
	cout << "Student " + s->data->getName() +  "'s faculty has the following details:" << endl;
	if (masterFaculty.search(fId)) {
		masterFaculty.returnNode(fId)->data->printDetails();
	}
	else {
		cout << "ERROR: Could not find faculty with Id: " << fId << endl;
	}
}

void Sim::ShowFacultyAdvisees() {
	int id = GetId("faculty");

	if (masterFaculty.search(id)) {

		Faculty* f = masterFaculty.returnNode(id)->data;

		cout << f->getName() << " has the following students as their advisee:" << endl;

		int listSize = f->advisees.GetListSize();
		int tempAdvisee = 0;

		for (int i = 0; i < listSize; ++i) {
			if (!f->advisees.isEmpty()) {
				tempAdvisee = f->advisees.popHead();			
				FindStudent(tempAdvisee);
				f->advisees.AddToTail(tempAdvisee);
			}
			else {
				cout << "ERROR: Unexpected NULL for advisee list" << endl;
			}
		}
		cout << endl;
	}
	else {
		cout << "ERROR: Could not find faculty with Id: " << id << endl;
	}
}

void Sim::ChangeAdvisor(List<string>* mylist) {
	int sid;
	int fid;


	cout << "Which student do you want to change advisor for? " << endl;
	// Get the student id
	bool keepRunning = true;
	while (keepRunning) {
		sid = GetId("student");

		if (!masterStudent.search(sid)) {
			cout << "ERROR: Could not find student with Id: " << sid << endl;
		}
		else {
			keepRunning = false;
		}
	}

	cout << "Which advisor do you want to change to ? " << endl;
	// Get the faculty id
	keepRunning = true;
	while (keepRunning) {
		fid = GetId("faculty");

		if (!masterFaculty.search(fid)) {
			cout << "ERROR: Could not find faculty with Id: " << fid << endl;
		}
		else {
			keepRunning = false;
		}
	}
	ChangeAdvisor(mylist, sid, fid);
}

void Sim::ChangeAdvisor(List<string>* mylist, int sid, int newfid) {
	int temp = mylist->GetListSize();
	Student* s = masterStudent.returnNode(sid)->data;
	int oldFid;
	oldFid = s->advisorID;
	string record = (to_string(sid) + "," + to_string(oldFid) + ",");
	DelAdvisee(mylist, sid, oldFid);
	AddToAdvisor(mylist, sid, newfid);
	s->advisorID = newfid;
	AddtoUndo(mylist, "c", 1, record);
}

void Sim::AddToAdvisor(List<string>* mylist, int studentId, int advisorID) {
	Faculty* f = masterFaculty.returnNode(advisorID)->data;
	f->advisees.AddToHead(studentId);
	string record = to_string(studentId) + "," + to_string(advisorID) + ",";
	AddtoUndo(mylist, "df", 0, record);
}

void Sim::RemoveAdvisee(List<string>* mylist) {
	// I dont know whats the difference between this and the Change
	ChangeAdvisor(mylist);
}

void Sim::DelAdvisee(List<string>* mylist, int sid, int fid) {
	// Del the student from the faculty
	Faculty* f = masterFaculty.returnNode(fid)->data;
	if (f->advisees.search(sid)) {
		string undoRecord = to_string(sid) + "," + to_string(fid);
		AddtoUndo(mylist, "af", 0, undoRecord);
		f->advisees.remove(sid);
		f->printDetails();
	}
}

void Sim::AddStudent(List<string>* mylist) {
	int sid;

	cout << "Please enter your Student ID " << endl;
	// Get the student id
	bool keepRunning = true;
	while (keepRunning) {
		sid = GetId("student");

		if (masterStudent.search(sid)) {
			cout << "ERROR >> Student with Id: " << sid << " alredy exists" << endl;
		}
		else {
			keepRunning = false;
		}
	}

	string name = GetString("Please enter your name : ");
	cout << "The name given was " << name << endl;

	int newfid;
	cout << "Please enter your Students Advisor ID ? " << endl;
	// Get the faculty id
	keepRunning = true;
	while (keepRunning) {
		newfid = GetId("faculty");

		if (!masterFaculty.search(newfid)) {
			cout << "ERROR: Could not find faculty with Id: " << newfid << endl;
		}
		else {
			keepRunning = false;
		}
	}

	string level;
	keepRunning = true;
	while (keepRunning) {
		level = GetString("Enter the students level : ");

		if (config.StudentLevels.search(level)) {
			cout << "setting level to " << level << endl;
			keepRunning = false;
		}
		else {
			cout << "ERROR: Please select from (case sensative) : " << endl;
			config.printStudentLevel();
		}
	}

	string major;
	keepRunning = true;
	while (keepRunning) {
		major = GetString("Enter the students major : ");

		if (config.Majors.search(major)) {
			cout << "setting major to " << major << endl;
			keepRunning = false;
		}
		else {
			cout << "ERROR: Please select from (case sensative) : " << endl;
			config.printMajors();
		}
	}

	double gpa;
	keepRunning = true;
	while (keepRunning) {
		gpa = GetDouble("Enter the gpa level : ");

		if (gpa <= 4.0) {
			cout << "setting level to " << level << endl;
			keepRunning = false;
		}
		else {
			cout << "ERROR: Please enter between 0.0 to 4.0 : " << endl;
		}
	}

	AddStudent(mylist, sid, name, newfid, gpa, level, major);
}

void Sim::AddStudent(List<string>* mylist, int sid, string name, int newfid, double gpa, string level, string major) {
	Student* s = new Student;
	s->setStudent(sid, newfid, gpa, name, level, major);
	TreeNode<Student>* studentNode = new TreeNode<Student>(sid, s);
	masterStudent.insert(studentNode);
	AddtoUndo(mylist, "d", 1, s->getCSV());
	AddToAdvisor(mylist, sid, newfid);
}

void Sim::AddFaculty(List<string>* mylist) {
	int fid;

	cout << "Please enter your Faculty ID " << endl;
	// Get the faculty id
	bool keepRunning = true;
	while (keepRunning) {
		fid = GetId("faculty");

		if (masterFaculty.search(fid)) {
			cout << "ERROR >> Faculty with Id: " << fid << " alredy exists" << endl;
		}
		else {
			keepRunning = false;
		}
	}

	string name = GetString("Please enter your name : ");
	cout << "The name given was " << name << endl;

	string level;
	keepRunning = true;
	while (keepRunning) {
		level = GetString("Enter the faculty level : ");

		if (config.FacultyLevels.search(level)) {
			cout << "setting level to " << level << endl;
			keepRunning = false;
		}
		else {
			cout << "ERROR: Please select from (case sensative) : " << endl;
			config.printFacultyLevel();
		}
	}

	string dept; // Is dept the same as majors ?
	keepRunning = true;
	while (keepRunning) {
		dept = GetString("Enter the Dept : ");

		if (config.Dept.search(dept)) {
			cout << "setting Dept to " << dept << endl;
			keepRunning = false;
		}
		else {
			cout << "ERROR: Please select from (case sensative) : " << endl;
			config.printDept();
		}
	}

	AddFaculty(mylist, fid, name, level, dept);

}

void Sim::AddFaculty(List<string>* mylist, int fid, string name, string level, string dept) {
	Faculty* f = new Faculty;
	f->setFaculty(fid, name, level, dept);
	TreeNode<Faculty>* facultytNode = new TreeNode<Faculty>(fid, f);
	masterFaculty.insert(facultytNode);
	AddtoUndo(mylist, "d", 0, f->getCSV());
}

void Sim::DelStudentById(List<string>* mylist) {
	int sid;

	cout << "Please enter your Student ID " << endl;
	// Get the student id
	bool keepRunning = true;
	while (keepRunning) {
		sid = GetId("student");

		if (!masterStudent.search(sid)) {
			cout << "ERROR >> Student with Id: " << sid << " does not exist" << endl;
		}
		else {
			keepRunning = false;
		}
	}

	DelStudentById(mylist, sid);
}

void Sim::DelStudentById(List<string>* mylist, int sid) {
	int fid;
	Student* s = masterStudent.returnNode(sid)->data;
	fid = s->advisorID;

	// Remove the student from the faculty advisee list
	DelAdvisee(mylist, sid, fid);

	// Remove the student
	AddtoUndo(mylist, "a", 1, s->getCSV());
	masterStudent.deleteNode(sid);
}

void Sim::DelAdvisorById(List<string>* mylist) {
	int fid;

	cout << "Please enter your Faculty ID " << endl;

	bool keepRunning = true;
	while (keepRunning) {
		fid = GetId("faculty");

		if (!masterFaculty.search(fid)) {
			cout << "ERROR >> Faculty with Id: " << fid << " does not exist" << endl;
		}
		else {
			keepRunning = false;
		}
	}

	Faculty* f = masterFaculty.returnNode(fid)->data;

	// Check if there are students and we have the last faculty
	if ((!f->advisees.isEmpty()) && (masterFaculty.getSize() == 1)) {
		cout << "ERROR: You cant delete this node as it has advisees and there is no other Faculty member to assign to." << endl;
		return;
	}

	if (!f->advisees.isEmpty()) {
		cout << "Need to move students to a new Faculty." << endl;
		int newFid;

		keepRunning = true;
		while (keepRunning) {
			newFid = GetId("faculty");
			if (!masterFaculty.search(newFid)) {
				cout << "ERROR >> Faculty with Id: " << fid << " does not exist. Please enter one that does." << endl;
			}
			else if (newFid == fid) {
				cout << "ERROR >> Cannot move to the same faculty: " << fid << " . Please enter another one." << endl;
			}
			else {
				keepRunning = false;
			}
		}

		Faculty* newFaculty = masterFaculty.returnNode(newFid)->data;

		int tempSid;
		string record;
		// move them over by looping till we have an empty list
		while (!f->advisees.isEmpty()) {
			tempSid = f->advisees.GetHead();
			ChangeAdvisor(mylist, tempSid, newFid);
		}
	}

	AddtoUndo(mylist, "a", 0, f->getCSV());
	// Remove the advisor
	masterFaculty.deleteNode(fid);
}

int Sim::DisplayMenu() {
	cout << endl << "==================================" << endl;
	cout << "1.  Display all students and information (in ascending order by Id)" << endl;
	cout << "2.  Display all faculty and information (in ascending order by Id)" << endl;
	cout << "3.  Find Student by Student Id" << endl;
	cout << "4.  Find Faculty by Faculty Id" << endl;
	cout << "5.  Given a Student Id, Display Student name and Faculty information" << endl;
	cout << "6.  Given a Faculty Id, Display advisee information" << endl;
	cout << "7.  Add Student" << endl;
	cout << "8.  Add Faculty" << endl;
	cout << "9.  Delete Student by Student Id" << endl;
	cout << "10. Delete Faculty by Faculty Id" << endl;
	cout << "11. Change a students advisor given Student Id and new Faculty Id" << endl;
	cout << "12. Remove an advisee from a faculty memebr given the ids." << endl;
	cout << "13. Rollback" << endl;
	cout << "14. Save Tables" << endl;
	cout << "15. Exit" << endl;

	int answer;

	cout << endl << "Enter option:" << endl;
	cin >> answer;

	// https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
	while (std::cin.fail()) {
		std::cout << "ERROR: please enter a number" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> answer;
	}

	while ((answer > 15) || (answer < 1)) {
		cout << "You entered " << answer << endl;
		cout << "Please select from 1 to 15." << endl;
		cin >> answer;

		while (std::cin.fail()) {
			std::cout << "ERROR: please enter a number" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> answer;
		}
	}
	return answer;
}

void Sim::AddtoUndo(List<string>* mylist, string action, int isStudent, string record) {
	string undoRecord = action + "," + to_string(isStudent) + "," + record;

	mylist->AddToHead(undoRecord);
	// Next lines are for debugging if you want to see what undo records are generated
	// cout << "UNDO REC" << mylist->popHead() << "the record should be " << undoRecord <<endl;
	// mylist->AddToHead(undoRecord);
}

void Sim::Commit(List<string>* undoRecords) {
	if (undoRecords->isEmpty()) {
		// Do nothing
	}
	else {
		undoList.AddToHead(undoRecords);
		if (undoList.GetListSize() > 5) {
			// Need to get rid of the older undo as we can only have at most 5
			cout << "List is greater than 5 so deleting older undo" << endl;
			(void)undoList.popTail();
		} 
	}
}

void Sim::Undo() {
	List<string>* mylist;
	string cmd;
	string action;
	string student;
	string sid;
	string fid;

	if (!undoList.isEmpty()) {
		cout << endl << "Performing an Undo" << endl;
		mylist = undoList.popHead();

		while (!mylist->isEmpty()) {
			cmd = mylist->popHead();
			
			// Create a stringstream of the current line
			stringstream ss(cmd);
			if (getline(ss, action, ',')) {
				if (action == "c") {
					getline(ss, student, ',');
					getline(ss, sid, ',');
					getline(ss, fid, ',');
					ChangeAdvisor(mylist, stoi(sid), stoi(fid));
					cmd = mylist->popHead(); // Removes the change just added
					cmd = mylist->popHead(); // Removes the df just added
					cmd = mylist->popHead(); // Removes the af just added
					cmd = mylist->popHead(); // Removes the df from previous
					cmd = mylist->popHead(); // Removes the af from previous

				}

				if (action == "d") {
					getline(ss, student, ',');
					if (student == "1") {
						getline(ss, sid, ',');
						DelStudentById(mylist, stoi(sid));
						cmd = mylist->popHead();
					}
					else {
						getline(ss, fid, ',');
						// Remove the advisor
						masterFaculty.deleteNode(stoi(fid));
					}
				}

				if (action == "a") {
					getline(ss, student, ',');
					if (student == "1") {
						getline(ss, sid, ',');
						string name;
						getline(ss, name, ',');
						string gpa;
						getline(ss, gpa, ',');
						string level;
						getline(ss, level, ',');
						string major;
						getline(ss, major, ',');
						getline(ss, fid, ',');
						AddStudent(mylist, stoi(sid), name, stoi(fid), stod(gpa), level, major);
						cmd = mylist->popHead();
					}
					else {
						getline(ss, fid, ',');
						string name;
						getline(ss, name, ',');
						string level;
						getline(ss, level, ',');
						string dept;
						getline(ss, dept, ',');
						// Ignore any other after this comma in ss as advisses will be added by student adds
						AddFaculty(mylist, stoi(fid), name, level, dept);
						cmd = mylist->popHead();
					}
				}
				if (action == "af") {
					getline(ss, student, ',');
					if (student == "1") {
						// Nothing to do
					}
					else {
						getline(ss, sid, ',');
						getline(ss, fid, ',');

						AddToAdvisor(mylist, stoi(sid), stoi(fid));
						cmd = mylist->popHead();
					}
				}
				if (action == "df") {
					getline(ss, student, ',');
					if (student == "1") {
						// Nothing to do
					}
					else {
						getline(ss, sid, ',');
						getline(ss, fid, ',');

						DelAdvisee(mylist, stoi(sid), stoi(fid));
						cmd = mylist->popHead();
					}
				}
			}
		}
		if (mylist->isEmpty()) {
			delete (mylist);
		}
	}
	else {
		cout << "Nothing to undo" << endl;
	}
}

List<string>* Sim::GetNewUndoList() {
	List<string>* mylist = new List<string>;
	return mylist;
}

void Sim::OutputTables() {
	ofstream myFile;

	// Should I ask if the user wants to save output to a filename
	// or is a default ok ?
	myFile.open("studentTable.csv", std::ofstream::trunc);
	if (!myFile.is_open()) throw std::runtime_error("Could not open file studentTable.csv");
	myFile.close();

	myFile.open("facultyTable.csv", std::ofstream::trunc);
	if (!myFile.is_open()) throw std::runtime_error("Could not open file facultyTable.csv");
	myFile.close();

	cout << "Saving the tables .." << endl;
	masterStudent.outputTree("studentTable.csv");
	masterFaculty.outputTree("facultyTable.csv");
}

void Sim::Start() {
	
	SetUpSim();

	int answer;
	bool keepRunning = true;

	while (keepRunning) {
		List<string>* mylist = GetNewUndoList();
		answer = DisplayMenu();
		cout << "You entered : " << answer << endl;

		switch (answer) {
		case 1:
			DisplayStudents();
			break;
		case 2:
			DisplayFaculty();
			break;
		case 3:
			FindStudent();
			break;
		case 4:
			FindFaculty();
			break;
		case 5:
			ShowFacultyForStudent();
			break;
		case 6:
			ShowFacultyAdvisees();
			break;
		case 7:
			AddStudent(mylist);
			Commit(mylist);
			break;
		case 8:
			
			AddFaculty(mylist);
			Commit(mylist);
			break;
		case 9:
			
			DelStudentById(mylist);
			Commit(mylist);
			break;
		case 10:
			
			DelAdvisorById(mylist);
			Commit(mylist);
			break;
		case 11:
			ChangeAdvisor(mylist);
			Commit(mylist);
			break;
		case 12:
			RemoveAdvisee(mylist);
			Commit(mylist);
			break;
		case 13:
			Undo();
			break;
		case 14:
			OutputTables();
			break;
		case 15:
			OutputTables();
			cout << "Goodbye." << endl;
			keepRunning = false;
		default:
			break;
		}
	}
}


Sim::~Sim() {
}