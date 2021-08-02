#pragma once

#include <cstdlib>

namespace termd {

class Damage {
private:
    int base;
    int random_amount;
    /**
	* Damage Types:
	* 0: hacking
	* 1: bruteforce
	* 2: spam
	*/
    //int type;
public:
    Damage(int, int);
    ~Damage();
    Damage(const Damage&);
    const Damage& operator=(const Damage&);

    int get_value() const;
    //int get_type() const;
};

}
