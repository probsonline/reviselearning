#include <iostream>

using namespace std;

/*
 * Write a program that asks for a user first name and last name separately.
The program must then store the users full name inside a single string and out put it to the string.
i.e.
Input:
John
Smith
Output:
John Smith

★ Modify the program so that it then replaces every a, e, i , o, u w/ the letter z.
i.e.
John Smith -> Jzhn Smzth

★★ Modify the Program so that it reverses the users name
i.e.
John Smith -> htimS nhoJ
 */

//#define C_STRING_VERSION

#ifndef C_STRING_VERSION

#include <string>

void prob9_1(int argc, char** argv){
	string first_name, last_name;
	string full_name;

	cout << "Enter your first name: " ;
	cin >> first_name;

	cout << "enter your last name: ";
	cin >> last_name;

	full_name = first_name + " " + last_name;

	cout << endl << full_name << endl;
}

/* replace vowels */
void prob9_2(int argc, char** argv){
	string first_name, last_name;
	string full_name;

	cout << "Enter your first name: " ;
	cin >> first_name;

	cout << "enter your last name: ";
	cin >> last_name;

	full_name = first_name + " " + last_name;
	cout << endl << full_name << endl;

	for(int ch=0; ch<(int)full_name.length(); ch++){
		if(
				full_name.at(ch) == 'a' ||
				full_name.at(ch) == 'e' ||
				full_name.at(ch) == 'i' ||
				full_name.at(ch) == 'o' ||
				full_name.at(ch) == 'u' ||
				full_name.at(ch) == 'A' ||
				full_name.at(ch) == 'E' ||
				full_name.at(ch) == 'I' ||
				full_name.at(ch) == 'O' ||
				full_name.at(ch) == 'U'
				)
		{
			full_name.replace(ch, 1, "z");
		}
	}

	cout << endl << full_name << endl;
}

/* reverse letters */
void prob9_3(int argc, char** argv){
	string first_name, last_name;
	string full_name;
	string reverse_name="";

	cout << "Enter your first name: " ;
	cin >> first_name;

	cout << "enter your last name: ";
	cin >> last_name;

	full_name = first_name + " " + last_name;
	int len = full_name.length();
	cout << endl << full_name << endl;

	for(int ch=0, rch=len-1; rch>=0; ch++, rch--)
	{
		reverse_name += full_name[rch];
	}

	cout << endl << reverse_name << endl;
}

#else

#include <cstring>

void prob9_1(int argc, char** argv){

	char first_name[22];	//10 chars for first name, 10 for the last name, and one each for null char.
	char last_name[11];
	char full_name [22];

	cout << "Enter your first name (upto to 10 chars): " ;
	cin >> first_name;

	cout << "enter your last name (upto 10 chars): ";
	cin >> last_name;

	/* concatenate the two strings. C concatenation copies into the firs string. */
	strcat(first_name, " ");
//	cout << endl << first_name << endl;
	strcat(first_name, last_name);
//	cout << endl << first_name << endl;

	/* copy it to full name */
	strcpy(full_name, first_name);

	cout << endl << full_name << endl;
}

/* replace vowels with z */
void prob9_2(int argc, char** argv){
	char first_name[22];	//10 chars for first name, 10 for the last name, and one each for null char.
	char last_name[11];
	char full_name [22];

	cout << "Enter your first name (upto to 10 chars): " ;
	cin >> first_name;

	cout << "enter your last name (upto 10 chars): ";
	cin >> last_name;

	/* concatenate the two strings. C concatenation copies into the firs string. */
	strcat(first_name, " ");
	strcat(first_name, last_name);

	/* copy it to full name */
	strcpy(full_name, first_name);
	cout << endl << full_name << endl;

	char vowels[] = {'a' , 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
	int vowels_count=sizeof(vowels)/sizeof(char);

	int c=0;
	while(full_name[c] != '\0'){
		for(int v=0; v<vowels_count; v++){
			if(full_name[c] == vowels[v]){
				full_name[c] = 'z';
			}
		}
		c++;
	}

	cout << endl << full_name << endl;

}
/* reverse name  */
void prob9_3(int argc, char** argv){
	char first_name[22];	//10 chars for first name, 10 for the last name, and one each for null char.
	char last_name[11];
	char full_name [22];
	char reverse_name[22];

	cout << "Enter your first name (upto to 10 chars): " ;
	cin >> first_name;

	cout << "enter your last name (upto 10 chars): ";
	cin >> last_name;

	/* concatenate the two strings. C concatenation copies into the firs string. */
	strcat(first_name, " ");
	strcat(first_name, last_name);

	/* copy it to full name */
	strcpy(full_name, first_name);
	int len = strlen(full_name);	//This returns the length not including the null termination character for the string

	for (int ch=0, rch=len-1; full_name[ch]!='\0'; ch++, rch--){
		reverse_name[rch]=full_name[ch];
	}
	reverse_name[len]='\0';	//Since null character was not copied so copy it as the last character.

	cout << endl << full_name << endl;
	cout << endl << reverse_name << endl;

}

#endif
