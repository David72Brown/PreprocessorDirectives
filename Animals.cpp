#include <assert.h>
#include <iostream>
#include "Animals.h"
using namespace std;

#ifdef MULTIPLE_ANIMAL_LISTS

const tAnimalInfo Animals[] = {
	{ 25,  "MEAT",    false},
	{ 72,  "GRASS",   false},
	{ 1,   "CHEESE",  false},
	{ 30,  "GRASS",   false},
	{ 120, "CAVEMEN", false},
	{ 80,  "BLOSSOM", true }
};

void OutputAnimalInfo(eAnimal animal)
{
	switch (animal)
	{
	case SP_DOG:
		cout << "DOG: " << Animals[animal].InchesHigh << ", " << Animals[animal].Diet << ", " << (Animals[animal].IsImaginary ? "true" : "false") << endl;
		break;
	case SP_BISON:
		cout << "BISON: " << Animals[animal].InchesHigh << ", " << Animals[animal].Diet << ", " << (Animals[animal].IsImaginary ? "true" : "false") << endl;
		break;
	case SP_MOUSE:
		cout << "MOUSE: " << Animals[animal].InchesHigh << ", " << Animals[animal].Diet << ", " << (Animals[animal].IsImaginary ? "true" : "false") << endl;
		break;
	case SP_SHEEP:
		cout << "SHEEP: " << Animals[animal].InchesHigh << ", " << Animals[animal].Diet << ", " << (Animals[animal].IsImaginary ? "true" : "false") << endl;
		break;
	case SP_VELOCIRAPTOR:
		cout << "VELOCIRAPTOR: " << Animals[animal].InchesHigh << ", " << Animals[animal].Diet << ", " << (Animals[animal].IsImaginary ? "true" : "false") << endl;
		break;
	case SP_UNICORN:
		cout << "UNICORN: " << Animals[animal].InchesHigh << ", " << Animals[animal].Diet << ", " << (Animals[animal].IsImaginary ? "true" : "false") << endl;
		break;
	default:
		assert(false);
		break;
	}
}

#else

const tAnimalInfo Animals[] = {
#define ANIMAL(Species, InchesHigh, Diet, IsImaginary) { InchesHigh, #Diet, IsImaginary },
#include "AnimalList.h"
#undef ANIMAL
};

void OutputAnimalInfo(eAnimal animal)
{
	switch (animal)
	{
#define ANIMAL(Species, InchesHigh, Diet, IsImaginary)											\
						case SP_##Species:														\
							cout << #Species << ": " << InchesHigh << ", " << #Diet << ", "		\
								<< (IsImaginary ? "true" : "false") << endl;					\
							break;
#include "AnimalList.h"
#undef ANIMAL
	default:
		assert(false);
		break;
	}
}

#endif // MULTIPLE_ANIMAL_LISTS
