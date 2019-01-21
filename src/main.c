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
#include <curl/curl.h>
#include "../include/main_window.h"
#include "../include/services/http.h"


/**
 * @brief Initialize UI
 */
static void activate (GtkApplication* app, gpointer user_data)
{
    gtk_widget_show_all (main_window_new(app));
}


int main(int argc, char **argv){
    GtkApplication *app;

    int status;

    app = gtk_application_new ("pl.mrokita.pri-proj-3", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}