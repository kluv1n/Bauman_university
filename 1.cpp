#include <gtkmm.h>

class MyDrawingArea : public Gtk::DrawingArea {
public:
    MyDrawingArea() {}

protected:
    // Обработчик события рисования
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override {
        // Устанавливаем красный цвет
        cr->set_source_rgb(1.0, 0.0, 0.0);

        // Рисуем линию от (0,0) до (5,5)
        cr->move_to(0, 0);
        cr->line_to(5, 5);

        // Выполняем рисование
        cr->stroke();

        return true;
    }
};

class MyWindow : public Gtk::Window {
public:
    MyWindow() {
        set_title("Red Line Drawing");
        set_default_size(200, 200);

        // Добавляем область рисования в окно
        add(drawing_area);

        // Показываем все виджеты в окне
        show_all_children();
    }

private:
    MyDrawingArea drawing_area;
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    MyWindow window;

    // Запуск приложения
    return app->run(window);
}
