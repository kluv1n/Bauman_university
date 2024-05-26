#include <gtk/gtk.h>
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
    const gchar *button_name = gtk_widget_get_name(GTK_WIDGET(button));

    // Определяем, какая кнопка была нажата и меняем изображение
    auto it = widgets->floor_images.find(button_name);
    if (it != widgets->floor_images.end()) {
        gtk_image_set_from_file(GTK_IMAGE(widgets->floor_image), it->second.c_str());
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

    // Заполняем карту соответствиями между кнопками и изображениями
    widgets.floor_images = {
        {"button1", "floor1.png"},
        {"button2", "floor2.png"},
        {"button3", "floor3.png"},
        {"button4", "floor4.png"},
        {"button5", "floor5.png"},
        {"button6", "floor6.png"},
        {"button7", "floor7.png"},
        {"button8", "floor8.png"},
        {"button9", "floor9.png"},
        {"button10", "floor10.png"},
        {"button11", "floor11.png"}
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

    return 0;
}