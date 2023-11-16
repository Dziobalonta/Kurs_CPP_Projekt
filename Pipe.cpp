#include "Pipe.h"
#include "Globals.h"

Pipe::Pipe(int y_pos)
{
	sprite_down.setTexture(texture_down);
	sprite_up.setTexture(texture_up);

	sprite_down.setScale(SCALE_FACTOR, SCALE_FACTOR);
	sprite_up.setScale(SCALE_FACTOR, SCALE_FACTOR);

	sprite_up.setPosition(Win_WIDTH, y_pos);
	sprite_down.setPosition(Win_WIDTH, y_pos - pipe_distance - sprite_up.getGlobalBounds().height);
}

void Pipe::update(sf::Time dt)
{
	sprite_up.move(-move_speed * dt.asSeconds(), 0.f);
	sprite_down.move(-move_speed * dt.asSeconds(), 0.f);
}

void Pipe::load_Textures()
{
	
	if (!texture_down.loadFromFile("Assets/books_down.png"))
	{
		throw "Blad ladowania tekstury rury!";
	}

	if (!texture_up.loadFromFile("Assets/books_up.png"))
	{
		throw "Blad ladowania tekstury rury!";
	}
}

float Pipe::getRightBound()
{
	return sprite_down.getGlobalBounds().left + sprite_down.getGlobalBounds().width;
}

void Pipe::draw(sf::RenderWindow& window)
{
	window.draw(sprite_down);
	window.draw(sprite_up);
}

sf::Texture Pipe::texture_down, Pipe::texture_up;
int Pipe::pipe_distance = 160, Pipe::move_speed = 300;

