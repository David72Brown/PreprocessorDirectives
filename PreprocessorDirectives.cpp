#include <assert.h>
#include <iostream>
#include "Animals.h"
using namespace std;

// In a header file somewhere we can switch the TRACE statement on and off. Maybe it's useful
// to have it turned on during development but turned off in releases sent to the customer.
// Define TRACE_ON if you want the TRACE statements to work, otherwise don't define it
// and the TRACE statements will be compiled out of the code completely.
#define TRACE_ON
#ifdef TRACE_ON
void OutputString(char *pStr) { cout << "Line " << ": " << pStr << endl; }
#define TRACE(str)	
#else
#define TRACE(str)
#endif

#define ADD(a, b) a+b
#define MULTIPLY(a, b) a*b
#define OUTPUT_NUMBER(x) cout << "The number is " << x << endl;

void TestYourselfOnHashDefineProblems(void)
{
	int x = 0;

	// The developer is expecting x to become 14 but it doesn't. What's wrong, and how would you fix it?
	x = 2 * ADD(3, 4);
	cout << "2 * ADD(3, 4) = " << x << endl;

	// The developer is expecting x to become 30 but it doesn't. What's wrong, and how would you fix it?
	x = MULTIPLY(5, 3 + 3);
	cout << "MULTIPLY(5, 3+3) = " << x << endl;

	//if (x == 123)
	//	OUTPUT_NUMBER(123);
	//else                             // <--- Why does this not compile?
	//	cout << "x is not 123." << endl;

}

void TestYourselfOnTrace(void)
{
	// Feel free to comment out the definition of TRACE_ON elsewhere in this file to compile out this line.
	// Then you'll notice that if you step through this function, execution goes straight to the closing } because the
	// TRACE() line will have been stripped out by the preprocessor so the compiler never even gets to see them.
	TRACE("Got to this bit");
}

int main()
{
	TRACE("Top of main");
	TestYourselfOnHashDefineProblems();
	TestYourselfOnTrace();
	TRACE("Middle of main");

	OutputAnimalInfo(SP_VELOCIRAPTOR);
}

/*	If you look for Dog, Bison etc in this file and in Animals.cpp and Animals.h you will see that we have a list of
	animals which turn up in each file. Animals.cpp contains the array Animals[] of animal-related info for each animal.
	Animals.h contains the extern declaration for that array of info, so PreprocessorDirectives.cpp can #include it
	and access the info, and also an enum for the different species of animal e.g. SP_DOG. Then, depending on what you
	want your software to do with this list of animals, you will probably have other code in this file or other .cpp
	files which also cater for every animals.
	Unfortunately, if you want to add or remove an animal, you have to do it in multiple places and there is a chance
	you will miss one or put them in a different order in one file compared to the others. At best you will get a
	compilation error but at worst the code will compile but will have a defect in it.

	There is another way to do this so we have just one single place in the code which contains everything we need.
	It involes using the file AnimalList.h which contains nothing but this:
			ANIMAL(DOG, 25, MEAT, false)
			ANIMAL(BISON, 72, GRASS, false)
			ANIMAL(MOUSE, 1, CHEESE, false)
			ANIMAL(SHEEP, 30, GRASS, false)
			ANIMAL(VELOCIRAPTOR, 120, CAVEMEN, false)
			ANIMAL(UNICORN, 80, BLOSSOM, true)

	Nothing else goes in that file. It doesn't even look like C++ code but it does contain everything we know about
	animals. Then, everywhere else where you need to declare or define the animals (i.e. in Animals.h, Animals.cpp,
	PreprocessorDirectives.cpp and any other files) you #define ANIMAL() so that it expands to whatever you need your
	code to be in that file, and you #include "AnimalList.h".

	For this demonstration, find this line in Animals.h:
	#define MULTIPLE_ANIMAL_LISTS
	And comment it out. That will activate the alternative code in all relevant files so you can see how it works.

	The enum definition in Animals.h will become:
			typedef enum {
			#define ANIMAL(Species, InchesHigh, Diet, IsImaginary) SP_##Species,
			#include "AnimalList.h"
			#undef ANIMAL
				NUM_ANIMALS
			} eAnimal;
	(Preprocessor directives, i.e. the lines starting with a #, must not be indented, they must start at the leftmost
	position. I have only indented them above so it looks clearer in this commented explanation.)
	The definition of ANIMAL above replaces each entire line in AnimalList.h with e.g. "SP_DOG,". The ## separates
	the SP_ and the Species value but will be removed by the preprocessor once Species has been replaced by e.g. DOG.
	Without that ##, it would just read SP_Species and the preprocessor would not replace the Species with DOG.

	The definition of Animals[] in Animals.cpp becomes:
			const tAnimalInfo Animals[] = {
			#define ANIMAL(Species, InchesHigh, Diet, IsImaginary) { InchesHigh, #Diet, IsImaginary },
			#include "AnimalList.h"
			#undef ANIMAL
			};
	The # operator (the "stringizer" operator) tells the preprocessor to take the Diet (e.g. GRASS) and put quotes
	around it to make it a string, i.e. "GRASS".
	The function OutputAnimalInfo() defined in Animals.cpp changes so that the CASE statements are replaced with:
	void OutputAnimalInfo(eAnimal animal)
			#define ANIMAL(Species, InchesHigh, Diet, IsImaginary)											\
									case SP_##Species:														\
										cout << #Species << ": " << InchesHigh << ", " << #Diet << ", "		\
											<< (IsImaginary ? "true" : "false") << endl;					\
										break;
			#include "AnimalList.h"
			#undef ANIMAL

	And in our main() function or any other function in any .cpp file which deals with animals, we can access Animals[]
	to get whatever info we want.
*/
