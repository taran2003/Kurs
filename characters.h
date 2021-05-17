#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "iostream"
#include "level.h"
#include <vector>
#include <list>
#include "TinyXML/tinyxml.h"

using namespace sf;
////////////////////////////////////Îáùèé êëàññ-ğîäèòåëü//////////////////////////

class Entity {
public:
	std::vector<Object> obj;//âåêòîğ îáúåêòîâ êàğòû
	float  defense, moveTimer;
	int w, h,x,y,dx,dy, health, mastery, agil, attack;
	bool life, isMove;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image& image, String Name,std::string Fname, int X, int Y, int W, int H);
	FloatRect getRect();
	float rotation(int X, int Y);
	Vector2f getCoordinates();
};
////////////////////////////////////////////////////ÊËÀÑÑ ÈÃĞÎÊÀ////////////////////////
class Player :public Entity {
public:
	enum staitobjectX { left, right, stayX };
	enum staitobjectY { up, down, stayY };
	staitobjectY stateY;
	staitobjectX stateX;
	std::string item;
	Player(Image& image, String Name, std::string Fname, Level& lev, int X, int Y, int W, int H);
	void controlX();
	void controlY();
	void DamegGain(int attack);
	void checkCollisionWithMap(int Dx, int Dy, Level* lvl);
	void update(float time, int X, int Y, View* view,Level *lvl);
};
////////////////////////////////////////////////////ÊËÀÑÑ ÂĞÀÃÀ////////////////////////

class Enemy :public Entity {
public:
	enum staitobjectX { left, right, stayX };
	enum staitobjectY { up, down, stayY };
	staitobjectY stateY;
	staitobjectX stateX;
	Enemy(Image& image, String Name, std::string Fname, Level& lvl, int X, int Y, int W, int H);
	void checkCollisionWithMap(int Dx, int Dy);
	void movmentX(int xPoint);
	void movmentY(int yPoint);
	void DamegGain(int attack,int mastery);
	void update(float time, int X, int Y);
};
////////////////////////////////////////////////////ÊËÀÑÑ ÎĞÓÆÈß////////////////////////
class weapon :public Entity
{
public:
	weapon(Image& image, String Name, std::string Fname, Level& lev, int X, int Y, int W, int H);
	enum staitobjectX { left, right, stayX };
	enum staitobjectY { up, down, stayY };
	staitobjectY stateY;
	staitobjectX stateX;
	void updait(float time, int X, int Y);
	void controlY(int Y);
	void controlX(int X);
};
