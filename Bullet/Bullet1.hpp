#ifndef BULLET1_HPP
#define BULLET1_HPP
#include "Bullet.hpp"

class Instance;
class Turret;
namespace Engine
{
    struct Point;
} // namespace Engine

class Bullet1 : public Bullet
{
    void CheckCollision() override;
public:
    explicit Bullet1(Engine::Point position, Engine::Point forwardDirection, float rotation, Tower *parent, int damage,
                     std::list<std::pair<bool, Engine::IObject *>> &FlyTarget,
                     std::list<std::pair<bool, Engine::IObject *>> &GroundTarget);
    void OnExplode(Instance *instance) override;
};
#endif // BULLET1_HPP
