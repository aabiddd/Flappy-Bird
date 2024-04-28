#pragma once
#include <SFML/Graphics.hpp>

class Bird
{
private:
	sf::Texture texture[2];
	const float gravity;
	const int strokes; // flapping speed of flappy bird
	float y_velocity;
	int animation_counter, texture_switch; // switch the texture according to the value of animation counter
	bool flying;

public:
	sf::Sprite bird_sprite;
	float bird_rotation;

	Bird();
	void SetFlying(bool);
	void Flap(sf::Time&);
	void ResetBirdPosition();
	void UpdateBirdPosition(sf::Time&);
	float GetBirdsRightBound(); // get x-coordinate of sprite Bird
	void rotateOnSpace();
};

