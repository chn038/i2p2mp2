#ifndef TOWER3_HPP
#define TOWER3_HPP
#include "Team/Team.hpp"
#include "Tower.hpp"

class Tower3 : public Tower
{
    int ticks;
    static const int spawnPeriod;
    Engine::Point SearchPlace();
    Team* team;
public:
    static const int Price;
    static const int Type;
    Tower3(float x, float y, Team* team);
    void CreateBullet() override;
    void Update(float deltaTime) override;
};
#endif // TOWER3
