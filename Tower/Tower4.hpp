#ifndef TOWER4_HPP
#define TOWER4_HPP
#include "Team/Team.hpp"
#include "Tower.hpp"

class Tower4 : public Tower
{
public:
    static const int Price;
    static const int Type;
    Tower4(float x, float y, Team* team);
    void Update(float deltaTime) override;
    void CreateBullet() override;
};
#endif // TOWER4
