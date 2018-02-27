#include <iostream>
#include <string>
#include <stdlib.h>

#include <math.h>

#include "probs.hpp"
using namespace std;

/*
Write a program that calculates a random number 1 through 100. The program then asks the user to guess the number.
If the user guesses too high or too low then the program should output "too high" or "too low" accordingly.
The program must let the user continue to guess until the user correctly guesses the number.

★ Modify the program to output how many guesses it took the user to correctly guess the right number.

★★ Modify the program so that instead of the user guessing a number the computer came up with, 
the computer guesses the number that the user has secretely decided. The user must tell the computer 
whether it guesed too high or too low.

★★★★ Modify the program so that no matter what number the user thinks of (1-100) the computer can guess it in 7 or less guesses.

18:00 - 18:14

Learning: using rand is inscured also it gives the same numbre again and again.
We need to seed it with some variable number to get different number. srand is used for that.

*/

bool prompt();
int check_guess();

static const int number_limit=100;
static const int proximity_range=1;	//Since the word is "TOO" high or low so if it's within proximity, no feedback will be given

static const int HIGH=1;
static const int LOW=2;
static const int FOUND=3;

void prog5_1(int argc, char** argv){
	srand(time(NULL));	
	int secret_number = rand()%number_limit;
	int guess;
	
	cout << "The secret number is " << secret_number << endl; //Added for debugging only
	
	do{
		cout << "Can you guess the secret number that I thought " << endl;
		cin >> guess;
		
		if (guess - secret_number > proximity_range)
			cout << "Too high." << endl;
		else if (secret_number - guess > proximity_range)
			cout << "Too Low. " << endl;
		else{
			//cout << "Try again" << endl;
		}
	
	}while(guess != secret_number);	
}

void prog5_2(int argc, char** argv){
	srand(time(NULL));
	int secret_number = rand()%number_limit;	
	int guess;
	int attempt_count=0;
	
	do{
		cout << "Computer: Can you guess the secret number that I thought " << endl;		
		cin >> guess;
		
		if (guess - secret_number > proximity_range)
			cout << "Too high." << endl;
		else if (secret_number - guess > proximity_range)
			cout << "Too Low. " << endl;
		else{
			//cout << "Try again" << endl;
		}
		attempt_count++;
	
	}while(guess != secret_number);	
	
	cout << "You took " << attempt_count << " attempts to guess the number " << endl;
}

void prog5_3(int argc, char** argv){
	
	srand(time(NULL));
	int guess=rand()%number_limit;
	int attempt_count=0;
	
	do{
		cout << "Computer: I guess that you have " << guess << " in mind" << endl;
		attempt_count++;
		guess=rand()%number_limit;
		
	}while(check_guess()!= FOUND);

	cout << "Computer: I took " << attempt_count << " attempts to guess the number " << endl;	
}

int check_guess(){
	int check;
	int found=0;
	cout << "How good is my guess " << endl;
	cout << "1. Too High" << endl;
	cout << "2. Too Low" << endl;
	cout << "3. Nailed it" << endl;

	cin >> check;
	
	
	switch (check){
		case 1:
			found=HIGH;
			break;
		case 2:
			found=LOW;			
			break;
		case 3:
			found=FOUND;
			break;
		default:
			cout << "Invalid input given.";
	}
	
	return found;

}

unsigned int rand_in_range(unsigned int min, unsigned int max){
	return min+rand()%(max-min+1);
}

unsigned int check_guess2(unsigned int user_selected_target, unsigned int computer_guess){
	unsigned fb=0;
	if (computer_guess>user_selected_target)
		fb=HIGH;
	else if (computer_guess < user_selected_target)
		fb=LOW;
	else
		fb=FOUND;

	return fb;		
}

void prog5_4_auto(unsigned int user_selected_target){

	unsigned int attempt_count=0;
	unsigned int min_limit=0;
	unsigned int max_limit=101;
	unsigned int feedback=0;
	unsigned int computer_guess;

	srand(time(NULL));

	do{
		attempt_count++;
		computer_guess = rand_in_range(min_limit, max_limit);
//		cout << "Attempte No: " << attempt_count << " Lower limit: " << min_limit << " Upper limit: " << max_limit << " Guessed: " << computer_guess << endl;

		feedback = check_guess2(user_selected_target, computer_guess);

		if(feedback == HIGH){
				max_limit = computer_guess;
		}
		else if(feedback == LOW){
				min_limit = computer_guess;
		}
		else{
//			cout << "Nailed it!!!!!!!" << endl;
		}
	}while(feedback!=FOUND && attempt_count < 100);

	if (attempt_count >= 20)
		cout << "I couldn't guess it. Sorry" << user_selected_target <<endl;
	else
		cout << "  I guessed that you have " << computer_guess << " in mind in " << attempt_count << " attempts." << endl;
}

unsigned int *nums[2];

void prog5_4(int argc, char** argv){
	int test_iterations=1;
	
	if (argc > 1){
		string test_count=argv[1];
		test_iterations = stoi(test_count);
		cout << "test_iterations: " << test_iterations  << endl;
	}
		
	for (int i =1; i<=test_iterations; i++){
//		cout << "Taget is " << i << endl;
		prog5_4_auto(i);
//		cout << "===========================" << endl;
	} 
}
