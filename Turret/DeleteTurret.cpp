#include <allegro5/base.h>
#include <string>

#include "DeleteTurret.hpp"
#include "Scene/PlayScene.hpp"

const int DeleteTurret::Price = 0;
DeleteTurret::DeleteTurret(float x, float y, int damageOffset) :
    Turret("play/dirt.png", "play/target-invalid.png", x, y, 0, Price, 0, damageOffset) {
    this->IsTurret = false;
}

void DeleteTurret::CreateBullet() {
}
