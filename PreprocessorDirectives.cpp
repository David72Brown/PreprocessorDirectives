#include <assert.h>
#include <iostream>
#include "Animals.h"
using namespace std;

#define OUTPUT_NUMBER(x) cout << "The number is " << x << endl;
#define ADD(a, b) a+b
#define MULTIPLY(a, b) a*b

void TestYourselfOnHashDefineProblems(void)
{
	int x = 0;

	// This bit won't compile - see if you can figure out what's wrong and fix it.
	if (x == 123)
		OUTPUT_NUMBER(123);
	else                             // <--- Why does this not compile?
		cout << "x is not 123." << endl;

	// The developer is expecting x to become 14 but it doesn't. What's wrong, and how would you fix it?
	x = 2 * ADD(3, 4);
	cout << "2 * ADD(3, 4) = " << x << endl;

	// The developer is expecting x to become 30 but it doesn't. What's wrong, and how would you fix it?
	x = MULTIPLY(5, 3 + 3);
	cout << "MULTIPLY(5, 3+3) = " << x << endl;
}

// In a header file somewhere we can switch the ASSERT statement on and off. Maybe it's useful
// to have asserts turned on during development but turned off in releases sent to the customer.
// Define ASSERTS_REQUIRED if you want the ASSERT statement to work, otherwise don't define it
// and the ASSERT statements will be compiled out of the code completely.
#define ASSERTS_REQUIRED
#ifdef ASSERTS_REQUIRED
#define ASSERT(Condition)	{																					\
								cout << "Assert fail, "  __FILE__ ", " << __LINE__ << ", " #Condition << endl;	\
								assert(Condition);																\
							}
#else
#define ASSERT(Condition)
#endif

bool DoVitalProcess(void)
{
	return true;
}

void TestYourselfOnAsserts(void)
{
	int x = 5;

	// This assert will fail and you will see its condition, filename and line number displayed on the console window.
	// Feel free to comment out the definition of ASSERTS_REQUIRED elsewhere in this file to compile out this line.
	// Then you'll notice that if you step through this function, execution goes straight to the closing } because the
	// ASSERT() lines will have been stripped out by the preprocessor so the compiler never even gets to see them.
	ASSERT(x == 6);

	// The developer intends to check that when the vital process is run, it returns true to indicate it ran OK.
	// But what's wrong with how it's been coded?
	ASSERT(DoVitalProcess());
}

void OutputAnimalName(eAnimal animal)
{
	switch (animal)
	{
	case DOG:
		cout << "DOG" << endl;
		break;
	case BISON:
		cout << "BISON" << endl;
		break;
	case MOUSE:
		cout << "MOUSE" << endl;
		break;
	case SHEEP:
		cout << "SHEEP" << endl;
		break;
	case VELOCIRAPTOR:
		cout << "VELOCIRAPTOR" << endl;
		break;
	case UNICORN:
		cout << "UNICORN" << endl;
		break;
	default:
		assert(false);
		break;
	}
}

int main()
{
	TestYourselfOnHashDefineProblems();
	TestYourselfOnAsserts();
}

/*	If you look for Dog, Bison etc in this file and in Animals.cpp and Animals.h you will see that we have a list of
	animals which turn up in each file. Animals.cpp contains the array Animals[] of animal-related info for each animal.
	Animals.h contains the extern declaration for that array of info, so PreprocessorDirectives.cpp can #include it
	and access the info. Then, depending on what you want your software to do with this list of animals, you will#
	probably have other code in this file or other .cpp files which also cater for every animals. The point here is
	that if you want to add or remove an animal, you have to do it in multiple places and there is a chance you will
	miss one. At best you will get a compilation error but at worst the code will compile but will have a defect in it.
	So there is another way to do this so we have just one single place in the code which contains everything we need,
	so it can never become out of step with anything. You'll see this method used occasionally so it's worth
	understanding it. And it's good practice in getting your head around #define directives too.

	You should create a new file called AnimalList.h which contains nothing but this:
			ANIMAL(DOG, 25, "Meat", false)
			ANIMAL(BISON, 72, "Grass", false)
			ANIMAL(MOUSE, 1, "Insects", false)
			ANIMAL(SHEEP, 30, "Grass", false)
			ANIMAL(VELOCIRAPTOR, 120, "Cavemen", false)
			ANIMAL(UNICORN, 80, "Blossom", true)

	Nothing else goes in that file. It doesn't even look like C++ code but it does contain everything we need to know.
	Then, everywhere else where you need to declare or define the animals (i.e. in Animals.h, Animals.cpp,
	PreprocessorDirectives.cpp and any other .cpp files) you #define ANIMAL() so that it expands to whatever you
	need your code to be in that file, and you #include "AnimalList.h".

	Animals.h will be:
			typedef enum {
			#define ANIMAL(Species, InchesHigh, Diet, Imaginary) "ANIMAL_" #Species,
			#include "AnimalList.h"
			#undef ANIMAL
				NUM_ANIMALS
			} eAnimal;
	(Preprocessor directives, i.e. the lines starting with a #, must not be indented, they must start at the leftmost
	position. I have only indented them above so it looks clearer in this commented explanation.)
	Note that the # operator (the "stringizer" operator) tells the preprocessor to take the Species string (e.g. DOG)
	and put quotes around it to make it a string, i.e. "DOG". Note also that whenever you put 2 quoted string literals
	side by side in C/C++, the preprocessor will join them together for you, e.g.:
		cout << "Hello " "world" << endl;
	The preprocessor will convert this to the following before compilation starts:
		cout << "Hello world" << endl;
	So in Animals.h (file contents shown above), the "ANIMAL_" and the stringized species e.g. "DOG" will be
	concatenated together to form "ANIMAL_DOG".

	Then Animals.cpp would be:
			const tAnimalInfo Animals[] = {
			#define ANIMAL(Species, InchesHigh, Diet, Imaginary) { InchesHigh, Diet, Imaginary },
			#include "AnimalList.h"
			#undef ANIMAL
			};

	And in our main() function or any other function in any .cpp file which deals with animals, we can access Animals[]
	to get whatever info we want. If we were particularly interested in animal height then we could just create an
	array of that info like this:
			const char* AnimalHeight[NUM_ANIMALS] = {
			#define ANIMAL(Species, InchesHigh, Diet, Imaginary) InchesHigh,
			#include "AnimalList.h"
			#undef ANIMAL
			};

	*/
