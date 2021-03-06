#pragma once

#include "BBrickType.h"
#include "BLevelLayout.h"

class BBricks : public BBrickType, public BGraphics
{
public:
	//Construcor
	BBricks();
	BBricks(bool thirdLevel);
	//Destructor
	~BBricks();

	//GET for Brick elements
	BBrickType* getSoftYellowBrick(int& element);
	BBrickType* getMediumBlueBrick(int& element);
	BBrickType* getHardRedBrick(int& element);
	//GET current level
	BLevelLayout* getLevel_1();
	BLevelLayout* getLevel_2();

	//SET for Bricks
	void setYellowBrick(bool& secondLevel, bool& thridLevel, const int& columnCount, const int& rowSpacing);
	void setBlueBrick(bool& secondLevel, bool& thridLevel, const int& columnCount, const int& rowSpacing);
	void setRedBrick(bool& secondLevel, bool& thridLevel, const int& columnCount, const int& rowSpacing);

private:
	//Brick types
	BBrickType** BrickSoftYellow;
	BBrickType** BrickMediumBlue;
	BBrickType** BrickHardRed;

	//Level 1
	BLevelLayout* Level_1;
	BLevelLayout* Level_2;

	//flag for destructor
	bool callDestructor = false;

	//Bricks row start positions on Y axis
	int BrickSoftYellow_Y_FromStart;
	int BrickSoftYellow_Y_ToEnd;
	int BrickMediumBlue_Y_FromStart;
	int BrickMediumBlue_Y_ToEnd;
	int BrickHardRed_Y_FromStart;
	int BrickHardRed_Y_ToEnd;

};