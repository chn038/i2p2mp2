#include "Engine/GameEngine.hpp"
#include <queue>
#include "Engine/LOG.hpp"
#include "Scene/PlayScene.hpp"
#include "Team/Team.hpp"
#include "Enemy/Enemy.hpp"
#include "Turret/Turret.hpp"

Team::~Team() {
    Terminate();
}

Team::Team(Engine::Point startPoint, Engine::Point endPoint, Team* opponent, int initLives, int initMoney, int spawnPeriod):
    opponent(opponent),
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
    }
    if (spawnCD > shiftSec) {
        for (int i = 0; i < waveData[startSpawn]; ++i) {
            SpawnInstances(startSpawn);
        }
        spawnCD -= shiftSec;
        startSpawn += 1;
        if (startSpawn >= instanceTypes) startSpawn = -1;
    }
}

void Team::SpawnInstances(int type) {
    if (spawnCD < shiftSec)
        return;
    spawnCD -= shiftSec;
    Enemy *enemy;
    switch (type) {
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
    enemy->Update(spawnCD);
}

void Team::addTower(int x, int y, int type) {
    Turret *newTurret;
    // This should add new things to waveData
    switch(type) {
    }
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
    static const Engine::Point directions[8] = {
        Engine::Point(-1, -1), Engine::Point(0, -1), Engine::Point(1, -1),
        Engine::Point(-1, 0), Engine::Point(1, 0),
        Engine::Point(-1, 1), Engine::Point(0, 1), Engine::Point(1, 1),
    };
    PlayScene* scene = getPlayScene();
    std::vector<std::vector<Engine::TileType>>& mapState = getMapState();
    int MapWidth = scene->MapWidth;
    int MapHeight = scene->MapHeight;

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
