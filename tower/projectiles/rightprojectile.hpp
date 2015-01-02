#ifndef termd_right_projectile
#define termd_right_projectile

#include "../../definitions"
#include "projectile.hpp"

class RightProjectile : public Projectile {
	private:
		vector<Virus*>& viruses;

		bool hit();
		void move();

	protected:

	public:
		RightProjectile(Coord, vector<Virus*>&);
		RightProjectile(const RightProjectile&) = delete;
		virtual ~RightProjectile();
		RightProjectile& operator=(const RightProjectile &);

		virtual bool update();
};

#endif //termd_HomingProjectile
