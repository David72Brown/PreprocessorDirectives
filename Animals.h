#pragma once

const unsigned int MAX_ANIMAL_SPECIES_LEN = 20;

typedef enum { DOG, BISON, MOUSE, SHEEP, VELOCIRAPTOR, UNICORN } eAnimal;
typedef struct { unsigned int InchesHigh; char Diet[MAX_ANIMAL_SPECIES_LEN]; bool Imaginary; } tAnimalInfo;
extern const tAnimalInfo Animals[];
