#ifndef termd_damage
#define termd_damage

class Damage{
private:
	int base;
	int random;
	int type;
	/**
	* Damage Types:
	* 0: hacking
	* 1: bruteforce
	*/
public:
	Damage();
	~Damage();
	Damage(const Damage &);
	operator=(const Damage &);


};

#endif //termd_damage