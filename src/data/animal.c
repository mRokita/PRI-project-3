//
// Created by mrokita on 20.01.19.
//

#include <stdlib.h>
#include "../../include/data/animal.h"

Animal* animal_new(char* name, char* species, int age, char* comment){
    Animal* animal = malloc(sizeof(Animal));
    animal->name = name;
    animal->species = species;
    animal->age = age;
    animal->comment = comment;
    return animal;
}
