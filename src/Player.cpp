#include "Player.h"

Player::Player() {
	spd = 100.0f;
}

Player::~Player() {
}

bool Player::isCollidingWith(Entity &e) {
	return false;
}
void Player::onInteract(Entity& e) {
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(sf::CircleShape(50));
}