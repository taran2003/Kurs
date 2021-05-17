#include "Item_Read.h"

item::item(std::string* activeItem, int X, int Y, int W, int H)
{
	std::ifstream fin;
	fin.open("items/store.txt");
	std::string item;
	int n = rand() % 3 + 1;
	for (int i = 0; i < n; i++)
	{
		getline(fin, item);
	}
	*activeItem = item;
	if (*activeItem == "iforgot")
	{
		texture.loadFromFile("images/iforgot.png");
	}
	if (*activeItem == "DIE")
	{
		texture.loadFromFile("images/DIE.png");
	}
	if (*activeItem == "<3")
	{
		texture.loadFromFile("images/hearth.png");
	}
	x = X, y = Y, w = W, h = H;
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2, h / 2);
	//sprite.setTextureRect(IntRect(0, 0, w, h));
	sprite.setPosition(x, y);
}

void item::itemPickUped(std::string* activeItem, std::string* floarItem, int* num)
{
	*activeItem = *floarItem;
	if (*activeItem == "iforgot")
	{
		if (*num == 10)
			*num = 0;
		if (*num > 10)
			*num = 3;
		
	}
	else { x = 16; y = 16; }
}

FloatRect item::getRect()
{
	return FloatRect(x, y, w, h);
}

void initialization(int* health, std::list<Enemy*> enemys, std::string* activeItem)
{
	std::list<Enemy*>::iterator it;
	if (*activeItem == "DIE")
	{
		for (it = enemys.begin(); it != enemys.end(); it++) {
			(*it)->health = 0;
		}
	}
	if (*activeItem == "<3")
	{
		*health += 50;
	}
}