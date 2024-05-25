#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtk/gtk.h>

class MainWindow {
public:
    MainWindow();
    void show();

private:
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *menuBar;
    GtkWidget *fileMenu;
    GtkWidget *fileMenuItem;
    GtkWidget *quitMenuItem;
    GtkWidget *buttonBox;
    GtkWidget *button1;
    GtkWidget *button2;

    void on_quit();
    static void on_button1_clicked(GtkWidget *widget, gpointer data);
    static void on_button2_clicked(GtkWidget *widget, gpointer data);
};

#endif // MAIN_WINDOW_H
