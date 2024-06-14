#ifndef EMPTYBULLET_HPP
#define EMPTYBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class EmptyBullet : public Bullet {
public:
	explicit EmptyBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent, int damage);
	void OnExplode(Enemy* enemy) override;
};
#endif // FIREBULLET_HPP
