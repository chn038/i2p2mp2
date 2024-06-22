#include <allegro5/base.h>
#include <random>
#include <string>

#include "UI/Animation/DirtyEffect.hpp"
#include "Instance/Instance.hpp"
#include "Bullet1.hpp"
#include "Engine/Group.hpp"
#include "Engine/Collider.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

class Tower;

Bullet1::Bullet1(Engine::Point position, Engine::Point forwardDirection, float rotation, Tower *parent, int damage, std::list<std::pair<bool, Engine::IObject *>> &FlyTarget, std::list<std::pair<bool, IObject*>> &GroundTarget) : Bullet("play/bullet-1.png", 400, damage, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent, FlyTarget, GroundTarget)
{
    // TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'FireBullet.hpp', 'FireBullet.cpp' to create a new bullet.
}
void Bullet1::CheckCollision() {
	for (auto &it : FlyTarget)
	{
		Instance *target = dynamic_cast<Instance *>(it.second);
		if (!target->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, target->Position, target->hitRadius))
		{
			OnExplode(target);
			target->Hit(damage);
			getPlayScene()->BulletGroup->RemoveObject(objectIterator);
			return;
		}
	}
}
void Bullet1::OnExplode(Instance *instance)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
    getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), instance->Position.x, instance->Position.y));
}
