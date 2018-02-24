#include <iostream>
using namespace std;

#define SIMPLE_VERSION 4

#if (SIMPLE_VERSION==0)
int main()
{
	cout << " Bismillah" <<  endl;
	return 0;
}

#elif (SIMPLE_VERSION==1)
int add(int a, int b)
{
	return a+b;	
}

float add(float a, float b)
{
	return a+b;	
}

void inputNums(int &num1, int& num2)
{
	cout << "Input a number: ";
	cin >> num1;
	cout << "Input the other number: ";
	cin >> num2;	
}

void inputNums(float &num1, float& num2)
{
	cout << "Input a number: ";
	cin >> num1;
	cout << "Input the other number: ";
	cin >> num2;	
}

int main()
{
	int num1, num2;
	inputNums(num1, num2);
	cout << "Adding ints:  " << add(num1,num2) << endl;

	float num3, num4;
	inputNums(num3, num4);
	cout << "Adding floats: " << add(num3,num4) << endl;

	return 0;
}
#elif (SIMPLE_VERSION==2)
//Let's see how templates make it very easy and reduce the coding required

template <typename T>
T add(T a, T b)
{
	return a+b;	
}

template <typename T>
void inputNums(T &num1, T& num2)
{
	cout << "Input a number: ";
	cin >> num1;
	cout << "Input the other number: ";
	cin >> num2;	
}

int main()
{
	int num1, num2;
	inputNums<int>(num1, num2);
	cout << "Adding ints:  " << add<int>(num1,num2) << endl;

	float num3, num4;
	inputNums<float>(num3, num4);
	cout << "Adding floats: " << add<float>(num3,num4) << endl;
	return 0;
}
#elif (SIMPLE_VERSION==3)

//Now let's do the simple version with classes instead of templates to see if that helps
//Let's see how templates make it very easy and reduce the coding required

class Adder{
public:
	int num1, num2;
	float num3, num4;

	int add(int a, int b);
	float add(float a, float b);

};

int Adder::add(int a, int b)
{
	return a+b;	
}

float Adder::add(float a, float b)
{
	return a+b;	
}

void inputNums(int &num1, int& num2)
{
	cout << "Input a number using non-class function: ";
	cin >> num1;
	cout << "Input the other number: ";
	cin >> num2;	
}

void inputNums(float &num1, float& num2)
{
	cout << "Input a number using non-class function: ";
	cin >> num1;
	cout << "Input the other number: ";
	cin >> num2;	
}


int main()
{
	int num1, num2;
	inputNums(num1, num2);
	Adder calculator;		//Notice, object is one but still separate functions are needed to implemented using function overloading
	cout << "Adding ints:  " << calculator.add(num1,num2) << endl;


	float num3, num4;
	inputNums(num3, num4);
	cout << "Adding floats: " << calculator.add(num3,num4) << endl;
	return 0;
}

#elif (SIMPLE_VERSION==4)

//Now let's see if classes and templates combined help even more than classes alone or templates alone
template <class T>  //Notice that class is a keyword 
class Adder{
public:
	int num1, num2;
	float num3, num4;

	int add(int a, int b);
	float add(float a, float b);

};

int Adder::add(int a, int b)
{
	return a+b;	
}

float Adder::add(float a, float b)
{
	return a+b;	
}

void inputNums(int &num1, int& num2)
{
	cout << "Input a number using non-class function: ";
	cin >> num1;
	cout << "Input the other number: ";
	cin >> num2;	
}

void inputNums(float &num1, float& num2)
{
	cout << "Input a number using non-class function: ";
	cin >> num1;
	cout << "Input the other number: ";
	cin >> num2;	
}


int main()
{
	int num1, num2;
	inputNums(num1, num2);
	Adder calculator;		//Notice, object is one but still separate functions are needed to implemented using function overloading
	cout << "Adding ints:  " << calculator.add(num1,num2) << endl;


	float num3, num4;
	inputNums(num3, num4);
	cout << "Adding floats: " << calculator.add(num3,num4) << endl;
	return 0;
}

#else
int main()
{
	cout << " Nothing lives here" <<  endl;
	return 0;
}
#endif
