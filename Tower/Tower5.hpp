#ifndef TOWER5_HPP
#define TOWER5_HPP
#include "Team/Team.hpp"
#include "Tower.hpp"

class Tower5 : public Tower
{
    int ticks;
    static const int spawnPeriod;
    Engine::Point SearchPlace();
    Team* team;
public:
    static const int Price;
    static const int Type;
    Tower5(float x, float y, Team* team);
    void CreateBullet() override;
    void Update(float deltaTime) override;


};
#endif // TOWER5
