#pragma once

const unsigned int MAX_DIET_LEN = 20;

#define MULTIPLE_ANIMAL_LISTS

#ifdef MULTIPLE_ANIMAL_LISTS

typedef enum { SP_DOG, SP_BISON, SP_MOUSE, SP_SHEEP, SP_VELOCIRAPTOR, SP_UNICORN, SP_FLY, NUM_ANIMALS } eAnimal;

#else

typedef enum {
#define ANIMAL(Species, InchesHigh, Diet, IsImaginary) SP_##Species,
#include "AnimalList.h"
#undef ANIMAL
	NUM_ANIMALS
} eAnimal;

#endif // MULTIPLE_ANIMAL_LISTS

typedef struct {
	unsigned int InchesHigh;
	char Diet[MAX_DIET_LEN+1];
	bool IsImaginary;
} tAnimalInfo;

extern const tAnimalInfo Animals[];
extern void OutputAnimalInfo(eAnimal animal);
