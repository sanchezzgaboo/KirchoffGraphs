#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Arrow {
private:
    sf::VertexArray line;   // main line (2 points)
    sf::ConvexShape arrowHead;  // triangle for the tip
    sf::Text weightLabel;   // edge weight label

    static sf::Font font;   // shared among all Arrows

public:
    Arrow();

    void setPoints(const sf::Vector2f& start, const sf::Vector2f& end);
    void setWeight(int weight);
    void setColor(const sf::Color& color);

    void draw(sf::RenderWindow& window) const;

    static bool loadFont(const std::string& fontPath);  // call once
};