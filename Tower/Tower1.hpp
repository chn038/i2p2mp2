#ifndef TOWER1_HPP
#define TOWER1_HPP
#include "Tower.hpp"

class Tower1 : public Tower
{
public:
    static const int Price;
    static const int Type;
    Tower1(float x, float y, int damageOffset, int team);
    void CreateBullet() override;
};
#endif // TOWER1
