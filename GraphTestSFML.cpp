// GraphTestSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include "DirectedGraph.h"
#include <random>
#include "Node.h"
#include "Arrow.h"


sf::Vector2f random_coord() {
    // Define the range
    int lower = 25; // Replace with your desired lower bound
    int upper = 775; // Replace with your desired upper bound

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(lower, upper);

    // Generate two random values in the range [lower, upper]
    int randomX = dis(gen);
    int randomY = dis(gen);

    return sf::Vector2f(randomX, randomY);
}
int load_fonts() {
    if (!Node::loadFont("./Fonts/arial-font/arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }
    if (!Arrow::loadFont("./Fonts/arial-font/arial.ttf")) {
        std::cerr << "Failed to load arrow font!" << std::endl;
        return -1;
    }
}
int main()
{

    // Create a graph with 3 vertices and 3 edges
    int V = 4;
    DirectedGraph grafo;
    std::unordered_map<int, Node> nodes;
    for (int i = 0; i < V; i++) {
        grafo.insertVertex(i, nodes, random_coord());
        std::cout << grafo.size() << std::endl;
    }
    


    // Now add edges one by one
    grafo.addEdge(1, 0, 1);
    grafo.addEdge(0, 1, 5);

    grafo.addEdge(1, 1, 1);
    grafo.addEdge(1, 2, 1);
    grafo.addEdge(2, 3, 1);
    grafo.addEdge(3, 1, 1);

    load_fonts();

 

    std::cout << "Adjacency List Representation:" << std::endl;
    grafo.displayAdjList();
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 800), "test", sf::Style::Default, settings);
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;
    sf::Vector2i offset;
    
    bool displayGraph = true;
    bool openContextMenu = false;

    int draggedNodeIndex = -1;  // -1 means no node selected

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            ImGui::SFML::ProcessEvent(e);
            if (e.type == sf::Event::Closed) { //IF Detected Close Window
                window.close();
            }
            if (displayGraph){
                if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) { //IF LEFT BUTTON PRESSED
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (size_t i = 0; i < nodes.size(); ++i) { //FOR EACH NODE
                        if (nodes[i].contains(mousePos)) { //IF MOUSE INSIDE FIGURE
                            draggedNodeIndex = i; //SET THE INDEX OF THE DRAGGED NODE TO THE CURRENT INDEX
                            nodes[i].startDragging(mousePos);
                            break;
                        }

                    }
                }
                else if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left) {
                    if (draggedNodeIndex != -1) {
                        nodes[draggedNodeIndex].stopDragging();
                        draggedNodeIndex = -1;  // release dragging

                    }
                }
            }
            //TODO ADD VERTICES Y MAS EVENT HANDLERS
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Right) { //IF LEFT BUTTON PRESSED
                openContextMenu = true;
            }
            
        }
        if (draggedNodeIndex != -1) { //IF A NODE IS BEING DRAGGED
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);//GET MOUSE POS
            nodes[draggedNodeIndex].updateDragging(mousePos);//SET POS OF CIRCLE TO THE MOUSE - OFFSET
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        // --- Global top toolbar ---
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    window.close();
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Graph")) {
                if (ImGui::MenuItem("Add Node")) {  }
                if (ImGui::MenuItem("Add Edge")) { /* ... */ }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View")) {
                if (ImGui::MenuItem("Zoom In")) { /* ... */ }
                if (ImGui::MenuItem("Zoom Out")) { /* ... */ }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // --- VIEW panel ---
        ImGui::Begin("Config");
        ImGui::Text("Mostrar");
        ImGui::Checkbox("Graph", &displayGraph);
        ImGui::End();

        // --- Context Menu DropDown ---
        if (openContextMenu) {
            ImGui::OpenPopup("RightClickMenu");
            ImGui::SetNextWindowPos(ImVec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
            openContextMenu = false;  // reset
        }

        if (ImGui::BeginPopup("RightClickMenu")) {
            if (ImGui::MenuItem("Add Vertex")) { system("cls"); grafo.insertVertex(grafo.size(), nodes, sf::Vector2f(400.f, 400.f)); grafo.displayAdjList(); }
            if (ImGui::MenuItem("Add Edge")) { /* ... */ }
            ImGui::EndPopup();
        }

        

        window.clear(sf::Color::Black);
        std::vector<Arrow> arrows;
        if (displayGraph) {
            for (auto& [id, node] : nodes) {
                for (const auto& neighbor : grafo.adjacents(id)) {
                    Arrow arrow;
                    arrow.setPoints(nodes[id].getPosition(), nodes[neighbor.first].getPosition());
                    arrow.setWeight(neighbor.second);  // assuming you store the weight here
                    arrow.setColor(sf::Color::White);
                    arrows.push_back(arrow);
                }
                window.draw(nodes[id].getShape());
                window.draw(nodes[id].getText());
            }
            for (const auto& arrow : arrows) {
                arrow.draw(window);
            }
        }
        
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}
