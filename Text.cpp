#include "Text.h"
#include <iostream>

Text::Text(std::string str, int xx, int yy, int textsize)
    : name(str), x(xx), y(yy), size(textsize)
{

    if (!font.loadFromFile("Assets/VCRosdNEUE.ttf"))
    {
        std::cout << "Nie mo¿na za³adowaæ czcionki!\n";
    }
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::Yellow);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(5);
    text.setPosition(x, y);
    text.setString(name);
}


/////////// SCORE TEXT ///////////

ScoreText::ScoreText(const std::string& name, int xx, int yy, int textsize)
    : Text(name, xx, yy, textsize)
{
    text.setOutlineThickness(3);
}

void ScoreText::setString(const std::string& name)
{
    text.setString(name);
}

void ScoreText::setPosition(float x, float y)
{
    text.setPosition(x, y);
}

void ScoreText::drawText(sf::RenderWindow& window)
{
    window.draw(text);
}

void ScoreText::setSize(int size)
{
    text.setCharacterSize(size);
}


/////////// MAIN TEXT ///////////

MainTitle::MainTitle(std::string str, int xx, int yy, int textsize)
        : Text(str, xx, yy, textsize)
{
    text.setLetterSpacing(1.5);
}

MainTitle::MainTitle(const MainTitle& other)        //KONSTRUKTOR KOPIUJACY
{
    name = other.name;
    x = other.x;
    y = other.y;
    size = other.size;

}

void MainTitle::setString(const std::string& name)
{
    text.setString(name);
}

void MainTitle::setPosition(float x, float y)
{
    text.setPosition(x, y);
}

void MainTitle::drawText(sf::RenderWindow& window)
{
    window.draw(text);
}

void MainTitle::setSize(int size)
{
    text.setCharacterSize(size);
}

/////////// RESTART TEXT ///////////

Restart::Restart(std::string str, int xx, int yy, int textsize)
    : Text(str, xx, yy, textsize)
{
    text.setFillColor(sf::Color::Red);
}

void Restart::setString(const std::string& name)
{
}

void Restart::setPosition(float x, float y)
{
    text.setPosition(x, y);
}

void Restart::drawText(sf::RenderWindow& window)
{
    window.draw(text);
}

void Restart::setSize(int size)
{
    text.setCharacterSize(size);
}