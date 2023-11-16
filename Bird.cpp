#include "Bird.h"
#include "Globals.h"

Bird::Bird() :
	gravity(10),
	flap_speed(250),
	velocity_y(0),
	anim_counter(0),
	texture_switch(1),
	should_fly(false)

{
	if (!textures[0].loadFromFile("Assets/student_down.png"))
	{
		throw "Blad ladowania tekstury ptaka!";
	}
	
	if (!textures[1].loadFromFile("Assets/student_up.png"))
	{
		throw "Blad ladowania tekstury ptaka!";
	}

	bird_sprite.setTexture(textures[0]);
	bird_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
	resetBirdPosition(start.getX(), start.getY());
}

void Bird::update(sf::Time& dt)
{
	if (bird_sprite.getGlobalBounds().top < 560 && should_fly)
	{
		velocity_y += gravity * dt.asSeconds();
		bird_sprite.move(0, velocity_y);

		if (bird_sprite.getGlobalBounds().top < 0)
			bird_sprite.setPosition(100, 0);
	}
	else
	{
		should_fly = false;  // Ustawienie should_fly na false, gdy ptak upadnie i nie lata
	}
}

void Bird::changetexture()
{
	bird_sprite.setTexture(textures[texture_switch]);
	if (texture_switch) texture_switch = 0;
	else texture_switch = 1;
}

void Bird::flapBird(sf::Time& dt)
{
	Bird::changetexture();
	velocity_y = -flap_speed * dt.asSeconds();


}

float Bird::getRightBound()
{
	return bird_sprite.getGlobalBounds().left + bird_sprite.getGlobalBounds().width;
}

void Bird::resetBirdPosition(int pos_x, int pos_y)
{
	bird_sprite.setPosition(pos_x, pos_y);
	velocity_y = 0;
}

void Bird::setShouldFly(bool should_fly)
{
	this->should_fly = should_fly;
}

void Bird::draw(sf::RenderWindow& window)
{
	window.draw(bird_sprite);
}

///// Point /////

Point::Point(double x, double y)
	: x(x), y(y)
{
}

double Point::getX() const
{
	return x;
}

double Point::getY() const
{
	return y;
}

void Point::setX(double x)
{
	this->x = x;
}

void Point::setY(double y)
{
	this->y = y;
}

Point Point::operator+(const Point& other) const					//PRZECIAZENIE OPERATORA
{
	Point result(x + other.x, y + other.y);
	return result;
}