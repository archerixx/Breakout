#pragma once

#include "BPlayerControl.h"
#include "BGame.h"

class BGame_Level_1_2
{
public:
    BGame_Level_1_2();
    ~BGame_Level_1_2();

    BGame* getGame();
    BPlayerControl* getPlayer();

    //update level (move bricks down on Y-axis)
    void updateLevel();

    //main game loop
    void mainGameLoop(bool& levelState);
    //standby mode
    void standByLoop();
    //game over loop
    void gameOverLoop();

    //checks if mouse button is clicked
    void setGameStart(bool state);

    //GETs
    bool getGameStart();
    bool getGameOver();

private:
    BGame* gGame;
    BPlayerControl* gPlayer;

    //Start game flag
    bool start;
    //Gameover flag
    bool gameOver;
    //Update/move lenght on y-axis
    int updateLenght;

    //temp values for score and lives
    int tempScore;
    int tempLives;

    //Score and Lives position on screen
    const int GAME_SCORE_POSITION_X = 730;
    const int GAME_LIVES_POSITION_X = 50;
    const int GAME_SCORE_AND_LIVES_POSITION_Y = 530;
};