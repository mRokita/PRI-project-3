//
// Created by mrokita on 20.01.19.
//

#include "../include/main_window.h"
#include "../include/data/animal.h"

/**
 * @brief Initialize main window
 * @param app Application
 * @return main window, not shown yet
 */
GtkWidget * main_window_new(GtkApplication *app){
    GtkWidget *window;
    GtkWidget *mainContainer;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Ogród zoologiczny");
    gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);

    mainContainer = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER (window), GTK_WIDGET (mainContainer));

    GtkWidget *containerTable;
    containerTable = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_hexpand(containerTable, 1);
    gtk_widget_set_vexpand(containerTable, 1);
    GtkWidget *table;
    table = gtk_grid_new();
    Animal animals[] = {{"Andrzej", "Struś", 10, "Gryzie"},
                         {"Andrzej", "Struś", 10, "Gryzie"},
                         {"Andrzej", "Struś", 10, "Gryzie"},
                         {"Andrzej", "Struś", 10, "Gryzie"},
                         {"Andrzej", "Struś", 10, "Gryzie"},
                         {"Andrzej", "Struś", 10, "Gryzie"},
                         {"Andrzej", "Struś", 10, "Gryzie"},
                         {"Andrzej", "Struś", 10, "Gryzie"},
                         {"Andrzej", "Struś", 10, "Gryzie"},
                         {"Andrzej", "Struś", 10, "Gryzie"},
                         {"Andrzej", "Struś", 10, "Gryzie"},
                         {"Andrzej", "Struś", 10, "Gryzie"},};
    gtk_container_add(GTK_CONTAINER(containerTable), GTK_WIDGET(table));
    GtkWidget *buttonName = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(buttonName), "Imię");
    gtk_widget_set_hexpand(buttonName, TRUE);
    gtk_grid_attach(GTK_GRID (mainContainer), GTK_WIDGET (buttonName), 0, 0, 1, 1);

    GtkWidget *buttonSpecies = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(buttonSpecies), "Gatunek");
    gtk_widget_set_hexpand(buttonSpecies, TRUE);
    gtk_widget_set_margin_start(buttonSpecies, 5);
    gtk_grid_attach(GTK_GRID (mainContainer), GTK_WIDGET (buttonSpecies), 1, 0, 1, 1);

    GtkWidget *buttonAge = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(buttonAge), "Wiek");
    gtk_widget_set_hexpand(buttonAge, TRUE);
    gtk_widget_set_margin_start(buttonAge, 5);
    gtk_grid_attach(GTK_GRID (mainContainer), GTK_WIDGET (buttonAge), 2, 0, 1, 1);

    GtkWidget *buttonComment = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(buttonComment), "Komentarz");
    gtk_widget_set_hexpand(buttonComment, TRUE);
    gtk_widget_set_margin_start(buttonComment, 5);
    gtk_grid_set_column_homogeneous(GTK_GRID(table), gtk_true());
    gtk_grid_set_column_homogeneous(GTK_GRID(mainContainer), gtk_true());

    gtk_grid_attach(GTK_GRID (mainContainer), GTK_WIDGET (buttonComment), 3, 0, 1, 1);
    for(int i=0; i<sizeof(animals)/sizeof(Animal); ++i){
        GtkWidget* labelName = gtk_label_new(animals[i].name);
        gtk_label_set_xalign(GTK_LABEL (labelName), 0.0);
        gtk_widget_set_margin_start(labelName, 5);
        gtk_widget_set_margin_top(labelName, 5);
        gtk_widget_set_hexpand(labelName, TRUE);
        gtk_grid_attach(GTK_GRID (table), labelName, 0, i+1, 1, 1);

        GtkWidget* labelSpecies = gtk_label_new(animals[i].species);
        gtk_label_set_xalign(GTK_LABEL (labelSpecies), 0.0);
        gtk_widget_set_margin_start(labelSpecies, 5);
        gtk_widget_set_margin_top(labelSpecies, 5);
        gtk_widget_set_hexpand(labelSpecies, TRUE);
        gtk_grid_attach(GTK_GRID (table), labelSpecies, 1, i+1, 1, 1);

        char* ageString = malloc(12);
        sprintf(ageString, "%d", animals[i].age);

        GtkWidget* labelAge = gtk_label_new(ageString);
        gtk_label_set_xalign(GTK_LABEL (labelAge), 0.0);
        gtk_widget_set_margin_start(labelAge, 5);
        gtk_widget_set_margin_top(labelAge, 5);
        gtk_widget_set_hexpand(labelAge, TRUE);
        gtk_grid_attach(GTK_GRID (table), labelAge, 2, i+1, 1, 1);

        GtkWidget* labelComment = gtk_label_new(animals[i].comment);
        gtk_label_set_xalign(GTK_LABEL (labelComment), 0.0);
        gtk_widget_set_margin_start(labelComment, 5);
        gtk_widget_set_margin_top(labelComment, 5);
        gtk_widget_set_hexpand(labelComment, TRUE);
        gtk_grid_attach(GTK_GRID (table), labelComment, 3, i+1, 1, 1);
    }

    gtk_grid_attach(GTK_GRID (mainContainer), GTK_WIDGET (containerTable), 0, 1, 4, 1);

    return window;
}
