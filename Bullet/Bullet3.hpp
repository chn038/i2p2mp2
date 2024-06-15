#ifndef BULLET_HPP
<<<<<<< HEAD
#define BULLET3_HPP
=======
#define BULLET1_HPP
>>>>>>> e5946213b1bd5f670156e6156b0a33b14d2bab2c
#include "Bullet.hpp"

class Instance;
class Turret;
namespace Engine
{
    struct Point;
} // namespace Engine

<<<<<<< HEAD
class Bullet3 : public Bullet
{
public:
    explicit Bullet3(Engine::Point position, Engine::Point forwardDirection, float rotation, Tower *parent, int damage);
    void OnExplode(Instance *instance) override;
};
#endif // BULLET3_HPP
=======
class FireBullet : public Bullet
{
public:
    explicit FireBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret *parent, int damage);
    void OnExplode(Instance *instance) override;
};
#endif // FIREBULLET_HPP
>>>>>>> e5946213b1bd5f670156e6156b0a33b14d2bab2c
