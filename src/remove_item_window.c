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

#include <gtk/gtk.h>
#include "../include/data/animal.h"


void
callback_delete_item(GtkWidget* widget,
            gpointer data){
    printf("%d\n", atoi(
            gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)))));
    printf("Delete %s\n", gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget))));
}


GtkWidget*
remove_item_window_new(GtkApplication *app, AnimalLinkedList animals){
    GtkWidget* window;
    GtkWidget* mainContainer;
    mainContainer = gtk_grid_new();
    window = gtk_application_window_new(app);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_modal(GTK_WINDOW(window), gtk_true());
    //gtk_window_set_position(window, gtk_window_posi)
    gtk_container_add(GTK_CONTAINER(window), mainContainer);
    GtkEntry* entryId = gtk_entry_new();
    g_signal_connect(entryId, "activate", G_CALLBACK(callback_delete_item), NULL);
    gtk_entry_set_placeholder_text(entryId, "Id elementu");
    gtk_grid_attach(GTK_GRID(mainContainer), entryId, 0, 0, 1, 1);
    gtk_widget_set_hexpand(entryId, 1);
    gtk_widget_set_vexpand(entryId, 1);
    gtk_window_set_title (GTK_WINDOW (window), "Usuwanie elementu");

    return window;
}

