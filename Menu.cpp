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

FocusController fc;

void registrationSkrin(RenderWindow& window)
{
	Texture menuTexture1,registBackground, eror;
	eror.loadFromFile("images/eror.jpg");
	menuTexture1.loadFromFile("images/hero.png");
	registBackground.loadFromFile("images/jak.jpg");
	Sprite menu1(menuTexture1),menuBg(registBackground), EROR(eror);
	bool isb = 1, erore = false;
	int menuNum = 0;
	menu1.setPosition(1000, 629);
	menuBg.setPosition(100, 0);
	EROR.setPosition(704, 0);
	sf::Font font;
	font.loadFromFile("CyrilicOld.ttf");
	sf::Text log, pas1,pas2;
	log.setPosition(153, 140);
	log.setFont(font);
	pas1.setPosition(153, 183);
	pas1.setFont(font);
	pas2.setPosition(153, 226);
	pas2.setFont(font);
	int x = 0;
	TextBox login(log), pasword1(pas1),pasword2(pas2);
	std::string f1, f2, buf1, buf2;
	std::ofstream fout;
	while (isb)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed && Mouse::getPosition(window).x > 153 && Mouse::getPosition(window).x < 419 && Mouse::getPosition(window).y < 178 && Mouse::getPosition(window).y > 147)
			{
				fc.setFocusObject(&login);
			}
			if (event.type == Event::MouseButtonPressed && Mouse::getPosition(window).x > 153 && Mouse::getPosition(window).x < 419 && Mouse::getPosition(window).y > 178&&Mouse::getPosition(window).y <209)
			{
				fc.setFocusObject(&pasword1);
			}
			if (event.type == Event::MouseButtonPressed && Mouse::getPosition(window).x > 153 && Mouse::getPosition(window).x < 419 && Mouse::getPosition(window).y > 213 && Mouse::getPosition(window).y < 280)
			{
				fc.setFocusObject(&pasword2);
			}
			FocusObject* fo = fc.getFocusObject();
			if (fo != 0 && !Keyboard::isKeyPressed(Keyboard::Enter) && !Keyboard::isKeyPressed(Keyboard::Space))
			{
				fo->event(event);
			}
		}
		f1 = login.getText();
		f2 = pasword1.getText();
		buf2 = pasword2.getText();
		buf1 = "plaeyrs/" + f1 + ".txt";
		menu1.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		if (IntRect(1000, 629, 64, 64).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Black); menuNum = 1; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				fout.open(buf1);
				erore = false;
				if (!erore)
				{
					if (f2 != buf2) {
						erore = true;
					}
				}
				if (!erore) {
					isb = false;
					fout << buf2<<std::endl;
				}
				fout.close();
			}
		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(login);
		if (erore)
			window.draw(EROR);
		window.draw(pasword1);
		window.draw(pasword2);
		window.display();
	}
}

std::string loginScrin(RenderWindow& window)
{
	Texture menuTexture1, menuTexture2, registBackground,eror;
	eror.loadFromFile("images/eror.jpg");
	menuTexture1.loadFromFile("images/hero.png");
	menuTexture2.loadFromFile("images/simpleEnime.png");
	registBackground.loadFromFile("images/jak.jpg");
	Sprite menu1(menuTexture1),menu2(menuTexture2), menuBg(registBackground),EROR(eror);
	bool isb = 1,erore=false;
	int menuNum = 0;
	menu1.setPosition(1064, 629);
	menu2.setPosition(1064, 693);
	menuBg.setPosition(100, 0);
	EROR.setPosition(704, 0);
	sf::Font font;
	font.loadFromFile("CyrilicOld.ttf");
	sf::Text log,pas;
	log.setPosition(153,140);
	log.setFont(font);
	pas.setPosition(153, 183);
	pas.setFont(font);
	int x = 0;
	TextBox login(log),pasword(pas);
	std::string f1,f2,buf1,buf2;
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
				fc.setFocusObject(&login);
			}
			if (event.type == Event::MouseButtonPressed && Mouse::getPosition(window).x > 153 && Mouse::getPosition(window).x < 419 && Mouse::getPosition(window).y > 178)
			{
				fc.setFocusObject(&pasword);
			}
			FocusObject* fo = fc.getFocusObject();
			if (fo != 0&&!Keyboard::isKeyPressed(Keyboard::Enter) && !Keyboard::isKeyPressed(Keyboard::Space))
			{
				fo->event(event);
			}
		}
		f1 = login.getText();
		f2 = pasword.getText();
		buf1 = "plaeyrs/" + f1 + ".txt";
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		if (IntRect(1064, 629, 64, 64).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Black); menuNum = 1; }
		if (IntRect(1064, 693, 64, 64).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Black); menuNum = 2; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				fin.open(buf1);
				erore = false;
				if (!fin.is_open())
				{
					erore = true;
				}
				else if (!erore)
				{
					fin >> buf2;
					if(buf2!=f2)
					{
						erore = true;
					}
				}
				if(!erore){ 
					isb = false;
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
		window.draw(EROR);
		window.draw(pasword);
		window.display();
	}
	return buf1;
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
