#include <SFML/Graphics.hpp>
#include "view.h"
#include <iostream>
#include <sstream>
#include "game.h"
#include "Menu.h"

using namespace sf;
int main()
{
	int playerScor=0;
	std::string login;
	srand(time(NULL));
	RenderWindow window(VideoMode(1920, 1800), "Deep dungeon"/*Style::Fullscreen*/);
	window.setVerticalSyncEnabled(true);
	int numberLevel = rand()%10+1;
	gameRunning(window, &numberLevel,&playerScor, menu(window, false));
	return 0;
}