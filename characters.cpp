#include "characters.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "iostream"
#include "level.h"
#include "view.h"
#include <vector>
#include <fstream>
#include <list>
#include "TinyXML/tinyxml.h"

using namespace sf;

Entity::Entity(Image& image, String Name, std::string Fname, int X, int Y, int W, int H)
{
	std::ifstream fin;
	x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
	fin.open(Fname);
	fin >> attack >> mastery >> health >> defense;
	fin.close();
	agil = 0; dx = 0; dy = 0;
	life = true; isMove = false;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2, h / 2);
}

FloatRect Entity::getRect()
{
	return FloatRect(x, y, w, h);
}

float Entity::rotation(int X, int Y)
{
	Y -= y, X -= x;
	float rez = (atan2(Y, X) * 180 / 3.14159265);
	return rez;
}

Vector2f Entity::getCoordinates()
{

	Vector2f Coordinates;
	Coordinates.x = x;
	Coordinates.y = y;
	return Coordinates;
}

Player::Player(Image& image, String Name, std::string Fname, Level& lev, int X, int Y, int W, int H) :Entity(image, Name,Fname, X, Y, W, H) {
	playerScore = 0; stateX = stayX; stateY = stayY;  obj = lev.GetAllObjects();//инициализируем.получаем все объекты для взаимодействия персонажа с картой
	if (name == "Player1") {
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
}

void Player::controlX()
{
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		stateX = left;
		agil = 5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		stateX = right;
		agil = 5;
	}
	else
	{
		stateX = stayX;
	}

}

void Player::controlY()
{
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		stateY = up;
		agil = 5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		stateY = down;
		agil = 5;
	}
	else
	{
		stateY = stayY;
	}
}

void Player::DamegGain(int attack)
{
	int damage, crit;
	crit = rand() % ((100 - 0 + 1) + 0);
	damage = attack - attack * defense;
	health -= damage;
}

void Player::checkCollisionWithMap(int Dx, int Dy, Level* lvl)
{
	for (int i = 0; i < obj.size(); i++)//проходимся по объектам
		if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "solid")//если встретили препятствие
			{
				if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; }
				if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w; }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
			}
		}
}

void Player::update(float time, int X, int Y, View* view, Level* lvl)
{
	controlX();
	controlY();
	switch (stateX)
	{
	case right:dx = agil; break;
	case left:dx = -agil; break;
	case stayX:dx = 0; break;
	}
	switch (stateY)
	{
	case up:dy = -agil; break;
	case down:dy = agil; break;
	case stayY:dy = 0; break;
	}
	x += dx * time;
	checkCollisionWithMap(dx, 0,&*lvl);
	y += dy * time;
	checkCollisionWithMap(0, dy,&*lvl);
	sprite.setPosition(x + w / 2, y + h / 2);
	if (health <= 0) { life = false; }
	if (!isMove) { agil = 0; }
	setPlayerCoordinateForView(x, y, view);
	if (life) { setPlayerCoordinateForView(x, y, view); }
	sprite.setRotation(rotation(X, Y));
}

Enemy::Enemy(Image& image, String Name, std::string Fname, Level& lvl, int X, int Y, int W, int H) :Entity(image, Name,Fname, X, Y, W, H)
{
	obj = lvl.GetObjects("solid");//инициализируем.получаем нужные объекты для взаимодействия врага с картой
	stateX = stayX;
	stateY = stayY;
	if (name == "EasyEnemy") {
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
}

void Enemy::checkCollisionWithMap(int Dx, int Dy)
{
	for (int i = 0; i < obj.size(); i++)//проходимся по объектам
		if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "solid")//если встретили препятствие
			{
				if (Dy > 0) { y = obj[i].rect.top - h; }
				if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height; }
				if (Dx > 0) { x = obj[i].rect.left - w; }
				if (Dx < 0) {
					x = obj[i].rect.left + obj[i].rect.width;
				}
			}
			
		}
}

void Enemy::movmentX(int xPoint)
{
	if (x < xPoint)
	{
		agil = 2;
		stateX = right;
	}
	if (x > xPoint)
	{
		agil = 2;
		stateX = left;
	}
	if (x - xPoint<1 && x - xPoint >-1)
	{
		stateX = stayX;
	}
}

void Enemy::movmentY(int yPoint)
{
	if (name == "EasyEnemy") {
		if (y < yPoint)
		{
			agil = 2;
			stateY = down;
		}
		if (y > yPoint)
		{
			agil = 2;
			stateY = up;
		}
		if (y - yPoint > -1 && y - yPoint < 1)
		{
			stateY = stayY;
		}
	}
	if (name == "Enemy") {
		if (y < yPoint)
		{
			agil = 2;
			stateY = down;
		}
		if (y > yPoint)
		{
			agil = 2;
			stateY = up;
		}
		if (y - yPoint > -1 && y - yPoint < 1)
		{
			stateY = stayY;
			agil = 7;
		}
	}
}

void Enemy::DamegGain(int attack,int mastery)
{
	int damage, crit;
	crit = rand() % ((100 - 0 + 1) + 0);
	damage = attack - attack * defense;
	if (crit <= mastery)
	{
		damage += attack * defense;
	}
	health -= damage;
}

void Enemy::update(float time, int X, int Y)
{

	movmentX(X);
	movmentY(Y);
	if (name == "EasyEnemy") {
		switch (stateX)
		{
		case right:dx = agil; break;
		case left:dx = -agil; break;
		case stayX:dx = 0; break;
		}
		switch (stateY)
		{
		case up:dy = -agil; break;
		case down:dy = agil; break;
		case stayY:dy = 0; break;
		}
	}
	if (name == "Enemy") {
		switch (stateX)
		{
		case right:dx = agil; break;
		case left:dx = -agil; break;
		case stayX:dx = 0; break;
		}
		switch (stateY)
		{
		case up:dy = -agil; break;
		case down:dy = agil; break;
		case stayY:dy = 0; break;
		}
	}
	x += dx * time;
	checkCollisionWithMap(dx, 0);
	y += dy * time;
	checkCollisionWithMap(0, dy);
	sprite.setPosition(x + w / 2, y + h / 2);
	if (health <= 0) { life = false; }
	sprite.setRotation(rotation(X, Y));
}

weapon::weapon(Image& image, String Name, std::string Fname, Level& lev, int X, int Y, int W, int H) : Entity(image,Name,Fname, X, Y, W, H)
{
	stateX = stayX; stateY = stayY;
	if (name == "Visp") {
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
}

void weapon::updait(float time, int X, int Y)
{
	controlY(Y);
	controlX(X);
	switch (stateX)
	{
	case left: dx = -agil; break;
	case right: dx = agil; break;
	case stayX:dx = 0.0f; break;
	}
	switch (stateY)
	{
	case up: dy = -agil; break;
	case down: dy = agil; break;
	case stayY:dy = 0.0f; break;
	}
	agil = 0;
	x += dx * time;
	y += dy * time;
	sprite.setPosition(x, y);
	//std::cout << "двигаю\n";
}

void weapon::controlY(int Y)
{
	if (y < Y)
	{
		agil = 3;
		stateY = down;
	}
	else if (y > Y)
	{
		agil = 3;
		stateY = up;
	}
	else if (Y- y > -1&&Y-y<1)
	{
		stateY = stayY;
	}
}

void weapon::controlX(int X)
{
	if (x < X)
	{
		agil = 3;
		stateX = right;
	}
	else if (x > X)
	{
		agil = 3;
		stateX = left;
	}
	else if (X-x >-1 && X-x<1)
	{
		stateX = stayX;
	}
}
