#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Game.h"

int main() {
	// user cant resize the window --> Style::Titlebar | Style::Close
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird", sf::Style::Titlebar | sf::Style::Close);

	// windows icon
	sf::Image icon;
	icon.loadFromFile("./assets/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// instance of Game class
	Game game(window);
	game.GameLoop();

	return EXIT_SUCCESS;
}