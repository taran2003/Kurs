#pragma once
#include <string>
#include "game.h"
#include <SFML/Graphics.hpp>
#include "view.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "iostream"
#include "level.h"
#include <vector>
#include <list>
#include "characters.h"
#include "TinyXML/tinyxml.h"
#include "Menu.h"

class item {
public:
	int w, h, x, y;
	Texture texture;
	Sprite sprite;
	item(std::string* floarItem, int X, int Y, int W, int H);
	void itemPickUped(std::string* activeItem, std::string* floarItem, int* num);
	FloatRect getRect();
};
void initialization(int* health, std::list<Enemy*> enemys, std::string* activeItem);