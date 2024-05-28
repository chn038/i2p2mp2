#include <allegro5/allegro.h>
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <vector>
#include <string>

#include "Engine/GameEngine.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/LOG.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "ScoreScene.hpp"
#include "Engine/Point.hpp"

static std::fstream file;
static std::vector<ScoreScene::Score> pages;
static std::string input;
static int maxPage;
static int currentPage;
Engine::Label* scoreLabel[8][2];
static Engine::Label *inputLabel;
static Engine::ImageButton *nextButton;
static Engine::ImageButton *prevButton;

// used to mimic input
static bool isShiftPressed;

/// Manually invoke this function to refresh the scoreLabel
static void UpdateDisplay(); 
/// Insert a new record and sort the whole record
static void InsertInput();
/// Parse the scoreboard file into vector "pages"
static void ParseFile();

void ScoreScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    pages.clear();
    input = "";
    maxPage = 1;
    currentPage = 0;
    isShiftPressed = false;
    // initialize the ui
    AddNewObject(new Engine::Label("ScoreBoard", "pirulen.ttf", 48, halfW, halfH / 4.0 + 10, 255, 255, 255, 255, 0.5, 0.5));

    Engine::ImageButton *btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7.0 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&ScoreScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7.0 / 4, 0, 0, 0, 255, 0.5, 0.5));

	prevButton = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 700, halfH * 7.0 / 4 - 50, 400, 100);
	prevButton->SetOnClickCallback(std::bind(&ScoreScene::PrevOnClick, this, 2));
    AddNewControlObject(prevButton);
    AddNewObject(new Engine::Label("Prev", "pirulen.ttf", 48, halfW - 500, halfH * 7.0 / 4, 255, 255, 255, 255, 0.5, 0.5));
    prevButton->Enabled = false;

	nextButton = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW + 300, halfH * 7.0 / 4 - 50, 400, 100);
	nextButton->SetOnClickCallback(std::bind(&ScoreScene::NextOnClick, this, 2));
    AddNewControlObject(nextButton);
	AddNewObject(new Engine::Label("Next", "pirulen.ttf", 48, halfW + 500, halfH * 7.0 / 4, 255, 255, 255, 255, 0.5, 0.5));
    nextButton->Enabled = false;

    if (Engine::GameEngine::GetInstance().GetScore() != 0 || Engine::GameEngine::GetInstance().GetAssignNew()) {
        AddNewObject(new Engine::Label("Score: " + std::to_string(Engine::GameEngine::GetInstance().GetScore()), "pirulen.ttf", 48, 0.1 * halfW, halfH - 200, 255, 255, 255, 255, 0, 0.5));
    }

    if (Engine::GameEngine::GetInstance().GetAssignNew()) {
        Engine::LOG(Engine::INFO) << "Assigning new record";
        inputLabel = new Engine::Label("Name: " + input, "pirulen.ttf", 48, halfW, halfH - 200 , 255, 255, 255, 255, 0, 0.5);
        AddNewObject(inputLabel);
    } else {
        inputLabel = nullptr;
    }

    for (int i = 0; i < 8; ++i) {
        scoreLabel[i][0] = new Engine::Label("", "pirulen.ttf", 48, halfW - 700, halfH - 100 + 40*i, 255, 255, 255, 255, 0, 0.5);
        scoreLabel[i][1] = new Engine::Label("", "pirulen.ttf", 48, halfW + 700, halfH - 100 + 40*i, 255, 255, 255, 255, 1, 0.5);
        AddNewObject(scoreLabel[i][0]);
        AddNewObject(scoreLabel[i][1]);
    }
    
    ParseFile();
	bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);

}

void ScoreScene::Terminate() {
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    file.open("Resource/scoreboard.txt", std::fstream::out | std::fstream::trunc);
    for (int i = 0; i < pages.size(); ++i) {
        file << pages[i].name << ' ' << pages[i].score << '\n';
    }
    file.close();
    pages.clear();
    Engine::GameEngine::GetInstance().GetScore() = 0;
    Engine::GameEngine::GetInstance().GetAssignNew() = false;
	IScene::Terminate();
}

void ScoreScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void ScoreScene::PrevOnClick(int stage) {
    if (currentPage == 0) return;
    currentPage -= 1;
    if (currentPage == maxPage - 1) nextButton->Enabled = false;
    else nextButton->Enabled = true;
    if (currentPage == 0) prevButton->Enabled = false;
    else prevButton->Enabled = true;
    UpdateDisplay();
}

void ScoreScene::NextOnClick(int stage) {
    if (currentPage == maxPage - 1) return;
    currentPage += 1;
    if (currentPage == 0) prevButton->Enabled = false;
    else prevButton->Enabled = true;
    if (currentPage == maxPage - 1) nextButton->Enabled = false;
    else nextButton->Enabled = true;
    UpdateDisplay();
}

static void ParseFile() {
    // read from file
    file.open("Resource/scoreboard.txt", std::fstream::in);
    if (file.good() == false) {
        Engine::LOG(Engine::ERROR) << "Can't open scoreboard file.";
        Engine::GameEngine::GetInstance().ChangeScene("stage-select");
    }
    int tmpScore;
    std::string tmp;
    while (file >> tmp, !file.eof()) {
        file >> tmpScore;
        pages.push_back(ScoreScene::Score(tmp, tmpScore));
    }
    file.close();
    maxPage = pages.size() / 8;
    if (pages.size() % 8) maxPage += 1;
    if (currentPage < maxPage - 1) nextButton->Enabled = true;
    UpdateDisplay();
}

static void UpdateDisplay() {
    for (int i = 0; i < 8; ++i) {
        if (currentPage*8 + i >= pages.size()) {
            scoreLabel[i][0]->Text = "";
            scoreLabel[i][1]->Text = "";
        } else {
            scoreLabel[i][0]->Text = pages[currentPage*8 + i].name;
            scoreLabel[i][1]->Text = std::to_string(pages[currentPage*8 + i].score);
        }
    }
}

static void InsertInput() {
    pages.push_back(ScoreScene::Score(input, Engine::GameEngine::GetInstance().GetScore()));
    std::sort(pages.begin(), pages.end(), 
              [] (const ScoreScene::Score& a, const ScoreScene::Score& b) {
                return a.score > b.score;
              });
    maxPage = pages.size() / 8;
    if (pages.size() % 8) maxPage += 1;
    if (currentPage >= maxPage - 1) {
        currentPage = maxPage - 1;
        nextButton->Enabled = false;
    }
    UpdateDisplay();
    input = "";
    inputLabel->Text = "Name: " + input;
    Engine::GameEngine::GetInstance().GetAssignNew() = false;
}

void ScoreScene::OnKeyUp(int keycode) {
    IScene::OnKeyUp(keycode);
    if (!Engine::GameEngine::GetInstance().GetAssignNew()) return;
    if (keycode == ALLEGRO_KEYMOD_SHIFT || keycode == ALLEGRO_KEY_LSHIFT || keycode == ALLEGRO_KEY_RSHIFT) {
        isShiftPressed = false;
    }
}

void ScoreScene::OnKeyDown(int keycode) {
    IScene::OnKeyDown(keycode);
    if (!Engine::GameEngine::GetInstance().GetAssignNew()) return;
    // mimic input
    switch (keycode) {
        case ALLEGRO_KEY_LSHIFT:
        case ALLEGRO_KEY_RSHIFT:
            isShiftPressed = true;
            break;
        case ALLEGRO_KEY_ENTER:
            InsertInput();
            break;
        case ALLEGRO_KEY_BACKSPACE:
            if (input.size())
                input.erase(std::prev(input.end()));
            break;
        case ALLEGRO_KEY_A:
            if (input.size() <= 12)
                input += (isShiftPressed)? "A" : "a";
            break;
        case ALLEGRO_KEY_B:
            if (input.size() <= 12)
                input += (isShiftPressed)? "B" : "b";
            break;
        case ALLEGRO_KEY_C:
            if (input.size() <= 12)
                input += (isShiftPressed)? "C" : "c";
            break;
        case ALLEGRO_KEY_D:
            if (input.size() <= 12)
                input += (isShiftPressed)? "D" : "d";
            break;
        case ALLEGRO_KEY_E:
            if (input.size() <= 12)
                input += (isShiftPressed)? "E" : "e";
            break;
        case ALLEGRO_KEY_F:
            if (input.size() <= 12)
                input += (isShiftPressed)? "F" : "f";
            break;
        case ALLEGRO_KEY_G:
            if (input.size() <= 12)
                input += (isShiftPressed)? "G" : "g";
            break;
        case ALLEGRO_KEY_H:
            if (input.size() <= 12)
                input += (isShiftPressed)? "H" : "h";
            break;
        case ALLEGRO_KEY_I:
            if (input.size() <= 12)
                input += (isShiftPressed)? "I" : "i";
            break;
        case ALLEGRO_KEY_J:
            if (input.size() <= 12)
                input += (isShiftPressed)? "J" : "j";
            break;
        case ALLEGRO_KEY_K:
            if (input.size() <= 12)
                input += (isShiftPressed)? "K" : "k";
            break;
        case ALLEGRO_KEY_L:
            if (input.size() <= 12)
                input += (isShiftPressed)? "L" : "l";
            break;
        case ALLEGRO_KEY_M:
            if (input.size() <= 12)
                input += (isShiftPressed)? "M" : "m";
            break;
        case ALLEGRO_KEY_N:
            if (input.size() <= 12)
                input += (isShiftPressed)? "N" : "n";
            break;
        case ALLEGRO_KEY_O:
            if (input.size() <= 12)
                input += (isShiftPressed)? "O" : "o";
            break;
        case ALLEGRO_KEY_P:
            if (input.size() <= 12)
                input += (isShiftPressed)? "P" : "p";
            break;
        case ALLEGRO_KEY_Q:
            if (input.size() <= 12)
                input += (isShiftPressed)? "Q" : "q";
            break;
        case ALLEGRO_KEY_R:
            if (input.size() <= 12)
                input += (isShiftPressed)? "R" : "r";
            break;
        case ALLEGRO_KEY_S:
            if (input.size() <= 12)
                input += (isShiftPressed)? "S" : "s";
            break;
        case ALLEGRO_KEY_T:
            if (input.size() <= 12)
                input += (isShiftPressed)? "T" : "t";
            break;
        case ALLEGRO_KEY_U:
            if (input.size() <= 12)
                input += (isShiftPressed)? "U" : "u";
            break;
        case ALLEGRO_KEY_V:
            if (input.size() <= 12)
                input += (isShiftPressed)? "V" : "v";
            break;
        case ALLEGRO_KEY_W:
            if (input.size() <= 12)
                input += (isShiftPressed)? "W" : "w";
            break;
        case ALLEGRO_KEY_X:
            if (input.size() <= 12)
                input += (isShiftPressed)? "X" : "x";
            break;
        case ALLEGRO_KEY_Y:
            if (input.size() <= 12)
                input += (isShiftPressed)? "Y" : "y";
            break;
        case ALLEGRO_KEY_Z:
            if (input.size() <= 12)
                input += (isShiftPressed)? "Z" : "z";
            break;
        case ALLEGRO_KEY_0:
            if (input.size() <= 12)
                input += (isShiftPressed)? ")" : "0";
            break;
        case ALLEGRO_KEY_1:
            if (input.size() <= 12)
                input += (isShiftPressed)? "!" : "1";
            break;
        case ALLEGRO_KEY_2:
            if (input.size() <= 12)
                input += (isShiftPressed)? "@" : "2";
            break;
        case ALLEGRO_KEY_3:
            if (input.size() <= 12)
                input += (isShiftPressed)? "#" : "3";
            break;
        case ALLEGRO_KEY_4:
            if (input.size() <= 12)
                input += (isShiftPressed)? "$" : "4";
            break;
        case ALLEGRO_KEY_5:
            if (input.size() <= 12)
                input += (isShiftPressed)? "%" : "5";
            break;
        case ALLEGRO_KEY_6:
            if (input.size() <= 12)
                input += (isShiftPressed)? "^" : "6";
            break;
        case ALLEGRO_KEY_7:
            if (input.size() <= 12)
                input += (isShiftPressed)? "&" : "7";
            break;
        case ALLEGRO_KEY_8:
            if (input.size() <= 12)
                input += (isShiftPressed)? "*" : "8";
            break;
        case ALLEGRO_KEY_9:
            if (input.size() <= 12)
                input += (isShiftPressed)? "(" : "9";
            break;
        case ALLEGRO_KEY_MINUS:
            if (input.size() <= 12)
                input += (isShiftPressed)? "_" : "-";
            break;
        case ALLEGRO_KEY_EQUALS:
            if (input.size() <= 12)
                input += (isShiftPressed)? "+" : "=";
            break;
    }
    inputLabel->Text = "Name: " + input;
}
