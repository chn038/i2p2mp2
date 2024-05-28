#ifndef TURRET_HPP
#define TURRET_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"

class Enemy;
class PlayScene;

class Turret: public Engine::Sprite {
protected:
    int price;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    Sprite imgBase;
    std::list<Turret*>::iterator lockedTurretIterator;
    PlayScene* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;
    int damageOffset;

public:
    bool Enabled = true;
    bool Preview = false;
    bool IsTurret = true;
    Enemy* Target = nullptr;
    Turret(std::string imgBase, std::string imgTurret, float x, float y, float radius, int price, float coolDown, int damageOffset);
    void Update(float deltaTime) override;
    void Draw() const override;
	int GetPrice() const;
    void UpgradeDamage(int toDamage);
};
#endif // TURRET_HPP
