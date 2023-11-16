#pragma once
#include <SFML/Graphics.hpp>
#include "Bird.h"
#include <vector>
#include "Pipe.h"
#include "Text.h"
#include <random>

class Game
{
public:
	Game(sf::RenderWindow&);													//KONSTRUKTOR
	~Game();																	//DESTRUKTOR
	sf::RenderWindow& win;
	void GameLoop();

private:
	sf::Texture bg_texture, ground_texture;
	sf::Sprite bg_sprite, ground_sprite1, ground_sprite2;//obiekt z tekstura
	Bird bird;
	GameObject* obj_ptr;														//POLIMORFIZM
	bool is_space_pressed, is_space_released, run_game,start_monitoring;
	const int move_speed = 250;
	void Draw();
	void moveGround(sf::Time&);
	friend bool check_fly(Bird&);
	void doProcessing(sf::Time& dt);
	void checkCollisions();
	void restartGame();
	void checkScore();
	void updatetopscores();
	bool fileExists(const std::string& filename);
	std::string toString(int);
	int pipe_counter, pipe_spawn_time, score, highest = 0;
	std::vector<Pipe> pipes;													//SZABLONY ( VECTOR )
	std::vector<int> topscores;
	std::random_device rd;                                  //generowanie liczb losowych
	std::uniform_int_distribution<int> dist{ 250,550 };	    //zakres od 250 do 550

	ScoreText scores, highscore, topscore;
	MainTitle title,instruction;
	Restart reset;
	Point pnt1, pnt2;
};


