#include "view.h"
void setPlayerCoordinateForView(float x, float y,View *view)
{
	float tempX = x; float tempY = y;

	if (y > 624) tempY = 624;
	view->setCenter(tempX, tempY);
}
