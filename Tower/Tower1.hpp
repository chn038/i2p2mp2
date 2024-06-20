#ifndef TOWER1_HPP
#define TOWER1_HPP
#include "Team/Team.hpp"
#include "Tower.hpp"

namespace Engine {
    class Point;
}

class Tower1 : public Tower
{
    float ticks;
    static const int spawnPeriod;
    Engine::Point SearchPlace();
    Team* team;
public:
    static const int Price;
    Tower1(float x, float y, Team* team);
    void CreateBullet() override;
    void Update(float deltaTime) override;
};
#endif // TOWER1
