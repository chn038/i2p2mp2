#ifndef TOWER5_HPP
#define TOWER5_HPP
#include "Team/Team.hpp"
#include "Tower.hpp"

class Tower5 : public Tower
{
public:
    static const int Price;
    static const int Type;
    Tower5(float x, float y, Team* team);
    void Update(float deltaTime) override;
    void CreateBullet() override;
};
#endif // TOWER5
