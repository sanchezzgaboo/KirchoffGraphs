#include "Node.h"

sf::Font Node::font;

Node::Node(float radius, const std::string& text) {
	circle.setRadius(radius);
	circle.setFillColor(sf::Color::White);
	circle.setOrigin(radius, radius);

	label.setFont(font);
	label.setString(text);
	label.setCharacterSize(14);
	label.setFillColor(sf::Color::Black);
	label.setStyle(sf::Text::Bold);
}

void Node::setPosition(const sf::Vector2f& pos){
	circle.setPosition(pos);
	// Center the text inside the circle
	sf::FloatRect textBounds = label.getLocalBounds();
	label.setOrigin(textBounds.left + textBounds.width / 2.0f,
		textBounds.top + textBounds.height / 2.0f);
	label.setPosition(pos);
}
void Node::setLabel(const std::string& text) {
	label.setString(text);
	// Recalculate origin after changing text
	sf::FloatRect textBounds = label.getLocalBounds();
	label.setOrigin(textBounds.left + textBounds.width / 2.0f,
		textBounds.top + textBounds.height / 2.0f);
}
sf::Vector2f Node::getPosition() const {
	return circle.getPosition();
}
sf::CircleShape& Node::getShape() {
	return circle;
}
std::string Node::getLabel() const {
	return label.getString();
}
sf::Text& Node::getText() {
	return label;
}
void Node::startDragging(const sf::Vector2i& mousePos) {
	offset = mousePos - sf::Vector2i(circle.getPosition());
	isDragging = true;
}
void Node::stopDragging() {
	isDragging = false;
}
void Node::updateDragging(const sf::Vector2i& mousePos) {
	if (isDragging) {
		setPosition(sf::Vector2f(mousePos - offset));
	}
}
bool Node::contains(const sf::Vector2i& mousePos) {
	return circle.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
bool Node::isBeingDragged() const {
	return isDragging;
}
bool Node::loadFont(const std::string& fontPath) {
	return font.loadFromFile(fontPath);
}