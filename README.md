# DataStructuresAssignment5

Name: Jeevan Acharya
Student ID:  2313321

 References:
 - https://www.includehelp.com/code-snippets/cpp-program-to-write-and-read-an-object-in-from-a-binary-file.aspx
 - https://stackoverflow.com/questions/21767053/c-std-does-not-have-member-string
 - https://www.softwaretestinghelp.com/binary-search-tree-in-cpp/
 - https://www.tutorialspoint.com/cplusplus/relational_operators_overloading.htm
 - https://www.tutorialspoint.com/cplusplus/cpp_conditional_operator.htm


Steps to make program run:
To ensure that the user inputs the correct data for department, majors, levels, etc I have created the following text files which allows values to be added without compiling again. The values need to be entered per line:
 - dept.txt = department values
 - facultyLevels.txt = levels of the faculty (i.e. prof ...)
 - majors.txt = list of majors the student can select from
 - studentLevels.txt = list of levels the student can be (Freshman, Sophmore, ...)

I also have two files which represent a serialized form of the database based on csv formatting.

For the studentTable.csv:

studentid,student name,gpa,student level,major,advisorid

e.g.
50,Jeevan Acharya,4.000000,Freshman,Math,22,

For facultyTable.csv:

facultyId,name,level,Dept,<follwed by a comma sperated list of studentids> 

e.g.
22,auto gen,prof,Math,90,50,

Notes:
- the program will ignore the students in the faculty table during loading and instead rebuild the advisee list based on the studentTable to ensure integrity is maintained.
- the program will perform checks during loading to ensure the database is correct

Handling of Undo:
I chose to use a doublelinked list that maintains the list of transaction records rather than a stack. I did this so I can check if the undo list is greater than 5 I can pop the tail. I did think about adding in a redo list but ran out of time.

On the internet there were many articles on how to do this especially using vectors. I decided to make my own based on them

Notes about the BST:
I have in my BST an element called color. I was hoping if I had time to convert teh BST to a selfbalancing one. I did not get enough time to make this happen but the nodes are there in to allow me to enhance this in the future.

Overloading operators:
I searched the web and found how to do this and instead of using an if then construct I chose to us ethe conditional ? to make it easier to read.

Note to professor:
I did not see a difference between Remove Advisee and Change Advisor. I kept the options on the menu but reused the command to do the change. I had sent a slack message to you to see if you could provide gudiance on what the difference would be but since I did not get a reply I chose this path. If I misunderstood I can redo this section quickly as I have all the methods defined for the logic required.



