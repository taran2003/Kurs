#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
	Music music;
	music.openFromFile("music.ogg");
	music.play();
	music.setVolume(5);
	music.setLoop(true);
	RenderWindow window(VideoMode(1920, 1080), "Deep dungeon",Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	int numberLevel = rand() % 2 + 1;
	gameRunning(window, &numberLevel,&playerScor, menu(window, false));
	return 0;
}