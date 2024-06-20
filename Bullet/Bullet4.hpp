#ifndef BULLET4_HPP
#define BULLET4_HPP
#include "Bullet.hpp"

class Instance;
class Tower;
namespace Engine
{
    struct Point;
} // namespace Engine

class Bullet4 : public Bullet
{
public:
    explicit Bullet4(Engine::Point position, Engine::Point forwardDirection, float rotation, Tower *parent, int damage);
    void OnExplode(Instance *instance) override;
};
#endif // BULLET4_HPP
