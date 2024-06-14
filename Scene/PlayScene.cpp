#include <fstream>
#include "Scene/PlayScene.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "Engine/Resources.hpp"
#include "Engine/AudioHelper.hpp"

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
    AddNewObject(teamA = new Team(spawnPointA, spawnPointB, 0));
    AddNewObject(teamB = new Team(spawnPointB, spawnPointA, 1));
    teamA->SetOpponent(teamB);
    teamB->SetOpponent(teamA);
	//ReadEnemyWave();
	ConstructUI();
	imgTarget = new Engine::Image("play/target.png", 0, 0);
	imgTarget->Visible = false;
	preview = nullptr;
	UIGroup->AddNewObject(imgTarget);
	// Preload Lose Scene
	Engine::Resources::GetInstance().GetBitmap("lose/benjamin-happy.png");
	// Start BGM.
	bgmId = AudioHelper::PlayBGM("play.ogg");
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
