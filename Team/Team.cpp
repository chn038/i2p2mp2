#include <queue>
#include "Engine/LOG.hpp"
#include "Engine/GameEngine.hpp"
#include "Scene/PlayScene.hpp"
#include "Team/Team.hpp"
#include "Enemy/Enemy.hpp"
#include "Tower/Tower1.hpp"
#include "Tower/Tower2.hpp"
#include "Tower/Tower3.hpp"
#include "Tower/Tower4.hpp"
#include "Tower/Tower5.hpp"

Team::~Team() {
    Terminate();
}

Team::Team(Engine::Point startPoint, Engine::Point endPoint, int ID, int initLives, int initMoney):
    ID(ID),
    opponent(nullptr),
    damageOffset(0),
    lives(initLives),
    money(initMoney),
    startPoint(startPoint),
    endPoint(endPoint) {
    Initialize();
}

void Team::Initialize() {
    AddNewObject(TowerGroup = new Group());
    AddNewObject(GroundGroup = new Group());
    AddNewObject(FlyGroup = new Group());
    UpdatePath();
}

void Team::Terminate() {
    Group::Clear();
}

void Team::Update(float deltaTime) {
    Group::Update(deltaTime);
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

Team* Team::GetOpponent() {
    return opponent;
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
            newTurret = new Tower1(x, y, this);
            break;
        case 2:
            newTurret = new Tower2(x, y, this);
            break;
        case 3:
            newTurret = new Tower3(x, y, this);
            break;
        case 4:
            newTurret = new Tower4(x, y, this);
            break;
        case 5:
            newTurret = new Tower5(x, y, this);
            break;
        default:
            break;
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

std::vector<std::vector<int>> Team::UpdateDistance(bool isGround) {
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
    if (isGround) {
        if (mapState[endPoint.x][endPoint.y] != Engine::TILE_DIRT) {
            return map;
        }
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
            if (map[np.y][np.x] != -1)
                continue;
            if (isGround && mapState[np.y][np.x] != Engine::TILE_DIRT)
                continue;
            map[np.y][np.x] = map[p.y][p.x] + 1;
            que.push(np);
        }
    }
    return map;
}

void Team::Hit() {
    lives -= 1;
}

void Team::UpdatePath() {
    flyMap = UpdateDistance(0);
    groundMap = UpdateDistance(1);
}
