#ifndef BULLET_HPP
#define BULLET1_HPP
#include "Bullet.hpp"

class Instance;
class Tower;
namespace Engine
{
    struct Point;
} // namespace Engine

class Bullet5 : public Bullet
{
public:
    explicit Bullet5(Engine::Point position, Engine::Point forwardDirection, float rotation, Tower *parent, int damage);
    void OnExplode(Instance *instance) override;
};
#endif // BULLET5_HPP
