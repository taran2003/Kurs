#pragma once
#include <SFML/Graphics.hpp>
#include "map.h"
using namespace sf;
class Player
{ 
  private: 
	 float x, y = 0;
  public:
	 float w, h, dx, dy, speed = 0;
	  int dir = 0;
	  String File;
	  Image image;
	  Texture texture;
	  Sprite sprite;
	  Player(String F, int X, int Y, float W, float H )
	  {
		  File = F;
		  w = W;  h = H;
		  image.loadFromFile("images/" + File);
		  texture.loadFromImage(image);
		  sprite.setTexture(texture);
		  x = X; y = Y;
		  sprite.setTextureRect(IntRect(w, h, w, h));
	  }
	  void update(float time)
	  {
		 switch (dir)
		 {
		  case 0: 
		  {
			  dx = speed; 
			  dy = 0;
			  break;
		  }
		  case 1:
		  {
			  dx = -speed; 
			  dy = 0;
			  break;
		  }
		  case 2:
		  {
			  dx = 0; 
			  dy = speed;
			  break;
		  }
		  case 3:
		  {
			  dx = 0;
			  dy = -speed;
			  break;
		  }
		 }
		 x += dx * time;
		 y += dy * time;

		 speed = 0;
		 sprite.setPosition(x, y);
		 interactionWithMap();
      }
	  void interactionWithMap()
	  {

		  for (int i = y / 32; i < (y  + 64) / 32; i++)
			  for (int j = x / 32; j < (x + 64) / 32; j++)
			  {
				  if (TileMap[i][j] == '0')
				  {
					  if (dy > 0)
					  {
						  y = i * 32 - 64;
					  }
					  if (dy < 0)
					  {
						  y = i * 32 + 64;
					  }
					  if (dx > 0)
					  {
						  x = j * 32 - 64;
					  }
					  if (dx < 0)
					  {
						  x = j * 32 + 64;
					  }
				  }
			  }
	  }
	  float getplayerX()
	  {
		  return x;
	  }
	  float getplayerY()
	  {
		  return y;
	  }
         

};
 