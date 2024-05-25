#include "main_window.h"

int main(int argc, char *argv[]) {
    // Инициализация GTK
    gtk_init(&argc, &argv);

    // Создание основного окна
    MainWindow mainWindow;
    mainWindow.show();

    // Запуск основного цикла обработки событий GTK
    gtk_main();

    return 0;
}
