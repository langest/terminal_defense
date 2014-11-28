#include "player.hpp"

Player::Player() {

}

Player::Player(const Player & src) {
	completed_maps = src.completed_maps;
}

Player::~Player() {
	//Currently nothing needs to be done
}

Player& Player::operator=(const Player & src) {
	completed_maps = src.completed_maps;
}
