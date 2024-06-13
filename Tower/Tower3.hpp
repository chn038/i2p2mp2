#ifndef TOWER3_HPP
#define TOWER3_HPP
#include "Tower.hpp"

class Tower3 : public Tower
{
public:
    static const int Type;
    static const int Price;
    Tower3(float x, float y, int damageOffset, int team);
    void CreateBullet() override;
};
#endif // TOWER3
