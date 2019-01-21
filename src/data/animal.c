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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/data/animal.h"


AnimalLinkedListItem*
animal_linked_list_item_new(Animal* value){
    AnimalLinkedListItem* item = malloc(sizeof(AnimalLinkedListItem));
    item->value = value;
    return item;
}


int
animal_linked_list_contains(AnimalLinkedList* animals, int id){
    Animal* cur = animals->firstItem;
    for(int i=0; i<animals->size; ++i){
        if (cur->id == id) return 1;
    }
    return 0;
}


Animal*
animal_new(int id, char* name, char* species, int age, char* comment){
    Animal* animal = malloc(sizeof(Animal));
    animal->id = id;
    animal->name = malloc(strlen(name)+1);
    strcpy(animal->name, name);
    animal->species = malloc(strlen(species)+1);
    strcpy(animal->species, species);

    animal->age = age;
    animal->comment = malloc(strlen(comment)+1);
    strcpy(animal->comment, comment);
    return animal;
}

AnimalLinkedList*
animal_linked_list_new(){
    AnimalLinkedList* list = malloc(sizeof(AnimalLinkedList));
    list->size = 0;
    return list;
}

void
animal_linked_list_sort(AnimalLinkedList *list,
                        int (*cmp)(Animal *a, Animal *b))
{
    int changed = 1;
    while(changed){
        changed = 0;
        AnimalLinkedListItem* cur = list->firstItem;
        for(int i=0; i<list->size-1; ++i){
            if((*cmp)(cur->value, cur->next->value)){
                changed = 1;
                int has_prev = list->firstItem != cur;
                int has_next = list->lastItem != cur->next;
                AnimalLinkedListItem* node_0 = has_prev ? cur->prev : NULL;
                AnimalLinkedListItem* node_1 = cur;
                AnimalLinkedListItem* node_2 = cur->next;
                AnimalLinkedListItem* node_3 = has_next ? cur->next->next : NULL;
                node_1->next = node_2->next;
                node_1->prev = node_2;
                node_2->next = node_1;
                node_2->prev = node_0;
                if(has_prev){
                    node_0->next = node_2;
                } else {
                    list->firstItem = node_2;
                }
                if(has_next){
                    node_3->prev = node_1;
                } else {
                    list->lastItem = node_1;
                }
                cur = node_2;
            }
            cur = cur->next;
        }
    }
}

void
animal_linked_list_add_item(AnimalLinkedList* list, Animal* value){

    AnimalLinkedListItem* cur = list->firstItem;
    AnimalLinkedListItem* toAdd = animal_linked_list_item_new(value);

    if(list->size == 0){
        list->firstItem = toAdd;
        list->lastItem = toAdd;
        list->size ++;
        return;
    }
    int i;
    for(i=0; i<list->size-1; ++i){
        cur = cur->next;
    }

    cur->next = toAdd;
    list->lastItem = toAdd;
    toAdd->prev = cur;

    list->size ++;
};
