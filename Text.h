#pragma once
#include <SFML/Graphics.hpp>

class Text																		//KLASA ABSTRAKCYJNA
{
protected:
	sf::Font font;
	sf::Text text;
	int x, y, size;
	std::string name;

public:
	Text(std::string name = "Placeholder", int xx = 0, int yy = 0, int textsize = 24);

	virtual void setString(const std::string& str) = 0;							//CZYSTO WIRTUALNE METODY
	virtual void setPosition(float x, float y) = 0;
	virtual void drawText(sf::RenderWindow& window) = 0;
	virtual void setSize(int size) = 0;
};

class ScoreText : public Text													//DZIEDZICZENIE
{
public:
	ScoreText(const std::string& name = "Score: 0", int xx =20, int yy = 10, int textsize = 24);
    void setString(const std::string& name) override;
	void setPosition(float x, float y) override;
	void drawText(sf::RenderWindow& window) override;
	void setSize(int size) override;
};

class MainTitle : public Text
{
public:
	MainTitle(std::string name = "FLAPPY STUDENT", int xx = 40, int yy = 200, int textsize = 64);
	MainTitle(const MainTitle& other);											//KONSTRUKTOR KOPIUJACY
	void setString(const std::string& name) override;
	void setPosition(float x, float y) override;
	void drawText(sf::RenderWindow& window) override;
	void setSize(int size) override;
};

class Restart : public Text
{
public:
	Restart(std::string name = "Spróbuj Ponownie!", int xx = 60, int yy = 150, int textsize = 56);
	void setString(const std::string& name) override;
	void setPosition(float x, float y) override;
	void drawText(sf::RenderWindow& window) override;
	void setSize(int size) override;
};
