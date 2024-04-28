#include "Pipe.h"
#include "Globals.h"

sf::Texture Pipe::texture_down, Pipe::texture_up;
int Pipe::distance_between_pipes = 180; 
int Pipe::pipe_speed = 200;

Pipe::Pipe(int pos) // pos -> position for the pipe facing upwards (pipeUp)
{
	pipeUp_sprite.setTexture(texture_up);
	pipeDown_sprite.setTexture(texture_down);

	pipeUp_sprite.setScale(PIPE_SCALE, PIPE_SCALE);
	pipeDown_sprite.setScale(PIPE_SCALE, PIPE_SCALE);

	pipeUp_sprite.setPosition(SCREEN_WIDTH, pos);
	pipeDown_sprite.setPosition(SCREEN_WIDTH, (pos - distance_between_pipes - pipeDown_sprite.getGlobalBounds().height));
}

void Pipe::loadTextuers() {
	texture_up.loadFromFile("./assets/pipeup.png");
	texture_down.loadFromFile("./assets/pipedown.png");
}

void Pipe::updatePosition(sf::Time& dt) {
	pipeUp_sprite.move(-1.2 * (pipe_speed * dt.asSeconds()), 0);
	pipeDown_sprite.move(-1.2 * (pipe_speed * dt.asSeconds()), 0);
}

float Pipe::getPipeRightBound() {
	return (pipeUp_sprite.getGlobalBounds().left + pipeUp_sprite.getGlobalBounds().width);
}
