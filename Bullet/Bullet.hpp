#ifndef BULLET_HPP
#define BULLET_HPP
#include <string>

#include "Engine/Sprite.hpp"

class Instance;
class PlayScene;
class Turret;
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

public:
	Instance *Target = nullptr;
	explicit Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Tower *parent);
	void Update(float deltaTime) override;
};
#endif // BULLET_HPP
