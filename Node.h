#pragma once
#ifndef  NODE_H
#define NODE_H
#include <SFML/Graphics.hpp>
#include <string>
class Node {
private:
	sf::CircleShape circle;
	sf::Text label;
	static sf::Font font;
	bool isDragging = false;
	sf::Vector2i offset;
public:
	Node(float radius = 25.f, const std::string& text = "");
	void setPosition(const sf::Vector2f& pos);
	void setLabel(const std::string& text);
	sf::Vector2f getPosition() const;
	sf::CircleShape& getShape();
	std::string getLabel() const;
	sf::Text& getText();
	void startDragging(const sf::Vector2i& mousePos);
	void stopDragging();
	void updateDragging(const sf::Vector2i& mousePos);
	bool contains(const sf::Vector2i& mousePos);
	bool isBeingDragged() const;
	static bool loadFont(const std::string& fontPath);
};

#endif