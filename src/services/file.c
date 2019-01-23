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

#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <string.h>
#include "../../include/services/file.h"
#include "../../include/data/animal.h"

void
load_data_from_file(AnimalLinkedList* animals)
{
    char tab[5][25] =
            {
                    "EEEEE  IIII  TTTTTT  IIII",
                    "E       II     TT     II ",
                    "EEEEE   II     TT     II ",
                    "E       II     TT     II ",
                    "EEEEE  IIII    TT    IIII" ,
            };
    for(int i=0; i<5; ++i){
        for(int j=0; j<25; ++j){
            printf("%c", tab[i][j]);
        }
        printf("\n");
    }
    FILE *file = fopen("zoo.dat", "r");

    printf("\n");

    enum TYPES {INT, CHAR};
    enum TYPES type_order[5] = {INT, CHAR, CHAR, INT, CHAR};
    int cur_order = 0;
    int c;
    if(file){
        while ((c = getc(file)) != EOF) {
            char cur = (char) c;
            if(cur == '\t') {
                cur_order ++;
                continue;
            }
            if(cur == '\n') {
                if(cur_order != 4){
                    printf("Data is incomplete\n");
                }
                cur_order = 0;
                continue;
            }
            if(cur_order > 4) {
                printf("Too many columns at some line\n");
                return;
            }
            if(type_order[cur_order] == INT){
                if(!isdigit(c)){
                    printf("Invalid value - %c is not a digit\n", c);
                    return;
                }
            }
        }
        int id;
        char* name = malloc(100);
        char* species = malloc(100);
        int age;
        char* comment = malloc(100);
        fseek(file, 0, 0);
        while (1){
            int res = fscanf(file, "%d\t%s\t%s\t%d\t%s\n", &id, name, species, &age, comment);
            if(res == 5) animal_linked_list_add_item(animals, animal_new(id, name, species, age, comment));

            if(res == EOF | res == 0) break;
        }
        fclose(file);
    }
}

void
save_data_to_file(AnimalLinkedList* animals)
{
    FILE *file = fopen("zoo.dat", "w");
    AnimalLinkedListItem* cur = animals->firstItem;
    for(int i=0; i<animals->size;++i){
        printf("Saving animal #%d\n", cur->value->id);
        fprintf(file,
                "%d\t%s\t%s\t%d\t%s\n",
                cur->value->id,
                cur->value->name,
                cur->value->species,
                cur->value->age,
                cur->value->comment);
        cur = cur->next;
    }
    fclose(file);
}