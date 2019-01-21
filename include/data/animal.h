/*
 * This file is part of the PRI-project-3 distribution (https://github.com/mRokita/PRI-project-3.
 * Copyright (c) 2018 Michał Rokita.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef PRI3_ANIMAL_H
#define PRI3_ANIMAL_H

typedef struct Animal {
    int id;
    char* name;
    char* species;
    int age;
    char* comment;
} Animal;



Animal*
animal_new(int id, char* name, char* species, int age, char* comment);

typedef struct AnimalLinkedList {
    int size;
    struct AnimalLinkedListItem* firstItem;
    struct AnimalLinkedListItem* lastItem;
} AnimalLinkedList;

void
animal_linked_list_sort(AnimalLinkedList *list, int (*cmp)(Animal *a, Animal *b));

typedef struct AnimalLinkedListItem{
    Animal* value;
    struct AnimalLinkedListItem* prev;
    struct AnimalLinkedListItem* next;
} AnimalLinkedListItem;

AnimalLinkedList*
animal_linked_list_new();

int
animal_linked_list_contains(AnimalLinkedList* animals, int id);

void
animal_linked_list_add_item(AnimalLinkedList* list, Animal* value);

Animal
animal_linked_list_get_item(int index);

#endif //PRI3_ANIMAL_H
