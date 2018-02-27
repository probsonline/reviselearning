#include <iostream>

#include "probs.hpp"
using namespace std;


/*
Write a program that asks the user to enter the number of pancakes eaten for breakfast by 10 different people (Person 1, Person 2, ..., Person 10)
Once the data has been entered the program must analyze the data and output which person ate the most pancakes for breakfast.

★ Modify the program so that it also outputs which person ate the least number of pancakes for breakfast.

★★★★ Modify the program so that it outputs a list in order of number of pancakes eaten of all 10 people.
i.e.
Person 4: ate 10 pancakes
Person 3: ate 7 pancakes
Person 8: ate 4 pancakes
...
Person 5: ate 0 pancakes

4:10 - 5:15 (3 typo errors which can be avoided with a better editor, one C++ syntax lack of knowledge error (array size) and many logical errors in the sort )
*/

void sort(int *pc);
void swap(int *l, int*r);
int* common_logic();

static const int guestsInvited=10;

void prog4_1(int argc, char** argv){
	
	int *pancakes =  common_logic();
	cout << "Person 9 ate the most pan cakes i.e. " << pancakes[9] << " cakes" << endl;
		
}

void prog4_2(int argc, char** argv){
	int *pancakes =  common_logic();		
	cout << "Person 0 ate the lest pan cakes i.e. " << pancakes[0] << " cakes" << endl;
}

	
	
void prog4_3(int argc, char** argv){
	int *pancakes =  common_logic();		
	
	for (int p=0; p<guestsInvited; p++){
		cout << "Person " << p << " ate " << pancakes[p] << " pancakes for breakfast" << endl;
	}
	
}


void swap(int* l, int* r){	
	int temp = *r;
	
//	cout << "left:" << *l << "right: " << *r << endl;
	*r = *l;
	*l = temp;
}


/* Trying to implement bubble sort on my own. Made many childish blunders */
void sort(int *pc){
	int i;
	int size=guestsInvited;
	int *pcs=pc;
	
	int left, right;
	
/*	cout << "Unsorted data" << endl;
	for (int i=0; i< size; i++){
		 cout << pcs[i] << endl;
	}
*/
	for(i=0; i< size; i++){
		for(int j=0; j<(size-i-1); j++){
			left = pcs[j];
			right = pcs [j+1];
			if (left > right)
				swap(&pcs[j], &pcs[j+1]);			
		}
	}
	
	cout << "sorted data" << endl;		 
	for (int i=0; i< size; i++){
		 cout << pcs[i] << endl;
	}
}

int* common_logic(){
	static int pancakes[guestsInvited];
	int guests=guestsInvited;

	
	for (int g_count=0; g_count<guests; g_count++){
		cout << "Enter the pancakes that person " << g_count << " ate" << endl;
		cin >> pancakes[g_count];
	}
	
	sort(pancakes);
	
//	return pancakes;	//cannot return the local variable here so pancakes needs to be made either a global or a static variable. I chose to make it static
	return pancakes;
}

