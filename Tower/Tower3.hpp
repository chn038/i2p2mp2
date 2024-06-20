#ifndef TOWER3_HPP
#define TOWER3_HPP
#include "Team/Team.hpp"
#include "Tower.hpp"

class Tower3 : public Tower
{
public:
    static const int Type;
    static const int Price;
    Tower3(float x, float y, Team* team);
    void Update(float deltaTime) override;
    void CreateBullet() override;
};
#endif // TOWER3
