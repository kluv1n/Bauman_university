#pragma once

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

    static std::unordered_map<std::string, Point*> objectsByName;

public:
    Point(char t, const char* n, int loc[3], const std::vector<std::pair<std::string, int>>& conns);
    ~Point();
    void addConnections(const std::vector<std::pair<std::string, int>>& newConnections);
    void printInfo();
    static Point* getObjectByName(const std::string& name);
    PathResult minSumConnections(const std::string& target, std::unordered_set<std::string>& visited, const std::string& previousNode);
    PathResult findMinSumTo(const std::string& target);
};

void createConnection(const std::string& name1, const std::string& name2, int distance);
void printShortestPath(const std::string& name1, const std::string& name2);
