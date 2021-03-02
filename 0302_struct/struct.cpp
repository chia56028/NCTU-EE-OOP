#include <iostream>

// Step 0: Define data tpye
struct DATA {
	char Name[100];
	int Score[4];
	float Total, Avgerage;
};

// Step 1: Declare memory
DATA User[100];
int  User_No = 0;

int main()
{
	printf("Hello World!\n");

	// Step 2: Read data (Book1.txt)
	FILE *In;
	errno_t err = fopen_s(&In, "Book1.txt", "rb"); // open file, read binary
	if (err != 0) {
		printf("File Book1.txt error.\n");
	}
	else {
		while (!feof(In)) { // check if file end
			// fscanf() is unsafe, use fscanf_s() to replace
			fscanf_s(In, "%s %d %d %d %d\n",
				User[User_No].Name, sizeof(User[User_No].Name),
				&User[User_No].Score[0], // fscanf wants pointer for every variable
				&User[User_No].Score[1],
				&User[User_No].Score[2],
				&User[User_No].Score[3]
			);
			User_No++;
		}
	}

	// Step 3: Count Total Score, Avgerage
	DATA *p;
	for (int i = 0; i < User_No; i++) {
		p = &User[i];
		p->Total = p->Score[0] + p->Score[1] + p->Score[2] + p->Score[3];
		p->Avgerage = p->Total / 4;
	}
	/* Another way to write
	DATA *p = &User[0];
	for (int i = 0; i < User_No; i++) {
		p->Total = p->Score[0] + p->Score[1] + p->Score[2] + p->Score[3];
		p->Avgerage = p->Total / 4;
		p++;
	}
	*/

	// Step 4: Print data
	p = &User[0];
	for (int i = 0; i < User_No; i++) {
		printf("%s %d %d %d %d %f %f\n",
			User[i].Name,
			User[i].Score[0],
			User[i].Score[1],
			User[i].Score[2],
			User[i].Score[3],
			// use . for variable; use -> for pointer
			p->Total,         // User[i].Total,
			p->Avgerage       // User[i].Avgerage
		);
		p++;
	}
}