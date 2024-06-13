#include "Engine/GameEngine.hpp"
#include <queue>
#include "Engine/LOG.hpp"
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

void Player::UpdateDistance() {
    PlayScene* scene = getPlayScene();
    std::vector<std::vector<Engine::TileType>>& mapState = getMapState();
    int MapWidth = scene->MapWidth;
    int MapHeight = scene->MapHeight;
    static const Engine::Point directions[8] = {
        Engine::Point(-1, -1), Engine::Point(0, -1), Engine::Point(1, -1),
        Engine::Point(-1, 0), Engine::Point(1, 0),
        Engine::Point(-1, 1), Engine::Point(0, 1), Engine::Point(1, 1),
    };
    // Reverse BFS to find path.
    std::vector<std::vector<int>> map(MapHeight, std::vector<int>(std::vector<int>(MapWidth, -1)));
    std::queue<Engine::Point> que;
    Engine::Point p, np;
    // Push end point.
    // BFS from end point.
    if (mapState[endPoint.x][endPoint.y] != Engine::TILE_DIRT) {
        mapDistance = std::move(map);
        return;
    }
    que.push(endPoint);
    map[endPoint.x][endPoint.y] = 0;
    while (!que.empty()) {
        p = que.front();
        que.pop();
        for (int i = 0; i < 8; ++i) {
            np = p + directions[i];
            if (np.x < 0 || np.x >= MapWidth ||
                np.y < 0 || np.y >= MapHeight)
                continue;
            if (mapState[np.y][np.x] != Engine::TILE_DIRT ||
                map[np.y][np.x] != -1)
                continue;
            map[np.y][np.x] = map[p.y][p.x] + 1;
            que.push(np);
        }
    }
    Engine::LOG(Engine::INFO) << "Map distance";
    for (int i = 0; i < MapHeight; ++i) {
        for (int j = 0; j < MapWidth; ++j) {
            printf("%2d ", map[i][j]);
        }
        std::cout << std::endl;
    }
    mapDistance = std::move(map);
}
