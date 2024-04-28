#include "Game.h"
#include "Globals.h"
#include <vector>
#include <string>

Game::Game(sf::RenderWindow& win) :
	window(win),
	ground_speed(180),  // speed of ground moving
	game_started(false),
	running(true),  // will become false once player dies
	monitor(false),
	game_score(0),
	pipe_spawn_time(65),
	default_spawn_time(120)
{
	// sf::RenderWindow object is a non-copyable object. so, use initialization list

	window.setFramerateLimit(60);

	// background
	bg_texture.loadFromFile("./assets/bg.png");
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y); //4.2, 4.5
	if (dist1(rd1) == 0) {
		bg_sprite.setPosition(0.f, -200.f);  // set x to 0 for day mode
	}
	else {
		bg_sprite.setPosition(-615.f, -200.f);  // set x to -615 for night mode
	}

	// ground: 168 * 56
	ground_texture.loadFromFile("./assets/ground.png");
	ground_sprite[0].setTexture(ground_texture);
	ground_sprite[1].setTexture(ground_texture);

	ground_sprite[0].setScale(SCALE_FACTOR_X, SCALE_FACTOR_X); // 705.6, 235.2
	ground_sprite[1].setScale(SCALE_FACTOR_X, SCALE_FACTOR_X);

	ground_sprite[0].setPosition(0.f, 750.f); // 750.f
	ground_sprite[1].setPosition(ground_sprite[0].getGlobalBounds().width, 750.f); // just at the end of first ground 

	font.loadFromFile("./assets/font.ttf");
	// start text
	start_text.setFont(font);
	start_text.setCharacterSize(30);
	start_text.setFillColor(sf::Color::Black);
	start_text.setLetterSpacing(2);
	start_text.setPosition(20, 815);
	start_text.setString("Press \"Space\" to Start");

	// restart text
	restart_text.setFont(font);
	restart_text.setCharacterSize(30);
	restart_text.setFillColor(sf::Color::Black);
	restart_text.setLetterSpacing(2);
	restart_text.setPosition(20, 815);
	restart_text.setString("Press \"Space\" to Restart");

	// score text
	score_text.setFont(font);
	score_text.setCharacterSize(80);
	score_text.setFillColor(sf::Color::Black);
	score_text.setLetterSpacing(2);
	score_text.setPosition(280, 60);
	score_text.setString("0");

	// load pipe textures (which are static)
	Pipe::loadTextuers();
}

void Game::GameLoop()
{
	sf::Clock clock;
	// game loop
	while (window.isOpen()) {
		sf::Time dt = clock.restart();  // will get the time spent in between consecutive restarts
		// handle events
		sf::Event event;
		
		// event loop
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case (sf::Event::KeyPressed):
				if (running) {
					if (event.key.code == sf::Keyboard::Space && !game_started) {
						game_started = true;
						bird.SetFlying(true);
					}

					if (event.key.code == sf::Keyboard::Space && game_started) {
						bird.Flap(dt);
						bird.rotateOnSpace();
					}
				}
				else {  // when game is not running, basically you're out
					if (event.key.code == sf::Keyboard::Space) {
						restartGame();
					}
				}
			}

		}

		processing(dt);

		window.clear();
		draw();
		window.display();
	}
}

void Game::draw() {
	window.draw(bg_sprite);
	for (std::vector<Pipe>::iterator it = pipes.begin(); it != pipes.end(); ++it) {
		window.draw(it->pipeUp_sprite);
		window.draw(it->pipeDown_sprite);
	}
	window.draw(ground_sprite[0]);
	window.draw(ground_sprite[1]);
	window.draw(bird.bird_sprite);
	window.draw(score_text);

	if (!running) {
		window.draw(restart_text);
	}
	if (running && !game_started) {
		window.draw(start_text);
	}
}

void Game::processing(sf::Time& dt) {
	if (game_started) {
		MoveGround(dt);

		if (pipe_spawn_time > default_spawn_time) {
			pipes.push_back(Pipe(dist(rd)));
			pipe_spawn_time = 0;
		}

		pipe_spawn_time++; // will increase at each frame
		
		for (int i = 0; i < pipes.size(); i++) {
			// update pipe position of each pipes in the vector container
			pipes[i].updatePosition(dt);

			if (pipes[i].getPipeRightBound() < 0) { // the pipe gets out of screen
				pipes.erase(pipes.begin() + i);  // iterator at ith position from beginning
			}
		}

		checkCollision();
		checkScore();
	}

	bird.UpdateBirdPosition(dt);
}

void Game::checkScore() {
	if (pipes.size() > 0) {
		if (!monitor) {
			if ((bird.bird_sprite.getGlobalBounds().left > pipes[0].pipeDown_sprite.getGlobalBounds().left) &&
				(bird.GetBirdsRightBound() < pipes[0].getPipeRightBound())) {
				monitor = true;
			}
		}
		else {
			if ((bird.bird_sprite.getGlobalBounds().left > pipes[0].getPipeRightBound())) {
				game_score++;
				score_text.setString(std::to_string(game_score));
				monitor = false;
			}
		}
	}
}

void Game::MoveGround(sf::Time& dt) {
	ground_sprite[0].move(-(ground_speed * dt.asSeconds()), 0.f);
	ground_sprite[1].move(-(ground_speed * dt.asSeconds()), 0.f);

	if ((ground_sprite[0].getGlobalBounds().left + ground_sprite[0].getGlobalBounds().width) < 0) {
		ground_sprite[0].setPosition(ground_sprite[1].getGlobalBounds().left + ground_sprite[1].getGlobalBounds().width, 750.f);
	}

	if ((ground_sprite[1].getGlobalBounds().left + ground_sprite[1].getGlobalBounds().width) < 0) {
		ground_sprite[1].setPosition(ground_sprite[0].getGlobalBounds().left + ground_sprite[0].getGlobalBounds().width, 750.f);
	}
}

void Game::checkCollision() {
	if (pipes.size() > 0) {
		if (pipes[0].pipeDown_sprite.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds()) ||
			pipes[0].pipeUp_sprite.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds()) ||
			(bird.bird_sprite.getGlobalBounds().top >= 700) ||
			(bird.bird_sprite.getGlobalBounds().top < 0)) {
			game_started = false; 
			running = false;
		}
	}
}

void Game::restartGame() {
	if (dist1(rd1) == 0) {
		bg_sprite.setPosition(0.f, -200.f);  // set x to 0 for day mode
	}
	else {
		bg_sprite.setPosition(-615.f, -200.f);  // set x to -615 for night mode
	}

	bird.ResetBirdPosition();
	bird.SetFlying(false);
	bird.bird_rotation = 0;
	bird.bird_sprite.setRotation(bird.bird_rotation);
	running = true;
	game_started = false;
	pipe_spawn_time = 65;
	pipes.clear();
	game_score = 0;
	score_text.setString("0");
}