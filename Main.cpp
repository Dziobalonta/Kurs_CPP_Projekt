#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Game.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(Win_WIDTH, Win_HEIGHT), "Flappy Student");  
	try
	{
		Game game(window);
		game.GameLoop();
	}
	catch (const char* exception)									//WYJATKI
	{
		std::cout << "Error: " << exception << std::endl;
	}
    return 0;
}