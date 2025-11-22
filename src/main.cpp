#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#import "map"
#import <vector>
#include "./../config/config.h"

using namespace std;

//Structures
enum class GameState {
    MAIN_MENU,
    HELP_MENU,
    LOAD_SCREEN_1,
    LOAD_SCREEN_2,
    GAME_PROCESS,
    GAME_END
};

struct Knyaz {
    sf::RectangleShape body;
    bool isMovingLeft = false;
    bool isMovingRight = false;
};

struct MainMenu {
    sf::Text startText;
    sf::Rect<float> startTextInfo;
    sf::Text settingsText;
    sf::Rect<float> settingsTextInfo;
    sf::Text exitText;
    sf::Rect<float> exitTextInfo;
};
//

//names
using SettingsMenu = vector<sf::Text>;
//

//localConstants
const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
const unsigned int SCREEN_WIDTH = desktopMode.width;
const unsigned int SCREEN_HEIGHT = desktopMode.height;
//

//MainMenu
sf::Texture MainMenuTexture;
MainMenu getMainMenu();
void MainMenuMouseClickHandler(const sf::Event& event);
void MainMenuEventsHandler(const sf::Event& event);
//

//HelpMenu
sf::Texture HelpMenuTexture;
vector<sf::Text> getSettingsMenu();
void HelpMenuKeyHandler();
void HelpMenuEventsHandler(const sf::Event& event);
//

//LoadScreen
sf::Texture LoadScreenOneTexture;
sf::Texture LoadScreenTwoTexture;
void LoadScreenClickHandler();
void LoadScreenEventsHandler(const sf::Event& event);
//

//GameProcess
sf::Texture GameProcessTexture;
void GameProcessEventsHandler(const sf::Event& event);
//

//GameEnd
sf::Texture GameEndTexture;
void GameEndClickHandler();
void GameEndEventsHandler(const sf::Event& event);
//

//CommonViewElements
sf::Music GameMusic;
sf::Font myFont;
sf::Sprite BGSprite;
void initGameMusic();
void initFont();
void initBGTexture();
void getBGSprite();
void playGameMusic();
//

//Knyaz
Knyaz knyaz;
void knyazMove(const float& elapsedTime);
//

//CommonCommands
void initDepends();
void initVariables();
sf::RenderWindow getWindow();
sf::RectangleShape getKnyazBody();
sf::Text getText(const string& textContent);
void stateCheck(vector<sf::Text>& textToPrint);
//

//CommonUsedModels
map<string, string> config = initConfig();
map<string, sf::Keyboard::Scancode> keymap = getKeymap();
sf::RenderWindow window = getWindow();
GameState curState = GameState::MAIN_MENU;
SettingsMenu settingsMenu = getSettingsMenu();
sf::Clock globalTimer;
MainMenu mainMenu;
//

//SFML
void pollEvents ();
void update(vector<sf::Text>& textToPrint);
void redrawFrame(vector<sf::Text> textToPrint);
//

int main() {
    initDepends();
    initVariables();

    playGameMusic();

    vector<sf::Text> textToPrint;

    while (window.isOpen()) {
        pollEvents();
        update(textToPrint);
        redrawFrame(textToPrint);
    }
}

void initDepends() {
    initGameMusic();
    initFont();
    initBGTexture();
}

void update(vector<sf::Text>& textToPrint) {
    stateCheck(textToPrint);
    if (curState == GameState::GAME_PROCESS) {
        float elapsedTime = globalTimer.getElapsedTime().asSeconds();
        knyazMove(elapsedTime);
    }
}

void knyazMove(const float& elapsedTime) {
    if (!knyaz.isMovingRight && !knyaz.isMovingLeft) {
        globalTimer.restart();
        return;
    }

    constexpr int KNYAZ_MOVE_SPEED = 2.f;
    const float offset = KNYAZ_MOVE_SPEED * elapsedTime;
    sf::Vector2f knyazPosition = knyaz.body.getPosition();

    if (knyaz.isMovingLeft) {
        knyazPosition = {knyazPosition.x - offset, knyazPosition.y};
    } else {
        knyazPosition = {knyazPosition.x + offset, knyazPosition.y};
    }

    knyaz.body.setPosition(knyazPosition);
}

void redrawFrame(vector<sf::Text> textToPrint) {
    window.clear();
    window.draw(BGSprite);

    if (curState == GameState::MAIN_MENU || curState == GameState::HELP_MENU) {
        for (sf::Text& text : textToPrint) {
            window.draw(text);
        }
    } else if (curState == GameState::GAME_PROCESS) {
        window.draw(knyaz.body);
    }

    window.display();
}

void playGameMusic() {
    GameMusic.play();
}

void pollEvents () {
    sf::Event event{};
    while (window.pollEvent(event)) {

        switch (curState) {
            case GameState::MAIN_MENU:
                MainMenuEventsHandler(event);
                break;
            case GameState::HELP_MENU:
                HelpMenuEventsHandler(event);
                break;
            case GameState::LOAD_SCREEN_2:
                LoadScreenEventsHandler(event);
                break;
            case GameState::GAME_PROCESS:
                GameProcessEventsHandler(event);
                break;
            case GameState::GAME_END:
                GameEndEventsHandler(event);
                break;
        }
    }
}

void GameProcessEventsHandler(const sf::Event& event) {
    //TODO сейчас это просто проверка способности игры завершиться
    if (event.type == sf::Event::MouseButtonPressed) {
        curState = GameState::GAME_END;
        getBGSprite();
    }

    if (
        (sf::Keyboard::isKeyPressed(keymap["MOVE_LEFT_KEY"]) && !knyaz.isMovingLeft) ||
        (!sf::Keyboard::isKeyPressed(keymap["MOVE_LEFT_KEY"]) && knyaz.isMovingLeft)
    ) {
        knyaz.isMovingLeft = !knyaz.isMovingLeft;
    }

    if (
        (sf::Keyboard::isKeyPressed(keymap["MOVE_RIGHT_KEY"]) && !knyaz.isMovingRight) ||
        (!sf::Keyboard::isKeyPressed(keymap["MOVE_RIGHT_KEY"]) && knyaz.isMovingRight)
    ) {
        knyaz.isMovingRight = !knyaz.isMovingRight;
    }

    //TODO В будущем тут будет больше обработчиков кнопок Князя
}

void GameEndEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) {
        GameEndClickHandler();
    }
}

void LoadScreenEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) {
        LoadScreenClickHandler();
    }
}

void HelpMenuEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        HelpMenuKeyHandler();
    }
}

void MainMenuEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        MainMenuMouseClickHandler(event);
    }
}

void GameEndClickHandler() {
    curState = GameState::MAIN_MENU;
    getBGSprite();
}

void LoadScreenClickHandler() {
    globalTimer.restart();
    curState = GameState::GAME_PROCESS;
    getBGSprite();
}

void HelpMenuKeyHandler() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        curState = GameState::MAIN_MENU;
        getBGSprite();
    }
}

void MainMenuMouseClickHandler(const sf::Event& event) {
    const int eventX = event.mouseButton.x;
    const int eventY = event.mouseButton.y;

    auto checkButtonMatch = [eventX, eventY] (const sf::Rect<float> textInfo) -> bool {
        if (
            eventX >= textInfo.left &&
            eventX <= textInfo.left + textInfo.width &&
            eventY >= textInfo.top &&
            eventY <= textInfo.top + textInfo.height
        ) {
            return true;
        }
        return false;
    };

    if (checkButtonMatch(mainMenu.startTextInfo)) {
        globalTimer.restart();
        curState = GameState::LOAD_SCREEN_1;
        getBGSprite();
    } else if (checkButtonMatch(mainMenu.settingsTextInfo)) {
        curState = GameState::HELP_MENU;
        getBGSprite();
    } else if (checkButtonMatch(mainMenu.exitTextInfo)) {
        window.close();
    }
}

void stateCheck(vector<sf::Text>& textToPrint) {
    constexpr float LOADING_DURATION = 5.f;
    switch (curState) {
        case GameState::MAIN_MENU:
            textToPrint = {mainMenu.startText, mainMenu.settingsText, mainMenu.exitText};
            break;
        case GameState::HELP_MENU:
            textToPrint = settingsMenu;
            break;
        case GameState::LOAD_SCREEN_1:
            if (globalTimer.getElapsedTime().asSeconds() >= LOADING_DURATION) {
                curState = GameState::LOAD_SCREEN_2;
                getBGSprite();
            }
            break;
    }
}

MainMenu getMainMenu() {
    const int Y_OFFSET = 25;

    const auto getXPosition = [] (sf::Rect<float> textInfo) -> float {
        return SCREEN_WIDTH/2 - textInfo.width/2;
    };

    sf::Text startText = getText("start");
    sf::Text settingsText = getText("help");
    sf::Text exitText = getText("exit");

    sf::Rect<float> settingsTextInfo = settingsText.getLocalBounds();
    settingsText.setPosition(getXPosition(settingsTextInfo), SCREEN_HEIGHT/2 - settingsTextInfo.height/2);
    settingsTextInfo = settingsText.getGlobalBounds();

    sf::Rect<float> startTextInfo = startText.getGlobalBounds();
    startText.setPosition(getXPosition(startTextInfo), settingsTextInfo.top - startTextInfo.height - Y_OFFSET);
    startTextInfo = startText.getGlobalBounds();

    sf::Rect<float> exitTextInfo = exitText.getGlobalBounds();
    exitText.setPosition(getXPosition(exitTextInfo), settingsTextInfo.top + settingsTextInfo.height + Y_OFFSET);
    exitTextInfo = exitText.getGlobalBounds();

    return {
        startText,
        startTextInfo,
        settingsText,
        settingsTextInfo,
        exitText,
        exitTextInfo
    };
}

vector<sf::Text> getSettingsMenu() {
    vector<sf::Text> texts;

    const map<string, string> controlKeys = {
        {"left moving", config["MOVE_LEFT_KEY"]},
        {"right moving", config["MOVE_RIGHT_KEY"]},
        {"jump", config["JUMP_KEY"]},
        {"rage", config["RAGE_KEY"]},
        {"focus", config["FOCUS_KEY"]},
        {"light attack", config["LIGHT_ATTACK_KEY"]},
        {"heavy attack", config["HEAVY_ATTACK_KEY"]},
    };

    const float SETTING_X_POS = SCREEN_WIDTH / 5;
    const float KEY_X_POS = SETTING_X_POS * 3.5;

    const int BASE_OFFSET = 60;
    float iter = 0.f;

    for (const auto& [key, value] : controlKeys) {
        sf::Text keyText = getText(key);
        keyText.setPosition(SETTING_X_POS, iter * 100 + BASE_OFFSET);

        sf::Text valueText = getText(value);
        valueText.setPosition(KEY_X_POS, iter * 100 + BASE_OFFSET);

        texts.push_back(keyText);
        texts.push_back(valueText);

        iter++;
    }
    return texts;
}

sf::Text getText(const string& textContent) {
    const int CHARACTER_SIZE = 65;
    const float OUTLINE_THICKNESS = 1.5;
    const sf::Color TEXT_COLOR = {0xFB, 0x2E, 0x00};
    const sf::Vector2f BASE_POSITION = {0, 0};

    sf::Text myTxt;
    myTxt.setPosition(BASE_POSITION);
    myTxt.setFont(myFont);
    myTxt.setFillColor(TEXT_COLOR);
    myTxt.setString(textContent);
    myTxt.setOutlineThickness(OUTLINE_THICKNESS);
    myTxt.setOutlineColor(sf::Color::Black);
    myTxt.setCharacterSize(CHARACTER_SIZE);
    return myTxt;
}

void getBGSprite() {
    switch (curState) {
        case (GameState::MAIN_MENU):
            BGSprite = sf::Sprite(MainMenuTexture);
            break;
        case (GameState::HELP_MENU):
            BGSprite = sf::Sprite(HelpMenuTexture);
            break;
        case (GameState::LOAD_SCREEN_1):
            BGSprite = sf::Sprite(LoadScreenOneTexture);
            break;
        case (GameState::LOAD_SCREEN_2):
            BGSprite = sf::Sprite(LoadScreenTwoTexture);
            break;
        case (GameState::GAME_PROCESS):
            BGSprite = sf::Sprite(GameProcessTexture);
            break;
        case (GameState::GAME_END):
            BGSprite = sf::Sprite(GameEndTexture);
            break;
    }
}

sf::RenderWindow getWindow() {
    return {
        sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}),
        config["GAME_NAME"]
    };
}

void initBGTexture() {
    MainMenuTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["MAIN_MENU_BG"]);
    HelpMenuTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["HELP_MENU_BG"]);
    LoadScreenOneTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["LOAD_SCREEN_BG_FIRST"]);
    LoadScreenTwoTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["LOAD_SCREEN_BG_SECOND"]);
    GameProcessTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["GAME_PROCESS_BG"]);
    GameEndTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["GAME_END_BG"]);
}

sf::RectangleShape getKnyazBody() {
    sf::RectangleShape knyazBody({(float)SCREEN_WIDTH/15, (float)SCREEN_HEIGHT/10});
    knyazBody.setPosition({(float)SCREEN_WIDTH/20, (float)SCREEN_HEIGHT/25 * 18});
    knyazBody.setFillColor(sf::Color::Black);
    return knyazBody;
}

void initFont() {
    myFont.loadFromFile(config["FONT_PATH"]);
}

void initGameMusic() {
    GameMusic.openFromFile(config["MUSIC_FOLDER"] + config["GAME_MUSIC_FILE"]);
    GameMusic.setVolume(5);
    GameMusic.setLoop(true);
}

void initVariables() {
    knyaz.body = getKnyazBody();
    getBGSprite();
    mainMenu = getMainMenu();
}