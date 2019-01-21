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

#ifndef PRI3_MAIN_WINDOW_H
#define PRI3_MAIN_WINDOW_H

#include <gtk/gtk.h>
#include "data/animal.h"

typedef enum COLUMN {ID,
    NAME,
    SPECIES,
    AGE,
    COMMENT}
        COLUMN;

typedef struct SortCallbackData {
    enum COLUMN col;
    AnimalLinkedList* list;
    GtkWidget* table;
} SortCallbackData;

GtkWidget*
main_window_new(GtkApplication* app);

void
callback_sort_click(GtkWidget *widget, gpointer callback_data);

void
add_table_headers (GtkWidget* mainContainer,
                   GtkWidget* table,
                   AnimalLinkedList* animals);

void
add_control_buttons(GtkApplication* app,
        GtkWidget* mainContainer);

void
fill_table(GtkWidget* table, AnimalLinkedList* animals);
#endif //PRI3_MAIN_WINDOW_H
