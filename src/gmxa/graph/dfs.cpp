#include <iostream>
#include <vector>
#include <stack>
#include <tuple>
#include <cmath>
#include "gmxa/graph/dfs.hpp"


std::vector<std::tuple<int, int, int>> depthFirstSearch(std::ostream& obj, const std::vector<std::vector<std::vector<bool>>>& array, \
                                                        std::vector<std::vector<std::vector<bool>>>& visited, int startX, int startY, int startZ){
    obj << "====================================================" << std::endl;
    obj << "# [gmxa, dfs.cpp] Start grid = " <<  "[" << startX << "]" << "[" << startY << "]" << "[" << startZ << "]" << std::endl;                   
    if(visited[startX][startY][startZ]){
        obj << "# [gmxa, dfs.cpp] Already explored" << std::endl;
        return std::vector<std::tuple<int, int, int>> ();   
    }
    else if(!array[startX][startY][startZ]){
        visited[startX][startY][startZ] = true;
        obj << "# [gmxa, dfs.cpp] Unable to start exploration on this grid" << std::endl;
        return std::vector<std::tuple<int, int, int>> ();  
    }

    std::vector<std::tuple<int, int, int>> gridPathIndex;
    std::stack<std::tuple<int, int, int>> stack;
    stack.push(std::make_tuple(startX, startY, startZ));
    visited[startX][startY][startZ] = true;

    while(!stack.empty()) {
        auto [x, y, z] = stack.top();
        stack.pop();

        gridPathIndex.push_back(std::make_tuple(x, y, z));
        obj << "# [gmxa, dfs.cpp] Visited: (" << x << ", " << y << ", " << z << ")" << std::endl;
        std::vector<std::tuple<int, int, int>> nextSearchIndex = _calculateSearchIndex(x, y, z, array.size(), array[x].size(), array[x][y].size());

        for(int i = 0; i < nextSearchIndex.size(); i++){
            auto [nextX, nextY, nextZ] = nextSearchIndex[i];
            if(!visited[nextX][nextY][nextZ] && array[nextX][nextY][nextZ]){
                stack.push(std::make_tuple(nextX, nextY, nextZ));
                visited[nextX][nextY][nextZ] = true;
            }
            else continue;
        }

    }

    return gridPathIndex;
}
std::vector<std::tuple<int, int, int>> _calculateSearchIndex(int x, int y, int z, int xMax, int yMax, int zMax){

    std::vector<std::tuple<int, int, int>> nextSearchIndex;
    for(int i = x - 1; i <= x + 1; i +=2){
        nextSearchIndex.push_back(std::make_tuple(_applyPeriodicBoundary(i, xMax),  _applyPeriodicBoundary(y, yMax), _applyPeriodicBoundary(z, zMax)));
    }
    for(int i = y - 1; i <= y + 1; i +=2){
        nextSearchIndex.push_back(std::make_tuple(_applyPeriodicBoundary(x, xMax),  _applyPeriodicBoundary(i, yMax), _applyPeriodicBoundary(z, zMax)));
    }
    for(int i = z - 1; i <= z + 1; i +=2){
        nextSearchIndex.push_back(std::make_tuple(_applyPeriodicBoundary(x, xMax),  _applyPeriodicBoundary(y, yMax), _applyPeriodicBoundary(i, zMax)));
    }
    return nextSearchIndex;
}
int _applyPeriodicBoundary(int targetIndex, int maxIndex){
    return (targetIndex + maxIndex)  % maxIndex;
}