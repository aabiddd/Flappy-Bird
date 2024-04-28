#include "Bird.h"
#include "Globals.h"

Bird::Bird() :  // Initializer List
	gravity(20),
	strokes(450),
	animation_counter(0),
	texture_switch(0),
	flying(false),
	bird_rotation(0)
{
	// set bird sprite's texture
	texture[0].loadFromFile("./assets/birddown.png");
	texture[1].loadFromFile("./assets/birdup.png");

	bird_sprite.setTexture(texture[texture_switch]);
	bird_sprite.setScale(BIRD_SCALE, BIRD_SCALE);
	bird_sprite.setOrigin(25.5, 18);  // setting the origin around middle of sprite for smoother rotations

	// reset bird's position initially
	ResetBirdPosition();
}

void Bird::SetFlying(bool flying) {
	this->flying = flying;
}

void Bird::Flap(sf::Time& dt) {
	y_velocity = -(strokes * dt.asSeconds());
}

void Bird::ResetBirdPosition() {
	bird_sprite.setPosition(200, 375);
	y_velocity = 0;
}

void Bird::UpdateBirdPosition(sf::Time& dt) {
	// 698 position for bird sprite when it touches the ground
	if ((bird_sprite.getGlobalBounds().top < 698) && flying) {  // position updates only when bird is flying above the ground
		// bird animation
		if (animation_counter == 5) {
			// switch the flying texture of bird only after 5 frames
			bird_sprite.setTexture(texture[texture_switch]);

			if (texture_switch) {
				texture_switch = 0;
			}
			else {
				texture_switch = 1;
			}

			animation_counter = 0;

			
		}
		animation_counter++;

		// set velocity
		y_velocity += (gravity * dt.asSeconds());
		bird_sprite.move(0, y_velocity);

		// falls down slowly unless space is pressed, plus rotated no more than 90deg
		if (bird_rotation < 90) {
			bird_rotation += 0.4 * y_velocity;
			bird_sprite.setRotation(bird_rotation);
		}
	}
}

float Bird::GetBirdsRightBound() {
	return (bird_sprite.getGlobalBounds().left + bird_sprite.getGlobalBounds().width);
}

void Bird::rotateOnSpace() {
	/*
	int animation_count = 0;

	if ((bird_sprite.getGlobalBounds().top < 698) && flying) {
		if (animation_count == 5) {
			bird_rotation = -0.2f;
			bird_sprite.setRotation(bird_rotation);
		}
		animation_count++;
	} */
	bird_rotation = -0.2f;
	bird_sprite.setRotation(bird_rotation);
}