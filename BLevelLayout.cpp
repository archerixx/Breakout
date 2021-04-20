#include "BLevelLayout.h"

BLevelLayout::BLevelLayout()
{
	brickRowCount = 3;
	brickColumnCount = 11;
	brickSpacing = 5;
	brickSpacing = 5;
	backgroundTexture = "Breakout_Media/retro_arcade_background.png";
	ballLives = 3;
}

BLevelLayout::BLevelLayout(int rowCount, int columnCount, int rowSpacing, int columnSpacing, const char* backGroundTexture, int ballLives)
{
	this->brickRowCount = rowCount;
	this->brickColumnCount = columnCount;
	this->brickSpacing = rowSpacing;
	this->brickSpacing = columnSpacing;
	this->backgroundTexture = backGroundTexture;
	this->ballLives = ballLives;
}

/*
	GETs
*/
int BLevelLayout::getColumnCount() const
{
	return brickColumnCount;
}
int BLevelLayout::getBrickSpacing() const
{
	return brickSpacing;
}
const char* BLevelLayout::getBackGroundTexture() const
{
	return backgroundTexture;
}
int BLevelLayout::getBallLives() const
{
	return ballLives;
}

/*
	SETs
*/
void BLevelLayout::setBallLives(int lifesLeft)
{
	this->ballLives = lifesLeft;
}