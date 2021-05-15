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

int health=100,num=0;

void saveScore(std::string login,int *playerScor);
std::string loadScore(std::string login);

void changeLevel(Level* lvl, int numberLevel)
{

	if (numberLevel == 2) { lvl->LoadFromFile("Zero.tmx"); }
	if (numberLevel == 1) { lvl->LoadFromFile("1.tmx"); }
	if (numberLevel == 3) { lvl->LoadFromFile("2.tmx"); }
	if (numberLevel == 4) { lvl->LoadFromFile("3.tmx"); }
	if (numberLevel == 5) { lvl->LoadFromFile("4.tmx"); }
	if (numberLevel == 6) { lvl->LoadFromFile("5.tmx"); }
	if (numberLevel == 7) { lvl->LoadFromFile("6.tmx"); }
	if (numberLevel == 8) { lvl->LoadFromFile("7.tmx"); }
	if (numberLevel == 9) { lvl->LoadFromFile("8.tmx"); }
	if (numberLevel == 10) { lvl->LoadFromFile("9.tmx"); }
}

bool startGame(RenderWindow& window, int* numberLevel, int* playerScor, std::string login)
{
	int score=0;
	Font font;
	std::string MaxScore=loadScore(login);
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	text.setStyle(Text::Bold);
	View view;
	view.reset(FloatRect(0, 0, 960, 480));
	Level lvl;//создали экземпл€р класса уровень
	changeLevel(&lvl, *numberLevel);
	Image heroImage;
	heroImage.loadFromFile("images/hero.png");
	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/simpleEnime.png");
	Image weaponImage;
	weaponImage.loadFromFile("images/weapon20.png");
	std::list<Enemy*>  enemys;
	std::list<Enemy*>::iterator it;
	std::list<Enemy*>::iterator it2;
	bool inPause = false;
	Vector2i mous;
	Vector2f weapo;
	std::vector<Vector2f>Enemys;
	Object player = lvl.GetObject("player");//объект игрока на нашей карте.задаем координаты игроку в начале при помощи него
	std::vector<Object> easyEnemyObject = lvl.GetObjects("easyEnemy");//объект легкого врага на нашей карте.задаем координаты игроку в начале при помощи него
	std::vector < Object> nextLvl = lvl.GetObjects("hod");
	std::vector < Object> spike = lvl.GetObjects("spike");
	Player p(heroImage, "Player1","stats/hero1.txt", lvl, player.rect.left, player.rect.top, 32, 32);//передаем координаты пр€моугольника player из карты в координаты нашего игрока
	p.health = health;
	for (int i = 0; i < easyEnemyObject.size(); i++) {
		enemys.push_back(new Enemy(easyEnemyImage, "EasyEnemy", "stats/simpleEnime1.txt", lvl, easyEnemyObject[i].rect.left, easyEnemyObject[i].rect.top, 32, 32));//nemy easyEnemy(easyEnemyImage, "EasyEnemy", lvl, easyEnemyObject.rect.left, easyEnemyObject.rect.top, 64, 64);//передаем координаты пр€моугольника easyEnemy из карты в координаты нашего врага
	}
	weapon visp(weaponImage, "Visp","", lvl, player.rect.left, player.rect.top, 16, 16);
	Clock clock, culdownE, culdownS;
	float time, cde,cds;
	Mouse::setPosition(sf::Vector2i(player.rect.left, player.rect.top), window);
	window.setMouseCursorVisible(false);
	Vector2i mousCor;
	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMilliseconds();
		cde = culdownE.getElapsedTime().asSeconds();
		cds= culdownS.getElapsedTime().asSeconds();
		clock.restart();
		time /= 10;
		mousCor = Mouse::getPosition(window);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		for (it = enemys.begin(); it != enemys.end();)
		{
			if ((*it)->life == false) {
				delete* it;
				it = enemys.erase(it);
				*playerScor+=1;
			}
			else it++;

		}
		for (it = enemys.begin(); it != enemys.end(); it++) {
			if (p.getRect().intersects((*it)->getRect()))
			{
				if (cde >= 0.9) {
					p.DamegGain((*it)->attack);
					culdownE.restart();
				}
			}
			if ((*it)->getRect().intersects(visp.getRect()))
			{
				(*it)->DamegGain(p.attack, p.mastery);
			}
			(*it)->update(time, p.x, p.y);
		}
		if (p.life) {
			p.update(time, visp.x, visp.y, &view, &lvl);
			visp.updait(time, mousCor.x, mousCor.y);
		}
		std::ostringstream playerHealthString, gameScoreString;    // объ€вили переменную здоровь€ и времени
		playerHealthString << p.health;//формируем строк
		gameScoreString << *playerScor;
		for (it = enemys.begin(); it != enemys.end(); it++) {
			for (it2 = enemys.begin(); it2 != enemys.end(); it2++) {
				if ((*it)->getRect() != (*it2)->getRect()) {
					if ((*it)->getRect().intersects((*it2)->getRect()))
					{
						if ((*it)->dx > 0)
						{
							(*it)->dx = 0;
							(*it)->x = (*it2)->x - (*it2)->w;
						}
						if ((*it)->dx < 0)
						{
							(*it)->dx = 0;
							(*it)->x = (*it2)->x + (*it2)->w;
						}
					}
				}
			}
		}
		for (it = enemys.begin(); it != enemys.end(); it++) {
			for (it2 = enemys.begin(); it2 != enemys.end(); it2++) {
				if ((*it)->getRect() != (*it2)->getRect()) {
					if ((*it)->getRect().intersects((*it2)->getRect()))
					{
						if ((*it)->dy > 0)
						{
							(*it)->dy = 0;
							(*it)->y = (*it2)->y - (*it2)->h;
						}
						if ((*it)->dy < 0)
						{
							(*it)->dy = 0;
							(*it)->y = (*it2)->y + (*it2)->h;
						}
					}
				}
			}
		}
		text.setString("«доровье: " + playerHealthString.str()+"\n"+"ќчки: " +gameScoreString.str()+"\nвысший рекорд:"+MaxScore);//задаем строку тексту и вызываем сформированную выше строку методом .str()
		text.setPosition(view.getCenter().x - 400, view.getCenter().y - 200);//задаем позицию текста, отступа€ от центра камеры
		for (int i = 0; i < nextLvl.size(); i++) {
			if (p.getRect().intersects(nextLvl[i].rect) && enemys.size() == 0)
			{
				*playerScor+=10;
				num++;
				health = p.health;
				return true;
			}
		}
		for (int i = 0; i < spike.size(); i++) {
			if (p.getRect().intersects(spike[i].rect))
			{
				if (cds >= 0.9) {
					p.health -= 20;
					culdownS.restart();
				}
			}
		}
		if (!p.life)
		{
			if (Keyboard::isKeyPressed(Keyboard::R))
			{
				saveScore(login, &*playerScor);
				return true;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
		    inPause = true;
			text.setString("             пауза\nнажмите(Y)дл€ продолжени€\nнажмите(X)дл€ выхода");
			text.setPosition(view.getCenter().x - 70, view.getCenter().y);
			window.clear();
			lvl.Draw(window);
			for (it = enemys.begin(); it != enemys.end(); it++) { window.draw((*it)->sprite); }
			window.draw(p.sprite);
			window.draw(visp.sprite);
			window.draw(text);
			window.display();
			while (inPause)
			{
				if (Keyboard::isKeyPressed(Keyboard::Y))
				{
					inPause = false;
				}
				if (Keyboard::isKeyPressed(Keyboard::X))
				{
					saveScore(login, &*playerScor);
					view.reset(FloatRect(0, 0, 1800, 900));
					window.setView(view);
					window.setMouseCursorVisible(true);
					return false;
				}
			}
		}
		window.setView(view);
		window.clear();
		lvl.Draw(window);
		for (it = enemys.begin(); it != enemys.end(); it++) { window.draw((*it)->sprite); }
		window.draw(p.sprite);
		window.draw(visp.sprite);
		window.draw(text);
		window.display();
	}

	return false;
}

void gameRunning(RenderWindow& window, int* numberLevel,int* playerScor, std::string login)
{
	if (startGame(*&window, &*numberLevel, &*playerScor,login))
	{
		*numberLevel = rand() % 10 + 1;
		gameRunning(*&window, *&numberLevel, &*playerScor,login);
	}
	else menu(window, false);;
}

std::string loadScore(std::string login)
{
	std::ifstream fin;
	std::string buf1, buf2,buf3;
	int score = 0;
	fin.open("plaeyrs/players.txt");
	while (buf1 != login)
	{
		getline(fin, buf1);
		getline(fin, buf2);
		getline(fin, buf3);
	}
	fin.close();
	if (buf3.size() == 0)
		buf3 = "0";
	return buf3;
}

void saveScore(std::string login,int* playerScor)
{
	std::ifstream fin;
	std::ofstream fout;
	std::vector<std::string> buf1, buf2,buf3;
	std::string f;
	int score=0,i=0;
	fin.open("plaeyrs/players.txt");
	while (!fin.eof())
	{
		getline(fin, f);
		buf1.push_back(f);
		getline(fin, f);
		buf2.push_back(f);
		getline(fin, f);
		buf3.push_back(f);
	}
	fin.close();
	while(buf1[i]!=login)
	{
		i++;
	}
	if (buf3[i].size() != 0) {
		for (int j = 0; j < buf3[i].size(); j++)
		{
			score += buf3[i][j] - '0';
			score *= 10;
		}
		score /= 10;
	}
	else score = 0;
	fout.open("plaeyrs/players.txt");
	for (int j = 0; j < buf1.size(); j++)
	{
		fout << buf1[j] << std::endl << buf2[j] << std::endl;
		if (score < *playerScor && j == i)
			fout << *playerScor << std::endl;
		else fout << buf3[j] << std::endl;
	}
	*playerScor = 0;
}
