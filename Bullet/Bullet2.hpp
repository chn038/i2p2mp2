#ifndef BULLET_HPP
#define BULLET2_HPP
#include "Bullet.hpp"

class Instance;
class Turret;
namespace Engine
{
    struct Point;
} // namespace Engine

class Bullet2 : public Bullet
{
public:
    explicit Bullet2(Engine::Point position, Engine::Point forwardDirection, float rotation, Tower *parent, int damage);
    void OnExplode(Instance *instance) override;
};
#endif // BULLET2_HPP