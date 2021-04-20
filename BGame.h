#pragma once

#include "BBricks.h"
#include "BSound.h"

class BGame : public BBricks
{
public:
	BGame();
	BGame(bool thirdLevel);
	~BGame();

	//load bacground media
	bool loadBackgroundMedia(const char* path);
	void renderBackground(int x = 0, int y = 0);
	void renderGameOverBackground(int x = 0, int y = 0);
	void renderMenu(int x = 210, int y = 0);

	//set ball position
	void setBallPoint(int x, int y);
	//get ball size
	int getBallSize() const;

	//load ball media
	bool loadBallMedia();
	//render ball
	void renderBall(int x, int y);

	//get BBrick object
	BBricks* getBrickLevel_1();
	BBricks* getBrickLevel_2();
	//get BSound object
	BSound* getSound();

	//responsible for ball movement, collision, brick destruction, gameScore and lives
	void ballMovementAndCollision(int board_x, int board_y, bool levelState);
	void brickCollision(int size, BBricks* getBrickLevel);
	void stateReset();

	//removes brick from gametable
	void removeYellowBricks(int index, BBricks* getBrickLevel);
	void removeBlueBricks(int index, BBricks* getBrickLevel);
	void removeRedBricks(int index, BBricks* getBrickLevel);

	// SET/GET gameScore
	void setScore(int addScore);
	int getScore();

	//get hit counter
	int getHitCounter();
	void updateHitCounter();

	//get state of lifeLost
	bool getLifeLostState();
	BTexture* getLivesTexture();

	//load font media for gameScore
	bool loadScoreAndLivesMedia(int gameScore, int livesLeft);
	BTexture* getScoreTexture();

	//qualify function name from BGraphics class
	BGraphics::getBoardWidth;

private:
	//background texture
	BTexture* baseBackgroundTexture;
	BTexture* gameOverBackground;

	//ball size
	const int BALL_SIZE = 10;

	//ball position in game on X and Y axis
	SDL_Point bBallPosition;
	SDL_Point bBallPreviousPosition;

	//game gameScore
	int gameScore;
	//brick hit counter
	int brickHitCounter;
	//life state
	bool lifeLost;

	//text/font for score texture
	BTexture* scoreTexture;
	//ball texture
	BTexture* ballTexture;
	//lives texture
	BTexture* livesTexture;
	//Menu text
	BTexture* menuText;


	//classess used in this header
	BBricks* gBrick_Level_1;
	BSound* gSound;

	//object for level 3
	bool levelState_3 = false;
	BBricks* gBrick_Level_2;

	//flag for destructor
	bool callDestructor = false;

	//ball states
	bool onLeftBoardSide = false;
	bool onRightBoardSide = false;
	bool onLeftWallBelow = false;
	bool onLeftWallAbove = false;
	bool onTopWallLeft = false;
	bool onTopWallRight = false;
	bool onRightWallBelow = false;
	bool onRightWallAbove = false;
};