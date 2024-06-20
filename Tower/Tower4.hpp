#ifndef TOWER4_HPP
#define TOWER4_HPP
#include "Team/Team.hpp"
#include "Tower.hpp"

class Tower4 : public Tower
{
    float ticks;
    static const int spawnPeriod;
    Engine::Point SearchPlace();
    Team* team;
public:
    static const int Price;
    Tower4(float x, float y, Team* team);
    void CreateBullet() override;
    void Update(float deltaTime) override;

};
#endif // TOWER4
