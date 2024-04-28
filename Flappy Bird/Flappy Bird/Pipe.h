#pragma once
#include <SFML/Graphics.hpp>

class Pipe
{
private:
	static sf::Texture texture_up, texture_down;
	// distance_between_pipes refers to distance between up pipe and down pipe
	static int distance_between_pipes, pipe_speed;
public:
	sf::Sprite pipeUp_sprite, pipeDown_sprite;

	Pipe(int);
	static void loadTextuers(); // static so that we only need to load the sprites textures once
	void updatePosition(sf::Time&);
	float getPipeRightBound();
};

