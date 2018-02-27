#include <iostream>

#include "probs.hpp"
using namespace std;


/*
Write a program that allows the user to enter the grade scored in a programming class (0-100).
If the user scored a 100 then notify the user that they got a perfect score 

★★ Modify the program so that it will notify the user of their letter grade
0-59 F 60-69 D 70-79 C 80-89 B 90-100 A

par t1: 12:33 - 12:43 (5 compiliation attempts, cin syntax not known
13:15 - 13:22 - (2 compilization attempts). typos)

*/


void prog1_1(int argc, char** argv){
	
	int grade=0;
	
	cout << "Enter Grade" << endl;
	cin >> grade; 
	
	if (grade == 100){
		cout << "you got the perfect score" << endl;
	}
	else{
		cout << "You didn't win" << endl;
	}
}

void prog1_2(int argc, char** argv){
	
	int gradeScore=0;
	char gradeLetter;
	
	cout << "Enter Grade" << endl;
	
	cin >> gradeScore;
	
	if (gradeScore <0 || gradeScore >100){		
		cout << "Invalid grade score entered" << endl;
		return;
	}
	
	if (gradeScore >=90 && gradeScore <=100)
		gradeLetter = 'A';
	else if (gradeScore >=80 && gradeScore <90)
		gradeLetter = 'B';
	else if (gradeScore >=70 && gradeScore <80)
		gradeLetter = 'C';
	else if (gradeScore >=60 && gradeScore <70)
		gradeLetter = 'D';
	else if (gradeScore >=0 && gradeScore <60)
		gradeLetter = 'F';
	else
		gradeLetter = '0';
	
	cout << "you got " << gradeLetter << " grade " << endl;
	
}
