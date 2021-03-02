#include <iostream>

// Step 1: Define Class
class MATH1 {
public: // public member includes variables and subroutine
	int ADD(int a, int b) { return (a + b); } // member function
	int SUB(int a, int b); // undefined member function
	int c; // member variable

};

// define details of member function
int MATH1::SUB(int a, int b) { return (a - b); }

int main()
{
	// Step 2: use Class
	MATH1 *lpMath1;
	lpMath1 = new MATH1();
	int a = 10, b = 20, c = 30;
	printf("%d+%d=%d\n", a, b, lpMath1->ADD(a, b));
	printf("%d-%d=%d\n", a, b, lpMath1->SUB(a, b));
	printf("c in main func: %d, c in class MATH1: %d\n", c, lpMath1->c);

	MATH1 lpMath2;
	lpMath2.c = 100;
	printf("c = %d", lpMath2.c);
}