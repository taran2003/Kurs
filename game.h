#pragma once
#include "game.h"
#include <SFML/Graphics.hpp>
#include "view.h"
#include <iostream>
#include <sstream>
#include "iostream"
#include "level.h"
#include <vector>
#include <list>
#include "TinyXML/tinyxml.h"
#include "characters.h"

using namespace sf;

void gameRunning(RenderWindow &window, int* numberLevel,int *playerScor,std::string login);