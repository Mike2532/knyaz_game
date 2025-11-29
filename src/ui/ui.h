#ifndef KNYAZ_GAME_UI_H
#define KNYAZ_GAME_UI_H

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../types.h"

sf::Text getText(const std::string& textContent);

MainMenu getMainMenu();
std::vector<sf::Text> getSettingsMenu();

void MainMenuMouseClickHandler(const sf::Event& event);
void MainMenuEventsHandler(const sf::Event& event);
void HelpMenuKeyHandler();
void HelpMenuEventsHandler(const sf::Event& event);
void LoadScreenEventsHandler(const sf::Event& event);
void LoadScreenClickHandler();
void GameEndEventsHandler(const sf::Event& event);
void GameEndClickHandler();
void GameProcessEventsHandler(const sf::Event& event);

#endif //KNYAZ_GAME_UI_H
