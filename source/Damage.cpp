#include <Damage.h>

namespace termd {

Damage::Damage(int b, int r)
    : base(b)
    , random_amount(r) /*, damage_type(t)*/
{
}

Damage::~Damage()
{
    //Should not need to do anything
}

Damage::Damage(const Damage& src)
    : base(src.base)
    , random_amount(src.random_amount) /*, damage_type(src.damage_type)*/
{
}

const Damage& Damage::operator=(const Damage& src)
{
    base = src.base;
    random_amount = src.random_amount;
    //damage_type = src.damage_type;
    return *this;
}

int Damage::get_value() const
{
    return base + (rand() % random_amount);
}

/*
int Damage::get_type() const {
	return damage_type;
}
*/

}
