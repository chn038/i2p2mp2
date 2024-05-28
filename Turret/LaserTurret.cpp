#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Bullet/LaserBullet.hpp"
#include "LaserTurret.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int LaserTurret::Price = 200;
LaserTurret::LaserTurret(float x, float y, int damageOffset) :
	Turret("play/tower-base.png", "play/turret-2.png", x, y, 300, Price, 0.5, damageOffset) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void LaserTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
	// Change bullet position to the front of the gun barrel.
	getPlayScene()->BulletGroup->AddNewObject(new LaserBullet(Position + normalized * 36 - normal * 6, diff, rotation, this, 2 + damageOffset));
	getPlayScene()->BulletGroup->AddNewObject(new LaserBullet(Position + normalized * 36 + normal * 6, diff, rotation, this, 2 + damageOffset));
	AudioHelper::PlayAudio("laser.wav");
}
