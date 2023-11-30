#include <stdio.h>

#define PINT(x) printf("%i\n", x)
#define PINTS(x, y) printf("%s %i\n", y, x)

int main(void) {
	int* p;
	int i1 = 1;
	int i2 = 2;

	// Compiler bullcrappery
	{
		#if 1
		const int& a = i1 + i2;
		#else
		int& a = i1 + i2; // Causes error
		#endif
		p = &(const_cast<int&>(a));
	}

	// Print out that integer
	PINT(*p);

	// Save it as a reference
	int& intRef = *p;

	// Do some random calculations to try and change it
	int a = 1 + intRef;
	int b = a + 1;
	int c = b - 1 + a;
	int d = d + 2 - 1 + 3;

	PINTS(a, "A is");
	PINTS(b, "B is");
	PINTS(c, "C is");
	PINTS(d, "D is");
	PINTS(intRef, "The ref is");

	return 0;
}