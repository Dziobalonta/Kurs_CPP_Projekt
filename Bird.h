#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

class Point
{
public:
	Point(double x = 100, double y = 100);

	double getX() const;
	double getY() const;

	void setX(double x);
	void setY(double y);

	Point operator+(const Point& other) const;

private:
	double x;
	double y;
};

class Bird : public GameObject
{
private:
	sf::Texture textures[2];
	const int gravity;
	const int flap_speed;
	float velocity_y;
	int anim_counter,texture_switch;
protected:
	bool should_fly;
public:
	sf::Sprite bird_sprite;
	Bird();
	void setShouldFly(bool);
	void changetexture();
	void flapBird(sf::Time&);
	void resetBirdPosition(int pos_x,int pos_y);
	void update(sf::Time&);
	float getRightBound();
	void draw(sf::RenderWindow& window) override;

	friend bool check_fly(Bird&);							//DEKLARACJA PRZYJACIELA

	Point start;
};

