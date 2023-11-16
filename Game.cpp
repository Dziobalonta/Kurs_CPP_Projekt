#include "Game.h"
#include "Globals.h"
#include "Bird.h"
#include "Text.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <sys/stat.h>

Game::Game(sf::RenderWindow& window) :						//KONSTRUKTOR
	win(window),
	is_space_pressed(false),
	is_space_released(false),
	run_game(true),
	start_monitoring(false),
	pipe_counter(71),
	pipe_spawn_time(70),
	score(0),
	highscore("Highscore: 0", 180, 10, 24),
	topscore("Topscore: 0", 20, 645, 22),
	instruction(title)												//KONSTRUKTOR KOPIUJACY
{
	win.setFramerateLimit(60);
	if ( !bg_texture.loadFromFile("Assets/uni_bg.png") )
	{
		throw "Blad ladowania tekstury tla!";						//WYJATKI
	}

	// ustawianie pozycji i skalowania tla
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
	bg_sprite.setPosition(0, -250);

	if ( !ground_texture.loadFromFile("Assets/ground.png") )
	{
		throw "Blad ladowania tekstury ziemii!";
	}
	
	// ustawianie pozycji i skalowania ziemii
	ground_sprite1.setTexture(ground_texture);
	ground_sprite2.setTexture(ground_texture);

	ground_sprite1.setScale(SCALE_FACTOR, SCALE_FACTOR);
	ground_sprite2.setScale(SCALE_FACTOR, SCALE_FACTOR);

	ground_sprite1.setPosition(0, 605);
	ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().width, 605);

	if (!fileExists("topscores.txt"))
	{
		std::ofstream newFile("topscores.txt");
		if (newFile.is_open())
		{
			for (int i = 0; i < 5; i++)
			{
				newFile << "0\n";
			}
			newFile.close();
		}
		else
		{
			throw "B³¹d otwierania pliku!";
		}
	}

	std::ifstream file("topscores.txt");
	if (file.is_open())
	{
		int value = 0;
		for (int i = 0; i < 5; i++)
		{
			if (file >> value)
			{
				topscores.push_back(value);
			}
			else
			{
				throw "Blad czytania wartosci z pliku!";
			}
		}
		file.close();
	}
	else
	{
		throw "B³¹d otwierania pliku!";
		
	}
	std::sort(topscores.begin(),topscores.end());									//ALGORYTMY
	std::reverse(topscores.begin(), topscores.end());

	updatetopscores();
	
	Pipe::load_Textures();

	instruction.setString("PRESS SPACE TO START");
	instruction.setPosition(105, 300);
	instruction.setSize(36);

	pnt1.setX(50);
	pnt1.setY(50);

	pnt2.setX(50);
	pnt2.setY(50);

	pnt1 = pnt1 + pnt2;																//PRZECIAZENIE OPERATORA
}

void Game::updatetopscores()
{
	topscore.setString("Topscores:\n"
						"1: " + toString(topscores[0]) + "\n"
						"2: " + toString(topscores[1]) + "\n"
						"3: " + toString(topscores[2]) + "\n"
						"4: " + toString(topscores[3]) + "\n"
						"5: " + toString(topscores[4]) + "\n");
}

void Game::doProcessing(sf::Time& dt)
{
	if (is_space_pressed)
	{
		moveGround(dt);
		if (pipe_counter > pipe_spawn_time)
		{
			pipes.push_back(Pipe(dist(rd)));
			pipe_counter = 0;
		}
		pipe_counter++;

		for (auto it = pipes.begin(); it != pipes.end(); )					//ITERATOR
		{
			it->update(dt);

			if (it->getRightBound() < 0) 
			{
				it = pipes.erase(it);
			}
			else ++it;
		}

		checkCollisions();
		checkScore();
	}
	bird.update(dt);
}

void Game::GameLoop()
{
	sf::Clock clock;

	//loopuje gre
	while (win.isOpen())
	{
		
		sf::Time dt = clock.restart();
		
		sf::Event event;
		//wykrywa zdarzenia np kilkniecia
		while (win.pollEvent(event))
		{
			//zamykanie okna
			if (event.type == sf::Event::Closed)
			{
				win.close();
			}

			//flapniecie skrzydlami
			if (event.type == sf::Event::KeyPressed && run_game)
			{
				if (event.key.code == sf::Keyboard::Space && !is_space_pressed)
				{
					is_space_pressed = true;
					bird.setShouldFly(true);
				}
				if (event.key.code == sf::Keyboard::Space && is_space_pressed && check_fly(bird) == true)
				{
					bird.flapBird(dt);
				}
			}

			if (event.type == sf::Event::KeyReleased && run_game)
			{
				if (event.key.code == sf::Keyboard::Space && !is_space_released)
				{
					is_space_released = true;
				}
				if (event.key.code == sf::Keyboard::Space && is_space_released && check_fly(bird) == true)
				{
					bird.changetexture();
				}
			}

			if (event.type == sf::Event::KeyPressed && !run_game)
			{
				if (event.key.code == sf::Keyboard::Space && !is_space_pressed)
				{
					restartGame();
				}
			}
		}

		doProcessing(dt);

		Draw();
		//wyswietla okno
		win.display();
	}

}

void Game::checkCollisions()
{
	if (pipes.size() > 0)
	{
		if (pipes[0].sprite_down.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds()) ||
			pipes[0].sprite_up.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds()) ||
			bird.bird_sprite.getGlobalBounds().top >= 560)
		{
			is_space_pressed = false;
			run_game = false;
		}
	}
}

void Game::checkScore()
{
	if (pipes.size() > 0)
	{
		if (!start_monitoring)
		{
			if (bird.bird_sprite.getGlobalBounds().left > pipes[0].sprite_down.getGlobalBounds().left &&
				bird.getRightBound() < pipes[0].getRightBound())
			{
				start_monitoring = true;
			}
		}
		else
		{
			if (bird.bird_sprite.getGlobalBounds().left > pipes[0].getRightBound())
			{
				score++;
				scores.setString("Score: " + toString(score));
				if (score > highest)
				{
					highest = score;
					highscore.setString("Highscore: " + toString(highest));
				}

				for (auto it = topscores.begin(); it != topscores.end(); ++it)
				{
					if (score >= *it)
					{
						*it = score;
						updatetopscores();
						break;
					}
				}


				start_monitoring = false;
			}
		}
	}

}

bool check_fly(Bird& bird)									//ZAPRZYJAZNIONA FUNKCJA
{
	return bird.should_fly;
}

void Game::Draw()
{
	win.draw(bg_sprite);

	for (Pipe& pipe : pipes)								//ZAKRESOWA PETLA FOR
	{
		obj_ptr = &pipe;									//POLIMORFIZM
		obj_ptr->draw(win);
	}

	win.draw(ground_sprite1);
	win.draw(ground_sprite2);

	obj_ptr = &bird;
	obj_ptr->draw(win);

	scores.drawText(win);
	highscore.drawText(win);
	topscore.drawText(win);

	if (!run_game)
	{
		reset.drawText(win);
	}

	if (check_fly(bird) == false && run_game)
	{
		title.drawText(win);
		instruction.drawText(win);
	}
}

void Game::moveGround(sf::Time& dt)
{
	ground_sprite1.move(-move_speed * dt.asSeconds(), 0.f);
	ground_sprite2.move(-move_speed * dt.asSeconds(), 0.f);

	//zapetla ruszajace sie podloge
	if (ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width < 0)
	{
		ground_sprite1.setPosition(ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width, 605);
	}

	if (ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width < 0)
	{
		ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width, 605 );
	}

}

void Game::restartGame()
{
	bird.resetBirdPosition(pnt1.getX(),pnt1.getY());
	bird.setShouldFly(false);
	run_game = true;
	pipe_counter = 71;
	pipes.clear();
	score = 0;
	scores.setString("Score: 0");
}

Game::~Game()													//DESTRUKTOR
{
	std::ofstream file("topscores.txt");
	if (file.is_open())
	{
		for (const auto& score : topscores)
		{
			file << score << "\n";
		}
		file.close();
	}
}

std::string Game::toString(int number)
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}

bool Game::fileExists(const std::string& filename)
{
	std::ifstream file(filename);
	return file.good();
}
