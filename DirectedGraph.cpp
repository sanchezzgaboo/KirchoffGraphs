#include <iostream>
#include <vector>
#include "DirectedGraph.h"
using namespace std;

DirectedGraph::DirectedGraph() {
}
std::unordered_map<int, std::unordered_map<int, float>> DirectedGraph::getGraph() {
    return adj;
}
void DirectedGraph::addEdge(int src, int dest, float weight) {
    if (dest != src) {
        adj[src][dest] = weight;
    }
    
}
void DirectedGraph::insertVertex(int vertexId, std::unordered_map<int, Node>& nodes, sf::Vector2f position) {
    adj[vertexId] = std::unordered_map<int, float>{};
    nodes[vertexId] = Node(25.f, std::to_string(vertexId));
    nodes[vertexId].setPosition(position);
}
std::unordered_map<int, float> DirectedGraph::adjacents(int vertex) {
    std::unordered_map<int, float> adj_map = adj[vertex];
    if (!adj_map.empty()) {
        return adj_map;
    }
    else {
        return std::unordered_map<int, float>{};
    }
}
void DirectedGraph::displayAdjList() {
    for (int i = 0; i < adj.size(); i++) {
        std::cout << "Vertex " << i << ":";
        for (const auto& neighbor : adj[i]) {
            std::cout << " -> (" << neighbor.first << ", weight " << neighbor.second << ")";
        }
        std::cout << std::endl;
    }
}

int DirectedGraph::size() {
    return adj.size();
}

// Function to add an edge between two vertices

