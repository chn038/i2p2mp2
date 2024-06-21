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
	float speed;
	int damage;
	Tower *parent;
	PlayScene *getPlayScene();
	virtual void OnExplode(Instance *instance);
	std::list<std::pair<bool, Engine::IObject *>> &FlyTarget;
	std::list<std::pair<bool, Engine::IObject *>> &GroundTarget;

public:
	Instance *Target = nullptr;
	explicit Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Tower *parent,
					std::list<std::pair<bool, Engine::IObject *>> &FlyTarget, std::list<std::pair<bool, Engine::IObject *>> &GroundTarget);
	void Update(float deltaTime);
};
#endif // BULLET_HPP
