#ifndef SIM_H
#define SIM_H
#include <iostream>
#include "treeNode.h"
#include "student.h"
#include "faculty.h"
#include "Input.h"
#include "bst.h"
#include "list.h"

using namespace std;

class Sim {
public:
	Sim();
	~Sim();

	void Start();
	void SetUpSim();

private:
	int DisplayMenu();
	int GetId(string type);
	double GetDouble(string prompt);
	string GetString(string prompt);
	void DisplayStudents();
	void DisplayFaculty();
	void FindStudent();
	void FindStudent(int id);
	void FindFaculty();
	void ShowFacultyForStudent();
	void ShowFacultyAdvisees();
	void OutputTables();

	//methods that operate on the db
	List<string>* GetNewUndoList();
	void ChangeAdvisor(List<string>* myList);
	void ChangeAdvisor(List<string>* myList, int sid, int newfid);
	void RemoveAdvisee(List<string>* myList);
	void AddStudent(List<string>* myList);
	void AddStudent(List<string>* myList, int sid, string naem, int newfid, double gpa, string level, string major);
	void DelStudentById(List<string>* myList);
	void DelStudentById(List<string>* myList, int sid);
	void DelAdvisorById(List<string>* myList);
	void AddToAdvisor(List<string>* myList, int studentId, int advisorID);
	void DelAdvisee(List<string>* myList, int sid, int fid);
	void AddFaculty(List<string>* myList);
	void AddFaculty(List<string>* myList, int fid, string name, string level, string dept);
	void AddtoUndo(List<string>* myList, string action, int isStudent, string record);
	void Undo();
	void Commit(List<string>* undoRecords);

	BST<TreeNode<Student>> masterStudent;
	BST<TreeNode<Faculty>> masterFaculty;

	List<List<string>*> undoList;

	int MAXUNDO = 5;
	Input config;
};
#endif
