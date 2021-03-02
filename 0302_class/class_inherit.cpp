#include <iostream>

/* Step 1: Declare and define Class */
class MATH1 {
public: // public member includes variables and subroutine
	int ADD(int a, int b) { return (a + b); } // member function
	int SUB(int a, int b); // undefined member function
	int c; // member variable
};

// define details of member function
int MATH1::SUB(int a, int b) { return (a - b); }

class MATH2 : public MATH1 { // inherit from MATH1
public:
	int MUL(int a, int b) { return (a * b); }
	float DIV(int a, int b) { return ((float)a / (float)b); }
};

class MATH3 : public MATH2 { // inherit from MATH1
public:
	int AND(int a, int b) { return (a & b); }
	int XOR(int a, int b) { return (a ^ b); }
};

int main()
{
	/* Step 2: use Class */
	MATH2 *lp2 = new MATH2();
	int a = 10, b = 20;
	printf("[MATH2]\n");
	printf("%d+%d=%d\n", a, b, lp2->ADD(a, b)); 
	printf("%d-%d=%d\n", a, b, lp2->SUB(a, b));
	printf("%d*%d=%d\n", a, b, lp2->MUL(a, b));
	printf("%d/%d=%f\n", a, b, lp2->DIV(a, b));

	MATH3 *lp3 = new MATH3();
	a = 0b1100, b = 0b1111;
	printf("\n[MATH3]\n");
	printf("%d+%d=%d\n", a, b, lp3->ADD(a, b)); // inherit from grandfather
	printf("%d-%d=%d\n", a, b, lp3->SUB(a, b));
	printf("%d*%d=%d\n", a, b, lp3->MUL(a, b)); // inherit from father
	printf("%d/%d=%f\n", a, b, lp3->DIV(a, b));
	printf("%d&%d=%d\n", a, b, lp3->AND(a, b)); // self
	printf("%d^%d=%d\n", a, b, lp3->XOR(a, b));
}