#ifndef TOWER_HPP
#define TOWER_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"

class Enemy;
class PlayScene;

class Tower : public Engine::Sprite
{
protected:
    int price;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    Sprite imgBase;
    std::list<Tower *>::iterator lockedTowerIterator;
    PlayScene *getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;
    int damageOffset;
    int team;
    int type;

public:
    bool Enabled = true;
    bool Preview = false;
    bool IsTower = true;
    Enemy *Target = nullptr;
    Tower(std::string imgBase, std::string imgTower, float x, float y, float radius, int price, float coolDown, int damageOffset, int team, int type);
    void Update(float deltaTime) override;
    void Draw() const override;
    int GetPrice() const;
    void UpgradeDamage(int toDamage);
};
#endif // TOWER_HPP
