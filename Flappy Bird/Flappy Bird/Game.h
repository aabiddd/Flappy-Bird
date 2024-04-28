#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Bird.h"
#include "Pipe.h"

class Game
{
public:
	Game(sf::RenderWindow&);
	void GameLoop();

private:
	sf::RenderWindow& window;
	sf::Font font;
	sf::Text start_text, restart_text, score_text;
	sf::Texture bg_texture, ground_texture;
	sf::Sprite bg_sprite, ground_sprite[2];  // two sprites declared to showcase the infinite movement of ground
	Bird bird;
	const int ground_speed;
	bool game_started, running, monitor;
	// game_started to check if bird has started flying
	// running will be used to find if the player is out or not
	// monitor for point calculcation

	// default_spawn_time -> time between two pipes being generated
	// pipe_spawn_time -> time passed since last pipe spawned
	int game_score, pipe_spawn_time, default_spawn_time;
	std::vector<Pipe> pipes;

	// generating random number for position of pipes
	std::random_device rd;
	std::uniform_int_distribution<int> dist{ 300, 630 };

	// generate random number for day/night
	std::random_device rd1;
	std::uniform_int_distribution<int> dist1{ 0, 1 };

	// these member functions need not to be accessed outside the class
	void draw();
	void processing(sf::Time&);
	void checkScore();
	void MoveGround(sf::Time&);
	void checkCollision();
	void restartGame();
};

