#include "BBricks.h"

BBricks::BBricks()
{
    Level_1 = new BLevelLayout();

    BrickSoftYellow = new BBrickType * [Level_1->getColumnCount()];
    BrickMediumBlue = new BBrickType * [Level_1->getColumnCount()];
    BrickHardRed = new BBrickType * [Level_1->getColumnCount()];
    for (int i = 0; i < Level_1->getColumnCount(); i++)
    {
        BrickSoftYellow[i] = new BBrickType;
        BrickMediumBlue[i] = new BBrickType;
        BrickHardRed[i] = new BBrickType;
    }

    BrickSoftYellow_Y_FromStart = 100;
    BrickMediumBlue_Y_FromStart = 75;
    BrickHardRed_Y_FromStart = 50;

    //enable desturctor
    callDestructor = true;
}
BBricks::BBricks(bool thirdLevel)
{
    Level_2 = new BLevelLayout(4, 18, 5, 5, "Breakout_Media/retro_arcade_background.png", 3);

    BrickSoftYellow = new BBrickType * [Level_2->getColumnCount()];
    BrickMediumBlue = new BBrickType * [Level_2->getColumnCount()];
    BrickHardRed = new BBrickType * [Level_2->getColumnCount()];
    for (int i = 0; i < Level_2->getColumnCount(); i++)
    {
        BrickSoftYellow[i] = new BBrickType;
        BrickMediumBlue[i] = new BBrickType;
        BrickHardRed[i] = new BBrickType;
    }

    BrickSoftYellow_Y_FromStart = 175;
    BrickSoftYellow_Y_ToEnd = 250;
    BrickMediumBlue_Y_FromStart = 200;
    BrickMediumBlue_Y_ToEnd = 225;
    BrickHardRed_Y_FromStart = 150;
    BrickHardRed_Y_ToEnd = 275;


    //enable desturctor
    callDestructor = false;
}
BBricks::~BBricks()
{
    if (callDestructor)
    {
        for (int i = 0; i < Level_1->getColumnCount(); i++)
        {
            delete BrickSoftYellow[i];
            BrickSoftYellow[i] = NULL;
        }
        delete[] BrickSoftYellow;
        for (int i = 0; i < Level_1->getColumnCount(); i++)
        {
            delete BrickMediumBlue[i];
            BrickMediumBlue[i] = NULL;
        }
        delete[] BrickMediumBlue;
        for (int i = 0; i < Level_1->getColumnCount(); i++)
        {
            delete BrickHardRed[i];
            BrickHardRed[i] = NULL;
        }
        delete[] BrickHardRed;

        //add purple

        delete Level_1;
        Level_1 = NULL;
        delete Level_2;
        Level_2 = NULL;
    }
}

/*
    GETs
*/
BBrickType* BBricks::getSoftYellowBrick(int& element)
{
    return *(BrickSoftYellow + element);
}
BBrickType* BBricks::getMediumBlueBrick(int& element)
{
    return *(BrickMediumBlue + element);
}
BBrickType* BBricks::getHardRedBrick(int& element)
{
    return *(BrickHardRed + element);
}
BLevelLayout* BBricks::getLevel_1()
{
    return Level_1;
}
BLevelLayout* BBricks::getLevel_2()
{
    return Level_2;
}

/*
    SETs
*/
void BBricks::setYellowBrick(bool& secondLevel, bool& thridLevel, const int& columnCount, const int& rowSpacing)
{
    int tempPosition = 0;

    for (int i = 0, j = getBricksWidthStart(); i < columnCount; i++, j += getBrickWidth() + rowSpacing)
    {
        if (!thridLevel && !secondLevel)
        {
            //set bricks texture
            BrickSoftYellow[i]->setBrickTexturePath("Breakout_Media/Yellow_Brick.png");
            //set brick Hit Points
            BrickSoftYellow[i]->setHitPoints(1);
            //set brick break gameScore
            BrickSoftYellow[i]->setBreakScore(10);

            //assign X and Y boarders of each bricks
            //will be used later for ball/bricks collision detection
            for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
            {
                BrickSoftYellow[i]->setBrickBoarderOn_X_Element(p, x);
            }
            for (int y = getGametableHeightStart() + BrickSoftYellow_Y_FromStart, p = 0; y <= getGametableHeightStart() + BrickSoftYellow_Y_FromStart + getBrickHeight(); y += getBrickHeight(), p++)
            {
                BrickSoftYellow[i]->setBrickBoarderOn_Y_Element(p, y);
            }

            BrickSoftYellow[i]->loadYellowBrickMedia(BrickSoftYellow[i]->getBrickTexturePath());
        }
        else if (!thridLevel && secondLevel)
        {
            //set bricks texture
            BrickSoftYellow[i]->setBrickTexturePath("Breakout_Media/Yellow_Brick.png");
            //set brick Hit Points
            BrickSoftYellow[i]->setHitPoints(1);
            //set brick break gameScore
            BrickSoftYellow[i]->setBreakScore(10);

            //assign X and Y boarders of each bricks
            //will be used later for ball/bricks collision detection
            for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
            {
                BrickSoftYellow[i]->setBrickBoarderOn_X_Element(p, x);
            }
            for (int y = getGametableHeightStart() + BrickSoftYellow_Y_FromStart, p = 0; p <2; y += getBrickHeight(), p++)
            {
                if (i < 5 && p == 0)
                    BrickSoftYellow_Y_FromStart += 25;
                else if (i >= 5 && p == 0)
                {
                    BrickSoftYellow_Y_FromStart -= 25;
                }

                BrickSoftYellow[i]->setBrickBoarderOn_Y_Element(p, y);
            }

            BrickSoftYellow[i]->loadYellowBrickMedia(BrickSoftYellow[i]->getBrickTexturePath());
        }
        else if (thridLevel && !secondLevel)
        {
            //set bricks texture
            BrickSoftYellow[i]->setBrickTexturePath("Breakout_Media/Purple_Brick.png");
            //set brick Hit Points
            BrickSoftYellow[i]->setHitPoints(10000);
            //set brick break gameScore
            BrickSoftYellow[i]->setBreakScore(0);

            if (i < 9)
            {
                if (i == 0)
                {
                    j += getBrickWidth() + rowSpacing;
                }
                for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
                {
                    BrickSoftYellow[i]->setBrickBoarderOn_X_Element(p, x);
                }

                for (int y = getGametableHeightStart() + BrickSoftYellow_Y_FromStart, p = 0; p < 2; y += getBrickHeight(), p++)
                {
                    if (i < 4 && p == 0)
                        BrickSoftYellow_Y_FromStart -= 25;
                    else if (i >= 4 && p == 0)
                    {
                        BrickSoftYellow_Y_FromStart += 25;
                    }
                    tempPosition = BrickSoftYellow_Y_FromStart;

                    BrickSoftYellow[i]->setBrickBoarderOn_Y_Element(p, y);
                }

            }
            else
            {

                if (i == 9)
                {
                    j = getBricksWidthStart() + getBrickWidth() + rowSpacing;
                }
                for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
                {
                    BrickSoftYellow[i]->setBrickBoarderOn_X_Element(p, x);
                }
                for (int y = getGametableHeightStart() + BrickSoftYellow_Y_ToEnd, p = 0; p < 2; y += getBrickHeight(), p++)
                {
                    if (i < 13 && p == 0)
                        BrickSoftYellow_Y_ToEnd += 25;
                    else if (i >= 13 && p == 0)
                    {
                        BrickSoftYellow_Y_ToEnd -= 25;
                    }
                    BrickSoftYellow[i]->setBrickBoarderOn_Y_Element(p, y);
                }
            }
            BrickSoftYellow[i]->loadYellowBrickMedia(BrickSoftYellow[i]->getBrickTexturePath());
        }


    }
}
void BBricks::setBlueBrick(bool& secondLevel, bool& thridLevel, const int& columnCount, const int& rowSpacing)
{

    for (int i = 0, j = getBricksWidthStart(); i < columnCount; i++, j += getBrickWidth() + rowSpacing)
    {
        //set bricks texture
        BrickMediumBlue[i]->setBrickTexturePath("Breakout_Media/Blue_Brick.png");
        //set brick Hit Points
        BrickMediumBlue[i]->setHitPoints(2);
        //set brick break gameScore
        BrickMediumBlue[i]->setBreakScore(30);

        //assign X and Y boarders of each bricks
        //will be used later for ball/bricks collision detection
        if (!thridLevel && !secondLevel)
        {
            for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
            {
                BrickMediumBlue[i]->setBrickBoarderOn_X_Element(p, x);
            }
            for (int y = getGametableHeightStart() + BrickMediumBlue_Y_FromStart, p = 0; y <= getGametableHeightStart() + BrickMediumBlue_Y_FromStart + getBrickHeight(); y += getBrickHeight(), p++)
            {
                BrickMediumBlue[i]->setBrickBoarderOn_Y_Element(p, y);
            }
        }
        else if (!thridLevel && secondLevel)
        {
            for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
            {
                BrickMediumBlue[i]->setBrickBoarderOn_X_Element(p, x);
            }
            for (int y = getGametableHeightStart() + BrickMediumBlue_Y_FromStart, p = 0; p <2; y += getBrickHeight(), p++)
            {
                if (i < 5 && p == 0)
                    BrickMediumBlue_Y_FromStart += 25;
                else if (i >= 5 && p == 0)
                {
                    BrickMediumBlue_Y_FromStart -= 25;
                }

                BrickMediumBlue[i]->setBrickBoarderOn_Y_Element(p, y);
            }
        }
        else if (thridLevel && !secondLevel)
        {

            if (i < 9)
            {
                if (i == 0)
                {
                    j += getBrickWidth() + rowSpacing;
                }
                for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
                {
                    BrickMediumBlue[i]->setBrickBoarderOn_X_Element(p, x);
                }

                for (int y = getGametableHeightStart() + BrickMediumBlue_Y_FromStart, p = 0; p < 2; y += getBrickHeight(), p++)
                {
                    if (i < 4 && p == 0)
                        BrickMediumBlue_Y_FromStart -= 25;
                    else if (i >= 4 && p == 0)
                    {
                        BrickMediumBlue_Y_FromStart += 25;
                    }
                    BrickMediumBlue[i]->setBrickBoarderOn_Y_Element(p, y);

                }
            }
            else
            {

                if (i == 9)
                {
                    j = getBricksWidthStart() + getBrickWidth() + rowSpacing;
                }
                for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
                {
                    BrickMediumBlue[i]->setBrickBoarderOn_X_Element(p, x);
                }
                for (int y = getGametableHeightStart() + BrickMediumBlue_Y_ToEnd, p = 0; p < 2; y += getBrickHeight(), p++)
                {
                    if (i < 13 && p == 0)
                        BrickMediumBlue_Y_ToEnd += 25;
                    else if (i >= 13 && p == 0)
                    {
                        BrickMediumBlue_Y_ToEnd -= 25;
                    }
                    BrickMediumBlue[i]->setBrickBoarderOn_Y_Element(p, y);
                }
            }
        }

        BrickMediumBlue[i]->loadBlueBrickMedia(BrickMediumBlue[i]->getBrickTexturePath());
    }
}
void BBricks::setRedBrick(bool& secondLevel, bool& thridLevel, const int& columnCount, const int& rowSpacing)
{
    //
    for (int i = 0, j = getBricksWidthStart(); i < columnCount; i++, j += getBrickWidth() + rowSpacing)
    {
        //set bricks texture
        BrickHardRed[i]->setBrickTexturePath("Breakout_Media/Red_Brick.png");
        //set brick Hit Points
        BrickHardRed[i]->setHitPoints(3);
        //set brick break gameScore
        BrickHardRed[i]->setBreakScore(50);

        //assign X and Y boarders of each bricks
        //will be used later for ball/bricks collision detection
        if (!thridLevel && !secondLevel)
        {
            for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
            {
                BrickHardRed[i]->setBrickBoarderOn_X_Element(p, x);
            }
            for (int y = getGametableHeightStart() + BrickHardRed_Y_FromStart, p = 0; y <= getGametableHeightStart() + BrickHardRed_Y_FromStart + getBrickHeight(); y += getBrickHeight(), p++)
            {
                BrickHardRed[i]->setBrickBoarderOn_Y_Element(p, y);
            }
        }
        else if (!thridLevel && secondLevel)
        {
            for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
            {
                BrickHardRed[i]->setBrickBoarderOn_X_Element(p, x);
            }
            for (int y = getGametableHeightStart() + BrickHardRed_Y_FromStart, p = 0; p < 2; y += getBrickHeight(), p++)
            {
                if (i < 5 && p == 0)
                    BrickHardRed_Y_FromStart += 25;
                else if (i >= 5 && p == 0)
                {
                    BrickHardRed_Y_FromStart -= 25;
                }

                BrickHardRed[i]->setBrickBoarderOn_Y_Element(p, y);
            }
        }
        else if (thridLevel && !secondLevel)
        {

            if (i < 9)
            {
                if (i == 0)
                {
                    j += getBrickWidth() + rowSpacing;
                }
                for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
                {
                    BrickHardRed[i]->setBrickBoarderOn_X_Element(p, x);
                }

                for (int y = getGametableHeightStart() + BrickHardRed_Y_FromStart, p = 0; p < 2; y += getBrickHeight(), p++)
                {
                    if (i < 4 && p == 0)
                        BrickHardRed_Y_FromStart -= 25;
                    else if (i >= 4 && p == 0)
                    {
                        BrickHardRed_Y_FromStart += 25;
                    }
                    BrickHardRed[i]->setBrickBoarderOn_Y_Element(p, y);

                }
            }
            else
            {

                if (i == 9)
                {
                    j = getBricksWidthStart() + getBrickWidth() + rowSpacing;
                }
                for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
                {
                    BrickHardRed[i]->setBrickBoarderOn_X_Element(p, x);
                }
                for (int y = getGametableHeightStart() + BrickHardRed_Y_ToEnd, p = 0; p < 2; y += getBrickHeight(), p++)
                {
                    if (i < 13 && p == 0)
                        BrickHardRed_Y_ToEnd += 25;
                    else if (i >= 13 && p == 0)
                    {
                        BrickHardRed_Y_ToEnd -= 25;
                    }
                    BrickHardRed[i]->setBrickBoarderOn_Y_Element(p, y);
                }
            }
        }

        BrickHardRed[i]->loadRedBrickMedia(BrickHardRed[i]->getBrickTexturePath());
    }
}