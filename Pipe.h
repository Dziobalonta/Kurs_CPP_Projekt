#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

class Pipe : public GameObject
{
public:
	Pipe(int);
	sf::Sprite sprite_up, sprite_down;
	static void load_Textures();
	void update(sf::Time);
	float getRightBound();

private:
	static sf::Texture texture_down, texture_up;
	static int pipe_distance, move_speed;
	void draw(sf::RenderWindow& window) override;
};