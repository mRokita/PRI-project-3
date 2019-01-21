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

#include <stdbool.h>
#include "../include/main_window.h"
#include "../include/data/animal.h"
#include "../include/remove_item_window.h"


/**
 * A container for data required to sort the table
 * @param col  Column
 * @param list List of animals
 * @param table GtkGrid of the table
 * @return All arguments neatly packed in an SortCallbackData instance.
 */
SortCallbackData*
sort_callback_data_new(COLUMN col,
                       AnimalLinkedList* list,
                       GtkWidget *table){
    SortCallbackData* sortCallbackData = malloc(sizeof(SortCallbackData));
    sortCallbackData->col = col;
    sortCallbackData->list = list;
    sortCallbackData->table = table;
    return sortCallbackData;
}


/**
 * @brief Initialize the main window
 * @param app Application
 * @return main window, not shown yet
 */
GtkWidget*
main_window_new(GtkApplication *app)
{

    GtkWidget* window;
    GtkWidget* mainContainer;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Ogród zoologiczny");
    gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);

    mainContainer = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER (window), GTK_WIDGET (mainContainer));

    GtkWidget* containerTable;
    containerTable = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_hexpand(containerTable, 1);
    gtk_widget_set_vexpand(containerTable, 1);
    GtkWidget* table;
    table = gtk_grid_new();
    AnimalLinkedList* animals = animal_linked_list_new();

    for(int i=0; i<200; ++i){
        Animal* a = animal_new(i, "Blazej", "Wielblad", i/4+3, "Je orzeszki");
        animal_linked_list_add_item(animals, a);
    }
    gtk_container_add(GTK_CONTAINER(containerTable), GTK_WIDGET(table));
    gtk_grid_set_column_homogeneous(GTK_GRID(table), gtk_true());
    gtk_grid_set_column_homogeneous(GTK_GRID(mainContainer), gtk_true());
    add_table_headers(mainContainer, table, animals);
    fill_table(table, animals);
    gtk_grid_attach(GTK_GRID (mainContainer), GTK_WIDGET (containerTable), 0, 1, 5, 1);
    add_control_buttons(app, mainContainer);

    return window;
}

void callback_remove_animal(
        GtkWidget *widget,
        gpointer callback_data)
        {
    gtk_widget_show_all(remove_item_window_new((GtkApplication*)callback_data));
}


/**
 * Add edit and delete buttons below the table
 * @param mainContainer
 */
void add_control_buttons(GtkApplication* app,
                         GtkWidget *mainContainer)
                         {
    GtkWidget* buttonRemoveAnimal = gtk_button_new_with_label("Usuń element");
    gtk_widget_set_hexpand(buttonRemoveAnimal, 1);
    gtk_grid_attach(GTK_GRID(mainContainer), buttonRemoveAnimal, 0, 2, 2, 1);
    g_signal_connect(G_OBJECT(buttonRemoveAnimal), "clicked", G_CALLBACK(callback_remove_animal), (gpointer) app);


    GtkWidget* buttonAddAnimal = gtk_button_new_with_label("Dodaj element");
    gtk_widget_set_hexpand(buttonAddAnimal, 1);
    gtk_widget_set_margin_start(buttonAddAnimal, 5);
    gtk_grid_attach(GTK_GRID(mainContainer), buttonAddAnimal, 2, 2, 3, 1);
}

int sort_by = -1;
int sort_asc = 1;


/**
 * @brief Animal comparator
 * Used to sort the table
 * @param a
 * @param b
 * @return boolean, true if a and b should be swapped
 */
int
cmp(Animal* a, Animal* b){
    int res = 0;
    if(!sort_asc) {
        Animal* t = a;
        a = b;
        b = t;
    }
    if(sort_by == ID) res = a->id > b->id;
    if(sort_by == AGE) res = a->age > b->age;
    if(sort_by == NAME) res = strcmp(a->name, b->name) > 0;
    if(sort_by == SPECIES) res = strcmp(a->species, b->species) > 0;
    if(sort_by == COMMENT) res = strcmp(a->comment, b->comment) > 0;
    return res;
}


/**
 * @brief Add table header buttons
 * @param mainContainer the main GtkGrid of the window
 * @param table table
 * @param animals list of animals
 */
void
add_table_headers (GtkWidget* mainContainer,
                   GtkWidget* table,
                   AnimalLinkedList* animals)
{
    GtkWidget *buttonId = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(buttonId), "Id");
    gtk_widget_set_hexpand(buttonId, TRUE);

    g_signal_connect(G_OBJECT(buttonId), "clicked", G_CALLBACK(callback_sort_click), (gpointer) sort_callback_data_new(ID, animals, table));
    gtk_grid_attach(GTK_GRID (mainContainer), GTK_WIDGET (buttonId), 0, 0, 1, 1);

    GtkWidget *buttonName = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(buttonName), "Imię");
    gtk_widget_set_hexpand(buttonName, TRUE);
    g_signal_connect(G_OBJECT(buttonName), "clicked", G_CALLBACK(callback_sort_click), (gpointer) sort_callback_data_new(NAME, animals, table));
    gtk_widget_set_margin_start(buttonName, 5);
    gtk_grid_attach(GTK_GRID (mainContainer), GTK_WIDGET (buttonName), 1, 0, 1, 1);

    GtkWidget *buttonSpecies = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(buttonSpecies), "Gatunek");
    gtk_widget_set_hexpand(buttonSpecies, TRUE);
    g_signal_connect(G_OBJECT(buttonSpecies), "clicked", G_CALLBACK(callback_sort_click),
                     (gpointer) sort_callback_data_new(SPECIES, animals, table));
    gtk_widget_set_margin_start(buttonSpecies, 5);
    gtk_grid_attach(GTK_GRID (mainContainer), GTK_WIDGET (buttonSpecies), 2, 0, 1, 1);

    GtkWidget* buttonAge = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(buttonAge), "Wiek");
    gtk_widget_set_hexpand(buttonAge, TRUE);
    g_signal_connect(G_OBJECT(buttonAge), "clicked", G_CALLBACK(callback_sort_click),
                     (gpointer) sort_callback_data_new(AGE, animals, table));
    gtk_widget_set_margin_start(buttonAge, 5);
    gtk_grid_attach(GTK_GRID (mainContainer), GTK_WIDGET (buttonAge), 3, 0, 1, 1);

    GtkWidget* buttonComment = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(buttonComment), "Komentarz");
    gtk_widget_set_hexpand(buttonComment, TRUE);
    g_signal_connect(G_OBJECT(buttonComment), "clicked", G_CALLBACK(callback_sort_click),
                     (gpointer) sort_callback_data_new(COMMENT, animals, table));
    gtk_widget_set_margin_start(buttonComment, 5);
    gtk_grid_attach(GTK_GRID (mainContainer), GTK_WIDGET (buttonComment), 4, 0, 1, 1);
}


/**
 * On click on any of the header buttons
 * @param widget
 * @param callback_data an instance of SortCallbackData
 */
void
callback_sort_click(
        GtkWidget *widget,
        gpointer callback_data)
{
    SortCallbackData* cd = (SortCallbackData*) callback_data;
    if(sort_by == cd->col) sort_asc = !sort_asc;
    sort_by = cd->col;
    animal_linked_list_sort(cd->list, cmp);
    fill_table(cd->table, cd->list);
}

/**
 * Add animal to the table
 * @param table
 * @param animal
 * @param row row number, should be empty.
 */
void
add_animal_to_table(
        GtkWidget* table,
        Animal* animal,
        int row)
{
    char* idString = malloc(12);
    sprintf(idString, "%d", animal->id);
    GtkWidget* labelId = gtk_label_new(idString);
    gtk_label_set_xalign(GTK_LABEL (labelId), 0.0);
    gtk_widget_set_margin_start(labelId, 5);
    gtk_widget_set_margin_top(labelId, 5);
    gtk_widget_set_hexpand(labelId, TRUE);
    gtk_grid_attach(GTK_GRID (table), labelId, 0, row, 1, 1);

    GtkWidget* labelName = gtk_label_new(animal->name);
    gtk_label_set_xalign(GTK_LABEL (labelName), 0.0);
    gtk_widget_set_margin_start(labelName, 5);
    gtk_widget_set_margin_top(labelName, 5);
    gtk_widget_set_hexpand(labelName, TRUE);
    gtk_grid_attach(GTK_GRID (table), labelName, 1, row, 1, 1);

    GtkWidget* labelSpecies = gtk_label_new(animal->species);
    gtk_label_set_xalign(GTK_LABEL (labelSpecies), 0.0);
    gtk_widget_set_margin_start(labelSpecies, 5);
    gtk_widget_set_margin_top(labelSpecies, 5);
    gtk_widget_set_hexpand(labelSpecies, TRUE);
    gtk_grid_attach(GTK_GRID (table), labelSpecies, 2, row, 1, 1);

    char* ageString = malloc(12);
    sprintf(ageString, "%d", animal->age);

    GtkWidget* labelAge = gtk_label_new(ageString);
    gtk_label_set_xalign(GTK_LABEL (labelAge), 0.0);
    gtk_widget_set_margin_start(labelAge, 5);
    gtk_widget_set_margin_top(labelAge, 5);
    gtk_widget_set_hexpand(labelAge, TRUE);
    gtk_grid_attach(GTK_GRID (table), labelAge, 3, row, 1, 1);

    GtkWidget* labelComment = gtk_label_new(animal->comment);
    gtk_label_set_xalign(GTK_LABEL (labelComment), 0.0);
    gtk_widget_set_margin_start(labelComment, 5);
    gtk_widget_set_margin_top(labelComment, 5);
    gtk_widget_set_hexpand(labelComment, TRUE);
    gtk_grid_attach(GTK_GRID (table), labelComment, 4, row, 1, 1);
    gtk_widget_show_all(table);
}


void
fill_table(GtkWidget* table,
           AnimalLinkedList* animals)
{
    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(table));
    for(iter = children; iter != NULL; iter = g_list_next(iter))
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);

    AnimalLinkedListItem* cur = animals->firstItem;
    for(int i=0; i<animals->size; ++i){
        add_animal_to_table(table, cur->value, i+1);
        cur = cur->next;
    }
}