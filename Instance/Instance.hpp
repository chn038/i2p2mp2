#ifndef INSTANCE_HPP
#define INSTANCE_HPP
#include <list>
#include <vector>
#include <string>

#include "Engine/Point.hpp"
#include "Tower/Tower.hpp"

class Bullet;
class PlayScene;
class Tower;

class Instance : public Tower
{
protected:
    std::vector<Engine::Point> path;
    float max_speed;
    float speed;
    float hp;
    int money;
    PlayScene *getPlayScene();
    virtual void OnExplode();

public:
    std::list<Tower *> lockedTowers;
    std::list<Bullet *> lockedBullets;
    // <summary>
    // create a new Enemy with given x, y, radius, speed, hp, money
    // </summary>
    // <param name = x>: new enemy x pos</param>
    // <param name = y>: new enemy y pos</param>
    // <param name = radius>: radius is used to detect collision</param>
    // <param name = speed>: movement speed of the enemy</param>
    // <param name = hp>: hp of the enemy </param>
    // <param name = money>: the money drop after the enemy was killed</param>
    Instance(std::string img, float x, float y, float radius, float speed, float hp, int money, int type, std::list<std::pair<bool, IObject *>> &TargetList);
    void Hit(float damage);
    void UpdatePath(const std::vector<std::vector<int>> &mapDistance);
    void Update(float deltaTime) override;
    void Draw() const override;
    // TODO
};
#endif // ENEMY_HPP
