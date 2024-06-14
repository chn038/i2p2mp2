#ifndef BULLET_HPP
#define BULLET1_HPP
#include "Bullet.hpp"

class Instance;
class Turret;
namespace Engine
{
    struct Point;
} // namespace Engine

class FireBullet : public Bullet
{
public:
    explicit FireBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret *parent, int damage);
    void OnExplode(Instance *instance) override;
};
#endif // FIREBULLET_HPP
