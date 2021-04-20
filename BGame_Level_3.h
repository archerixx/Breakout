#pragma once

#include "BPlayerControl.h"
#include "BGame.h"

class BGame_Level_3
{
public:
    BGame_Level_3();
    ~BGame_Level_3();

    BGame* getGame();
    BPlayerControl* getPlayer();

    //main game loop
    void mainGameLoop(bool& levelState);
    //standby mode
    void standByLoop();
    //game over screen
    void gameOverLoop();

    //GETs
    int getGameScorePosition_X() const;
    int getGameLivesPosition_X() const;
    int getScoreAndLivesPosition_Y() const;

    //checks if mouse button is clicked
    void setGameStart(bool state);

    //GETs
    bool getGameStart();
    bool getGameOver();
private:
    BGame* gGame_Level_3;
    BPlayerControl* gPlayer;

    //Start game flag
    bool start;
    //Gameover flag
    bool gameOver;

    //temp values for score and lives
    int tempScore;
    int tempLives;

    const int GAME_SCORE_POSITION_X = 730;
    const int GAME_LIVES_POSITION_X = 50;
    const int GAME_SCORE_AND_LIVES_POSITION_Y = 530;
};