#include "BGame_Level_3.h"

BGame_Level_3::BGame_Level_3()
{
    gGame_Level_3 = new BGame(true);
    gPlayer = new BPlayerControl;

    start = false;
    gameOver = false;

    tempScore = 0;
    tempLives = 0;
}

BGame_Level_3::~BGame_Level_3()
{
    delete gGame_Level_3;
    delete gPlayer;
}
BGame* BGame_Level_3::getGame()
{
    return gGame_Level_3;
}

BPlayerControl* BGame_Level_3::getPlayer()
{
    return gPlayer;
}

void BGame_Level_3::mainGameLoop(bool& levelState)
{
    //Clear screen
    SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);
    SDL_RenderClear(baseRenderer);

    //Render background texture to screen
    gGame_Level_3->renderBackground();

    //render bricks from level
    for (int i = 0; i < gGame_Level_3->getBrickLevel_2()->getLevel_2()->getColumnCount(); i++)
    {
        gGame_Level_3->getBrickLevel_2()->getSoftYellowBrick(i)->renderYellowBrick(gGame_Level_3->getBrickLevel_2()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0), gGame_Level_3->getBrickLevel_2()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0));
        gGame_Level_3->getBrickLevel_2()->getMediumBlueBrick(i)->renderBlueBrick(gGame_Level_3->getBrickLevel_2()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0), gGame_Level_3->getBrickLevel_2()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0));
        gGame_Level_3->getBrickLevel_2()->getHardRedBrick(i)->renderRedBrick(gGame_Level_3->getBrickLevel_2()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0), gGame_Level_3->getBrickLevel_2()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0));
    }

    //keep previous score
    tempScore = gGame_Level_3->getScore();
    tempLives = gGame_Level_3->getBrickLevel_2()->getLevel_2()->getBallLives();

    //ball movement/collision
    gGame_Level_3->ballMovementAndCollision(gPlayer->getBoardPosition().x, gPlayer->getBoardPosition().y, levelState);

    //checks if it is game over
    if (gGame_Level_3->getBrickLevel_2()->getLevel_2()->getBallLives() == 0)
    {
        gameOver = true;
        //load last score and number of lives
        if (gGame_Level_3->getScore() > tempScore || gGame_Level_3->getBrickLevel_2()->getLevel_2()->getBallLives() < tempLives)
        {
            gGame_Level_3->loadScoreAndLivesMedia(gGame_Level_3->getScore(), gGame_Level_3->getBrickLevel_2()->getLevel_2()->getBallLives());
        }
    }
    //if game is not lost, reset ball on board and wait for mouse click
    else if (gGame_Level_3->getLifeLostState() == true)
    {
        start = false;
    }

    //if score is changed, load and render it on screen
    if (gGame_Level_3->getScore() > tempScore || gGame_Level_3->getBrickLevel_2()->getLevel_2()->getBallLives() < tempLives)
    {
        gGame_Level_3->loadScoreAndLivesMedia(gGame_Level_3->getScore(), gGame_Level_3->getBrickLevel_2()->getLevel_2()->getBallLives());
    }
    gGame_Level_3->getScoreTexture()->renderTexture(GAME_SCORE_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);
    gGame_Level_3->getLivesTexture()->renderTexture(GAME_LIVES_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);


    //game delay, speed
    SDL_Delay(2);

    //Render player board
    gPlayer->renderPlayerBoard();

    //Update screen
    SDL_RenderPresent(baseRenderer);
}

void BGame_Level_3::standByLoop()
{
    //Clear screen
    SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);
    SDL_RenderClear(baseRenderer);

    //Render background texture to screen
    gGame_Level_3->renderBackground();
    gGame_Level_3->renderMenu();

    //render bricks from level
    for (int i = 0; i < gGame_Level_3->getBrickLevel_2()->getLevel_2()->getColumnCount(); i++)
    {
        gGame_Level_3->getBrickLevel_2()->getSoftYellowBrick(i)->renderYellowBrick(gGame_Level_3->getBrickLevel_2()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0), gGame_Level_3->getBrickLevel_2()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0));
        gGame_Level_3->getBrickLevel_2()->getMediumBlueBrick(i)->renderBlueBrick(gGame_Level_3->getBrickLevel_2()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0), gGame_Level_3->getBrickLevel_2()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0));
        gGame_Level_3->getBrickLevel_2()->getHardRedBrick(i)->renderRedBrick(gGame_Level_3->getBrickLevel_2()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0), gGame_Level_3->getBrickLevel_2()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0));
    }

    gGame_Level_3->setBallPoint(gPlayer->getBoardPosition().x + gGame_Level_3->getBoardWidth() / 2, gPlayer->getBoardPosition().y - gGame_Level_3->getBallSize());
    gGame_Level_3->renderBall(gPlayer->getBoardPosition().x + gGame_Level_3->getBoardWidth() / 2, gPlayer->getBoardPosition().y - gGame_Level_3->getBallSize());

    //Render player board
    gPlayer->renderPlayerBoard();

    //Render current frame
    gGame_Level_3->getScoreTexture()->renderTexture(GAME_SCORE_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);
    gGame_Level_3->getLivesTexture()->renderTexture(GAME_LIVES_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);

    //Update screen
    SDL_RenderPresent(baseRenderer);
}

void BGame_Level_3::gameOverLoop()
{
    //Clear screen
    SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);
    SDL_RenderClear(baseRenderer);

    //Render background texture to screen
    gGame_Level_3->renderGameOverBackground();
    gGame_Level_3->getScoreTexture()->renderTexture(GAME_SCORE_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);
    gGame_Level_3->getLivesTexture()->renderTexture(GAME_LIVES_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);

    //Update screen
    SDL_RenderPresent(baseRenderer);
}

int BGame_Level_3::getGameScorePosition_X() const
{
    return GAME_SCORE_POSITION_X;
}

int BGame_Level_3::getGameLivesPosition_X() const
{
    return GAME_LIVES_POSITION_X;
}

int BGame_Level_3::getScoreAndLivesPosition_Y() const
{
    return GAME_SCORE_AND_LIVES_POSITION_Y;
}

void BGame_Level_3::setGameStart(bool state)
{
    start = state;
}

bool BGame_Level_3::getGameStart()
{
    return start;
}

bool BGame_Level_3::getGameOver()
{
    return gameOver;
}
