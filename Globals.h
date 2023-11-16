#pragma once
constexpr int Win_WIDTH = 600, Win_HEIGHT = 800;
constexpr float SCALE_FACTOR = 1.5f;

class GameObject {				//POLIMORFIZM
public:
	virtual void draw(sf::RenderWindow& window) = 0;
};