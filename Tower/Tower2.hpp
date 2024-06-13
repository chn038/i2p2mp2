#ifndef TOWER2_HPP
#define TOWER2_HPP
#include "Tower.hpp"

class Tower2 : public Tower
{
public:
    static const int Price;
    static const int Type;
    Tower2(float x, float y, int damageOffset, int team);
    void CreateBullet() override;
};
#endif // TOWER2
