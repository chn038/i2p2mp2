#include <fstream>
#include "Scene/PlayScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Turret/TurretButton.hpp"
#include "UI/Component/Image.hpp"
#include "Engine/Resources.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/LOG.hpp"

bool PlayScene::DebugMode = false;
const int PlayScene::BlockSize = 64;
const int PlayScene::MapWidth = 20;
const int PlayScene::MapHeight = 15;

void PlayScene::Initialize() {
	mapState.clear();
    originMap.clear();
	keyStrokes.clear();
	ticks = 0;
	SpeedMult = 1;
    // set the score to 0
    Engine::GameEngine::GetInstance().GetScore() = 0;
	// Add groups from bottom to top.
	AddNewObject(TileMapGroup = new Group());
	AddNewObject(GroundEffectGroup = new Group());
	AddNewObject(DebugIndicatorGroup = new Group());
	AddNewObject(BulletGroup = new Group());
	AddNewObject(EffectGroup = new Group());
	// Should support buttons.
	AddNewControlObject(UIGroup = new Group());
	ReadMap();
    // Team initialize
    AddNewObject(teamPlayer = new Team(spawnPointA, spawnPointB, 0));
    AddNewObject(teamEnemy = new Team(spawnPointB, spawnPointA, 1));
    teamPlayer->SetOpponent(teamEnemy);
    teamEnemy->SetOpponent(teamPlayer);
	ReadEnemyWave();
	ConstructUI();
	imgTarget = new Engine::Image("play/target.png", 0, 0);
	imgTarget->Visible = false;
	preview = nullptr;
	UIGroup->AddNewObject(imgTarget);
	// Preload Scene
	Engine::Resources::GetInstance().GetBitmap("lose/benjamin-happy.png");
	Engine::Resources::GetInstance().GetBitmap("win/benjamin-sad.png");
	// Start BGM.
	bgmId = AudioHelper::PlayBGM("play.ogg");
}

void PlayScene::Draw() const {
    IScene::Draw();
}

void PlayScene::Update(float deltaTime) {
    IScene::Update(deltaTime);

    if (teamEnemy->lives <= 0) {
		Engine::GameEngine::GetInstance().ChangeScene("win");
        return;
    }
    if (teamPlayer->lives <= 0) {
        Engine::GameEngine::GetInstance().ChangeScene("lose");
        return;
    }

    if (enemyWave.empty()) return;
    Wave& current = enemyWave.front();
    ticks += deltaTime;
    if (ticks < current.time) return;
    ticks -= current.time;
    float objx = current.pos.x * BlockSize + BlockSize / 2.0;
    float objy = current.pos.y * BlockSize + BlockSize / 2.0;
    teamEnemy->addTower(objx, objy, current.type);
    enemyWave.pop();
}

void PlayScene::Terminate() {
    AudioHelper::StopBGM(bgmId);
    IScene::Terminate();
}

void PlayScene::Hit(int id) {
    switch(id) {
        case 0:
            teamEnemy->Hit();
            return;
        case 1:
            teamPlayer->Hit();
            // maybe a warning here?
            return;
    }
}

int PlayScene::GetMoney() const {
    return teamPlayer->money;
}

void PlayScene::EarnMoney(int val, int ID) {
    if (ID == 0) 
        return;
    teamPlayer->money += val;
}

void PlayScene::ConstructUI() {
    int startX = MapWidth * BlockSize;
    int gap = 20;
    int size = 40;
    int SWidth = Engine::GameEngine::GetInstance().GetScreenWidth();
    int SHeight = Engine::GameEngine::GetInstance().GetScreenHeight();
    // Background
    UIGroup->AddNewObject(
        new Engine::Image("play/sand.png", 
                          startX, 0, SWidth - startX, SHeight));


}

void PlayScene::ReadMap() {
    int i = 0, j = 0;
    std::string filename = std::string("Resource/map.txt");
    char c;
    std::vector<bool> mapData;
    std::ifstream fin(filename);
    while (fin >> c) {
        switch (c) {
            case '0':
                mapData.push_back(false);
                j++;
                break;
            case '1':
                mapData.push_back(true);
                j++;
                break;
            case '2':
                spawnPointA = Engine::Point(i, j);
                mapData.push_back(true);
                j++;
                break;
            case '3':
                spawnPointB = Engine::Point(i, j);
                mapData.push_back(true);
                j++;
                break;
            case '\n':
            case '\r':
                if (j != MapWidth)
                    throw std::ios_base::failure("Map data is corrupted.");
                i++;
                j = 0;
                break;
            default:
                throw std::ios_base::failure("Map data is corrupted.");
        }
    }
    fin.close();
    if (static_cast<int>(mapData.size()) != MapWidth * MapHeight)
        throw std::ios_base::failure("Error reading map data");
    originMap = std::vector<std::vector<Engine::TileType>>(MapHeight, std::vector<Engine::TileType>(MapWidth));
    for (int h = 0; h < MapHeight; ++h) {
        for (int w = 0; w < MapWidth; ++w) {
            bool type = mapData[h * MapWidth + w];
            mapState[h][w] = type ? Engine::TILE_FLOOR : Engine::TILE_DIRT;
			if (type)
				TileMapGroup->AddNewObject(new Engine::Image("play/floor.png", w * BlockSize, h * BlockSize, BlockSize, BlockSize));
			else
				TileMapGroup->AddNewObject(new Engine::Image("play/dirt.png", w * BlockSize, h * BlockSize, BlockSize, BlockSize));
        }
    }
    mapState = originMap;
}

void PlayScene::ReadEnemyWave() {
    std::string filename = std::string("Resource/enemy") + std::to_string(MapId) + ".txt";
	// Read enemy file.
    // time type posx posy
    while (!enemyWave.empty()) {
        enemyWave.pop();
    }
	std::ifstream fin(filename);
    int time, type, posx, posy;
	while (fin >> time && fin >> type && fin >> posx && fin >> posy) {
        enemyWave.emplace(time, type, Engine::Point(posx, posy));
	}
    Engine::LOG(Engine::INFO) << "Total wave size " << enemyWave.size();
	fin.close();
}
