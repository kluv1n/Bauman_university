#include "point.h"

std::unordered_map<std::string, Point*> Point::objectsByName;

Point::Point(char t, const char* n, int loc[3], const std::vector<std::pair<std::string, int>>& conns) {
    type = t;
    strncpy(name, n, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
    for (int i = 0; i < 3; ++i) {
        location[i] = loc[i];
    }
    connections = conns;
    objectsByName[name] = this;
}

Point::~Point() {
    objectsByName.erase(name);
}

void Point::addConnections(const std::vector<std::pair<std::string, int>>& newConnections) {
    for (const auto& conn : newConnections) {
        connections.push_back(conn);
    }
}

void Point::printInfo() {
    std::cout << "Type: " << type << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Location: [" << location[0] << ", " << location[1] << ", " << location[2] << "]" << std::endl;
    std::cout << "Connections: ";
    for (const auto& conn : connections) {
        std::cout << "[" << conn.first << ", " << conn.second << "] ";
    }
    std::cout << std::endl;
}

Point* Point::getObjectByName(const std::string& name) {
    if (objectsByName.find(name) != objectsByName.end()) {
        return objectsByName[name];
    }
    return nullptr;
}

PathResult Point::minSumConnections(const std::string& target, std::unordered_set<std::string>& visited, const std::string& previousNode) {
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

PathResult Point::findMinSumTo(const std::string& target) {
    std::unordered_set<std::string> visited;
    PathResult result = minSumConnections(target, visited, "");
    if (result.sum == std::numeric_limits<int>::max()) {
        result.sum = -1;
    }
    return result;
}

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
