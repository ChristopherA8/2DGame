#include "Game.h"

Game::Game(int width, int height) {
  _window.create(sf::VideoMode(width, height), "2D Game", sf::Style::Close);
  _screenWidth = width;
  _screenHeight = height;
  _distance = 0.0f;
  _isFocused = true;
  _player = Player();
  _numEntities = 0;
}

Game::~Game() {
	_window.close();
}

///////////////////// GAME LOOP //////////////////////

void Game::loop() {
	sf::Clock clock;

	while (_window.isOpen()) {
		eventHandler();

		_elapsedTime = clock.restart();
		keyInput();

		/* DRAWING  */
		_window.clear();

		drawSky(sf::Color::White, sf::Color::Blue);
		drawGround(0.5f, 0.3f);
		drawEntities();

		_window.display();
	}
}

/////////////////////////////////////////////////////////

void Game::eventHandler() {
	sf::Event event;
	while (_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			_window.close();
			break;
		case sf::Event::GainedFocus:
			_isFocused = true;
			break;
		case sf::Event::LostFocus:
			_isFocused = false;
			break;
		}
	}
}

void Game::keyInput() {
	if (_isFocused) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			// up key is pressed: move screen
			_distance += _elapsedTime.asSeconds() * _player.spd;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			// down key is pressed: move screen
			_distance -= _elapsedTime.asSeconds() * _player.spd;
		}
	}
}

void Game::drawSky(sf::Color topColor, sf::Color bottomColor) {
	sf::Vertex sky[] = {
		sf::Vertex(sf::Vector2f(0, 0), topColor), // TL
		sf::Vertex(sf::Vector2f(_screenWidth, 0), topColor), // TR
		sf::Vertex(sf::Vector2f(_screenWidth, _screenHeight * 0.75), bottomColor), // BR
		sf::Vertex(sf::Vector2f(0, _screenHeight * 0.75), bottomColor) // BL
	};

	_window.draw(sky, 4, sf::Quads);
}

void Game::drawGround(float horizon, float width) {
	if (horizon > 1.0f || width > 1.0f || horizon < 0.25f || width < 0.0f) {
		printf("Error: argument(s) invalid\n");
		return;
	}

	for (int y = 0; y < _screenHeight * horizon; y++) {
		float perspective = (float)y / (_screenHeight * horizon);

		float midPoint = 0.5f;
		float roadWidth = width + perspective * 0.8f;

		roadWidth *= 0.5f;
		int nLeftGround = (midPoint - roadWidth) * _screenWidth;
		int nRightGround = (midPoint + roadWidth) * _screenWidth;
		int nRow = y + _screenHeight * (1 - horizon);

		sf::Color groundColor = sinf(20.0f * powf(1.0f - perspective, 3) + _distance * 0.1f) > 0.0f ? sf::Color(65, 152, 10, 255) : sf::Color(19, 133, 16, 255);
		sf::Color pathColor = sf::Color(102, 68, 0, 255);

		sf::Vertex leftGround[] = {
			sf::Vertex(sf::Vector2f(0, nRow), groundColor),
			sf::Vertex(sf::Vector2f(nLeftGround, nRow), groundColor),
		};
		sf::Vertex rightGround[] = {
			sf::Vertex(sf::Vector2f(nRightGround, nRow), groundColor),
			sf::Vertex(sf::Vector2f(_screenWidth, nRow), groundColor),
		};
		sf::Vertex path[] = {
			sf::Vertex(sf::Vector2f(nLeftGround, nRow), pathColor),
			sf::Vertex(sf::Vector2f(nRightGround, nRow), pathColor),
		};
		_window.draw(leftGround, 2, sf::Lines);
		_window.draw(path, 2, sf::Lines);
		_window.draw(rightGround, 2, sf::Lines);
	}
}

void Game::drawEntities() {
	for (int i = 0; i < _numEntities; i++) {
		Entity *entity = _onScreen[i];

		_window.draw(*entity);
	}
	_window.draw(_player);
}