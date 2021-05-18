#include <iostream>
#include <sstream>
#include "iostream"
#include "level.h"
#include <vector>
#include <fstream>
#include <list>
#include "TinyXML/tinyxml.h"
#include "characters.h"
#include "Menu.h"
#include "text_box.h"

bool isInt(std::string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]))return false;
	}
	return true;
}

void registrationSkrin(RenderWindow& window)
{
	FocusController fcR;
	Texture menuTexture1,registBackground;
	menuTexture1.loadFromFile("images/hero.png");
	registBackground.loadFromFile("images/jak.jpg");
	Sprite menu1(menuTexture1), menuBg(registBackground);
	bool isb = 1, erore1 = false, erore2 = false;
	int menuNum = 0;
	menu1.setPosition(800, 50);
	menuBg.setPosition(100, 0);
	sf::Font font;
	font.loadFromFile("CyrilicOld.ttf");
	sf::Text log, pas1,pas2,eror;
	log.setPosition(153, 140);
	log.setFont(font);
	pas1.setPosition(153, 183);
	pas1.setFont(font);
	pas2.setPosition(153, 226);
	pas2.setFont(font);
	eror.setPosition(704, 0);
	eror.setFont(font);
	eror.setCharacterSize(40);
	eror.setFillColor(Color::Red);
	int x = 0;
	TextBox login(log), pasword1(pas1),pasword2(pas2);
	std::string f1, f2, buf1, buf2,buf3;
	std::ofstream fout;
	std::ifstream fin;
	while (isb)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed && Mouse::getPosition(window).x > 153 && Mouse::getPosition(window).x < 419 && Mouse::getPosition(window).y < 178 && Mouse::getPosition(window).y > 147)
			{
				fcR.setFocusObject(&login);
			}
			if (event.type == Event::MouseButtonPressed && Mouse::getPosition(window).x > 153 && Mouse::getPosition(window).x < 419 && Mouse::getPosition(window).y > 178&&Mouse::getPosition(window).y <209)
			{
				fcR.setFocusObject(&pasword1);
			}
			if (event.type == Event::MouseButtonPressed && Mouse::getPosition(window).x > 153 && Mouse::getPosition(window).x < 419 && Mouse::getPosition(window).y > 213 && Mouse::getPosition(window).y < 280)
			{
				fcR.setFocusObject(&pasword2);
			}
			FocusObject* fo = fcR.getFocusObject();
			if (fo != 0 && !Keyboard::isKeyPressed(Keyboard::Enter) && !Keyboard::isKeyPressed(Keyboard::Space) && !Keyboard::isKeyPressed(Keyboard::Tab) && !Keyboard::isKeyPressed(Keyboard::Escape))
			{
				fo->event(event);
			}
		}
		f1 = login.getText();
		f2 = pasword1.getText();
		menu1.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		if (IntRect(800, 50, 64, 64).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Black); menuNum = 1; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			fin.open("plaeyrs/players.txt");
			erore2 = false;
			erore1 = false;
			while (fin.is_open()&&menuNum == 1&&!erore2 && !fin.eof())
			{
				getline(fin, buf1);
				getline(fin, buf2);
				if (buf1 == f1)
				{
					erore2 = true;
				}
				getline(fin, buf3);
			}
			fin.close();
			buf2 = pasword2.getText();
			buf1 = f1;
			if (menuNum == 1 && !erore1 &&!erore2) {
				fout.open("plaeyrs/players.txt",std::ios::app);
				if (!erore1)
				{
					if (f2 != buf2 || buf2.size()==0||f1.size()==0) {
						erore1 = true;
					}
				}
				if (!erore1) {
					fout << buf1 << std::endl;
					fout << buf2<<std::endl << std::endl;
				}
				fout.close();
			}
			if (menuNum == 1 && !erore1 && !erore2 && buf2.size() != 0 && f1.size() != 0)
			{
				isb = false;
			}
		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(login);
		if (erore2)eror.setString("пользователь с таким именем уже существует");
		else if (erore1)eror.setString("несовпадение паролей");
		window.draw(eror);
		window.draw(pasword1);
		window.draw(pasword2);
		window.display();
	}
}

std::string loginScrin(RenderWindow& window)
{
	FocusController fcL;
	Texture menuTexture1, menuTexture2, registBackground;
	menuTexture1.loadFromFile("images/hero.png");
	menuTexture2.loadFromFile("images/simpleEnime.png");
	registBackground.loadFromFile("images/jak.jpg");
	Sprite menu1(menuTexture1),menu2(menuTexture2), menuBg(registBackground);
	bool isb = 1,erore=false;
	int menuNum = 0;
	menu1.setPosition(730, 50);
	menu2.setPosition(730, 114);
	menuBg.setPosition(100, 0);
	sf::Font font;
	font.loadFromFile("CyrilicOld.ttf");
	sf::Text log,pas,eror;
	log.setPosition(153,140);
	log.setFont(font);
	pas.setPosition(153, 183);
	pas.setFont(font);
	eror.setPosition(704, 0);
	eror.setFont(font);
	eror.setString("неправельный логин или пароль");
	eror.setCharacterSize(40);
	eror.setFillColor(Color::Red);
	int x = 0;
	TextBox login(log),pasword(pas);
	std::string f1,f2,name, buf1, buf2, buf3;
	std::ifstream fin;
	while (isb)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed && Mouse::getPosition(window).x > 153 && Mouse::getPosition(window).x < 419&& Mouse::getPosition(window).y<178 && Mouse::getPosition(window).y > 147)
			{
				fcL.setFocusObject(&login);
			}
			if (event.type == Event::MouseButtonPressed && Mouse::getPosition(window).x > 153 && Mouse::getPosition(window).x < 419 && Mouse::getPosition(window).y > 178)
			{
				fcL.setFocusObject(&pasword);
			}
			FocusObject* fo = fcL.getFocusObject();
			if (fo != 0&&!Keyboard::isKeyPressed(Keyboard::Enter) && !Keyboard::isKeyPressed(Keyboard::Space) && !Keyboard::isKeyPressed(Keyboard::Tab) && !Keyboard::isKeyPressed(Keyboard::Escape))
			{
				fo->event(event);
			}
		}
		f1 = login.getText();
		f2 = pasword.getText();
	    name = "plaeyrs/players.txt";
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		if (IntRect(730, 50, 64, 64).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Black); menuNum = 1; }
		if (IntRect(730, 114, 64, 64).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Black); menuNum = 2; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				fin.open(name);
				erore = true;
				while (erore && !fin.eof())
				{
					getline(fin,buf1);
					getline(fin, buf2);
					if (buf1 == f1 && buf2 == f2)
					{
						erore = false;
						isb = false;
					}
					getline(fin, buf3);
				}
				fin.close();
			}
			if (menuNum == 2) {
				registrationSkrin(window);
			}
		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(login);
		if(erore)
		window.draw(eror);
		window.draw(pasword);
		window.display();
	}
	return f1;
}

std::string menu(RenderWindow& window, bool inGame)
{
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuTexture3.loadFromFile("images/333.png");
	aboutTexture.loadFromFile("images/about.jpg");
	menuBackground.loadFromFile("images/Penguins.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	std::string login;
	short menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(345, 0);
	while (isMenu)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Black); menuNum = 1;}
		else if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Black);menuNum = 2; }
		else if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Black);menuNum = 3;}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (menuNum)
			{
			case 1:
			{
			if (!inGame) {
			login=loginScrin(window);
			}
			isMenu = false;
				break;
			}
			case 2:
			{
				window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape));
				break;
			}
			case 3:
			{
				window.close(); isMenu = false;
				break;
			}
			}
		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.display();
	}
	return login;
}
