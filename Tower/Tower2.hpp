#ifndef TOWER2_HPP
#define TOWER2_HPP
#include "Tower/Tower.hpp"
#include "Team/Team.hpp"

class Tower2 : public Tower
{
    float ticks;
    static const int spawnPeriod;
    Engine::Point SearchPlace();
    Team* team;
public:
    static const int Price;
    Tower2(float x, float y, Team* team);
    void CreateBullet() override;
    void Update(float deltaTime) override;
};
#endif // TOWER2
