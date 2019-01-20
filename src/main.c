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

    http_get("https://mrokita.pl/");
    int status;
    app = gtk_application_new ("pl.mrokita.pri3", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}