#ifndef TOWER_HPP
#define TOWER_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"

class Instance;
class PlayScene;

class Tower : public Engine::Sprite
{
protected:
    int price;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    Sprite imgBase;
    PlayScene *getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;
    virtual void SearchTarget();
    int damageOffset;
    std::list<std::pair<bool, Engine::IObject *>> &FlyTarget;
    std::list<std::pair<bool, Engine::IObject *>> &GroundTarget;
    float barRatio;
    ALLEGRO_COLOR barColor;

public:
    bool Enabled = true;
    Instance *Target = nullptr;
    Tower(std::string imgBase, 
          std::string imgTower, 
          float x, 
          float y, 
          float radius,
          int price, 
          float coolDown, 
          int damageOffset, 
          std::list<std::pair<bool, IObject *>> &FlyTarget,
          std::list<std::pair<bool, IObject *>> &GroundTarget,
          ALLEGRO_COLOR color = al_map_rgb(150, 150, 150));
    void Update(float deltaTime) override;
    void Draw() const override;
    int GetPrice() const;
    void UpgradeDamage(int toDamage);
};
#endif // TOWER_HPP
