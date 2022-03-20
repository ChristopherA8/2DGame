#pragma once
#include "Entity.h"

class Player: public Living
{
	public:
		float xp;
		// Item inventory[];

		Player();
		~Player();

		bool isCollidingWith(Entity &e);
		void onInteract(Entity &e);
		void draw(sf::RenderTarget& target, sf::RenderStates state) const;
};

