#include <allegro5/base.h>
#include <random>
#include <string>

#include "UI/Animation/DirtyEffect.hpp"
#include "Enemy/Enemy.hpp"
#include "EmptyBullet.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/AudioHelper.hpp"

class Turret;

EmptyBullet::EmptyBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent, int damage) :
	Bullet("play/bullet-7.png", 888, damage, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
	// TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'FireBullet.hpp', 'FireBullet.cpp' to create a new bullet.
}
void EmptyBullet::OnExplode(Enemy* enemy) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/light-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
	AudioHelper::PlayAudio("shockwave.ogg");
}

