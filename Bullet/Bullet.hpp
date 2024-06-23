#ifndef BULLET_HPP
#define BULLET_HPP
#include <string>

#include "Engine/Sprite.hpp"

class Instance;
class PlayScene;
class Tower;
namespace Engine
{
	struct Point;
} // namespace Engine

class Bullet : public Engine::Sprite
{
protected:
    bool pendingToDelete = false;
	float speed;
	int damage;
	Tower *parent;
	PlayScene *getPlayScene();
	virtual void OnExplode(Instance *instance);
	std::list<std::pair<bool, Engine::IObject *>> &FlyTarget;
	std::list<std::pair<bool, Engine::IObject *>> &GroundTarget;
    virtual void CheckCollision() = 0;

public:
	explicit Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Tower *parent,
					std::list<std::pair<bool, Engine::IObject *>> &FlyTarget, std::list<std::pair<bool, Engine::IObject *>> &GroundTarget);
	void Update(float deltaTime) override;
};
#endif // BULLET_HPP
