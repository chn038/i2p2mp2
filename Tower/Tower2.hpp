#ifndef TOWER2_HPP
#define TOWER2_HPP
#include "Tower/Tower.hpp"
#include "Team/Team.hpp"

class Tower2 : public Tower
{
public:
    static const int Price;
    static const int Type;
    Tower2(float x, float y, Team* team);
    void Update(float deltaTime) override;
    void CreateBullet() override;
};
#endif // TOWER2
