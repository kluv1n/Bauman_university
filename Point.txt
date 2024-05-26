#include <mysql_driver.h>
#include <mysql_connection.h> //подключение MySQL к С++ 
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <limits>
#include <utility>

struct PathResult {
    int sum;
    std::vector<std::string> path;
};

class Point {
private:
    char type; 
    std::string name;
    int location[3];
    std::vector<std::pair<std::string, int>> connections;

    // Статическая карта для хранения объектов по имени
    static std::unordered_map<std::string, Point*> objectsByName;

public:
    // Конструктор
    Point(char t, const std::string& n, int loc[3], const std::vector<std::pair<std::string, int>>& conns)
        : type(t), name(n), connections(conns) {
        std::copy(loc, loc + 3, location);

        // Добавление объекта в карту
        objectsByName[name] = this;
    }

    // Деструктор
    ~Point() {
        // Удаление объекта из карты
        objectsByName.erase(name);
    }

    // Метод для добавления соединений
    void addConnections(const std::vector<std::pair<std::string, int>>& newConnections) {
        connections.insert(connections.end(), newConnections.begin(), newConnections.end());
    }

    // Метод для вывода информации об объекте
    void printInfo() const {
        std::cout << "Type: " << type << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Location: [" << location[0] << ", " << location[1] << ", " << location[2] << "]" << std::endl;
        std::cout << "Connections: ";
        for (const auto& conn : connections) {
            std::cout << "[" << conn.first << ", " << conn.second << "] ";
        }
        std::cout << std::endl;
    }

    // Статический метод для получения объекта по имени
    static Point* getObjectByName(const std::string& name) {
        auto it = objectsByName.find(name);
        return it != objectsByName.end() ? it->second : nullptr;
    }

    // Метод для нахождения минимальной суммы connections от текущего объекта до указанного
    PathResult minSumConnections(const std::string& target, std::unordered_set<std::string>& visited) {
        if (name == target) {
            return {0, {name}};
        }
        if (visited.count(name)) {
            return {std::numeric_limits<int>::max(), {}};
        }

        visited.insert(name);
        PathResult minResult = {std::numeric_limits<int>::max(), {}};

        for (const auto& conn : connections) {
            Point* nextObject = getObjectByName(conn.first);
            if (nextObject != nullptr) {
                PathResult nextResult = nextObject->minSumConnections(target, visited);
                if (nextResult.sum != std::numeric_limits<int>::max()) {
                    int totalSum = conn.second + nextResult.sum;
                    if (totalSum < minResult.sum) {
                        minResult.sum = totalSum;
                        minResult.path = nextResult.path;
                        minResult.path.insert(minResult.path.begin(), name);
                    }
                }
            }
        }

        visited.erase(name);
        return minResult;
    }

    // Обертка для вызова minSumConnections с начальной настройкой visited
    PathResult findMinSumTo(const std::string& target) {
        std::unordered_set<std::string> visited;
        PathResult result = minSumConnections(target, visited);
        if (result.sum == std::numeric_limits<int>::max()) {
            result.sum = -1;
        }
        return result;
    }
};

// Инициализация статической карты
std::unordered_map<std::string, Point*> Point::objectsByName;

// Функции для создания соединений и печати кратчайшего пути
void createConnection(const std::string& name1, const std::string& name2, int distance) {
    Point* obj1 = Point::getObjectByName(name1);
    Point* obj2 = Point::getObjectByName(name2);

    if (obj1 && obj2) {
        obj1->addConnections({{name2, distance}});
        obj2->addConnections({{name1, distance}});
    } else {
        std::cout << "One or both objects not found.\n";
    }
}

void printShortestPath(const std::string& name1, const std::string& name2) {
    Point* obj1 = Point::getObjectByName(name1);

    if (obj1) {
        PathResult result = obj1->findMinSumTo(name2);
        if (result.sum != -1) {
            std::cout << "Minimum sum of connections from " << name1 << " to " << name2 << ": " << result.sum << std::endl;
            std::cout << "Path: ";
            for (const auto& nodeName : result.path) {
                std::cout << nodeName << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "No path found from " << name1 << " to " << name2 << std::endl;
        }
    } else {
        std::cout << "Object not found: " << name1 << std::endl;
    }
}

int main() {
    // Подключение к драйверу MySQL
    sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

    // Установка соединения с базой данных
    std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "root", "skoda1655_"));

    // Выбор схемы (базы данных)
    con->setSchema("university");

    // Создание объекта Statement для выполнения SQL-запросов
    std::unique_ptr<sql::Statement> stmt(con->createStatement());

    // Выполнение запроса для получения данных из таблицы classes
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM classes"));


    // Обработка результатов запроса и создание объектов Point
    while (res->next()) {
        int id = res->getInt("id");
        std::string type_of_class = res->getString("type_of_class");
        int class_number = res->getInt("class_number");
        int floor_number = res->getInt("floor_number");
        int location[3] = {class_number, floor_number, 0}; // Coordinate z is set to 0 for simplicity
        std::string name = type_of_class + std::to_string(class_number);

        Point* obj = new Point(type_of_class[0], name, location, {});
    }


    // Выполнение запроса для получения данных из таблицы distance
    res.reset(stmt->executeQuery("SELECT * FROM distance"));
    while (res->next()) {
        int current_class = res->getInt("current_class");
        int target_class = res->getInt("target_class");
        int distance = res->getInt("distance");

        // Создание соединений между классами
        createConnection("Class" + std::to_string(current_class), "Class" + std::to_string(target_class), distance);
    }

    // Печать кратчайшего пути между классами
    printShortestPath("Class1", "Class7");
    printShortestPath("Class2", "Class5");

    return 0;
}

