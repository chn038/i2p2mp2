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
    const float max_speed;
    const float max_hp;
    float speed;
    float hp;
    PlayScene *getPlayScene();
    virtual void OnExplode();
    int type;
    bool isGround;
    float baseRotation;

public:
    // <summary>
    // create a new Enemy with given x, y, radius, speed, hp, money
    // </summary>
    // <param name = x>: new enemy x pos</param>
    // <param name = y>: new enemy y pos</param>
    // <param name = radius>: radius is used to detect collision</param>
    // <param name = speed>: movement speed of the enemy</param>
    // <param name = hp>: hp of the enemy </param>
    // <param name = money>: the money drop after the enemy was killed</param>
    float hitRadius;
    Instance(std::string img, 
             float x, float y, 
             float radius, float hitRadius, float speed, 
             float hp, int money, int type, bool isGround,
             float coolDown, int damageOffset, 
             std::list<std::pair<bool, IObject *>> &FlyTarget,
             std::list<std::pair<bool, IObject *>> &GroundTarget,
             ALLEGRO_COLOR teamColor);
    void Hit(float damage);
    void UpdatePath(const std::vector<std::vector<int>> &mapDistance, Engine::Point endPoint);
    void Update(float deltaTime) override;
    void Draw() const override;
    // TODO
};
#endif // ENEMY_HPP
