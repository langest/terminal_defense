#include "player.hpp"

namespace termd {

	Player::Player() : availiable_towers({BASIC_TOWER_1x1_ID, RIGHT_TOWER_1x1_ID}), ram(PLAYER_DEFAULT_RAM), hp(PLAYER_DEFAULT_HP) {
	}

	Player::~Player() {
		//Currently nothing needs to be done
	}

	void Player::new_map_refresh() {
		hp = PLAYER_DEFAULT_HP;
		ram = PLAYER_DEFAULT_RAM;
	}

	int Player::get_hp() const {
		return hp;
	}

	bool Player::is_alive() const {
		return hp > 0;
	}

	void Player::take_damage(int amount) {
		hp -= amount;
	}

	void Player::modify_ram(int amount) {
		ram += amount;
	}

	int Player::get_ram() const{
		return ram;
	}

	void Player::unlock_tower(int id) {
		availiable_towers.insert(id);
	}

	void Player::lock_tower(int id) {
		availiable_towers.erase(id);
	}

}
