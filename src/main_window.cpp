#include "main_window.h"
#include <iostream>

MainWindow::MainWindow() {
    // Создание нового окна
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Пример GTK на C++");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Создание вертикального бокса
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Создание меню
    menuBar = gtk_menu_bar_new();
    fileMenu = gtk_menu_new();
    fileMenuItem = gtk_menu_item_new_with_label("File");
    quitMenuItem = gtk_menu_item_new_with_label("Quit");

    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMenuItem);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMenuItem), fileMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), fileMenuItem);

    g_signal_connect(quitMenuItem, "activate", G_CALLBACK(+[](GtkWidget *, gpointer self) {
        static_cast<MainWindow*>(self)->on_quit();
    }), this);

    gtk_box_pack_start(GTK_BOX(vbox), menuBar, FALSE, FALSE, 0);

    // Создание бокса для кнопок
    buttonBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(vbox), buttonBox, TRUE, TRUE, 0);

    // Создание кнопок
    button1 = gtk_button_new_with_label("Кнопка 1");
    button2 = gtk_button_new_with_label("Кнопка 2");

    g_signal_connect(button1, "clicked", G_CALLBACK(on_button1_clicked), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button2_clicked), NULL);

    gtk_container_add(GTK_CONTAINER(buttonBox), button1);
    gtk_container_add(GTK_CONTAINER(buttonBox), button2);
}

void MainWindow::show() {
    gtk_widget_show_all(window);
}

void MainWindow::on_quit() {
    gtk_main_quit();
}

void MainWindow::on_button1_clicked(GtkWidget *widget, gpointer data) {
    std::cout << "Кнопка 1 нажата!" << std::endl;
}

void MainWindow::on_button2_clicked(GtkWidget *widget, gpointer data) {
    std::cout << "Кнопка 2 нажата!" << std::endl;
}
