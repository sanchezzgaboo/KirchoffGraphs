#pragma once
#ifndef  DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H
#include <vector>
#include <unordered_map>
#include "Node.h"
class DirectedGraph {
private:
    std::unordered_map<int,std::unordered_map<int, float>> adj;
public:
    DirectedGraph();
    void insertVertex(int vertexID, std::unordered_map<int, Node>& nodes, sf::Vector2f position);
    std::unordered_map<int, std::unordered_map<int, float>> getGraph();
    void addEdge(int source, int dest, float w);
    void displayAdjList();
    std::unordered_map<int, float> adjacents(int vertex);
    int size();
    //TODO BFS, DFO, PRIM, DJIKSTRA

};
#endif // ! DIRECTEDGRAPH_H
