#include "player.hpp"

Player::Player() : ram(PLAYER_DEFAULT_RAM), hp(PLAYER_DEFAULT_HP) {
}

Player::~Player() {
	//Currently nothing needs to be done
}

void Player::new_map_refresh() {
	hp = PLAYER_DEFAULT_HP;
	ram = PLAYER_DEFAULT_RAM;
}

inline bool Player::is_alive() {
	return hp > 0;
}

inline void Player::take_damage(int amount) {
	hp -= amount;
}