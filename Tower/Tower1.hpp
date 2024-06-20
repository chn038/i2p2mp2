#ifndef TOWER1_HPP
#define TOWER1_HPP
#include "Team/Team.hpp"
#include "Tower.hpp"

class Tower1 : public Tower
{
public:
    static const int Price;
    static const int Type;
    Tower1(float x, float y, Team* team);
    void CreateBullet() override;
    void Update(float deltaTime) override;
};
#endif // TOWER1
