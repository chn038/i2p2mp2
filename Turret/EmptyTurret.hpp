#ifndef EMPTYTURRET_HPP
#define EMPTYTURRET_HPP
#include "Turret.hpp"

class EmptyTurret: public Turret {
public:
	static const int Price;
    EmptyTurret(float x, float y, int damageOffset);
	void CreateBullet() override;
};
#endif // EMPTYTURRET_HPP

