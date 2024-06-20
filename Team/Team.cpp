#include <queue>
#include "Engine/LOG.hpp"
#include "Engine/GameEngine.hpp"
#include "Scene/PlayScene.hpp"
#include "Team/Team.hpp"
#include "Enemy/Enemy.hpp"
#include "Tower/Tower.hpp"

Team::~Team() {
    Terminate();
}

Team::Team(Engine::Point startPoint, Engine::Point endPoint, int ID, int initLives, int initMoney, int spawnPeriod):
    ID(ID),
    opponent(nullptr),
    damageOffset(0),
    lives(initLives),
    money(initMoney),
    spawnCD(spawnPeriod),
    spawnPeriod(spawnPeriod),
    startPoint(startPoint),
    endPoint(endPoint) {
    Initialize();
}

void Team::Initialize() {
    AddNewObject(TowerGroup = new Group());
    AddNewObject(InstanceGroup = new Group());
    waveData.clear();
    waveData.resize(instanceTypes, 0);
    startSpawn = -1;
    UpdateDistance();
}

void Team::Terminate() {
    Group::Clear();
}

void Team::Update(float deltaTime) {
    spawnCD += deltaTime;
    Group::Update(deltaTime);
    if (startSpawn == -1) {
        if (spawnCD < spawnPeriod) {
            return;
        }
        spawnCD -= spawnPeriod;
        startSpawn = 0;
        spawnCount = 0;
    }

    if (spawnCD < shiftSec) 
        return;

    SpawnInstances(startSpawn);
    spawnCD -= shiftSec;
    spawnCount += 1;
    if (spawnCount == waveData[startSpawn]) {
        startSpawn += 1;
        spawnCount = 0;
    }
    if (startSpawn >= instanceTypes) startSpawn = -1;
}

int Team::getCountDown() {
    if (startSpawn != -1) return 0;
    return spawnPeriod - spawnCD;
}

void Team::SetOpponent(Team *oppo) {
    if (oppo == nullptr) {
        Engine::LOG(Engine::ERROR) << "No opponent in team " << ID;
        return;
    }
    if (opponent) {
        Engine::LOG(Engine::WARN) << "Reassigning opponent of team " << ID;
    }
    opponent = oppo;
}

void Team::SpawnInstances(int type) {
    Enemy *enemy;
    const int BlockSize = getPlayScene()->BlockSize;
    const Engine::Point SpawnCoordinate = Engine::Point(startPoint.x * BlockSize + BlockSize / 2.0, startPoint.y * BlockSize + BlockSize / 2.0);
    switch (type) {
        case 0:
            enemy = new Enemy1(SpawnCoordinate.x, SpawnCoordinate.y, ID);
            break;
        case 1:
            enemy = new Enemy2(SpawnCoordinate.x, SpawnCoordinate.y, ID);
            break;
        case 2:
            enemy = new Enemy3(SpawnCoordinate.x, SpawnCoordinate.y, ID);
            break;
        case 3:
            enemy = new Enemy4(SpawnCoordinate.x, SpawnCoordinate.y, ID);
            break;
        case 4:
            enemy = new Enemy5(SpawnCoordinate.x, SpawnCoordinate.y, ID);
            break;
        case 5:
            enemy = new Enemy6(SpawnCoordinate.x, SpawnCoordinate.y, ID);
            break;
        default:
            break;
    }
    enemy->UpdatePath(mapDistance, endPoint);
    // Maybe update here
    enemy->Update(spawnCD);
}

void Team::addTower(int x, int y, int type) {
    Tower *newTurret;
    if (opponent == nullptr) {
        Engine::LOG(Engine::ERROR) << "No opponent in team " << ID;
        return;
    }
    // This should add new things to waveData
    switch(type) {
        case 1:
            newTurret = new Tower1(x, y, opponent->InstanceGroup->GetObjects());
            waveData[0] += 1;
            break;
        case 2:
            newTurret = new Tower2(x, y, opponent->InstanceGroup->GetObjects());
            waveData[1] += 1;
            break;
        case 3:
            newTurret = new Tower3(x, y, opponent->InstanceGroup->GetObjects());
            waveData[0] += 1;
            waveData[2] += 1;
            break;
        case 4:
            newTurret = new Tower4(x, y, opponent->InstanceGroup->GetObjects());
            waveData[1] += 1;
            waveData[3] += 1;
            break;
        case 5:
            newTurret = new Tower5(x, y, opponent->InstanceGroup->GetObjects());
            waveData[4] += 1;
            waveData[5] += 1;
            break;
        default:
            break;
    }
    UpdateDistance();
    TowerGroup->AddNewObject(static_cast<Engine::IObject*>(newTurret));
}

bool Team::deleteTower(int x, int y) {
    for (auto &it: TowerGroup->GetObjects()) {
        if (it.second->Position.x == x && it.second->Position.y == y) {
            TowerGroup->RemoveObject(it.second->GetObjectIterator());
            return true;
        }
    }
    return false;
}

PlayScene* Team::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

std::vector<std::vector<Engine::TileType>>& Team::getMapState() {
    return getPlayScene()->mapState;
}

void Team::UpdateDistance() {
    static const Engine::Point directions[4] = { Engine::Point(0, -1), Engine::Point(-1, 0), Engine::Point(1, 0), Engine::Point(0, 1) };
    std::vector<std::vector<Engine::TileType>>& mapState = getMapState();
    const int MapWidth = getPlayScene()->MapWidth;
    const int MapHeight = getPlayScene()->MapHeight;

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
        for (int i = 0; i < 4; ++i) {
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
    mapDistance = std::move(map);
}

void Team::Hit() {
    lives -= 1;
}
