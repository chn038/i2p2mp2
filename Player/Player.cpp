#include "Engine/GameEngine.hpp"
#include "Scene/PlayScene.hpp"
#include "Player/Player.hpp"
#include "Enemy/Enemy.hpp"
#include "Turret/Turret.hpp"

Player::~Player() {
    Terminate();
}

void Player::Initialize() {
    AddNewObject(TowerGroup = new Group());
    AddNewObject(InstanceGroup = new Group());
    waveData.clear();
    waveData.resize(instanceTypes, 0);
    damageOffset = 0;
    money = initMoney;
    lives = initLives;
}

void Player::Terminate() {
    Group::Clear();
}

void Player::SpawnInstances() {
    Enemy *enemy;
    for (int i = 0; i < Player::instanceTypes; ++i) {
        for (int j = 0; j < waveData[i]; ++j) {
            // This should add new enemy
            switch (i) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                default:
                    break;
            }
            enemy->UpdatePath(mapDistance);
            // Maybe update here
        }
    }
}

void Player::addTower(int x, int y, int type) {
    Turret *newTurret;
    // This should add new things to waveData
    switch(type) {
    }
    TowerGroup->AddNewObject(static_cast<Engine::IObject*>(newTurret));
}

bool Player::deleteTower(int x, int y) {
    for (auto &it: TowerGroup->GetObjects()) {
        if (it.second->Position.x == x && it.second->Position.y == y) {
            TowerGroup->RemoveObject(it.second->GetObjectIterator());
            return true;
        }
    }
    return false;
}

PlayScene* Player::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

std::vector<std::vector<Engine::TileType>>& Player::getMapState() {
    return getPlayScene()->mapState;
}
