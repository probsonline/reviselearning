#include <iostream>

#include "probs.hpp"
using namespace std;

/*
Write a program that ccontinues to asks the user to enter any number other than 5 until the user enters the number 5.
Then tell the user "Hey! you weren't supposed to enter 5!" and exit the program.

★ Modify the program so that after 10 iterations if the user still hasn't entered 5 will tell the user "Wow, you're more patient then I am, you win." and exit.

★★ Modify the program so that it asks the user to enter any number other than the number equal to the number of times they've been asked to enter a number. (i.e on the first iteration "Please enter any number other than 0" and on the second iteration "Please enter any number other than 1"m etc. etc. The program must behave accordingly exiting when the user enters the number they were asked not to.)

13:26 - 13:30 (2 logical errors, 2 keyword typos, 5 recompliation attempts needed to get it done)
13:30 - 13:40 (multiple time logic errors for part 2, typos for keywords)
13:40 - 13:49 ( 1 logical error,  typos for keywords, not nice error checking)

*/

void prog2_1(int argc, char** argv){
	int targetNum=5;
	int num=0;
	
	do{
		cout << "input any number other than " << targetNum << endl;
		cin >> num;
	}while (num != targetNum);
	
	cout << "Hey! you weren't supposed to enter " << targetNum << endl;
}


void prog2_2(int argc, char** argv){
	int targetNum=5;
	int attemptsLimit=10;
	int attemptCount=0;
	int num=0;
	
	do{
		cout << "input any number other than " << targetNum << endl;
		cin >> num;
		if (++attemptCount > attemptsLimit){
			cout << "Wow, you're more patient then I am, you win." <<  endl;
			return;
		}		
	}while (num != targetNum);
	
	cout << "Hey! you weren't supposed to enter " << targetNum << endl;
}

void prog2_3(int argc, char** argv){
	int targetNum=5;
	int num=0;
	
	cout << "input any forbidden number which is greater than 0" << endl;
	cin >> targetNum;
	if (targetNum == 0 ){
		cout << "Come back when you are not drunk. " << targetNum << " cannot be a forbidden number" << endl;
		return;
	}
	
	do{
		cout << "input any number other than " << targetNum << endl;		
		cin >> num;
	}while (num != targetNum);
	
	cout << "Hey! you weren't supposed to enter " << targetNum << endl;
}
