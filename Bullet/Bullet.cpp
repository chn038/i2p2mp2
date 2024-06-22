#include "Bullet.hpp"
#include "Engine/Collider.hpp"
#include "Instance/Instance.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
// #include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

PlayScene *Bullet::getPlayScene()
{
	return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Bullet::OnExplode(Instance *instance)
{
}
Bullet::Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Tower *parent,
			   std::list<std::pair<bool, Engine::IObject *>> &FlyTarget, std::list<std::pair<bool, Engine::IObject *>> &GroundTarget)
	: Sprite(img, position.x, position.y), speed(speed), damage(damage), parent(parent), FlyTarget(FlyTarget), GroundTarget(GroundTarget)
{
	Velocity = forwardDirection.Normalize() * speed;
	Rotation = rotation;
	CollisionRadius = 4;
}

void Bullet::Update(float deltaTime)
{
	Sprite::Update(deltaTime);
	PlayScene *scene = getPlayScene();
	// Can be improved by Spatial Hash, Quad Tree, ...
	// However simply loop through all enemies is enough for this program.
    CheckCollision();
	// Check if out of boundary.
	if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), PlayScene::GetClientSize()))
		getPlayScene()->BulletGroup->RemoveObject(objectIterator);
}
