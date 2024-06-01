cmake_minimum_required(VERSION 3.10)

# Название проекта
project(FloorImageChanger)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем исполняемый файл
add_executable(FloorImageChanger main.cpp)
add_subdirectory(Point)
# Находим пакеты GTK и их компоненты
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

# Включаем директории
include_directories(${GTK_INCLUDE_DIRS})

# Линкуем библиотеки
target_link_libraries(FloorImageChanger ${GTK_LIBRARIES})