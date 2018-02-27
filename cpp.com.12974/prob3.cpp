#include <iostream>

#include "probs.hpp"
using namespace std;

/*
Write a program that presents the user w/ a choice of your 5 favorite beverages (Coke, Water, Sprite, ... , Whatever).
Then allow the user to choose a beverage by entering a number 1-5.
Output which beverage they chose.

★ If you program uses if statements instead of a switch statement, modify it to use a switch statement.

★★ Modify the program so that if the user enters a choice other than 1-5 then it will output "Error. choice was not valid, here is your money back."
	
15:41 - 	15:46 (1 compilation error dur to missing logic of cin"
*/

void prog3_1(int argc, char** argv){

	int choice=0;
	cout << "Choose the drink" << endl;
	cout << "1. Water" << endl;
	cout << "2. Coke" << endl;
	cout << "3. Sprite" << endl;
	cout << "4. SparkingWater" << endl;
	cout << "5. Milk" << endl;
	
	cin >> choice;


	switch(choice){
	case 1:
		cout << "You chose Water" << endl;
	break;
	
	case 2:
		cout << "You chose Coke" << endl;
	break;
	
	case 3:
		cout << "You chose Sprite" << endl;
	break;
	
	case 4:
		cout << "You chose SparkingWater" << endl;
	break;
	
	case 5:
		cout << "You chose Milk" << endl;
	break;
	
	default:
		cout << "invalid choice" << endl;
	}
	
}
