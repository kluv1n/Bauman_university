cmake_minimum_required(VERSION 3.10)

# Название проекта
project(MyGtkApp)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Поиск библиотек GTK
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

# Установка флагов компилятора и линкера
include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})
add_definitions(${GTK_CFLAGS_OTHER})

# Добавление исходных файлов
add_executable(BaumanUniversity2 src/main.cpp src/main_window.cpp)

# Линковка с библиотеками GTK
target_link_libraries(BaumanUniversity2 ${GTK_LIBRARIES})
