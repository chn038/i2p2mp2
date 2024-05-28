#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Bullet/EmptyBullet.hpp"
#include "EmptyTurret.hpp"
#include "Scene/PlayScene.hpp"

const int EmptyTurret::Price = 500;
EmptyTurret::EmptyTurret(float x, float y, int damageOffset) :
	Turret("play/tower-base.png", "play/turret-6.png", x, y, 1000, Price, 8, damageOffset) {
}

void EmptyTurret::CreateBullet(){
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
	// Change bullet position to the front of the gun barrel.
	getPlayScene()->BulletGroup->AddNewObject(new EmptyBullet(Position + normalized * 36 - normal * 6, diff, rotation, this, 300 + damageOffset));
}
