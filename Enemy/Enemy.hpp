#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <vector>
#include <string>

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

class Bullet;
class PlayScene;
class Turret;

class Enemy : public Engine::Sprite
{
protected:
	std::vector<Engine::Point> path;
	float speed;
	float hp;
	int money;
	PlayScene *getPlayScene();
	virtual void OnExplode();

public:
	float reachEndTime;
	std::list<Turret *> lockedTurrets;
	std::list<Bullet *> lockedBullets;
	// <summary>
	// create a new Enemy with given x, y, radius, speed, hp, money
	// </summary>
	// <param name = x>: new enemy x pos</param>
	// <param name = y>: new enemy y pos</param>
	// <param name = radius>: radius is used to detect collision</param>
	// <param name = speed>: movement speed of the enemy</param>
	// <param name = hp>: hp of the enemy </param>
	// <param name = money>: the money drop after the enemy was killed</param>
	Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money);
	void Hit(float damage);
	void UpdatePath(const std::vector<std::vector<int>> &mapDistance);
	void Update(float deltaTime) override;
	void Draw() const override;
};
#endif // ENEMY_HPP
