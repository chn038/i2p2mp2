#include <allegro5/base.h>
#include <random>
#include <string>

#include "UI/Animation/DirtyEffect.hpp"
#include "Instance/Instance.hpp"
#include "Bullet2.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

class Tower;

Bullet2::Bullet2(Engine::Point position, Engine::Point forwardDirection, float rotation, Tower *parent, int damage, std::list<std::pair<bool, Engine::IObject *>> &GroundTarget) : Bullet("play/bullet-2.png", 400, damage, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent, GroundTarget, GroundTarget)
{
    // TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'FireBullet.hpp', 'FireBullet.cpp' to create a new bullet.
}
void Bullet2::OnExplode(Instance *instance)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
    getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-2.png", dist(rng), instance->Position.x, instance->Position.y));
}
