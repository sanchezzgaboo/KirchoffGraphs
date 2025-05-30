#include "Arrow.h"
#include <cmath>

sf::Font Arrow::font;
//CHATGPT MIRACLE

//TODO MIRAR COMO HACER CURVAS BEZIER PARA GRAFOS MULTIPESOS
Arrow::Arrow() {
    line.setPrimitiveType(sf::Lines);
    line.resize(2);

    arrowHead.setPointCount(3);
    arrowHead.setFillColor(sf::Color::White);

    weightLabel.setFont(font);
    weightLabel.setCharacterSize(14);
    weightLabel.setFillColor(sf::Color::Yellow);
    weightLabel.setStyle(sf::Text::Bold);
}

void Arrow::setPoints(const sf::Vector2f& start, const sf::Vector2f& end) {
    sf::Vector2f dir = end - start;
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length == 0) return;

    sf::Vector2f unitDir = dir / length;
    sf::Vector2f normal(-unitDir.y, unitDir.x);

    float radiusMargin = 25.f;
    float arrowSize = 10.f;

    sf::Vector2f newStart = start + unitDir * radiusMargin;
    sf::Vector2f newEnd = end - unitDir * radiusMargin;

    // Update line positions
    line[0].position = newStart;
    line[1].position = newEnd;

    // Arrowhead points
    arrowHead.setPoint(0, newEnd);
    arrowHead.setPoint(1, newEnd - unitDir * arrowSize + normal * arrowSize / 2.f);
    arrowHead.setPoint(2, newEnd - unitDir * arrowSize - normal * arrowSize / 2.f);

    // Position weight label halfway
    sf::Vector2f mid = (newStart + newEnd) / 2.f;
    weightLabel.setPosition(mid);
}

void Arrow::setWeight(int weight) {
    weightLabel.setString(std::to_string(weight));

    // Center the text on its position
    sf::FloatRect bounds = weightLabel.getLocalBounds();
    weightLabel.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
}

void Arrow::setColor(const sf::Color& color) {
    line[0].color = color;
    line[1].color = color;
    arrowHead.setFillColor(color);
}

void Arrow::draw(sf::RenderWindow& window) const {
    window.draw(line);
    window.draw(arrowHead);
    window.draw(weightLabel);
}

bool Arrow::loadFont(const std::string& fontPath) {
    return font.loadFromFile(fontPath);
}
