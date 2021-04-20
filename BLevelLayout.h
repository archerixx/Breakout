#pragma once

class BLevelLayout
{
public:
	//Constructors
	BLevelLayout();
	BLevelLayout(int rowCount, int columnCount, int rowSpacing, int columnSpacing, const char* backGroundTexture, int ballLives);

	//GET class variables
	int getColumnCount() const;
	int getBrickSpacing() const;
	const char* getBackGroundTexture() const;
	int getBallLives() const;

	//SET ball lives
	void setBallLives(int lifesLeft);

private:
	int brickRowCount;
	int brickColumnCount;
	int brickSpacing;
	const char* backgroundTexture;
	int ballLives;
};