#include "BPlayerControl.h"
#include "BGame.h"
#include "BGame_Level_1_2.h"
#include "BGame_Level_3.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 648;

//The window we'll be rendering to
SDL_Window* baseWindow = NULL;
//The window renderer
SDL_Renderer* baseRenderer = NULL;
//Globally used font
TTF_Font* baseFont = NULL;

bool initWindow();
void startGame();
void closeWindow();

int main(int argc, char* args[])
{
    startGame();
    return 0;
}

bool initWindow()
{
    //Initialization flag - check if function ends successfully
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        std::cout << "SDL could not initialize! SDL_Error: %s\n", SDL_GetError();
        success = false;
    }
    else
    {
        //Create window
        baseWindow = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (baseWindow == NULL)
        {
            std::cout << "Window could not be created! SDL_Error: %s\n", SDL_GetError();
            success = false;
        }
        else
        {
            //Create renderer for window
            baseRenderer = SDL_CreateRenderer(baseWindow, -1, SDL_RENDERER_ACCELERATED);
            if (baseRenderer == NULL)
            {
                std::cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
                success = false;
            }
            else
            {
                //Initialize renderer color (2D)
                SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError();
                    success = false;
                }

                //Initialize SDL_mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError();
                    success = false;
                }

                //Initialize SDL_ttf
                if (TTF_Init() == -1)
                {
                    std::cout << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError();
                    success = false;
                }
            }
        }
    }

    return success;
}

void startGame()
{
    //Start up SDL and create window
    if (!initWindow())
    {
        std::cout << "Failed to initialize!\n";
    }
    else
    {
        //level states
        bool lvl_1_state = true;
        bool lvl_2_state = false;
        bool lvl_3_state = false;
        //score passed between levels
        int passTheScore = 0;
        //lives passed between levels
        int passLives = 0;
        //max score
        int maxScore_Level_1 = 990;
        int maxScore_Level_2 = 1980;
        int maxScore_Level_3 = 3420;

        //game won flag
        bool gameWon = false;

        //Main loop flag
        bool quit = false;
        //Event handler
        SDL_Event e;

        //Create Level 1
        BGame_Level_1_2* Level_1 = new BGame_Level_1_2;
        Level_1->getGame()->setupBricks(lvl_2_state);
        if (lvl_1_state)
        {
            while (!quit)
            {
                //Handle events on queue
                while (SDL_PollEvent(&e))
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                        break;
                    }

                    //Handle mouse motion events
                    Level_1->getPlayer()->handleEvent(&e);

                    //Enable music with key 9 (to play/pause) and 0 (to stop)
                    Level_1->getGame()->getSound()->handleMusicEvent(&e);

                    //start game with mouse click
                    if (e.type == SDL_MOUSEBUTTONUP)
                    {
                        Level_1->setGameStart(true);
                    }
                }

                //game start when mouse button is clicked
                if (Level_1->getGameStart())
                {
                    Level_1->mainGameLoop(lvl_3_state);
                }
                //wait for mouse click screen
                else
                {
                    Level_1->standByLoop();
                }

                //Level finished
                if (Level_1->getGame()->getScore() == maxScore_Level_1)
                {
                    lvl_1_state = false;
                    lvl_2_state = true;
                    passTheScore = Level_1->getGame()->getScore();
                    passLives = Level_1->getGame()->getBrickLevel_1()->getLevel_1()->getBallLives();
                    break;
                }

                //if no more lives, game over
                if (Level_1->getGameOver())
                {
                    while (!quit)
                    {
                        //Handle events on queue
                        while (SDL_PollEvent(&e))
                        {
                            //User requests quit
                            if (e.type == SDL_QUIT)
                            {
                                quit = true;
                                break;
                            }
                        }
                        //game over screen
                        Level_1->gameOverLoop();
                    }
                }
            }
        }
        //delete level 1
        delete Level_1;

        //create Level 2
        BGame_Level_1_2* Level_2 = new BGame_Level_1_2;
        Level_2->getGame()->setupBricks(lvl_2_state);
        //pass the previous score
        Level_2->getGame()->setScore(passTheScore);
        //pass lives that were left
        Level_2->getGame()->getBrickLevel_1()->getLevel_1()->setBallLives(passLives);
        //load score media
        Level_2->getGame()->loadScoreAndLivesMedia(Level_2->getGame()->getScore(), Level_2->getGame()->getBrickLevel_1()->getLevel_1()->getBallLives());
        //update level with dropping bricks on every fifth board hit
        bool updateLevel_2 = false;
        if (lvl_2_state)
        {
            while (!quit)
            {
                //Handle events on queue
                while (SDL_PollEvent(&e))
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                        break;
                    }

                    //Handle mouse motion events
                    Level_2->getPlayer()->handleEvent(&e);

                    //Enable music with key 9 (to play/pause) and 0 (to stop)
                    Level_2->getGame()->getSound()->handleMusicEvent(&e);

                    //start game with mouse click
                    if (e.type == SDL_MOUSEBUTTONUP)
                    {
                        Level_2->setGameStart(true);
                    }
                }

                //game start when mouse button is clicked
                if (Level_2->getGameStart())
                {
                    Level_2->mainGameLoop(lvl_3_state);
                }
                //wait for mouse click screen
                else
                {
                    Level_2->standByLoop();
                }

                //Reset hit counter when ball hits board 5 times
                if (Level_2->getGame()->getHitCounter() == 5)
                {
                    updateLevel_2 = true;
                    Level_2->getGame()->updateHitCounter();
                }

                //Update level, move bricks down
                if (updateLevel_2)
                {
                    Level_2->updateLevel();
                    updateLevel_2 = false;
                }

                //Level finished
                if (Level_2->getGame()->getScore() == maxScore_Level_2)
                {
                    lvl_2_state = false;
                    lvl_3_state = true;
                    passTheScore = Level_2->getGame()->getScore();
                    passLives = Level_2->getGame()->getBrickLevel_1()->getLevel_1()->getBallLives();
                    break;
                }

                //if no more lifes, game over
                if (Level_2->getGameOver())
                {
                    while (!quit)
                    {
                        //Handle events on queue
                        while (SDL_PollEvent(&e))
                        {
                            //User requests quit
                            if (e.type == SDL_QUIT)
                            {
                                quit = true;
                                break;
                            }
                        }
                        //game over screen
                        Level_2->gameOverLoop();
                    }
                }
            }
        }
        //delete level 2
        delete Level_2;

        //create Level 3 
        BGame_Level_3* Level_3 = new BGame_Level_3;
        Level_3->getGame()->setScore(passTheScore);
        Level_3->getGame()->getBrickLevel_2()->getLevel_2()->setBallLives(passLives);
        Level_3->getGame()->loadScoreAndLivesMedia(Level_3->getGame()->getScore(), Level_3->getGame()->getBrickLevel_2()->getLevel_2()->getBallLives());
        if (lvl_3_state)
        {
            while (!quit)
            {
                //Handle events on queue
                while (SDL_PollEvent(&e))
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                        break;
                    }

                    //Handle mouse motion events
                    Level_3->getPlayer()->handleEvent(&e);

                    //Enable music with key 9 (to play/pause) and 0 (to stop)
                    Level_3->getGame()->getSound()->handleMusicEvent(&e);

                    //start game with mouse click
                    if (e.type == SDL_MOUSEBUTTONUP)
                    {
                        Level_3->setGameStart(true);
                    }
                }

                //game start when mouse button is clicked
                if (Level_3->getGameStart())
                {
                    Level_3->mainGameLoop(lvl_3_state);
                }
                //wait for mouse click screen
                else
                {
                    Level_3->standByLoop();
                }

                //Level finished
                if (Level_3->getGame()->getScore() >= maxScore_Level_3)
                {
                    lvl_3_state = false;
                    gameWon = true;
                    passTheScore = Level_3->getGame()->getScore();
                    passLives = Level_3->getGame()->getBrickLevel_2()->getLevel_2()->getBallLives();
                    break;
                }

                //if no more lifes, game over
                if (Level_3->getGameOver())
                {
                    while (!quit)
                    {
                        //Handle events on queue
                        while (SDL_PollEvent(&e))
                        {
                            //User requests quit
                            if (e.type == SDL_QUIT)
                            {
                                quit = true;
                                break;
                            }
                        }
                        //game over screen
                        Level_3->gameOverLoop();
                    }
                }
            }
        }

        //Game is won
        if (gameWon)
        {
            while (!quit)
            {
                //Handle events on queue
                while (SDL_PollEvent(&e))
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                        break;
                    }
                }
                //Clear screen
                SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);
                SDL_RenderClear(baseRenderer);

                //Render background texture to screen
                Level_3->getGame()->renderGameWon();
                Level_3->getGame()->getScoreTexture()->renderTexture(Level_3->getGameScorePosition_X(), Level_3->getScoreAndLivesPosition_Y());
                Level_3->getGame()->getLivesTexture()->renderTexture(Level_3->getGameLivesPosition_X(), Level_3->getScoreAndLivesPosition_Y());

                //Update screen
                SDL_RenderPresent(baseRenderer);
            }
        }
        //delete level 3
        delete Level_3;
    }

    //Free resources and close SDL
    closeWindow();
}

void closeWindow()
{
    //Destroy window    
    SDL_DestroyRenderer(baseRenderer);
    SDL_DestroyWindow(baseWindow);
    baseRenderer = NULL;
    baseWindow = NULL;
    //Free global font
    TTF_CloseFont(baseFont);
    baseFont = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}