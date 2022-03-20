#pragma once
#include <SFML/Graphics.hpp>

class Entity: public sf::Drawable
{
	public:
		const char* name;
		sf::Vector2f midPoint;
		float spawnDistance, despawnDistance;

		//Entity();
		//~Entity();

		virtual void onInteract(Entity &e) = 0;
		virtual bool isCollidingWith(Entity &e) = 0;
};

class Living: public Entity 
{
	public:
		float hp, def, dmg, spd;
		enum Status { /**/ };
		enum AttackPattern { /**/ };
};

class NonLiving: public Entity 
{

};

