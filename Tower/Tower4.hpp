#ifndef TOWER4_HPP
#define TOWER4_HPP
#include "Tower.hpp"

class Tower4 : public Tower
{
public:
    static const int Price;
    static const int Type;
    Tower4(float x, float y, int damageOffset, int team);
    void CreateBullet() override;
};
#endif // TOWER4
