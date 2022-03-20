#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include "Player.h"

#define MAX_ENTITIES 200

class Game
{
	// Members
	public:
		bool isRunning;

		// Constructors/Destructors
		Game(int width, int height);
		~Game();

		// Methods
		void loop();

	private:
		sf::RenderWindow _window;
		int _screenWidth;
		int _screenHeight;
		float _distance;
		bool _isFocused;

		sf::Time _elapsedTime;
		Player _player;
		Entity* _onScreen[MAX_ENTITIES];
		int _numEntities;
		
		
		// spawnEnemies()
		// despawnEnemies()
		void eventHandler();
		void keyInput();
		//   updateEntities();
		void drawEntities();
		void drawSky(sf::Color topColor, sf::Color bottomColor);
		void drawGround(float horizon, float width);

};

