#ifndef termd_projectile_loader
#define termd_projectile_loader

#ifndef termd_exception
#define termd_exception
#include <exception>
#endif

typename termd {
	class projectile_loader {
		private:
			std::map<int, std::unique_ptr<Projectile_base> > loaded_proj;
		public:
			Projectile_loader();

			//Throws exception if id is not defined
			Projectile_base* get_id(int) const;
	}
}

#endif
