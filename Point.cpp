#include <iostream>
#include <unordered_map>
#include <cstring>
#include <limits>
#include <unordered_set>
#include <vector>
#include <utility>
struct PathResult {
    int sum;
    std::vector<std::string> path;
};
class Point {
private:
    char type;
    char name[50];
    int location[3];
    std::vector<std::pair<std::string, int>> connections;


    // Статическая карта для хранения объектов по имени
    static std::unordered_map<std::string, Point*> objectsByName;

public:
    // Конструктор
    Point(char t, const char* n, int loc[3], const std::vector<std::pair<std::string, int>>& conns) {
    type = t;
    strncpy(name, n, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
    for (int i = 0; i < 3; ++i) {
        location[i] = loc[i];
    }
    connections = conns;

    // Добавление объекта в карту
    objectsByName[name] = this;

    //std::cout << "Object created: " << name << std::endl;
    }
    void addConnections(const std::vector<std::pair<std::string, int>>& newConnections) {
    for (const auto& conn : newConnections) {
        connections.push_back(conn);
    }
    }


    // Деструктор
    ~Point() {
        // Удаление объекта из карты
        objectsByName.erase(name);
        //std::cout << "Object destroyed: " << name << std::endl;
    }

    // Метод для вывода информации об объекте
    void printInfo() {
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
        if (objectsByName.find(name) != objectsByName.end()) {
            return objectsByName[name];
        }
        return nullptr;
    }
    
    // Метод для нахождения минимальной суммы connections от текущего объекта до указанного
    PathResult minSumConnections(const std::string& target, std::unordered_set<std::string>& visited, const std::string& previousNode) {
    //std::cout <<name<<std::endl;
    if (name == target) {
        return {0, {name}};
    }
    if (visited.find(name) != visited.end()) {
        return {std::numeric_limits<int>::max(), {}};
    }

    visited.insert(name);
    PathResult minResult = {std::numeric_limits<int>::max(), {}};

    for (const auto& conn : connections) {
        if (conn.first == previousNode) {
            continue;
        }
        Point* nextObject = getObjectByName(conn.first);
        if (nextObject != nullptr) {
            PathResult nextResult = nextObject->minSumConnections(target, visited, name);
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

// Обертка для вызова minSumConnections с начальной настройкой visited и без предыдущего узла
PathResult findMinSumTo(const std::string& target) {
    std::unordered_set<std::string> visited;
    PathResult result = minSumConnections(target, visited, "");
    if (result.sum == std::numeric_limits<int>::max()) {
        result.sum = -1;
    }
    return result;
}

};


// Инициализация статической карты
std::unordered_map<std::string, Point*> Point::objectsByName;


void createConnection(const std::string& name1, const std::string& name2, int distance) {
    Point* obj1 = Point::getObjectByName(name1);
    Point* obj2 = Point::getObjectByName(name2);

    if (obj1 != nullptr && obj2 != nullptr) {
        obj1->addConnections({{name2, distance}});
        obj2->addConnections({{name1, distance}});
    } else {
        std::cout << "One or both objects not found.\n";
    }
}
void printShortestPath(const std::string& name1, const std::string& name2) {
    Point* obj1 = Point::getObjectByName(name1);

    if (obj1 != nullptr) {
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
    int loc1[3] = {1, 2, 3};
    Point obj1('A', "Object1", loc1, {});

    int loc2[3] = {4, 5, 6};
    Point obj2('B', "Object2", loc2, {});

    int loc3[3] = {7, 8, 9};
    Point obj3('C', "Object3", loc3, {});

    int loc4[3] = {10, 11, 12};
    Point obj4('D', "Object4", loc4, {});

    int loc5[3] = {13, 14, 15};
    Point obj5('E', "Object5", loc5, {});

    int loc6[3] = {16, 17, 18};
    Point obj6('F', "Object6", loc6, {});

    int loc7[3] = {19, 20, 21};
    Point obj7('G', "Object7", loc7, {});
    createConnection("Object1", "Object2", 5);
    createConnection("Object1", "Object3", 10);
    createConnection("Object2", "Object4", 15);
    createConnection("Object3", "Object5", 20);
    createConnection("Object4", "Object6", 25);
    createConnection("Object5", "Object7", 30);
    createConnection("Object6", "Object7", 35);
    createConnection("Object4", "Object5", 5);

    
    printShortestPath("Object1", "Object7");
    printShortestPath("Object2", "Object5");
    return 0;
}