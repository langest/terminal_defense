#ifndef termd_homing_projectile
#define termd_homing_projectile

class HomingProjectile : public Projectile {
	private:
		Virus& target;
		int speed_increment;
		int speed_curr;

		bool step();
		void move();

	protected:

	public:
		HomingProjectile(Coord, Virus &);
		HomingProjectile(const HomingProjectile &);
		~HomingProjectile();
		HomingProjectile& operator=(const HomingProjectile &);

		virtual bool update();
};

#endif //termd_HomingProjectile
