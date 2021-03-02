#include <iostream>

/* Step 1: Declare and define Class */
class MATH1 {
public: // public member includes variables and subroutine
	MATH1(int a) { c = a; } // constructor
	~MATH1(); // destructor
	int ADD(int a, int b) { return (a + b); } // member function
	int SUB(int a, int b); // undefined member function
	int c; // member variable
};

// define details of member function
int MATH1::SUB(int a, int b) { return (a - b); }

MATH1::~MATH1() {
	printf("Return memory\n");
}

int main()
{
	/* Step 2: use Class */
	MATH1 *lpMath1;
	lpMath1 = new MATH1(50);
	int a = 10, b = 20, c = 30;
	printf("%d+%d=%d\n", a, b, lpMath1->ADD(a, b));
	printf("%d-%d=%d\n", a, b, lpMath1->SUB(a, b));
	printf("c in main func: %d, c in class MATH1: %d\n", c, lpMath1->c);
	delete lpMath1; // trigger destructor

	MATH1 lpMath2(100);
	printf("c = %d\n", lpMath2.c);
}