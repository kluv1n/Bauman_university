#include <gtk/gtk.h>
#include "Point/Point.h"
#include "creationDB.cpp"
#include <string>
#include <map>
#include <iostream>
#include <fstream>

// Глобальные переменные для хранения введенного текста
std::string text1;
std::string text2;

// Структура для хранения указателей на виджеты
struct AppWidgets {
    GtkWidget *floor_image;
    GtkWidget *entry1;
    GtkWidget *entry2;
    //GtkWidget *dialog1;
    GtkWidget *dialog_vbox1;
    GtkWidget *vpaned1;
    GtkWidget *hpaned1;
    GtkWidget *vpaned2;
    GtkWidget *vpaned3;
    GtkWidget *vpaned4;
    GtkWidget *vpaned5;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *menubar1;
    GtkWidget *dialog_action_area1;
    std::map<std::string, std::string> floor_images;
};

// Обработчик для первого GtkEntry
void on_entry1_activate(GtkEntry *entry, gpointer data) {
    AppWidgets *widgets = static_cast<AppWidgets*>(data);
    const gchar *text = gtk_entry_get_text(entry);
    text1 = text;
    g_print("Text1: %s\n", text1.c_str());
}

// Обработчик для второго GtkEntry
void on_entry2_activate(GtkEntry *entry, gpointer data) {
    AppWidgets *widgets = static_cast<AppWidgets*>(data);
    const gchar *text = gtk_entry_get_text(entry);
    text2 = text;
    g_print("Text2: %s\n", text2.c_str());
}

// Обработчик для кнопок
void on_button_clicked(GtkButton *button, gpointer data) {
    AppWidgets *widgets = static_cast<AppWidgets*>(data);
    
    // Получаем ID кнопки
    const gchar *button_id = gtk_buildable_get_name(GTK_BUILDABLE(button));
    
    // Проверяем, что ID кнопки не равен NULL
    if (button_id != NULL) {
        //g_print("Button clicked: %s\n", button_id);
        
        // Ищем изображение для данного ID в std::map
        auto it = widgets->floor_images.find(button_id);
        
        // Если нашли, устанавливаем изображение
        if (it != widgets->floor_images.end()) {
            gtk_image_set_from_file(GTK_IMAGE(widgets->floor_image), it->second.c_str());
        } else {
            g_print("Image not found for button: %s\n", button_id);
        }
    } else {
        g_print("Button ID is NULL\n");
    }
}

// Функция для проверки существования файла
bool file_exists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window;
    AppWidgets widgets;

    gtk_init(&argc, &argv);

    // Устанавливаем путь к файлу Glade
    std::string glade_file = "../interface.glade";

    if (!file_exists(glade_file)) {
        std::cerr << "Error: File " << glade_file << " not found." << std::endl;
        return 1;
    }

    // Загружаем интерфейс из файла Glade
    builder = gtk_builder_new_from_file(glade_file.c_str());

    // Получаем основное окно
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

    // Получаем виджеты GtkImage и GtkEntry
    widgets.floor_image = GTK_WIDGET(gtk_builder_get_object(builder, "floor_image"));
    widgets.entry1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
    widgets.entry2 = GTK_WIDGET(gtk_builder_get_object(builder, "entry2"));

    // Получаем дополнительные виджеты
    //widgets.dialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog1"));
    widgets.dialog_vbox1 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog-vbox1"));
    widgets.vpaned1 = GTK_WIDGET(gtk_builder_get_object(builder, "vpaned1"));
    widgets.hpaned1 = GTK_WIDGET(gtk_builder_get_object(builder, "hpaned1"));
    widgets.vpaned2 = GTK_WIDGET(gtk_builder_get_object(builder, "vpaned2"));
    widgets.vpaned3 = GTK_WIDGET(gtk_builder_get_object(builder, "vpaned3"));
    widgets.vpaned4 = GTK_WIDGET(gtk_builder_get_object(builder, "vpaned4"));
    widgets.vpaned5 = GTK_WIDGET(gtk_builder_get_object(builder, "vpaned5"));
    widgets.label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
    widgets.label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
    widgets.label3 = GTK_WIDGET(gtk_builder_get_object(builder, "label3"));
    widgets.menubar1 = GTK_WIDGET(gtk_builder_get_object(builder, "menubar1"));
    widgets.dialog_action_area1 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog-action_area1"));

    // Проверяем, что все виджеты были успешно получены
    if (!widgets.floor_image || !widgets.entry1 || !widgets.entry2 || 
        !widgets.dialog_vbox1 || !widgets.vpaned1 || !widgets.hpaned1 ||
        !widgets.vpaned2 || !widgets.vpaned3 || !widgets.vpaned4 || !widgets.vpaned5 ||
        !widgets.label1 || !widgets.label2 || !widgets.label3 || !widgets.menubar1 ||
        !widgets.dialog_action_area1) {
        std::cerr << "Error: Not all widgets could be found in the interface file." << std::endl;
        if (!widgets.floor_image) std::cerr << "Missing: floor_image" << std::endl;
        if (!widgets.entry1) std::cerr << "Missing: entry1" << std::endl;
        if (!widgets.entry2) std::cerr << "Missing: entry2" << std::endl;
        //if (!widgets.dialog1) std::cerr << "Missing: dialog1" << std::endl;
        if (!widgets.dialog_vbox1) std::cerr << "Missing: dialog-vbox1" << std::endl;
        if (!widgets.vpaned1) std::cerr << "Missing: vpaned1" << std::endl;
        if (!widgets.hpaned1) std::cerr << "Missing: hpaned1" << std::endl;
        if (!widgets.vpaned2) std::cerr << "Missing: vpaned2" << std::endl;
        if (!widgets.vpaned3) std::cerr << "Missing: vpaned3" << std::endl;
        if (!widgets.vpaned4) std::cerr << "Missing: vpaned4" << std::endl;
        if (!widgets.vpaned5) std::cerr << "Missing: vpaned5" << std::endl;
        if (!widgets.label1) std::cerr << "Missing: label1" << std::endl;
        if (!widgets.label2) std::cerr << "Missing: label2" << std::endl;
        if (!widgets.label3) std::cerr << "Missing: label3" << std::endl;
        if (!widgets.menubar1) std::cerr << "Missing: menubar1" << std::endl;
        if (!widgets.dialog_action_area1) std::cerr << "Missing: dialog-action_area1" << std::endl;
        return 1;
    }

    // Заполняем карту соответствиями между кнопками и изображениями
    widgets.floor_images = {
        {"button1", "../floor/floor1.PNG"},
        {"button2", "../floor/floor2.PNG"},
        {"button3", "../floor/floor3.PNG"},
        {"button4", "../floor/floor4.PNG"},
        {"button5", "../floor/floor5.PNG"},
        {"button6", "../floor/floor6.PNG"},
        {"button7", "../floor/floor7.PNG"},
        {"button8", "../floor/floor8.PNG"},
        {"button9", "../floor/floor9.PNG"},
        {"button10", "../floor/floor10.PNG"},
        {"button11", "../floor/floor11.PNG"}
    };

    // Подключаем обработчики сигналов для кнопок
    for (int i = 1; i <= 11; ++i) {
        std::string button_name = "button" + std::to_string(i);
        GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(builder, button_name.c_str()));
        g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), &widgets);
    }

    // Подключаем обработчики сигналов для GtkEntry
    g_signal_connect(widgets.entry1, "activate", G_CALLBACK(on_entry1_activate), &widgets);
    g_signal_connect(widgets.entry2, "activate", G_CALLBACK(on_entry2_activate), &widgets);

    // Отображаем все виджеты
    gtk_widget_show_all(window);

    gtk_main();


    // printShortestPath(defRoom(text1), defRoom(text2));

    // creationDB();

    return 0;
}