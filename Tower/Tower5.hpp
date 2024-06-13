#ifndef TOWER5_HPP
#define TOWER5_HPP
#include "Tower.hpp"

class Tower5 : public Tower
{
public:
    static const int Price;
    static const int Type;
    Tower5(float x, float y, int damageOffset, int team);
    void CreateBullet() override;
};
#endif // TOWER5
