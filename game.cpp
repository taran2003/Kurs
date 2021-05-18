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
#include "Item_Read.h"

int health=100,num=1;
std::string activeItem,floarItem;

void saveScore(std::string login,int *playerScor);
std::string loadScore(std::string login);

void changeLevel(Level* lvl, int numberLevel)
{

	if (numberLevel == 2) { lvl->LoadFromFile("3.tmx"); }
	if (numberLevel == 1) { lvl->LoadFromFile("4.tmx"); }
	if (numberLevel == 3) { lvl->LoadFromFile("zero.tmx"); }
	if (numberLevel == 4) { lvl->LoadFromFile("1.tmx"); }
	if (numberLevel == 5) { lvl->LoadFromFile("2.tmx"); }
	if (numberLevel == 6) { lvl->LoadFromFile("5.tmx"); }
	if (numberLevel == 7) { lvl->LoadFromFile("6.tmx"); }
	if (numberLevel == 8) { lvl->LoadFromFile("7.tmx"); }
	if (numberLevel == 9) { lvl->LoadFromFile("8.tmx"); }
	if (numberLevel == 10) { lvl->LoadFromFile("9.tmx"); }
	if (numberLevel == 11) { lvl->LoadFromFile("store.tmx");}
}

bool startGame(RenderWindow& window, int* numberLevel, int* playerScor, std::string login)
{
	int x=0, y=0;
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
	Image heroImage, easyEnemyImage, weaponImage;
	heroImage.loadFromFile("images/hero.png");
	easyEnemyImage.loadFromFile("images/simpleEnime.png");
	weaponImage.loadFromFile("images/weapon20.png");
	std::list<Enemy*>  enemys;
	std::list<Enemy*>::iterator it;
	std::list<Enemy*>::iterator it2;
	bool inPause = false, PickUped = false;
	Vector2i mous;
	Object player = lvl.GetObject("player");
	std::vector<Object> easyEnemyObject = lvl.GetObjects("easyEnemy"), nextLvl = lvl.GetObjects("hod"), spike = lvl.GetObjects("spike"),EnemyObject = lvl.GetObjects("Enemy");
	Player p(heroImage, "Player1","stats/hero1.txt", lvl, player.rect.left, player.rect.top, 32, 32);//передаем координаты пр€моугольника player из карты в координаты нашего игрока
	p.health = health;
	p.item = activeItem;
	for (int i = 0; i < easyEnemyObject.size(); i++) {
		enemys.push_back(new Enemy(easyEnemyImage, "EasyEnemy", "stats/simpleEnime1.txt", lvl, easyEnemyObject[i].rect.left, easyEnemyObject[i].rect.top, 32, 32));//nemy easyEnemy(easyEnemyImage, "EasyEnemy", lvl, easyEnemyObject.rect.left, easyEnemyObject.rect.top, 64, 64);//передаем координаты пр€моугольника easyEnemy из карты в координаты нашего врага
	}
	for (int i = 0; i < EnemyObject.size(); i++) {
		enemys.push_back(new Enemy(easyEnemyImage, "Enemy", "stats/simpleEnime1.txt", lvl, EnemyObject[i].rect.left, EnemyObject[i].rect.top, 32, 32));//nemy easyEnemy(easyEnemyImage, "EasyEnemy", lvl, easyEnemyObject.rect.left, easyEnemyObject.rect.top, 64, 64);//передаем координаты пр€моугольника easyEnemy из карты в координаты нашего врага
	}
	weapon visp(weaponImage, "Visp","", lvl, player.rect.left, player.rect.top, 16, 16);
	if (num % 10 == 0) {
		x = 682;
		y = 456;
	}
	item Item(&floarItem, x,y, 16, 16);
	x = 0; y = 0;
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
		if (p.getRect().intersects(Item.getRect()))
		{
			Item.itemPickUped(&activeItem, &floarItem, &num);
			p.item = activeItem;
			Item.sprite.setPosition(0, 0);
		}
		std::ostringstream playerHealthString, gameScoreString;
		playerHealthString << p.health;
		gameScoreString << *playerScor;
		text.setString("«доровье: " + playerHealthString.str()+"\n"+"ќчки: " +gameScoreString.str()+"\nвысший рекорд:"+MaxScore);//задаем строку тексту и вызываем сформированную выше строку методом .str()
		text.setPosition(view.getCenter().x - 400, view.getCenter().y - 200);//задаем позицию текста, отступа€ от центра камеры
		if (!p.life)
		{
			text.setString("GAME OVER");//задаем строку тексту и вызываем сформированную выше строку методом .str()
			text.setCharacterSize(50);
			text.setPosition(view.getCenter().x-90, view.getCenter().y );//задаем позицию текста, отступа€ от центра камеры
		}
		for (int i = 0; i < nextLvl.size(); i++) {
			if (p.getRect().intersects(nextLvl[i].rect) && enemys.size() == 0)
			{
				*playerScor+=10;
				num++;
				health = p.health;
				easyEnemyObject.clear();
				nextLvl.clear();
				spike.clear();
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
				health = 100;
				num = 1;
				return true;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			text.setCharacterSize(30);
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
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			initialization(&p.health, enemys, &p.item);
			activeItem = "";
			PickUped = true;
		}
		window.setView(view);
		window.clear();
		lvl.Draw(window);
		for (it = enemys.begin(); it != enemys.end(); it++) { window.draw((*it)->sprite); }
		window.draw(p.sprite);
		if(num%10==0&& !PickUped)window.draw(Item.sprite);
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
		if (num <= 3) { *numberLevel = rand() % 2 + 1; }
		else if(num>3&&num<10){ *numberLevel = rand() % 7 + 1; }
		else *numberLevel = rand() % 10 + 1;
		if (num % 10 == 0) { *numberLevel = 11;}
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
	fout << "";
	for (int j = 0; j < buf3.size()-1; j++)
	{
		fout << buf1[j] << std::endl << buf2[j] << std::endl;
		if (score < *playerScor && j == i)
			fout << *playerScor << std::endl;
		else if (buf3[j].size()!=0)fout << buf3[j] << std::endl;
		else fout << std::endl;
	}
	*playerScor = 0;
}
